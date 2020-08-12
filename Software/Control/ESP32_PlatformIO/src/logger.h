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
#ifndef INC_LOGGER_H
#define INC_LOGGER_H

//==============================================================================
//  Multi-include guard
//==============================================================================
#include "globals.h"


//==============================================================================
//  Defines
//==============================================================================


//==============================================================================
//  Exported types
//==============================================================================
typedef enum _eLogLevel
{
    eLogDebug,
    eLogInfo,
    eLogWarn,
    eLogError,
    eLogCrit,
    eLogLevelCount,
} eLogLevel;

// Function pointers to different log sinks. Would've been cleaner with an 
// interface, but I want to keep it as C as possible
typedef eStatus (*LogSinkInitFn)();
typedef size_t  (*LogSinkGetWriteSizeFn)();
typedef size_t  (*LogSinkWriteFn)(const uint8_t * const buffer, const size_t toSend);

typedef struct _LogSink
{
    const char*             Name;
    LogSinkInitFn           Init;
    LogSinkGetWriteSizeFn   GetWriteSize;
    LogSinkWriteFn          Write;
} LogSink;

//==============================================================================
//  Exported data
//==============================================================================

//==============================================================================
//  Exported functions
//==============================================================================
eStatus Log(const eLogLevel level, const char * const component, ...);
eStatus LogSetMinLevel(const eLogLevel level);

//==============================================================================
//  Module generic interface
//==============================================================================
eStatus LogInit(void * params);
eStatus LogLoop();

#endif // INC_LOGGER_H
