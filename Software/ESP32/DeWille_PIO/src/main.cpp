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

#include <WString.h>
#include <pgmspace.h>

#include <HardwareSerial.h>

#include <SPI.h>

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


// LEDs
// conflict with Tx/Rx USB?
#define   DO_LED_1              2
#define   DO_LED_2              0

// Digital Configuration Inputs 
#define   DI_CFG_1              39
#define   DI_CFG_2              36

// Peripheral control
#define   DO_nRST_CLK           14
#define   DO_nRST_DACR          26
#define   DO_nRST_DACL          33
#define   DO_nRST_FPGA          21

#define   DO_nFPGA_INIT         5
#define   DO_nFPGA_PROGRAM      22
#define   DI_FPGA_DONE          1

// SPI
#define   DO_nCS_CLK            27
#define   DO_nCS_DACR           25
#define   DO_nCS_DACL           32
#define   DO_nCS_FPGA           3

#define   SPI_MISO              19 
#define   SPI_MOSI              23
#define   SPI_SCLK              18
#define   SPI_DUMMY_CS          12

// FT2232 serial interface
#define   DebugSerial           (&(Serial2))
#define   DEBUG_SERIAL_RX       16
#define   DEBUG_SERIAL_TX       17
#define   DEBUG_SERIAL_BAUD     115200



//==============================================================================
//  Local types
//==============================================================================
typedef enum _tSpiDev 
{
    eSpiDevFPGA,
    eSpiDevDACR,
    eSpiDevDACL,
    eSpiDevCLK,
    eSpiDevNum,
} tSpiDev;

//==============================================================================
//  Local data
//==============================================================================
static SPIClass * spi = NULL;

//==============================================================================
//  Local function definitions
//==============================================================================
// define two tasks for Blink & AnalogRead
static void TaskBlink( void *pvParameters );

//==============================================================================
//  Local functions
//==============================================================================
static uint8_t spiTransferByte(const tSpiDev dev, const uint8_t tx)
{
    return 0;
}

static void setupHardware()
{
    DebugSerial->begin(DEBUG_SERIAL_BAUD, SERIAL_8N1, DEBUG_SERIAL_RX, DEBUG_SERIAL_TX);

    // SPI
    spi = new SPIClass(VSPI);
    spi->begin(SPI_SCLK, SPI_MISO, SPI_MOSI, SPI_DUMMY_CS); //SCLK, MISO, MOSI, SS
  
    INIT_DO_HIGH(DO_nCS_FPGA);
    INIT_DO_HIGH(DO_nCS_DACR);
    INIT_DO_HIGH(DO_nCS_DACL);
    INIT_DO_HIGH(DO_nCS_CLK);

    // Hold all devices in reset
    INIT_DO_LOW(DO_nRST_FPGA);
    INIT_DO_LOW(DO_nRST_DACR);
    INIT_DO_LOW(DO_nRST_DACL);
    INIT_DO_LOW(DO_nRST_CLK);

    // LED1 and LED2 off
    INIT_DO_HIGH(DO_LED_1);
    INIT_DO_HIGH(DO_LED_2);
}

//==============================================================================
//  Exported functions
//==============================================================================

void setup() 
{
  // put your setup code here, to run once:
    setupHardware();
  
    xTaskCreatePinnedToCore(
        TaskBlink
        ,  "TaskBlink"  // A name just for humans
        ,  1024         // Stack size
        ,  NULL
        ,  1            // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
        ,  NULL 
        ,  ARDUINO_RUNNING_CORE);
}

void loop() 
{
  // put your main code here, to run repeatedly:

}

void TaskBlink(void *pvParameters)
{
    (void) pvParameters;
    for (;;) // A Task shall never return or exit.
    {
        digitalWrite(DO_LED_1, HIGH);
        vTaskDelay(500); 
        digitalWrite(DO_LED_1, LOW);
        vTaskDelay(500);
    }
}
