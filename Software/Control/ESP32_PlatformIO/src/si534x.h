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
#ifndef INC_SI534x_H
#define INC_SI534x_H

//==============================================================================
//  Multi-include guard
//==============================================================================
#include <globals.h>


//==============================================================================
//  Defines
//==============================================================================
#define SI534X_SETUP_TIME   1000    // time in ms to wait for config to be 
                                    // applied


//==============================================================================
//  Exported types
//==============================================================================
typedef enum _eSi534xType
{
    eSiTypeUnknown,
    eSi5342 = 0x5342,
    eSi5344 = 0x5344,
    eSi5345 = 0x5345
} eSi534xType;

//==============================================================================
//  Exported data
//==============================================================================

//==============================================================================
//  Exported functions
//==============================================================================
eStatus Si534xReadId(eSi534xType * const type);
eStatus Si534xListConfigs(const uint8_t maxCount, uint8_t * count, const char * configList[]);
eStatus Si534xSetConfig(const uint8_t configId);
eStatus Si534xDumpStatus();
eStatus Si534xSoftReset();

//==============================================================================
//  Module generic interface
//==============================================================================
eStatus Si534xInit(void * params);

#endif // INC_SI534x_H

