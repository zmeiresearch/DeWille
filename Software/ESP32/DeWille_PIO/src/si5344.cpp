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

#include "si5344.h"

#include "logger.h"

#include "spi.h"

//==============================================================================
//  Defines
//==============================================================================
#define CMP_NAME                "SI5344"
#define SEND_SLEEP_TIME         (uint32_t)5     // time to sleep between write attempts
#define LOG_MAX_WAIT            (uint32_t)100   // max time to wait for synchronization

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
typedef struct _tSiReg
{
    uint8_t     page;
    uint8_t     address;
    uint8_t     len;
    bool        readOnly;
} tSiReg;

//==============================================================================
//  Local data
//==============================================================================

// the two registers accessible on each page - Page and Status
const tSiReg Reg_Page =                 { 0x0, 0x01, 1, false };
const tSiReg Reg_DeviceReady =          { 0x0, 0xfe, 1, true  };

// Page 0 registers
// Control and status
const tSiReg Reg_BasePartNumber =       { 0x0, 0x02, 2, true };
const tSiReg Reg_DeviceGrade =          { 0x0, 0x04, 1, true };
const tSiReg Reg_DeviceRevision =       { 0x0, 0x05, 1, true };
const tSiReg Reg_ToolVersion =          { 0x0, 0x06, 3, false };
const tSiReg Reg_TemperatureGrade =     { 0x0, 0x09, 1, false };
const tSiReg Reg_PackageID =            { 0x0, 0x0a, 1, false };
const tSiReg Reg_I2CAddress =           { 0x0, 0x0b, 1, false };
const tSiReg Reg_InternalStatus =       { 0x0, 0x0c, 1, true };
const tSiReg Reg_OofLosAlarms =         { 0x0, 0x0d, 1, true };
const tSiReg Reg_HoldoverLolStatus =    { 0x0, 0x0e, 1, true };
const tSiReg Reg_CalibrationStatus =    { 0x0, 0x0f, 1, true };
const tSiReg Reg_InternalError =        { 0x0, 0x11, 1, false };
const tSiReg Reg_StickyOofLos =         { 0x0, 0x12, 1, false };
const tSiReg Reg_StickyHoldoverLol =    { 0x0, 0x13, 1, false };
const tSiReg Reg_StickyPllInCalib =     { 0x0, 0x14, 1, false };
const tSiReg Reg_LolOnHold =            { 0x0, 0x16, 1, false };
const tSiReg Reg_StatusFlagMasks =      { 0x0, 0x17, 1, false };
const tSiReg Reg_OofLosMasks =          { 0x0, 0x18, 1, false };
const tSiReg Reg_HoldoverLolMasks =     { 0x0, 0x19, 1, false };
const tSiReg Reg_PllInCalibIntMask =    { 0x0, 0x1a, 1, false };
const tSiReg Reg_SoftResetCalib =       { 0x0, 0x1c, 1, false };
const tSiReg Reg_FincFdec =             { 0x0, 0x1d, 1, false };
const tSiReg Reg_PowerDownHardReset =   { 0x0, 0x1e, 1, false };
const tSiReg Reg_Spi34Wire =            { 0x0, 0x2b, 1, false };

// Loss of Signal (LOS) registers
const tSiReg Reg_LosEnable =            { 0x0, 0x2c, 1, false };
const tSiReg Reg_LosReqalVal =          { 0x0, 0x2d, 1, false };
const tSiReg Reg_Los0TrigThresh =       { 0x0, 0x2e, 2, false };
const tSiReg Reg_Los1TrigThresh =       { 0x0, 0x30, 2, false };
const tSiReg Reg_Los2TrigThresh =       { 0x0, 0x32, 2, false };
const tSiReg Reg_Los3TrigThresh =       { 0x0, 0x34, 2, false };
const tSiReg Reg_Los0ClearThresh =      { 0x0, 0x36, 2, false };
const tSiReg Reg_Los1ClearThresh =      { 0x0, 0x38, 2, false };
const tSiReg Reg_Los2ClearThresh =      { 0x0, 0x3a, 2, false };
const tSiReg Reg_Los3ClearThresh =      { 0x0, 0x3c, 2, false };

// Out of Frequency (OOF) registers
const tSiReg Reg_OofEnable =            { 0x0, 0x3f, 1, false };
const tSiReg Reg_OofReferenceSelect =   { 0x0, 0x40, 1, false };
const tSiReg Reg_Oof0DividerSelect =    { 0x0, 0x41, 1, false };
const tSiReg Reg_Oof1DividerSelect =    { 0x0, 0x42, 1, false };
const tSiReg Reg_Oof2DividerSelect =    { 0x0, 0x43, 1, false };
const tSiReg Reg_Oof3DividerSelect =    { 0x0, 0x44, 1, false };
const tSiReg Reg_OofXoDividerSelect =   { 0x0, 0x45, 1, false };
const tSiReg Reg_Oof0SetThresh =        { 0x0, 0x46, 1, false };
const tSiReg Reg_Oof1SetThresh =        { 0x0, 0x47, 1, false };
const tSiReg Reg_Oof2SetThresh =        { 0x0, 0x48, 1, false };
const tSiReg Reg_Oof3SetThresh =        { 0x0, 0x49, 1, false };
const tSiReg Reg_Oof0ClearThresh =      { 0x0, 0x4a, 1, false };
const tSiReg Reg_Oof1ClearThresh =      { 0x0, 0x4b, 1, false };
const tSiReg Reg_Oof2ClearThresh =      { 0x0, 0x4c, 1, false };
const tSiReg Reg_Oof3ClearThresh =      { 0x0, 0x4d, 1, false };
const tSiReg Reg_Oof01DetwinSel =       { 0x0, 0x4e, 1, false };
const tSiReg Reg_Oof23DetwinSel =       { 0x0, 0x4f, 1, false };
const tSiReg Reg_OofOnLos =             { 0x0, 0x50, 1, false };
const tSiReg Reg_FastOof0SetThresh =    { 0x0, 0x51, 1, false };
const tSiReg Reg_FastOof1SetThresh =    { 0x0, 0x52, 1, false };
const tSiReg Reg_FastOof2SetThresh =    { 0x0, 0x53, 1, false };
const tSiReg Reg_FastOof3SetThresh =    { 0x0, 0x54, 1, false };
const tSiReg Reg_FastOof0ClrThresh =    { 0x0, 0x55, 1, false };
const tSiReg Reg_FastOof1ClrThresh =    { 0x0, 0x56, 1, false };
const tSiReg Reg_FastOof2ClrThresh =    { 0x0, 0x57, 1, false };
const tSiReg Reg_FastOof3ClrThresh =    { 0x0, 0x58, 1, false };
const tSiReg Reg_FastOofDetwinSel =     { 0x0, 0x59, 1, false };
const tSiReg Reg_Oof0RatioRef =         { 0x0, 0x5a, 4, false };
const tSiReg Reg_Oof1RatioRef =         { 0x0, 0x5e, 4, false };
const tSiReg Reg_Oof2RatioRef =         { 0x0, 0x62, 4, false };
const tSiReg Reg_Oof3RatioRef =         { 0x0, 0x66, 4, false };

// Loss of Lock (LOL) registers
const tSiReg Reg_FastLolEnable =        { 0x0, 0x92, 1, false };
const tSiReg Reg_FastLolDetwinSel =     { 0x0, 0x93, 1, false };
const tSiReg Reg_FastLolDetvalSel =     { 0x0, 0x95, 1, false };
const tSiReg Reg_FastLolSetThresh =     { 0x0, 0x96, 1, false };
const tSiReg Reg_FastLolClearThresh =   { 0x0, 0x98, 1, false };
const tSiReg Reg_LolEnable =            { 0x0, 0x9a, 1, false };
const tSiReg Reg_SlowLolDetwinSel =     { 0x0, 0x9b, 1, false };
const tSiReg Reg_SlowLolDetvalSel =     { 0x0, 0x9d, 1, false };
const tSiReg Reg_LolSetThresh =         { 0x0, 0x9e, 1, false };
const tSiReg Reg_LolClearThresh =       { 0x0, 0xa0, 1, false };
const tSiReg Reg_LolTimerEnable =       { 0x0, 0xa2, 1, false };
const tSiReg Reg_LolClearDelay256 =     { 0x0, 0xa9, 4, false };

// NVM control
const tSiReg Reg_NvmNumBankWrites =     { 0x0, 0xe2, 1, true };
const tSiReg Reg_NvmBankWrite =         { 0x0, 0xe3, 1, false };
const tSiReg Reg_NvmBankRead =          { 0x0, 0xe4, 1, false };

// Fastlock registers
const tSiReg Reg_FaslockExtendEnable =  { 0x0, 0xe5, 1, false };
const tSiReg Reg_FastlockExtend =       { 0x0, 0xea, 4, false };

// Interrupt status
const tSiReg Reg_F678_Intr =            { 0x0, 0xf6, 1, true };    // ???
const tSiReg Reg_F7_Intr =              { 0x0, 0xf7, 1, true };
const tSiReg Reg_F8_Intr =              { 0x0, 0xf8, 1, true };
const tSiReg Reg_F9_Intr =              { 0x0, 0xf9, 1, true };

static bool initialized = false;
static uint8_t currentBank = 0;

static uint8_t buffer[32];      // adjust accordingly

//==============================================================================
//  Local functions
//==============================================================================
static eStatus readReg(const tSiReg& reg, uint8_t * buf, uint8_t bufferSize)
{
    eStatus retVal = eOK;
    uint8_t tmp[3];

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
                "Reading Si534x register: page: %d, address: %x, got: %s", 
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
