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

//==============================================================================
// Peripherals
//==============================================================================

// Debug UART
#define     LOG_SERIAL_PORT         2
#define     LOG_SERIAL_BAUD         115200
#define     LOG_SERIAL_RX_PIN       16 
#define     LOG_SERIAL_TX_PIN       17

// LEDs
#define   DO_LED_1                  2
#define   DO_LED_2                  0

// Digital Configuration Inputs 
#define   DI_CFG_1                  39
#define   DI_CFG_2                  36

// Peripheral control
#define   DO_nRST_CLK               27
#define   DO_nRST_DACR              25
#define   DO_nRST_DACL              32
#define   DO_nRST_FPGA              21

#define   DO_nFPGA_INIT             5
#define   DO_nFPGA_PROGRAM          22
//#define   DI_FPGA_DONE            1   // TODO: fix on the board

// SPI
#define   DO_nCS_CLK                26
#define   DO_nCS_DACR               33
#define   DO_nCS_DACL               35
//#define   DO_nCS_FPGA             3   // TODO: fix on the board
#define   DO_nCS_DUMMY              12  // Dummy CS to provide to the driver.

#define   SPI_MISO                  19 
#define   SPI_MOSI                  23
#define   SPI_SCLK                  18


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
