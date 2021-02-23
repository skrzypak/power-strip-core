#ifndef _http_h_day_of_week_
#define _http_h_day_of_week_

#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "sqlite/sqlite.h"

void httpGetTimetable(AsyncWebServerRequest *request);
void httpInitTimetable(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
void httpDeleteTimetable(AsyncWebServerRequest *request);

#endif