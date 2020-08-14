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
    { 16, 0xff }, // Left attenuator
    { 17, 0xff }, // Right attenuator
    { 18, 0x50 }, // 0b0101 0000 = 24bit, I2S, no deemp, no mute
    { 19, 0x00 }, // all default
    { 20, 0x08 }, // monaural mode, left channel
    { 21, 0x01 }  // PCMZ enabled
};

// Individual variables - not really used for now
const tPcmVariable  PcmAttenuatorL =        { 16, 0, 8, false };
const tPcmVariable  PcmAttenuatorR =        { 17, 0, 8, false };
const tPcmVariable  PcmAttenuatorLoad =     { 18, 7, 1, false };
const tPcmVariable  PcmAudioFormat =        { 18, 4, 3, false };
const tPcmVariable  PcmDeemphFreq =         { 18, 2, 2, false };
const tPcmVariable  PcmDeemphEnable =       { 18, 1, 1, false };
const tPcmVariable  PcmSoftMute =           { 18, 0, 1, false };
const tPcmVariable  PcmPhaseRevert =        { 19, 7, 1, false };
const tPcmVariable  PcmAttenuatorRate =     { 19, 5, 2, false };
const tPcmVariable  PcmDacEnable =          { 19, 4, 1, false };
const tPcmVariable  PcmDFModeSelect =       { 19, 2, 1, false };
const tPcmVariable  PcmDFRollof =           { 19, 1, 1, false };
const tPcmVariable  PcmInfZeroMute =        { 19, 0, 1, false };
const tPcmVariable  PcmReset =              { 20, 6, 1, false };
const tPcmVariable  PcmDsd =                { 20, 5, 1, false };
const tPcmVariable  PcmDFBypass =           { 20, 4, 1, false };
const tPcmVariable  PcmMono =               { 20, 3, 1, false };
const tPcmVariable  PcmMonoChannel =        { 20, 2, 1, false };
const tPcmVariable  PcmOversampleRate =     { 20, 0, 2, false };
const tPcmVariable  PcmDsdZeroOutputEn =    { 21, 1, 2, false };
const tPcmVariable  PcmPcmZeroOutputEn =    { 21, 0, 1, false };
const tPcmVariable  PcmZeroR =              { 22, 1, 1, true };
const tPcmVariable  PcmZeroL =              { 22, 0, 1, true };
const tPcmVariable  PcmTdmcaId =            { 23, 0, 5, true };


//==============================================================================
//  Exported functions
//==============================================================================


#endif // INC_PCM1792_REGS_H

