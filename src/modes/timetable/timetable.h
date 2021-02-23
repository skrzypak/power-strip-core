#ifndef _dayOfWeek_h
#define _dayOfWeek_h

#include "configs/pins.h"
#include <Arduino.h>
#include "sqlite/sqlite.h"

class Timetable {
    String id;
    SOCKET socket;
    DAY day;
    String time;
    bool state;

public:
    String getId();
    SOCKET getSocket();
    DAY getDay();
    String getTime();
    bool getState();

    bool activate();
    bool truncate();

    Timetable(String _id, SOCKET _socket, DAY _day, String __time, bool _state);
    ~Timetable();
};

#endif
