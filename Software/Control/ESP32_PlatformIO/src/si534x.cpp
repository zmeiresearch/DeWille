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
#include <stdlib.h>

#include "si534x.h"
#include "si534x_regs.h"

#include "../../Si5344_ClockBuilder/Si5344_RevD_DeWille01.h" 

#include "logger.h"

#include "spi.h"

//==============================================================================
//  Defines
//==============================================================================
#define CMP_NAME                "SI534x"
#define ALWAYS_SET_PAGE         false

// Si5342/44/45 commands - pg. 53 Si5345-44-42-D-RM.pdf
#define CMD_SET_ADDRESS         (uint8_t)0x0    // 000x xxxx
#define CMD_WRITE_DATA          (uint8_t)0x40   // 010x xxxx
#define CMD_READ_DATA           (uint8_t)0x80   // 100x xxxx
#define CMD_WRITE_INCREMENT     (uint8_t)0x60   // 011x xxxx
#define CMD_READ_INCREMENT      (uint8_t)0xa0   // 101x xxxx
#define CMD_WRITE_BURST         (uint8_t)0xe0   // 1110 0000

#define DATA_DUMMY              (uint8_t)0xA5
#define DEVICE_READY            (uint8_t)0xF0   // RM pg.182

//==============================================================================
//  Local types
//==============================================================================

//==============================================================================
//  Local data
//==============================================================================

static eSi534xType clkType = eSiTypeUnknown;
static bool initialized = false;
static uint8_t currentPage = 0xDE;

//static uint8_t buffer[32];      // adjust accordingly

//==============================================================================
//  Local functions
//==============================================================================

static bool isReady()
{
    bool retVal = false;
    
    // DEVICE_READY is accessible on every page
    uint8_t tmp[2] = { CMD_SET_ADDRESS, Reg_DeviceReady.address };
    SpiTransfer(eSpiDevCLK, &tmp[0], 2);
    
    tmp[0] = CMD_READ_DATA;
    tmp[1] = DATA_DUMMY;

    if (tmp[1] == DEVICE_READY)
    {
        retVal = true;
    }

    Log(eLogDebug, CMP_NAME, "isReady: %d", retVal);

    return retVal;
}

static eStatus setPage(uint8_t page)
{
    eStatus retVal = eOK;
    // Valid pages are 0-5 and 9, Si5345-44-42-D-RM pg. 81
    // However, there are also pg. A and pg. B - the same
    // Ref manual, pg. 122 and 123
    if (((0 <= page) && (page <= 5)) ||
        ((9 <= page) && (page <= 0xb)))
    {
        if ((page != currentPage) || ALWAYS_SET_PAGE)
        {
            // the page-setting address is accessible from every page
            uint8_t tmp[2];
            tmp[0] = CMD_SET_ADDRESS;
            tmp[1] = Reg_Page.address; 
            SpiTransfer(eSpiDevCLK, &tmp[0], 2);

            tmp[0] = CMD_WRITE_DATA;
            tmp[1] = page;
            SpiTransfer(eSpiDevCLK, &tmp[0], 2);
            currentPage = page;
            Log(eLogDebug, CMP_NAME, "setPage: %d", page);
        }
    }
    else
    {
        Log(eLogWarn, CMP_NAME, "setPage: Tried setting invalid page %d", page);
        retVal = eINVALIDARG;
    }

    return retVal;
}

static eStatus readReg(const tSiReg& reg, uint8_t * buf, uint8_t bufferSize)
{
    eStatus retVal = eOK;
    uint8_t tmp[2];

    if ((NULL == buf) || (0 == bufferSize))
    {
        retVal = eINVALIDARG;
    }
    else if (bufferSize < reg.len)
    {
        retVal = eFAIL; 
    }
    else
    {
        // Switch to  the correct page
        retVal = setPage(reg.page);
        if (eOK == retVal)
        {
            // Set address to start reading from
            tmp[0] = CMD_SET_ADDRESS;
            tmp[1] = reg.address;
            SpiTransfer(eSpiDevCLK, &tmp[0], 2);

            // Then read as many bytes as required
            for (int i = 0; i < reg.len; i++)
            {
                // needs to be set on each iteration as SpiTransfer overwrites the buffer
                tmp[0] = CMD_READ_INCREMENT;
                tmp[1] = DATA_DUMMY;
                SpiTransfer(eSpiDevCLK, &tmp[0], 2);
                buf[i] = tmp[1];
            }

            // everything below is for debug purposes
            char * printBuf = (char *)malloc(reg.len * 5);    // 0xXX,0xYY + zero termination

            if (NULL == printBuf)
            {
                retVal = eOUTOFMEMORY;
                Log(eLogError, CMP_NAME, "readReg: Memory allocation failed!");
            }
            else
            {
                // print the first byte
                sprintf(&printBuf[0], "0x%02X", buf[0]);
                for (int i = 1; i < reg.len; i++)
                {
                    // overwrite the null-termination of the previous sprintf
                    sprintf(&printBuf[((i - 1)*5) + 4], ",0x%02X", buf[i]);
                }
                
                Log(eLogDebug, CMP_NAME, 
                    "readReg: Reading Si534x register: page: %d, address: 0x%02X, got: %s", 
                    reg.page, reg.address, printBuf);
                
                free(printBuf);
            }
        }
    }

    return retVal;
}

static eStatus writeReg(const tSiReg& reg, uint8_t * buf, uint8_t bufferSize)
{
    eStatus retVal = eOK;
    uint8_t tmp[2];

    if ((NULL == buf) || (0 == bufferSize))
    {
        retVal = eINVALIDARG;
    }
    else if (bufferSize < reg.len)
    {
        retVal = eFAIL; 
    }
    else if (reg.readonly)
    {
        retVal = eUNSUPPORTED;
        Log(eLogWarn, CMP_NAME, 
                "writeReg: Attempted to write read-only register: page %d, address: 0x%02X", 
                reg.page, reg.address);
    }
    else
    {
        // Switch to  the correct page
        retVal = setPage(reg.page);
        if (eOK == retVal)
        {
            // Set the address to start writing to
            tmp[0] = CMD_SET_ADDRESS;
            tmp[1] = reg.address;
            SpiTransfer(eSpiDevCLK, &tmp[0], 2);

            // Then write as many bytes as required
            for (int i = 0; i < reg.len; i++)
            {
                // needs to be set on each iteration as SpiTransfer overwrites the buffer
                tmp[0] = CMD_WRITE_INCREMENT;
                tmp[1] = buf[i];
                SpiTransfer(eSpiDevCLK, &tmp[0], 2);
            }

            // everything below is for debug purposes
            char * printBuf = (char *)malloc(reg.len * 5);    // 0xXX,0xYY + zero termination

            if (NULL == printBuf)
            {
                retVal = eOUTOFMEMORY;
                Log(eLogError, CMP_NAME, "readReg: Memory allocation failed!");
            }
            else
            {
                // print the first byte
                sprintf(&printBuf[0], "0x%02X", buf[0]);
                for (int i = 1; i < reg.len; i++)
                {
                    // overwrite the null-termination of the previous sprintf
                    sprintf(&printBuf[((i - 1)*5) + 4], ",0x%02X", buf[i]);
                }
                
                Log(eLogDebug, CMP_NAME, 
                    "writeReg: Written Si534x register: page: %d, address: 0x%02X, got: %s", 
                    reg.page, reg.address, printBuf);
                
                free(printBuf);
            }
        }
    }

    return retVal;
}


//==============================================================================
//  Exported functions
//==============================================================================

eStatus Si534xReadId(eSi534xType * const type)
{
    eStatus retVal = eOK;
    uint16_t buf;

    if (NULL == type)
    {
        retVal = eINVALIDARG;
    }
    else
    {
        *type = eSiTypeUnknown;

        readReg(Reg_BasePartNumber, (uint8_t *)&buf, 2);

        if ((buf == (uint16_t)eSi5342) || 
            (buf == (uint16_t)eSi5344) ||
            (buf == (uint16_t)eSi5345))
        {
            retVal = eOK;
            *type = (eSi534xType)buf;
            Log(eLogInfo, CMP_NAME, "Si534xReadId: Found Si%4x", buf);
        }
        else
        {
            retVal = eFAIL;
            Log(eLogWarn, CMP_NAME, "Si534xReadId: Unable to read type, got: 0x4X", buf);
        }
    }

    return retVal;
}

// Fills-in a list of available configs
eStatus Si534xListConfigs(const uint8_t maxCount, uint8_t * count, const char * configList[])
{
    eStatus retVal = eOK;

    if ((NULL == configList) || (NULL == count))
    {
        retVal = eINVALIDARG;
    }
    else
    {
        *count = 0;

        for (int i = 0; i < sizeof(si534xConfig)/sizeof(si534xConfig[0]); i++)
        {
            if (*count < maxCount)
            {
                (*count)++;
                configList[i] = si534xConfig[i].name;
                Log(eLogDebug, CMP_NAME,
                        "Si534xListConfigs: Config id: %d, name: %s",
                        i, si534xConfig[i].name);
            }
            else
            {
                retVal = eOUTOFMEMORY;
                Log(eLogWarn, CMP_NAME, 
                        "Si534xListConfigs: Too many configs! Config count: %d, array size: %d", 
                        sizeof(si534xConfig)/sizeof(si534xConfig[0]),
                        maxCount);
            }
        }
    }

    return retVal;
}

eStatus Si534xInit()
{
    eStatus retVal = eOK;
    
    SpiInit();

    retVal = Si534xReadId(&clkType);

    if (eOK == retVal)
    {
        initialized = true;
    }
    else
    {
        Log(eLogWarn, CMP_NAME, "Si534xInit Failed!");
    }

    return retVal;
}
