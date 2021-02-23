#include "timetable.h"
#include "configs/global/TimetableContainer.h"
#include "configs/global/DbConn.h"
#include "configs/global/PinsValue.h"

Timetable::Timetable(String _id, SOCKET _socket, DAY _day, String _time, bool _state) 
{
    this->id = _id;
    this->socket = _socket;
    this->day = _day;
    this->time = _time;
    this->state = _state;

    Serial.printf("Timetable::Timetable(): socket -> %s, state -> %s, time -> %s \n", String(this->socket).c_str(), String(this->state).c_str(), String(this->time).c_str());
}

bool Timetable::activate()
{
    Serial.println("================================================");
    Serial.printf("Timetable::activate(): socket -> %s, state -> %s, time -> %s \n", String(this->socket).c_str(), String(this->state).c_str(), String(this->time).c_str());
    Serial.println("================================================");
    
    gPinsValue->Write(this->socket, this->state);

    // if(this->state)
    //     digitalWrite(socketGetGpio(this->socket), HIGH);
    // else digitalWrite(socketGetGpio(this->socket), LOW);
    
    return true;
}

String Timetable::getId()
{
    return this->id;
}

SOCKET Timetable::getSocket()
{
    return this->socket;
}

DAY Timetable::getDay()
{
    return this->day;
}

String Timetable::getTime()
{
    return this->time;
}

bool Timetable::getState()
{
    return this->state;
}

Timetable::~Timetable()
{
    Serial.printf("Timetable::~Timetable(): socket -> %s, state -> %s, time -> %s \n", String(this->socket).c_str(), String(this->state).c_str(), String(this->time).c_str());

}
