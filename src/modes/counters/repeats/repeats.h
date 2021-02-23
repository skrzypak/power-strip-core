#ifndef _stopAndGo_h_
#define _stopAndGo_h_

#include "configs/pins.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include "sqlite/sqlite.h"

class Repeats {
    SOCKET socket;
    int * zones;
    int repeats;
    bool state;
    int countdown;
    int lastZoneIndex;
    int currZone;
    bool infinity;
public:
    Repeats(const SOCKET& _socket, const JsonArray& _jsonZones, const bool& _state, const int& _repeats);
    SOCKET getSocketType();
    void update();
    void putToJson(DynamicJsonDocument& json);
    bool isToRemove();
    ~Repeats();
};

#endif