#ifndef _countersContainer_h
#define _countersContainer_h

#include "configs/pins.h"
#include <Arduino.h>
#include <ArduinoJson.h>

#include "countdown/countdown.h"
#include "repeats/repeats.h"

class CountersContainer {
private:
    enum trunc {countdown_enum = 0, repeats_enum};
    Countdown * countdown[4];
    Repeats * repeats[4];
    bool truncate[2] = {false, false};
    void truncateCountdown();
    void truncateRepeats();
public:
    CountersContainer();
    Countdown * getCountdown(const SOCKET& _socket);
    Repeats * getStopAndGo(const SOCKET& _socket);
    bool addCountdown(const SOCKET& _socket, const int& _counter, const bool& _state);
    bool addRepeats(const SOCKET& _socket, const JsonArray& _jsonZones, const bool& _startState, const int& _repeats);
    bool removeCountdown(const SOCKET& _socket);
    bool removeRepeats(const SOCKET& _socket);
    void update();
    bool isSocetCountdown(const SOCKET& s);
    bool isSocetRepeatMode(const SOCKET& s);
    void setCoundownTruncate();
    void setRepeatsTruncate();
    void setTruncate();
};

#endif