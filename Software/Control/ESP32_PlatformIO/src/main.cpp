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

#include "webserver.h"

#include "si534x.h"
#include "pcm1792.h"

//==============================================================================
//  Defines
//==============================================================================
#define CMP_NAME                "Main"

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
// Function pointers for the pseudo-modules. Each module gets a separate task,
// in which 1) It's Init function is executed; 2) If init is OK, the Loop
// function is called  periodically until it returns != OK, after which, the
// task is deleted. Loop can also not return at all, but in this case, it needs
// to call delay/yield on it's own
typedef eStatus (*ModuleInitFn)(void * params);
typedef eStatus (*ModuleLoopFn)();

typedef struct _Module
{
    const char *    Name;
    ModuleInitFn    Init;
    ModuleLoopFn    Loop;
    uint32_t        Period;
    void *          Params;
    uint32_t        StackSize;
    uint8_t         Priority;   // Priority, with 3 (configMAX_PRIORITIES - 1)
                                // being the highest, and 0 being the lowest.
} Module;


//==============================================================================
//  Local function definitions
//==============================================================================
static eStatus blinkLoop();
static eStatus si534xLoop();


//==============================================================================
//  Local data
//==============================================================================
const Module Modules[] = {
    { "Logger",     LogInit,        LogLoop,    LOG_TASK_PERIOD,    NULL,   4096,   2 },
    { "Blink",      NULL,           blinkLoop,  0,                  NULL,   4096,   1 },
    { "Webserver",  WebserverInit,  NULL,       5,                  NULL,   4096,   1 },
    { "Si534x",     Si534xInit,     si534xLoop, 0,                  NULL,   4096,   1 },
    { "Pcm1792",    Pcm1792Init,    Pcm1792CheckDevice,   5000,     NULL,   4096,   1 }
};


//==============================================================================
//  Local functions
//==============================================================================
static eStatus blinkLoop()
{
    digitalWrite(DO_LED_1, HIGH);
    vTaskDelay(500/portTICK_PERIOD_MS);
    digitalWrite(DO_LED_1, LOW);
    vTaskDelay(500/portTICK_PERIOD_MS);

    //Log(eLogWarn, CMP_NAME, "Still alive!");

    return eOK;
}

static eStatus si534xLoop()
{
    const char * configList[10];
    uint8_t configCount;
    eStatus retVal = Si534xListConfigs(10, &configCount, configList);
    Log(eLogInfo, CMP_NAME, "Si534xListConfigs returned: %d, got %d configs", retVal, configCount);
    for (int i = 0; i < configCount; i++)
    {
        Log(eLogInfo, CMP_NAME, "config ID: %d, name: %s", i, configList[i]);
    }

    Si534xDumpStatus();
    retVal = Si534xSetConfig(1);

    Si534xDumpStatus();

    return eDONE;
}

static void setupHardware()
{
    // Hold all devices in reset
    INIT_DO_LOW(DO_nRST_FPGA);
    INIT_DO_HIGH(DO_nRST_DACR);
    INIT_DO_HIGH(DO_nRST_DACL);
    INIT_DO_HIGH(DO_nRST_CLK);

    // LED1 and LED2 off
    INIT_DO_HIGH(DO_LED_1);
    INIT_DO_HIGH(DO_LED_2);
}

static void moduleHost(void * param)
{
    eStatus retVal = eOK;
    const Module * const module = (const Module * const)param;

    if (NULL != module->Init)
    {
        retVal = module->Init(module->Params);
    }

    if (NULL != module->Loop)
    {
        while (eOK == retVal)
        {
            retVal = module->Loop();
            if (0 != module->Period)
            {
                vTaskDelay(module->Period / portTICK_PERIOD_MS);
            }
        }
    }
    // FreeRTOS will reclaim resources
    vTaskDelete(NULL);
}

static eStatus startModules()
{
    eStatus retVal = eOK;
    TaskHandle_t    taskHandle;

    for (int i = 0; i < ARRAY_SIZE(Modules); i++)
    {
        xTaskCreate(moduleHost,
                Modules[i].Name,
                Modules[i].StackSize,   // Stack size
                (void*)&Modules[i],
                Modules[i].Priority,
                &taskHandle);
        if (taskHandle == NULL)
        {
            Log(eLogCrit, CMP_NAME, "startModules: Error creating task for %s", Modules[i].Name);
            // Logger may not be working at that time!
            Serial.begin(115200);
            Serial.print("startModules: Error creating task for");
            Serial.println(Modules[i].Name);

            retVal = eFAIL;
        }
    }
    return retVal;
}

//==============================================================================
//  Exported functions
//==============================================================================

void setup()
{
    eStatus retVal = eOK;

    setupHardware();

    LogSetMinLevel(eLogInfo);

    retVal = startModules();

    //retVal = Pcm1792CheckDevice();
    //if (eOK == retVal)
    //{
    //    retVal = Pcm1792Init();
    //}

    //retVal = DewilleWebserverSetup();

}

// All tasks already started during setup()
void loop()
{

}



