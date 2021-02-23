#ifndef _countdown_h
#define _countdown_h

#include "configs/pins.h"
#include <Arduino.h>
#include <ArduinoJson.h>

class Countdown {
    SOCKET socket;
    int countdown;
    int state;
public:
    Countdown(const SOCKET& _socket, const int& _counter, const bool& _state);
    SOCKET getSocketType();
    int getCountdown();
    void update();
    void putToJson(DynamicJsonDocument& json);
    ~Countdown();
};

#endif