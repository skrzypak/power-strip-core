#ifndef _http_h_countdown_
#define _http_h_countdown_

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "configs/pins.h"
#include "modes/counters/countdown/countdown.h"

void httpGetCountdown(AsyncWebServerRequest *request);
void httpInitCountdown(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
void httpDeleteCountdown(AsyncWebServerRequest *request);

#endif