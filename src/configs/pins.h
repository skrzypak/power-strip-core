#ifndef __pins_h__
#define __pins_h__

#define ORANGE 22
#define BROWN 23
#define GREEN 19
#define BLUE 26
#define NONE -1

#include <Arduino.h>

enum SOCKET { USB = 0, FIRST  = 1, SECOND  = 2, THIRD  = 3, ERR = -1};
enum DAY { SUN = 0, MON = 1, TUE = 2, WED = 3, THU = 4, FRI = 5, SAT = 6, DAY_ERR = -1};

inline int socketGetGpio(SOCKET s)
{
    switch (s)
    {
        case SOCKET::USB:       return BLUE;
        case SOCKET::FIRST:     return GREEN;
        case SOCKET::SECOND:    return ORANGE;
        case SOCKET::THIRD:     return BROWN;
        case SOCKET::ERR:       return NONE;
    }
    return NONE;
}

inline int socketGetGpio(const int& s)
{
    switch (s)
    {
        case SOCKET::USB:       return BLUE;
        case SOCKET::FIRST:     return GREEN;
        case SOCKET::SECOND:    return ORANGE;
        case SOCKET::THIRD:     return BROWN;
        case SOCKET::ERR:       return NONE;
    }
    return NONE;
}

inline int socketGetGpio(const char* s)
{
    if(strcmp(s, "0") == 0) return BLUE;
    if(strcmp(s, "1") == 0) return GREEN;
    if(strcmp(s, "2") == 0) return ORANGE;
    if(strcmp(s, "3") == 0) return BROWN;
    return NONE;
}

inline SOCKET getSocketFromInt(const int& s) {
    switch (s)
    {
        case 0: return SOCKET::USB;
        case 1: return SOCKET::FIRST;
        case 2: return SOCKET::SECOND;
        case 3: return SOCKET::THIRD;
        default: return SOCKET::ERR;
    }
    return SOCKET::ERR;
}

inline SOCKET getSocketFromChar(const char* s) {
    if(strcmp(s, "0") == 0) return SOCKET::USB;
    if(strcmp(s, "1") == 0) return SOCKET::FIRST;
    if(strcmp(s, "2") == 0) return SOCKET::SECOND;
    if(strcmp(s, "3") == 0) return SOCKET::THIRD;
    return SOCKET::ERR;
}

inline DAY charToDay(const char* val)
{
    if(strcmp(val, "0") == 0) return DAY::SUN;
    if(strcmp(val, "1") == 0) return DAY::MON;
    if(strcmp(val, "2") == 0) return DAY::TUE;
    if(strcmp(val, "3") == 0) return DAY::WED;
    if(strcmp(val, "4") == 0) return DAY::THU;
    if(strcmp(val, "5") == 0) return DAY::FRI;
    if(strcmp(val, "6") == 0) return DAY::SAT;
    return DAY::DAY_ERR;
}

#endif