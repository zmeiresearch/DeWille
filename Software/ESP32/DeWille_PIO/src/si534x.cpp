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

#include "logger.h"

#include "spi.h"

//==============================================================================
//  Defines
//==============================================================================
#define CMP_NAME                "SI5344"

// Si5342/44/45 commands - pg. 53 Si5345-44-42-D-RM.pdf
#define CMD_SET_ADDRESS         (uint8_t)0x0    // 000x xxxx
#define CMD_WRITE_DATA          (uint8_t)0x40   // 010x xxxx
#define CMD_READ_DATA           (uint8_t)0x80   // 100x xxxx
#define CMD_WRITE_INCREMENT     (uint8_t)0x60   // 011x xxxx
#define CMD_READ_INCREMENT      (uint8_t)0xa0   // 101x xxxx
#define CMD_WRITE_BURST         (uint8_t)0xe0   // 1110 0000

#define DATA_DUMMY              (uint8_t)0xA5

//==============================================================================
//  Local types
//==============================================================================

//==============================================================================
//  Local data
//==============================================================================

static bool initialized = false;
static uint8_t currentBank = 0;

static uint8_t buffer[32];      // adjust accordingly

//==============================================================================
//  Local functions
//==============================================================================
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
        // First set address to start reading from
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
        // First set address to start reading from
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

    return retVal;
}


//==============================================================================
//  Exported functions
//==============================================================================

void Si534xReadId()
{
    readReg(Reg_BasePartNumber, buffer, 32);
    //readReg(Reg_DeviceGrade, buffer, 32);
    //readReg(Reg_DeviceRevision, buffer, 32);
}

eStatus Si534xInit()
{
    eStatus retVal = eOK;

    SpiInit();

    initialized = true;

    return retVal;
}
