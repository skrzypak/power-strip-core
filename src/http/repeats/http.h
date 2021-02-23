#ifndef _http_h_stop_and_go_
#define _http_h_stop_and_go_

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "configs/pins.h"
#include "modes/counters/repeats/repeats.h"

void httpGetRepeats(AsyncWebServerRequest *request);
void httpInitRepeats(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
void httpDeleteRepeats(AsyncWebServerRequest *request);

#endif