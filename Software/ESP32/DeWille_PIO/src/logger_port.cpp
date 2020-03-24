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
#include "globals.h"
#include "logger_port.h"

#include "driver/uart.h"    // for UART_PIN_NO_CHANGE

#include "HardwareSerial.h"

//==============================================================================
//  Defines
//==============================================================================


//==============================================================================
//  Local types
//==============================================================================

//==============================================================================
//  Local data
//==============================================================================
SemaphoreHandle_t   LogSemaphore;
HardwareSerial      serial(LOG_SERIAL_PORT);

//==============================================================================
//  Local functions
//==============================================================================


//==============================================================================
//  Exported functions
//==============================================================================

bool LogPortLock(size_t waitTime)
{
    return ((xSemaphoreTake(LogSemaphore, waitTime / portTICK_PERIOD_MS) == pdTRUE) ? true : false);
}

void LogPortUnlock()
{
    xSemaphoreGive(LogSemaphore);
}


size_t LogPortGetWriteSize()
{
    return serial.availableForWrite();
}

size_t LogPortWrite(const uint8_t * const buffer, const size_t toSend)
{
    return serial.write(buffer, toSend);
}

eStatus LogPortInit(void (*task)(void*) )
{
    eStatus retVal = eOK;

    LogSemaphore = xSemaphoreCreateMutex();

    if (NULL == LogSemaphore)
    {
        retVal = eFAIL;
    }

    if (eOK == retVal)
    {
        TaskHandle_t    taskHandle;
        xTaskCreate((*task), "Log Task", 
                2048,   // Stack size
                NULL,   // no params
                configMAX_PRIORITIES - 1,
                &taskHandle);

        if (NULL == taskHandle)
        {
            retVal = eFAIL;
        }
    }

    if (eOK == retVal)
    {
        // init serial port. Nothing should go wrong here
        serial.begin(LOG_SERIAL_BAUD, SERIAL_8N1, LOG_SERIAL_RX_PIN, LOG_SERIAL_TX_PIN); 
    }

    return retVal;
}


