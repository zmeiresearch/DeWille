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

#include "spi_mux.h"

//==============================================================================
//  Defines
//==============================================================================
#define CMP_NAME                "SI534x"
#define ALWAYS_SET_PAGE         false

#define MAX_CONSECUTIVE_REGS    64  // maximal number of config registers to try
                                    // writing consecutively

#define ARRAY_SIZE(x)           (sizeof(x)/sizeof(x[0]))

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
    // And finally, ClockBuilderPro generates settings for 
    // page 8 as well.
    if (((0 <= page) && (page <= 5)) ||
        ((8 <= page) && (page <= 0xb)))
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
                Log(eLogError, CMP_NAME, "writeReg: Memory allocation failed!");
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
                    "writeReg: Written Si534x register: page: %d, address: 0x%02X: %s",
                    reg.page, reg.address, printBuf);

                free(printBuf);
            }
        }
    }

    return retVal;
}

static eStatus writeBuffer(const uint16_t addr, const uint8_t * const buf, size_t bufferLen)
{
    eStatus retVal = eOK;
    uint8_t tmp[2];
    const uint8_t address = (uint8_t)(addr & 0xff);
    const uint8_t page = (uint8_t)((addr >> 8) & 0x0f);

    // Switch to  the correct page
    retVal = setPage(page);
    if (eOK == retVal)
    {
        // Set the address to start writing to
        tmp[0] = CMD_SET_ADDRESS;
        tmp[1] = address;
        SpiTransfer(eSpiDevCLK, &tmp[0], 2);

        // Then write as many bytes as required
        for (int i = 0; i < bufferLen; i++)
        {
            // needs to be set on each iteration as SpiTransfer overwrites the buffer
            tmp[0] = CMD_WRITE_INCREMENT;
            tmp[1] = buf[i];
            SpiTransfer(eSpiDevCLK, &tmp[0], 2);
        }

        // everything below is for debug purposes
        char * printBuf = (char *)malloc(bufferLen * 5);    // 0xXX,0xYY + zero termination

        if (NULL == printBuf)
        {
            retVal = eOUTOFMEMORY;
            Log(eLogError, CMP_NAME, "writeBuffer: Memory allocation failed!");
        }
        else
        {
            // print the first byte
            sprintf(&printBuf[0], "0x%02X", buf[0]);
            for (int i = 1; i < bufferLen; i++)
            {
                // overwrite the null-termination of the previous sprintf
                sprintf(&printBuf[((i - 1)*5) + 4], ",0x%02X", buf[i]);
            }

            Log(eLogDebug, CMP_NAME,
                "writeBuffer: Written: 0x%04X: %s (%d bytes)",
                addr, printBuf, bufferLen);

            free(printBuf);
        }
    }

    return retVal;
}

static eStatus writeConfigArray(const si5344_revd_register_t * const config,
        const size_t configLen)
{
    eStatus retVal = eOK;

    uint8_t tempBuf[MAX_CONSECUTIVE_REGS];
    size_t tempCount = 0;
    uint16_t address = 0;
    size_t written = 0;

    Log(eLogDebug, CMP_NAME,
            "writeConfigArray: writing config: %08X, len: %d",
            config, configLen);

    while ((written < configLen) && (eOK == retVal))
    {
        address = config[written].address;

        tempBuf[tempCount] = config[written].value;
        tempCount++;

        // check whether the next value is for the next address and append
        // it to tempBuf if so
        while ( ((written + tempCount) < configLen) &&
                (tempCount < MAX_CONSECUTIVE_REGS) &&
                (   config[written + tempCount].address ==
                    (address + tempCount)) )
        {
            tempBuf[tempCount] = config[written + tempCount].value;
            tempCount++;
        }
        retVal = writeBuffer(address, &tempBuf[0], tempCount);
        written += tempCount;
        tempCount = 0;
    }
    Log(eLogDebug, CMP_NAME, "writeConfigArray: Done!");

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

eStatus Si534xSoftReset()
{
    uint8_t buf = 0x01;

    Log(eLogInfo, CMP_NAME, "Si534xSoftReset()");
    writeReg(Reg_SoftResetCalib, &buf, 1);

    return eOK;
}

eStatus Si534xDumpStatus()
{
    eStatus retVal = eOK;

    uint8_t buf[10];

    readReg(Reg_InternalStatus, &buf[0], 1);
    Log(eLogInfo, CMP_NAME, "DumpStatus: InternalStatus:0x%02x", (uint8_t)*buf);
    
    //readReg(Reg_OofLosAlarms, &buf[0], 1);
    //Log(eLogInfo, CMP_NAME, "DumpStatus: OofLosAlarms:0x%02x", buf);

    //readReg(Reg_HoldoverLolStatus, &buf[0], 1);
    //Log(eLogInfo, CMP_NAME, "DumpStatus: HoldoverLolStatus:0x%02x", buf);

    //readReg(Reg_CalibrationStatus, &buf[0], 1);
    //Log(eLogInfo, CMP_NAME, "DumpStatus: CalibrationStatus:0x%02x", buf);

    readReg(Reg_InternalError, &buf[0], 1);
    Log(eLogInfo, CMP_NAME, "DumpStatus: InternalError:0x%02x", (uint8_t)*buf);

    readReg(Reg_ActiveInput, &buf[0], 1);
    Log(eLogInfo, CMP_NAME, "DumpStatus: ActiveInput:0x%02x", (uint8_t)*buf);

    readReg(Reg_ScratchPad, &buf[0], 8);
    buf[8] = 0;
    Log(eLogInfo, CMP_NAME, "DumpStatus: ScrachPad: %s", &buf[0]);
    

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

        for (int i = 0; i < ARRAY_SIZE(si534xConfig); i++)
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
                        ARRAY_SIZE(si534xConfig),
                        maxCount);
            }
        }
    }

    return retVal;
}

eStatus Si534xSetConfig(const uint8_t configId)
{
    eStatus retVal = eOK;

    if (configId >= ARRAY_SIZE(si534xConfig))
    {
        retVal = eINVALIDARG;
        Log(eLogWarn, CMP_NAME, "Si534xSetConfig: Trying to set invalid config id %d", configId);
    }
    else
    {
        Log(eLogInfo, CMP_NAME, "Si534xSetConfig: Setting config %s", si534xConfig[configId].name);
        writeConfigArray(&si5344_preamble[0], ARRAY_SIZE(si5344_preamble));
        writeConfigArray(si534xConfig[configId].configArr, si534xConfig[configId].configLen);
        writeConfigArray(&si5344_postamble[0], ARRAY_SIZE(si5344_postamble));
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
