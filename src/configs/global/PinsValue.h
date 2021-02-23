#ifndef _global_PinsValue_h_
#define _global_PinsValue_h_

#include "../pins.h"
#include "Arduino.h"
#include "configs/pins.h"

class PinsValue
{
    bool digitalValue[4] = {false};

public:

    PinsValue()
    {
        pinMode(socketGetGpio(SOCKET::USB), OUTPUT);
        pinMode(socketGetGpio(SOCKET::FIRST), OUTPUT);
        pinMode(socketGetGpio(SOCKET::SECOND), OUTPUT);
        pinMode(socketGetGpio(SOCKET::THIRD), OUTPUT);
        pinMode(25, INPUT);   
    }


    void Write(SOCKET socket, bool value)
    {
        digitalWrite(socketGetGpio(socket), value ? HIGH : LOW);
        this->digitalValue[socket] = value;
    }

    void Write(int socket, bool value)
    {
        digitalWrite(socketGetGpio(socket), value ? HIGH : LOW);
        this->digitalValue[socket] = value;
    }

    int Read(SOCKET socket)
    {
        return this->digitalValue[socket] ? 1 : 0;
    }
};

extern PinsValue * gPinsValue;

#endif