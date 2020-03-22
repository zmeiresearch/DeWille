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

//==============================================================================
//  Defines
//==============================================================================
#define CMP_NAME            "Logger"
#define SEND_SLEEP_TIME     (uint32_t)5     // time to sleep between write attempts
#define LOG_MAX_WAIT        (uint32_t)100   // max time to wait for synchronization

//==============================================================================
//  Local types
//==============================================================================


//==============================================================================
//  Local data
//==============================================================================
static eLogLevel currentLevel = eLogInfo;
static uint8_t logBuffer[LOG_BUFFER_SIZE] = { 0 };
static size_t readPtr = 0;
static size_t writePtr = 0;

//==============================================================================
//  Local functions
//==============================================================================
size_t getFree() 
{
    return (LOG_BUFFER_SIZE - writePtr);
}

void writeTask(void * params)
{
    while(1)
    {
        // Anyting to send?
        if (readPtr < writePtr)
        {
            // is some space available?
            size_t toSend = LogPortGetWriteSize();
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
                
                    size_t sent = LogPortWrite(&logBuffer[readPtr], toSend);
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

        LogPortSleep(SEND_SLEEP_TIME);
    }
}

//==============================================================================
//  Exported functions
//==============================================================================
eStatus Log(eLogLevel level, const char * const component, ...)
{
    eStatus retVal = eOK;

    if (LogPortInISR())
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
                i = snprintf((char *)&logBuffer[writePtr], getFree(), "%08d|%s|", LogPortGetTime(), component);

                if (i < 0)
                {
                    retVal = eFAIL;
                } 
                else 
                {
                    // if that went well, append the actual message as well
                    va_list args;
                    va_start(args, component);
                    const char * fmt = va_arg(args, char *);
                    
                    int i = vsnprintf((char *)&logBuffer[writePtr], getFree(), fmt, args);
                    va_end(args);
                    LogPortUnlock();
                
                    if (i < 0) 
                    {
                        retVal = eFAIL;
                    } 
                    else
                    {
                        // add a newline
                        i = snprintf((char *)&logBuffer[writePtr], getFree(), "\n");
                        if (i < 0)
                        {
                            retVal = eFAIL;
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

eStatus LogSetMinLevel(eLogLevel level)
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

eStatus LogStart()
{
    eStatus retVal = eOK;

    currentLevel = eLogWarn;    // default log level
    
    readPtr = writePtr = 0;
    
    retVal = LogPortInit(writeTask);

    return retVal;
}
