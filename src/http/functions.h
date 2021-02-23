#ifndef _http_h_functions_
#define _http_h_functions_

#include "configs/pins.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include "sqlite/sqlite.h"

void httpGetSocketsState(AsyncWebServerRequest *request);

void httpNotFound(AsyncWebServerRequest *request);

void httpChangeSocketsOn(AsyncWebServerRequest *request);
void httpChangeSocketsOff(AsyncWebServerRequest *request);

bool changeSocketState(AsyncWebServerRequest *request, int state);

void httpGetStartupSockets(AsyncWebServerRequest *request);
void httpChangeStartupsSocketsOn(AsyncWebServerRequest *request);
void httpChangeStartupsSocketsOff(AsyncWebServerRequest *request);

#endif