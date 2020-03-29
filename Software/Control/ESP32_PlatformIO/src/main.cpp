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
#include <Arduino.h>

#include "logger.h"

#include <WString.h>
#include <pgmspace.h>

#include "si534x.h"

//==============================================================================
//  Defines
//==============================================================================


#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE    0
#else
#define ARDUINO_RUNNING_CORE    1
#endif

#define   INIT_DO_HIGH(x)       { pinMode((x), OUTPUT); digitalWrite((x), HIGH); }
#define   INIT_DO_LOW(x)        { pinMode((x), OUTPUT); digitalWrite((x), LOW); }


//==============================================================================
//  Local types
//==============================================================================

//==============================================================================
//  Local data
//==============================================================================

//==============================================================================
//  Local function definitions
//==============================================================================
static void TaskBlink( void *pvParameters );

//==============================================================================
//  Local functions
//==============================================================================

static void setupHardware()
{
    // Hold all devices in reset
    INIT_DO_LOW(DO_nRST_FPGA);
    INIT_DO_LOW(DO_nRST_DACR);
    INIT_DO_LOW(DO_nRST_DACL);
    INIT_DO_HIGH(DO_nRST_CLK);

    // LED1 and LED2 off
    INIT_DO_HIGH(DO_LED_1);
    INIT_DO_HIGH(DO_LED_2);
}

static void setupTasks()
{
    xTaskCreatePinnedToCore(
        TaskBlink
        ,  "TaskBlink"  // A name just for humans
        ,  4096          // Stack size - resets after some time with 1024, apparently an overflow
        ,  NULL
        ,  1            // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
        ,  NULL 
        ,  ARDUINO_RUNNING_CORE);

}

//==============================================================================
//  Exported functions
//==============================================================================

void setup() 
{
    // put your setup code here, to run once:
    setupHardware();

    setupTasks();

    LogStart();
    LogSetMinLevel(eLogDebug);

    Si534xInit();

}

void loop() 
{
    // put your main code here, to run repeatedly:
    //Si534xReadId();


}

void TaskBlink(void *pvParameters)
{
    (void) pvParameters;
    for (;;) // A Task shall never return or exit.
    {
        Log(eLogDebug, "TaskBlink", "Turning LED ON");
        digitalWrite(DO_LED_1, HIGH);
        vTaskDelay(500);
        Log(eLogDebug, "TaskBlink", "Turning LED OFF");
        digitalWrite(DO_LED_1, LOW);
        vTaskDelay(500);
    }
}