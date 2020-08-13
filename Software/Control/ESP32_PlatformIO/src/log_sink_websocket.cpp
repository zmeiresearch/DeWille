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
#include "logger.h"

#include "ESPAsyncWebServer.h"

//==============================================================================
//  Defines
//==============================================================================
#define CMP_NAME    "WS_SINK"

//==============================================================================
//  Local types
//==============================================================================

//==============================================================================
//  Local data
//==============================================================================
static bool initialized = false;
static AsyncWebServer server(LOG_SOCKET_PORT);
static AsyncWebSocket socket(LOG_SOCKET_PATH);

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
    // None of this is really needed
    if(type == WS_EVT_CONNECT)
    {
        //client connected
        Log(eLogDebug, CMP_NAME, "ws[%s][%u] connect\n", server->url(), client->id());
        client->printf("Hello Client %u :)", client->id());
        client->ping();
    } 
    else if(type == WS_EVT_DISCONNECT)
    {
        //client disconnected
        Log(eLogDebug, CMP_NAME, "ws[%s][%u] disconnect: %u\n", server->url(), client->id());
    } 
    else if(type == WS_EVT_ERROR)
    {
        //error was received from the other end
        Log(eLogDebug, CMP_NAME, "ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
    } 
    else if(type == WS_EVT_PONG)
    {
        //pong message was received (in response to a ping request maybe)
        Log(eLogDebug, CMP_NAME, "ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len)?(char*)data:"");
    } 
}

static void initTask(void * params)
{
    while (WiFi.status() != WL_CONNECTED) 
    {
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
   
    Log(eLogInfo, CMP_NAME, "Initializing log websocket on ws://%s:%d%s",
            WiFi.localIP().toString().c_str(), LOG_SOCKET_PORT, LOG_SOCKET_PATH );
    socket.onEvent(onEvent);
    server.addHandler(&socket);
    server.onNotFound(notFound);
    server.begin();

    initialized = true;
    // delete current task
    vTaskDelete(NULL);
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
    if (initialized)
    {
        // Cast needed as there's no const uint8_t *, size_t overload
        socket.textAll((const char* )buffer, toSend); 
    }
    
    // No method seems to return any information on how much data was actually 
    // written, just assume everything is OK 
    return toSend;
}

eStatus LogSinkWebsocketInit()
{
    eStatus retVal = eOK;
    TaskHandle_t    taskHandle;

    Log(eLogInfo, CMP_NAME, "LogSinkWebsocketInit()");

    xTaskCreate(initTask, 
            "Websocket Logsink init", 
            4096,   // Stack size
            NULL,   // no params
            configMAX_PRIORITIES - 1,
            &taskHandle);

    if (NULL == taskHandle)
    {
        Log(eLogWarn, CMP_NAME, "Error creating init task!");
        retVal = eFAIL;
    }
 
    return retVal;
}


