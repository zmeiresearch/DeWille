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

#include "pcm1792.h"
#include "pcm1792_regs.h"

#include "logger.h"

#include "spi_mux.h"

//==============================================================================
//  Defines
//==============================================================================
#define CMP_NAME                "PCM1792"

#define ARRAY_SIZE(x)           (sizeof(x)/sizeof(x[0]))

#define PCM_READ_FLAG           (uint8_t)0x80
#define DATA_DUMMY              (uint8_t)0xA5

//==============================================================================
//  Local types
//==============================================================================

//==============================================================================
//  Local data
//==============================================================================


//==============================================================================
//  Local functions
//==============================================================================

static eStatus readReg(const eSpiDevice dev, tPcmReg& reg)
{
    eStatus retVal = eOK;
    uint8_t tmp[2];

    if ((dev != eSpiDevDACR) && (dev != eSpiDevDACL))
    {
        retVal = eINVALIDARG;
    }
    else
    {
        // Set address to start reading from
        tmp[0] = (uint8_t)(PCM_READ_FLAG | reg.address);
        tmp[1] = DATA_DUMMY;
        SpiTransfer(dev, &tmp[0], 2);
        reg.value = tmp[1];

        // everything below is for debug purposes
        char printBuf[5];   // 0xXX + zero termination
        sprintf(&printBuf[0], "0x%02X", tmp[1]);
        Log(eLogInfo, CMP_NAME,
                "readReg: Reading PCM1792_%s register: 0x%02X, got: %s",
                (dev == eSpiDevDACR) ? "D" : "L", 
                reg.address, 
                printBuf);
    }

    return retVal;
}

static eStatus writeReg(const eSpiDevice dev, const tPcmReg& reg)
{
    eStatus retVal = eOK;
    uint8_t tmp[2];

    if ((dev != eSpiDevDACR) && (dev != eSpiDevDACL))
    {
        retVal = eINVALIDARG;
    }
    /*else if (reg.readonly)
    {
        retVal = eUNSUPPORTED;
        Log(eLogWarn, CMP_NAME,
                "writeReg: Attempted to write read-only register: 0x%02X",
                reg.address);
    }*/
    else
    {
        // Set the address to start writing to
        tmp[0] = (uint8_t)((~PCM_READ_FLAG) & reg.address);
        tmp[1] = reg.value;
        SpiTransfer(eSpiDevCLK, &tmp[0], 2);

        // everything below is for debug purposes
        char printBuf[5];   // 0xXX + zero termination
        sprintf(&printBuf[0], "0x%02X", tmp[1]);
        Log(eLogInfo, CMP_NAME,
                "writedReg: Writing PCM1792_%s register: 0x%02X: %s",
                (dev == eSpiDevDACR) ? "D" : "L", 
                reg.address, 
                printBuf);    
    }

    return retVal;
}

/*static eStatus writeConfigArray(const si5344_revd_register_t * const config,
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
}*/


//==============================================================================
//  Exported functions
//==============================================================================

eStatus Pcm1792CheckDevice()
{
    eStatus retVal = eOK;

    // Check both devices by writing to ATL (16) register
    tPcmReg tmp;
    tmp.address = PcmAttenuatorL.address;
    
    tmp.value = DATA_DUMMY;
    writeReg(eSpiDevDACR, tmp);
    readReg(eSpiDevDACR, tmp);
    if (tmp.value == DATA_DUMMY) 
    {
        Log(eLogInfo, CMP_NAME, "Pcm1792CheckDevice - Right DAC OK.");
    }
    else
    {
        Log(eLogError, CMP_NAME, "PCM1792CheckDevice - Error accessing Right DAC!!");
        retVal = eFAIL;
    }

    tmp.value = (uint8_t)(~DATA_DUMMY);
    writeReg(eSpiDevDACL, tmp);
    readReg(eSpiDevDACL, tmp);
    if (tmp.value == (uint8_t)(~DATA_DUMMY))
    {
        Log(eLogInfo, CMP_NAME, "Pcm1792CheckDevice - Left DAC OK.");
    }
    else
    {
        Log(eLogError, CMP_NAME, "PCM1792CheckDevice - Error accessing Left DAC!!");
        retVal = eFAIL;
    }

    return retVal;
}

eStatus Pcm1792Init()
{
    eStatus retVal = eOK;

    tPcmReg tmp;

    for (int i = 0; i < ARRAY_SIZE(pcm1792DefaultConfig); i++)
    {
        writeReg(eSpiDevDACL, pcm1792DefaultConfig[i]);
        writeReg(eSpiDevDACR, pcm1792DefaultConfig[i]);
    }

    tmp.address = PcmMonoChannel.address;
    readReg(eSpiDevDACR, tmp);
    tmp.value = tmp.value | 1 << PcmMonoChannel.offset;
    writeReg(eSpiDevDACR, tmp);

    return retVal;
}


/*eStatus Pcm1792SoftReset()
{
    uint8_t buf = 0x01;

    Log(eLogInfo, CMP_NAME, "Pcm1792SoftReset()");
    writeReg(Reg_SoftResetCalib, &buf, 1);

    return eOK;
}*/

/*eStatus Si534xDumpStatus()
{
    eStatus retVal = eOK;

    uint8_t buf[10];

    readReg(Reg_InternalError, &buf[0], 1);
    Log(eLogInfo, CMP_NAME, "DumpStatus: InternalError:0x%02x", (uint8_t)*buf);

    readReg(Reg_ActiveInput, &buf[0], 1);
    Log(eLogInfo, CMP_NAME, "DumpStatus: ActiveInput:0x%02x", (uint8_t)*buf);

    readReg(Reg_ScratchPad, &buf[0], 8);
    buf[8] = 0;
    Log(eLogInfo, CMP_NAME, "DumpStatus: ScrachPad: %s", &buf[0]);
    

    return retVal;
}*/

