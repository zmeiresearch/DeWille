/*==============================================================================
   DeWille ESP32 firmware

   A simple SPI bus arbiter. Deliberately uses Arduino SPI/GPIO rather the
   more feature-rich esp-idf one to allow easier switch to a different module if
   required later on.

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
#include <SPI.h>

#include "globals.h"
#include "logger.h"

#include "spi_mux.h"

//==============================================================================
//  Defines
//==============================================================================#
#define     INIT_DO_HIGH(x)         { pinMode((x), OUTPUT); digitalWrite((x), HIGH); }
#define     INIT_DO_LOW(x)          { pinMode((x), OUTPUT); digitalWrite((x), LOW); }

#define     SPI_MAX_BLOCK_TIME      (uint32_t)250   // max time to wait for the SPI
                                                    // bus to become available

//==============================================================================
//  Local data
//==============================================================================#
static const char * CMP = "SPI";

static SPIClass *spi = NULL;
static bool initialized = false;
static SemaphoreHandle_t   spiSemaphore = NULL;

static const uint8_t csPins[eSpiDevNum] = { 
    DO_nCS_CLK, 
    DO_nCS_DACR, 
    DO_nCS_DACL, 
    DO_nCS_DUMMY }; // TODO

//==============================================================================
//  Local functions
//==============================================================================#

//==============================================================================
//  Exported functions
//==============================================================================#
eStatus SpiTransfer(eSpiDevice device, uint8_t * buffer, const uint8_t size)
{
    eStatus retVal = eOK;

    if ((device >= eSpiDevNum) || (size == 0) || (buffer == NULL))
    {
        retVal = eINVALIDARG;
    }
    else if (!initialized)
    {
        retVal = eNOTINITIALIZED;
    }
    else
    {   
        if (xSemaphoreTake(spiSemaphore, SPI_MAX_BLOCK_TIME / portTICK_PERIOD_MS))
        {
            INIT_DO_LOW(csPins[device]);
            spi->beginTransaction(SPISettings(SPI_CLK_FREQ, MSBFIRST, SPI_MODE0));
            for (int i = 0; i < size; i++)
            {
                uint8_t tmp = spi->transfer(*buffer);
                *buffer++ = tmp;
            }
            spi->endTransaction();
            INIT_DO_HIGH(csPins[device]);
            xSemaphoreGive(spiSemaphore);
        }
        else
        {
            retVal = eBUSY;
        }
    }

    if (eOK != retVal) Log(eLogWarn, CMP, "SpiTransfer returned %d", retVal);

    return retVal;
}

eStatus SpiInit()
{
    eStatus retVal = eOK;

    spiSemaphore = xSemaphoreCreateMutex();

    if (NULL == spiSemaphore)
    {
        Log(eLogCrit, CMP, "SPI Initialization failed!");
        retVal = eFAIL;
    } 
    else 
    {
        INIT_DO_HIGH(DO_nCS_CLK);
        INIT_DO_HIGH(DO_nCS_DACR);
        INIT_DO_HIGH(DO_nCS_DACL);

        //pinMode(SPI_MOSI, INPUT);

        spi = new SPIClass(VSPI);
        spi->begin(SPI_SCLK, SPI_MISO, SPI_MOSI, DO_nCS_DUMMY);

        initialized = true;
        Log(eLogDebug, CMP, "SPI Initialized");
    }

    return retVal;
}


