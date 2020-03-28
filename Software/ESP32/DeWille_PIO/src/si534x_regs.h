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
//  Multi-include guard
//==============================================================================
#ifndef INC_SI534x_REGS_H
#define INC_SI534x_REGS_H

//==============================================================================
//  Multi-include guard
//==============================================================================
#include <globals.h>


//==============================================================================
//  Defines
//==============================================================================


//==============================================================================
//  Exported types
//==============================================================================
typedef struct _tSiReg
{
    uint8_t     page;
    uint8_t     address;
    uint8_t     len;
    bool        readonly;
} tSiReg;


//==============================================================================
//  Exported data
//==============================================================================
// the two registers accessible on each page - Page and Status
const tSiReg Reg_Page =                 { 0x0, 0x01, 1, false };
const tSiReg Reg_DeviceReady =          { 0x0, 0xfe, 1, true  };

// Page 0 registers - Alarms, interrupts, reset, other config
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


// Page 1 registers - Clock output configuration
const tSiReg Reg_GlobalOeGating =       { 0x1, 0x02, 1, false };

// Clock 0
const tSiReg Reg_ClockOut0DriverCfg =   { 0x1, 0x08, 1, false };
const tSiReg Reg_ClockOut0FormatSync =  { 0x1, 0x09, 1, false };
const tSiReg Reg_ClockOut0SwingAmpl =   { 0x1, 0x0a, 1, false };
const tSiReg Reg_ClockOut0MuxSel =      { 0x1, 0x0b, 1, false };

// Clock 1
const tSiReg Reg_ClockOut1DriverCfg =   { 0x1, 0x0d, 1, false };
const tSiReg Reg_ClockOut1FormatSync =  { 0x1, 0x0e, 1, false };
const tSiReg Reg_ClockOut1SwingAmpl =   { 0x1, 0x0f, 1, false };
const tSiReg Reg_ClockOut1MuxSel =      { 0x1, 0x10, 1, false };

// Clock 2
const tSiReg Reg_ClockOut2DriverCfg =   { 0x1, 0x12, 1, false };
const tSiReg Reg_ClockOut2FormatSync =  { 0x1, 0x13, 1, false };
const tSiReg Reg_ClockOut2SwingAmpl =   { 0x1, 0x14, 1, false };
const tSiReg Reg_ClockOut2MuxSel =      { 0x1, 0x15, 1, false };

// Clock 3
const tSiReg Reg_ClockOut3DriverCfg =   { 0x1, 0x17, 1, false };
const tSiReg Reg_ClockOut3FormatSync =  { 0x1, 0x18, 1, false };
const tSiReg Reg_ClockOut3SwingAmpl =   { 0x1, 0x19, 1, false };
const tSiReg Reg_ClockOut3MuxSel =      { 0x1, 0x1a, 1, false };

// Clock 4
const tSiReg Reg_ClockOut4DriverCfg =   { 0x1, 0x1c, 1, false };
const tSiReg Reg_ClockOut4FormatSync =  { 0x1, 0x1d, 1, false };
const tSiReg Reg_ClockOut4SwingAmpl =   { 0x1, 0x1e, 1, false };
const tSiReg Reg_ClockOut4MuxSel =      { 0x1, 0x1f, 1, false };

// Clock 5
const tSiReg Reg_ClockOut5DriverCfg =   { 0x1, 0x21, 1, false };
const tSiReg Reg_ClockOut5FormatSync =  { 0x1, 0x22, 1, false };
const tSiReg Reg_ClockOut5SwingAmpl =   { 0x1, 0x23, 1, false };
const tSiReg Reg_ClockOut5MuxSel =      { 0x1, 0x24, 1, false };

// Clock 6
const tSiReg Reg_ClockOut6DriverCfg =   { 0x1, 0x26, 1, false };
const tSiReg Reg_ClockOut6FormatSync =  { 0x1, 0x27, 1, false };
const tSiReg Reg_ClockOut6SwingAmpl =   { 0x1, 0x28, 1, false };
const tSiReg Reg_ClockOut6MuxSel =      { 0x1, 0x29, 1, false };

// Clock 7
const tSiReg Reg_ClockOut7DriverCfg =   { 0x1, 0x2b, 1, false };
const tSiReg Reg_ClockOut7FormatSync =  { 0x1, 0x2c, 1, false };
const tSiReg Reg_ClockOut7SwingAmpl =   { 0x1, 0x2d, 1, false };
const tSiReg Reg_ClockOut7MuxSel =      { 0x1, 0x2e, 1, false };

// Clock 8
const tSiReg Reg_ClockOut8DriverCfg =   { 0x1, 0x30, 1, false };
const tSiReg Reg_ClockOut8FormatSync =  { 0x1, 0x31, 1, false };
const tSiReg Reg_ClockOut8SwingAmpl =   { 0x1, 0x32, 1, false };
const tSiReg Reg_ClockOut8MuxSel =      { 0x1, 0x33, 1, false };

// Clock 9 - address not consecutive to Clk8!
const tSiReg Reg_ClockOut9DriverCfg =   { 0x1, 0x3a, 1, false };
const tSiReg Reg_ClockOut9FormatSync =  { 0x1, 0x3b, 1, false };
const tSiReg Reg_ClockOut9SwingAmpl =   { 0x1, 0x3c, 1, false };
const tSiReg Reg_ClockOut9MuxSel =      { 0x1, 0x3d, 1, false };

const tSiReg Reg_OutXAlwaysOn =         { 0x1, 0x3f, 2, false };
const tSiReg Reg_OutputDisableLos =     { 0x1, 0x41, 1, false };
const tSiReg Reg_OutputDisableLol =     { 0x1, 0x42, 1, false };
const tSiReg Reg_PowerDownAll =         { 0x1, 0x45, 1, false };


// Page 2 registers - P,R dividers, scratch area
const tSiReg Reg_RefPrescaleDivRatio =  { 0x2, 0x06, 1, false };

// Input (P) dividers
const tSiReg Reg_P0DivNum =             { 0x2, 0x08, 6, false };
const tSiReg Reg_P0DivDen =             { 0x2, 0x0e, 4, false };

const tSiReg Reg_P1DivNum =             { 0x2, 0x12, 6, false };
const tSiReg Reg_P1DivDen =             { 0x2, 0x18, 4, false };

const tSiReg Reg_P2DivNum =             { 0x2, 0x1c, 6, false };
const tSiReg Reg_P2DivDen =             { 0x2, 0x22, 4, false };

const tSiReg Reg_P3DivNum =             { 0x2, 0x26, 6, false };
const tSiReg Reg_P3DivDen =             { 0x2, 0x2c, 4, false };

const tSiReg Reg_PxUpdate =             { 0x2, 0x30, 1, false };

const tSiReg Reg_P0FracDivEnable =      { 0x2, 0x31, 1, false };
const tSiReg Reg_P1FracDivEnable =      { 0x2, 0x32, 1, false };
const tSiReg Reg_P2FracDivEnable =      { 0x2, 0x33, 1, false };
const tSiReg Reg_P3FracDivEnable =      { 0x2, 0x34, 1, false };

// Reference input - XAXB divider
const tSiReg Reg_MXaxbDivNum =          { 0x2, 0x35, 6, false };
const tSiReg Reg_MXaxbDivDen =          { 0x2, 0x3b, 4, false };
const tSiReg Reg_MXaxbUpdate =          { 0x2, 0x3f, 1, false };

// Output (R) clokc dividers 
const tSiReg Reg_R0Divider =            { 0x2, 0x4a, 3, false };
const tSiReg Reg_R1Divider =            { 0x2, 0x4d, 3, false };
const tSiReg Reg_R2Divider =            { 0x2, 0x50, 3, false };
const tSiReg Reg_R3Divider =            { 0x2, 0x53, 3, false };
const tSiReg Reg_R4Divider =            { 0x2, 0x56, 3, false };
const tSiReg Reg_R5Divider =            { 0x2, 0x59, 3, false };
const tSiReg Reg_R6Divider =            { 0x2, 0x5c, 3, false };
const tSiReg Reg_R7Divider =            { 0x2, 0x5f, 3, false };
const tSiReg Reg_R8Divider =            { 0x2, 0x62, 3, false };
const tSiReg Reg_R9Divider =            { 0x2, 0x68, 3, false };

// Scratch pad and OPN
const tSiReg Reg_ScratchPad =           { 0x2, 0x6b, 8, false };
const tSiReg Reg_OpnIdent =             { 0x2, 0x78, 5, false };
const tSiReg Reg_OpnRevision =          { 0x2, 0x7d, 1, false };
const tSiReg Reg_BaselineId =           { 0x2, 0x7e, 1, false };

// Out-of-frequency detection - don't know the difference between 
// this and e.g. Oof0ClearThresh
const tSiReg Reg_Oof0TrigThreshExt =    { 0x2, 0x8a, 1, false };
const tSiReg Reg_Oof1TrigThreshExt =    { 0x2, 0x8b, 1, false };
const tSiReg Reg_Oof2TrigThreshExt =    { 0x2, 0x8c, 1, false };
const tSiReg Reg_Oof3TrigThreshExt =    { 0x2, 0x8d, 1, false };
const tSiReg Reg_Oof0ClearThreshExt =   { 0x2, 0x8e, 1, false };
const tSiReg Reg_Oof1ClearThreshExt =   { 0x2, 0x8f, 1, false };
const tSiReg Reg_Oof2ClearThreshExt =   { 0x2, 0x90, 1, false };
const tSiReg Reg_Oof3ClearThreshExt =   { 0x2, 0x91, 1, false };

const tSiReg Reg_FastlockExtendScale =  { 0x2, 0x94, 1, false };
const tSiReg Reg_LolSlwValwinSelx =     { 0x2, 0x96, 1, false };
const tSiReg Reg_FastlockDelayOnSwEn =  { 0x2, 0x97, 1, false };
const tSiReg Reg_FastlockDelayOnLolEn = { 0x2, 0x99, 1, false };
const tSiReg Reg_FastlockDelayOnLol =   { 0x2, 0x9d, 3, false };
const tSiReg Reg_FastlockDelayOnSw =    { 0x2, 0xa9, 3, false };
const tSiReg Reg_LolDelayOnLos =        { 0x2, 0xb7, 1, false };
const tSiReg Reg_LolLosRefclk =         { 0x2, 0xb8, 1, true }; // is it really RO?


// Page 3 registers - Output N dividers, N divider Finc/Fdec
const tSiReg Reg_N0Num =                { 0x3, 0x02, 6, false };
const tSiReg Reg_N0Den =                { 0x3, 0x08, 4, false };
const tSiReg Reg_N0Update =             { 0x3, 0x0c, 1, false };

const tSiReg Reg_N1Num =                { 0x3, 0x0d, 6, false };
const tSiReg Reg_N1Den =                { 0x3, 0x13, 4, false };
const tSiReg Reg_N1Update =             { 0x3, 0x17, 1, false };

const tSiReg Reg_N2Num =                { 0x3, 0x18, 6, false };
const tSiReg Reg_N2Den =                { 0x3, 0x1e, 4, false };
const tSiReg Reg_N2Update =             { 0x3, 0x22, 1, false };

const tSiReg Reg_N3Num =                { 0x3, 0x23, 6, false };
const tSiReg Reg_N3Den =                { 0x3, 0x29, 4, false };
const tSiReg Reg_N3Update =             { 0x3, 0x2d, 1, false };

const tSiReg Reg_N4Num =                { 0x3, 0x2e, 6, false };
const tSiReg Reg_N4Den =                { 0x3, 0x34, 4, false };

const tSiReg Reg_N4NGlobalUpdate =      { 0x3, 0x38, 1, false };

const tSiReg Reg_FincFdecMasks =        { 0x3, 0x39, 1, false };
const tSiReg Reg_N0FrequencyStep =      { 0x3, 0x3b, 6, false };
const tSiReg Reg_N1FrequencyStep =      { 0x3, 0x41, 6, false };
const tSiReg Reg_N2FrequencyStep =      { 0x3, 0x47, 6, false };
const tSiReg Reg_N3FrequencyStep =      { 0x3, 0x4d, 6, false };
const tSiReg Reg_N4FrequencyStep =      { 0x3, 0x53, 6, false };


// Page 4 registers - Zero Delay mode configuration
const tSiReg Reg_ZdModeSetup =          { 0x4, 0x87, 1, false };


// Page 5 registers - M divider, BW, holdover, input switch, FINC/DEC
const tSiReg Reg_ActiveInput =          { 0x5, 0x07, 1, true };
const tSiReg Reg_LoopBandwidth =        { 0x5, 0x08, 6, false };
const tSiReg Reg_FastLockLoopBandwidth ={ 0x5, 0x0e, 6, false };
const tSiReg Reg_BandwidthUpdate =      { 0x5, 0x14, 1, false };
const tSiReg Reg_MNum =                 { 0x5, 0x15, 7, false };
const tSiReg Reg_MDen =                 { 0x5, 0x1c, 4, false };
const tSiReg Reg_MDivUpdate =           { 0x5, 0x20, 1, false };
const tSiReg Reg_MDivFracEnable =       { 0x5, 0x21, 1, false };
const tSiReg Reg_InputClockSelect =     { 0x5, 0x2a, 1, false };
const tSiReg Reg_FastLockControl =      { 0x5, 0x2b, 1, false };

// Holdover
const tSiReg Reg_HoldoverExitControl =  { 0x5, 0x2c, 1, false };
const tSiReg Reg_HoldoverRampBypass =   { 0x5, 0x2d, 1, false };
const tSiReg Reg_HoldoverHistoryLength ={ 0x5, 0x2e, 1, false };
const tSiReg Reg_HoldoverHistoryDelay = { 0x5, 0x2f, 1, false };
const tSiReg Reg_HoldoverRefCountFrac = { 0x5, 0x31, 1, false }; // ???
const tSiReg Reg_Holdover15MCycCount =  { 0x5, 0x32, 3, false };
const tSiReg Reg_HoldoverForce =        { 0x5, 0x35, 1, false };

const tSiReg Reg_InputClockSwControl =  { 0x5, 0x36, 1, false };
const tSiReg Reg_InputAlarmMask =       { 0x5, 0x37, 1, false };
const tSiReg Reg_Clk0Clk1Priority =     { 0x5, 0x38, 1, false };
const tSiReg Reg_Clk2Clk3Priority =     { 0x5, 0x39, 1, false };

const tSiReg Reg_HitlessSwitchMode =    { 0x5, 0x3a, 1, false }; 
const tSiReg Reg_HitlessSwThresh =      { 0x5, 0x3b, 2, false };
const tSiReg Reg_HitlessSwCoarsePmLen = { 0x5, 0x3d, 1, false };
const tSiReg Reg_HitlessSwCoarsePmDly = { 0x5, 0x3e, 1, false };

const tSiReg Reg_HoldHistValFastLockSt= { 0x5, 0x3f, 1, true };
const tSiReg Reg_540Reserved =          { 0x5, 0x40, 1, false }; // ??

const tSiReg Reg_HitlessSwFinePmLen =   { 0x5, 0x88, 1, false };
const tSiReg Reg_PfdEnableDelay =       { 0x5, 0x89, 2, false };

const tSiReg Reg_HoldoverExit =         { 0x5, 0x9b, 1, false };
const tSiReg Reg_HoldoverExitBw =       { 0x5, 0x9d, 6, false };
const tSiReg Reg_HitlessSwControl =     { 0x5, 0xa6, 1, false };


// Page 9 registers - IO Configuration control
const tSiReg Reg_XaxbConfig =           { 0x9, 0x0e, 1, false };
const tSiReg Reg_ControlVoltageSel =    { 0x9, 0x43, 1, false };
const tSiReg Reg_ClockInputConfig =     { 0x9, 0x49, 1, false };
const tSiReg Reg_InputClockDspllEn =    { 0x9, 0x4a, 1, false };
const tSiReg Reg_InputClockBufHyst =    { 0x9, 0x4e, 1, false };
const tSiReg Reg_MxaxbFracMode =        { 0x9, 0x5e, 1, false };


// Page A registers - Not listed on pg 81 but on pg. 122
const tSiReg Reg_NDiv05x =              { 0xa, 0x02, 1, false };
const tSiReg Reg_NClkOutxEnable =       { 0xa, 0x03, 1, false };
const tSiReg Reg_NClkIntDivMode =       { 0xa, 0x04, 1, false };
const tSiReg Reg_NClkDivPowerDown =     { 0xa, 0x05, 1, false };
const tSiReg Reg_N0HighFreq =           { 0xa, 0x14, 1, false };
const tSiReg Reg_N1HighFreq =           { 0xa, 0x1a, 1, false };
const tSiReg Reg_N2HighFreq =           { 0xa, 0x20, 1, false };
const tSiReg Reg_N3HighFreq =           { 0xa, 0x26, 1, false };
const tSiReg Reg_N4HighFreq =           { 0xa, 0x2c, 1, false };


// Page B registers
const tSiReg Reg_B24Reserved =          { 0xb, 0x24, 1, false };
const tSiReg Reg_B25Reserved =          { 0xb, 0x25, 1, false };
const tSiReg Reg_FracDivClkDis =        { 0xb, 0x44, 1, false };
const tSiReg Reg_LosClkDis =            { 0xb, 0x46, 1, false };
const tSiReg Reg_OofClkDis =            { 0xb, 0x47, 1, false };
const tSiReg Reg_OofDivClkDis =         { 0xb, 0x48, 1, false };
const tSiReg Reg_NDivClkDis =           { 0xb, 0x4a, 1, false };
const tSiReg Reg_VcoCalCode =           { 0xb, 0x57, 2, false };

//==============================================================================
//  Exported functions
//==============================================================================


#endif // INC_SI534x_REGS_H

