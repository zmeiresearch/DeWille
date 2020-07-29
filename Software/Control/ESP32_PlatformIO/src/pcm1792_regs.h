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
#ifndef INC_PCM1792_REGS_H
#define INC_PCM1792_REGS_H

//==============================================================================
//  Multi-include guard
//==============================================================================
#include <globals.h>


//==============================================================================
//  Defines
//==============================================================================
#define PcmAudioFormat_

//==============================================================================
//  Exported types
//==============================================================================
typedef struct _tPcmReg
{
    uint8_t     address;
    uint8_t     value;
} tPcmReg;

typedef struct _tPcmVariable
{
    uint8_t     address;    // register address
    uint8_t     offset;     // offset of the variable, i.e. 0 for reg[1:0], 
                            // 2 for reg[4:2]
    uint8_t     size;       // variable size - i.e. 2 for reg[1:0], 3 for reg[4:2]
    bool        readonly;   // is available for writing?
} tPcmVariable;


//==============================================================================
//  Exported data
//==============================================================================

// Default config
tPcmReg const pcm1792DefaultConfig[] = {
    { 0x10, 0xff }, // Left attenuator
    { 0x11, 0xff }, // Right attenuator
    { 0x12, 0x50 }, // 0b0101 0000 = 24bit, I2S, no deemp, no mute
    { 0x13, 0x00 }, // all default
    { 0x14, 0x08 }, // monaural mode, left channel
    { 0x15, 0x01 }  // PCMZ enabled
};

// Individual variables - not really used for now
const tPcmVariable  PcmAttenuatorL =        { 0x16, 0, 8, false };
const tPcmVariable  PcmAttenuatorR =        { 0x17, 0, 8, false };
const tPcmVariable  PcmAttenuatorLoad =     { 0x18, 7, 1, false };
const tPcmVariable  PcmAudioFormat =        { 0x18, 4, 3, false };
const tPcmVariable  PcmDeemphFreq =         { 0x18, 2, 2, false };
const tPcmVariable  PcmDeemphEnable =       { 0x18, 1, 1, false };
const tPcmVariable  PcmSoftMute =           { 0x18, 0, 1, false };
const tPcmVariable  PcmPhaseRevert =        { 0x19, 7, 1, false };
const tPcmVariable  PcmAttenuatorRate =     { 0x19, 5, 2, false };
const tPcmVariable  PcmDacEnable =          { 0x19, 4, 1, false };
const tPcmVariable  PcmDFModeSelect =       { 0x19, 2, 1, false };
const tPcmVariable  PcmDFRollof =           { 0x19, 1, 1, false };
const tPcmVariable  PcmInfZeroMute =        { 0x19, 0, 1, false };
const tPcmVariable  PcmReset =              { 0x20, 6, 1, false };
const tPcmVariable  PcmDsd =                { 0x20, 5, 1, false };
const tPcmVariable  PcmDFBypass =           { 0x20, 4, 1, false };
const tPcmVariable  PcmMono =               { 0x20, 3, 1, false };
const tPcmVariable  PcmMonoChannel =        { 0x20, 2, 1, false };
const tPcmVariable  PcmOversampleRate =     { 0x20, 0, 2, false };
const tPcmVariable  PcmDsdZeroOutputEn =    { 0x21, 1, 2, false };
const tPcmVariable  PcmPcmZeroOutputEn =    { 0x21, 0, 1, false };
const tPcmVariable  PcmZeroR =              { 0x22, 1, 1, true };
const tPcmVariable  PcmZeroL =              { 0x22, 0, 1, true };
const tPcmVariable  PcmTdmcaId =            { 0x23, 0, 5, true };


//==============================================================================
//  Exported functions
//==============================================================================


#endif // INC_PCM1792_REGS_H

