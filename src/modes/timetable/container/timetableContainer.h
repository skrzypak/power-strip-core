#ifndef _timetable_h
#define _timetable_h

#include "configs/pins.h"
#include <Arduino.h>
#include "sqlite/sqlite.h"
#include "../timetable.h"

class TimetableContainer {
    Timetable * nextDOW[4] = {nullptr};
    struct tm timeInfo;
    String time;
    enum trunc {dayOfWeek = 0};
    bool truncate[1] = {false};
    bool getCompartedTime(String& time);
    void truncateDayOfWeek();
public:
    TimetableContainer();
    bool refreshTimetable(const int& socket_num);
    void update();
    bool set(const String& id, const SOCKET& socket, const DAY& day, const String& time, const bool& state);
    tm getTimeInfo();
    void setTimetableTruncate();
    ~TimetableContainer();
};

#endif
