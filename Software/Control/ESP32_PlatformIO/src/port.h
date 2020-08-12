/*==============================================================================
   DeWille ESP32 firmware

   Copyright 2020 Ivan Vasilev, Zmei Research Ltd.

   Platform-specific support functions and macros

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
#ifndef INC_PORT_H
#define INC_PORT_H

//==============================================================================
//  Multi-include guard
//==============================================================================
#include <stdint.h>

#include <Arduino.h>

//==============================================================================
//  Defines
//==============================================================================
#define PortGetTime()       (xTaskGetTickCount() * portTICK_PERIOD_MS)
#define PortSleepMs(x)      (vTaskDelay((x)/portTICK_PERIOD_MS))

//==============================================================================
//  Exported types
//==============================================================================


//==============================================================================
//  Exported data
//==============================================================================


//==============================================================================
//  Exported functions
//==============================================================================

#endif // INC_PORT_H
