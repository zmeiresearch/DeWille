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
#ifndef INC_GLOBALS_H
#define INC_GLOBALS_H

//==============================================================================
//  Multi-include guard
//==============================================================================
#include <stdint.h>


//==============================================================================
//  Defines
//==============================================================================
#define     LOG_SERIAL_PORT         2
#define     LOG_SERIAL_BAUD         115200
#define     LOG_SERIAL_RX_PIN       16 //UART_PIN_NO_CHANGE
#define     LOG_SERIAL_TX_PIN       17 //UART_PIN_NO_CHANGE

//==============================================================================
//  Exported types
//==============================================================================
typedef enum _eStatus
{
    eOK,
    eFAIL,
    eINVALIDARG,
    eUNSUPPORTED,
    eBUSY,
    eNOTINITIALIZED,
    eStatusCount
} eStatus;

//==============================================================================
//  Exported data
//==============================================================================

//==============================================================================
//  Exported functions
//==============================================================================

#endif // INC_GLOBALS_H
