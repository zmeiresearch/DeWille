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
#include "globals.h"
#include "log_sink_serial.h"

#include "driver/uart.h"    // for UART_PIN_NO_CHANGE

#include "HardwareSerial.h"

//==============================================================================
//  Defines
//==============================================================================


//==============================================================================
//  Local types
//==============================================================================

//==============================================================================
//  Local data
//==============================================================================
static HardwareSerial       serial(LOG_SERIAL_PORT);

//==============================================================================
//  Local functions
//==============================================================================


//==============================================================================
//  Exported functions
//==============================================================================

size_t LogSinkSerialGetWriteSize()
{
    return serial.availableForWrite();
}

size_t LogSinkSerialWrite(const uint8_t * const buffer, const size_t toSend)
{
    return serial.write(buffer, toSend);
}

eStatus LogSinkSerialInit()
{
    serial.begin(LOG_SERIAL_BAUD, SERIAL_8N1, LOG_SERIAL_RX_PIN, LOG_SERIAL_TX_PIN); 

    return eOK;
}


