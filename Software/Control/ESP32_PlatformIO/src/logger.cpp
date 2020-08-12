/*==============================================================================
   DeWille ESP32 firmware

   Copyright 2020 Ivan Vasilev, Zmei Research Ltd.

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
  ============================================================================*/

//==============================================================================
//  Includes
//==============================================================================
#include <stdio.h>

#include "logger.h"
#include "logger_port.h"
#include "log_sink_serial.h"
#include "log_sink_websocket.h"

//==============================================================================
//  Defines
//==============================================================================
#define CMP_NAME            "Logger"
#define LOG_MAX_WAIT        (uint32_t)100   // max time to wait for synchronization

//==============================================================================
//  Local types
//==============================================================================


//==============================================================================
//  Local data
//==============================================================================
static eLogLevel    currentLevel = eLogInfo;
static uint8_t      logBuffer[LOG_BUFFER_SIZE] = { 0 };
static size_t       readPtr = 0;
static size_t       writePtr = 0;
static bool         initialized = false;

// Log sinks
static const LogSink sinks[] = {
    { "Serial", LogSinkSerialInit, LogSinkSerialGetWriteSize, LogSinkSerialWrite },
    { "Websocket", LogSinkWebsocketInit, LogSinkWebsocketGetWriteSize, LogSinkWebsocketWrite }
};

//==============================================================================
//  Local functions
//==============================================================================
static size_t getFree() 
{
    return (LOG_BUFFER_SIZE - writePtr);
}

static size_t getSinksSmallestWriteSize()
{
    size_t writeSize = 0xffffffff;
    for (int i = 0; i < ARRAY_SIZE(sinks); i++)
    {
        int tmp = sinks[i].GetWriteSize();
        if (tmp < writeSize) 
        {
            writeSize = tmp;
        }
    }
    return writeSize;
}

static size_t sinksWrite(const uint8_t * const buffer, const size_t toSend)
{
    size_t written = toSend;
    
    for (int i = 0; i < ARRAY_SIZE(sinks); i++)
    {
        int tmp = sinks[i].Write(buffer, toSend);
        if (tmp != written) 
        {
            Log(eLogWarn, CMP_NAME, "Failure writing to sink %s: tried to write: %d, written: %d", 
                    sinks[i].Name, toSend, tmp);
        }
    }
    return written;
}


static const char getLevelChar(const eLogLevel level)
{
    const char chars[eLogLevelCount+1] = {
        'D',    // []ebug
        'I',    // []nfo
        'W',    // []arning
        'E',    // []rror
        'C',    // []itical
        'X'     // Unknown
    };

    if ((level >= 0) && (level < eLogLevelCount))
    {
        return chars[level];
    }
    else 
    {
        Log(eLogWarn, CMP_NAME, "getLevelsChar: Unknown level: %d", level);
        return chars[eLogLevelCount];
    }
}

//==============================================================================
//  Exported functions
//==============================================================================
eStatus Log(const eLogLevel level, const char * const component, ...)
{
    eStatus retVal = eOK;

    if (!initialized) 
    {
        retVal = eNOTINITIALIZED;
    } 
    else if (LogPortInISR())
    {
        // not a good idea to call prinf and friends inside an ISR
        retVal = eUNSUPPORTED;
    }
    else if (level >= eLogLevelCount)
    {
        retVal = eINVALIDARG;
    }

    if (eOK == retVal)
    {
        if (level >= currentLevel)
        {
            int i;

            if (LogPortLock(LOG_MAX_WAIT))
            {
                // first print the time
                i = snprintf((char *)&logBuffer[writePtr], getFree(),
                        "%08d|%c|%s|", PortGetTime(), getLevelChar(level), component);

                if (i < 0)
                {
                    retVal = eFAIL;
                } 
                else 
                {
                    writePtr += i;
                    // if that went well, append the actual message as well
                    va_list args;
                    va_start(args, component);
                    const char * fmt = va_arg(args, char *);
                    
                    int i = vsnprintf((char *)&logBuffer[writePtr], getFree(), fmt, args);
                    va_end(args);
                
                    if (i < 0) 
                    {
                        retVal = eFAIL;
                    } 
                    else
                    {
                        writePtr += i;
                        // add a newline
                        i = snprintf((char *)&logBuffer[writePtr], getFree(), "\r\n");
                        if (i < 0)
                        {
                            retVal = eFAIL;
                        }
                        else
                        {
                            writePtr += i;
                        }
                    }
                }
                
                LogPortUnlock();
            }
            else
            {
                retVal = eBUSY;
            }
        }
    }

    return retVal;
}

eStatus LogSetMinLevel(const eLogLevel level)
{
    eStatus retVal = eINVALIDARG;

    if (level < eLogLevelCount)
    {
        currentLevel = level;
        retVal = eOK;
    }
    else 
    {
        Log(eLogWarn, CMP_NAME, "Invalid log level: %d", level);
    }
    
    return retVal;
}

eStatus LogInit(void * params)
{
    eStatus retVal = eOK;
    bool oneSinkOk = false;

    (void)params;

    currentLevel = LOG_LEVEL_DEFAULT;   // default log level
    
    readPtr = writePtr = 0;
    
    retVal = LogPortInit();

    if (eOK == retVal)
    {
        for (int i = 0; i < ARRAY_SIZE(sinks); i++)
        {
            retVal = sinks[i].Init();
            if (eOK == retVal)
            {
                oneSinkOk = true;
            }
            else
            {
                Log(eLogWarn, CMP_NAME, "Error initializing %s sink", sinks[i].Name);
            }
        }

        retVal = (oneSinkOk) ? eOK : eFAIL;
    }

    initialized = true;

    return retVal;
}

eStatus LogLoop()
{
    // Anyting to send?
    if (readPtr < writePtr)
    {
        // is some space available?
        size_t toSend = getSinksSmallestWriteSize();
        if (toSend > 0)
        {
            if (LogPortLock(LOG_MAX_WAIT))
            {
                // Lock aquired

                if ((writePtr - readPtr) < toSend)
                {
                    // queue as much as possible for the writer to accept
                    toSend = writePtr - readPtr;
                }

                size_t sent = sinksWrite(&logBuffer[readPtr], toSend);
                readPtr += sent;

                if (readPtr == writePtr)
                {
                    // Everything sent? - rewind pointers to the start
                    readPtr = writePtr = 0;
                }

                LogPortUnlock();
            }
        }
    }
    return eOK; // Always running
}

