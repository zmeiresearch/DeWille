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
#include "log_sink_websocket.h"

#include "ESPAsyncWebServer.h"

//==============================================================================
//  Defines
//==============================================================================


//==============================================================================
//  Local types
//==============================================================================

//==============================================================================
//  Local data
//==============================================================================
static AsyncWebServer server(LOG_SOCKET_PORT);
static AsyncWebSocket socket("/log");

//==============================================================================
//  Local functions
//==============================================================================
void notFound(AsyncWebServerRequest *request)
{
    request->send(404);
}

void onEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, 
        AwsEventType type, void * arg, uint8_t *data, size_t len)
{
    // Nothing to do?
}

//==============================================================================
//  Exported functions
//==============================================================================

size_t LogSinkWebsocketGetWriteSize()
{
    return 1024;                // Arbitrary size, no idea how much it can handle
}

size_t LogSinkWebsocketWrite(const uint8_t * const buffer, const size_t toSend)
{
    // Cast needed as there's no const uint8_t *, size_t overload
    socket.textAll((const char* )buffer, toSend); 
    
    // No method seems to return any information on how much data was actually 
    // written, just assume everything is OK 
    return toSend;
}

eStatus LogSinkWebsocketInit()
{
    socket.onEvent(onEvent);
    server.addHandler(&socket);
    server.onNotFound(notFound);

    return eOK;
}


