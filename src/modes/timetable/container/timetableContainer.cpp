#include "timetableContainer.h"
#include "configs/global/DbConn.h"

TimetableContainer::TimetableContainer()
{
    Serial.println("TimetableContainer::TimetableContainer()");
    for(int i = 0; i < 4; i++)
        this->nextDOW[i] = nullptr;
}

bool TimetableContainer::refreshTimetable(const int& socket_num)
{
    Serial.println("TimetableContainer::refreshTimetable(): socket -> " + String(socket_num));

    if(socket_num < 0 || socket_num > 3) return false;

    try {
        String q = String("SELECT * FROM dayOfWeek WHERE time >= '")
        + String(this->time)
        + String("' AND day=")
        + String(this->timeInfo.tm_wday)
        + String(" AND socket=")
        + String(socket_num)
        + String(" ORDER BY time LIMIT 1;");
        db_exec(g_DbConn,  const_cast<const char*>(q.c_str()), (void*)"Getting next Timetable value from database", refreshTimetableCallback);
    } catch (const std::runtime_error& msg) {
        return false;
    }
    
    return true;
}

bool TimetableContainer::set(const String& id, const SOCKET& socket, const DAY& day, const String& time, const bool& state)
{
    Serial.println("TimetableContainer::set(): id -> " + id);

    if(time < this->time) {
        Serial.println("No set new timetable object, earlier time detect");
        return false;
    }

    Timetable * newDOW = new Timetable(id, socket, day, time, state);
    if(newDOW->getTime() == this->time) {
        // Current time so activate
        newDOW->activate();
        delete newDOW;
        return false;
    }

    if(this->nextDOW[socket] == nullptr) {
        this->nextDOW[socket] = newDOW;
        Serial.println("Set new timetable object");
        return true;
    }

    if(this->nextDOW[socket]->getId() != id) {
        delete this->nextDOW[socket];
        this->nextDOW[socket] = newDOW;
        Serial.println("Set new timetable object");
        return true;
    } 

    Serial.println("No set new timetable object");

    return false;
}

void TimetableContainer::update()
{
    String time = "";

    if(this->truncate[dayOfWeek] == true) {
        this->truncateDayOfWeek();
        return;
    }

    if(!getCompartedTime(time)) return;
    if(time == this->time) return;

    this->time = time;

    Serial.println("#####################################################");
    Serial.println("TimetableContainer::update(): time -> " + this->time);

    for(int i = 0; i < 4; i++) {

        // Guard
        if (this->nextDOW[i] != nullptr &&  this->nextDOW[i]->getTime() < this->time) {
            delete this->nextDOW[i];
            this->nextDOW[i] = nullptr;
        }

        if(this->nextDOW[i] == nullptr) {
            refreshTimetable(i);
        }

        if(this->nextDOW[i] != nullptr && this->nextDOW[i]->getDay() == this->timeInfo.tm_wday) {
            if(this->nextDOW[i]->getTime() == this->time) {
                this->nextDOW[i]->activate();
                delete this->nextDOW[i];
                this->nextDOW[i] = nullptr;
                continue;
            }
            else {
                Serial.println("================================================");
                Serial.printf("Queue: socket -> %s, state -> %s, time -> %s \n", String(this->nextDOW[i]->getSocket()).c_str(), String(this->nextDOW[i]->getState()).c_str(), String(this->nextDOW[i]->getTime()).c_str());
                Serial.println("================================================");
                continue;
            }
        }

    }
}

bool TimetableContainer::getCompartedTime(String& time)
{
    time = "";

    if(!getLocalTime(&(this->timeInfo))){
        Serial.println("Failed to obtain time");
        return false;
    }

    if(this->timeInfo.tm_hour < 10)
        time += "0";
    
    time += String(this->timeInfo.tm_hour);
    time += ":";
    
    if(this->timeInfo.tm_min < 10) 
        time += "0";
    time += String(this->timeInfo.tm_min);

    return true;
}

tm TimetableContainer::getTimeInfo() 
{
    return this->timeInfo;
}

void TimetableContainer::setTimetableTruncate() {
    this->truncate[trunc::dayOfWeek] = true;
    for(int i = 0; i < 4; i++) {
        if(this->nextDOW[i] != nullptr) {
            delete this->nextDOW[i];
            this->nextDOW[i] = nullptr;
        }
    }
}

void TimetableContainer::truncateDayOfWeek() {
    
    Serial.println("void TimetableContainer::truncateDayOfWeek()");

    if(this->truncate[trunc::dayOfWeek] == false) return;

    try {
        String q = String("DELETE FROM dayOfWeek;");
        db_exec(g_DbConn,  const_cast<const char*>(q.c_str()), (void*)"Truncate dayOfWeek table");
    } catch (const std::runtime_error& msg) {
        Serial.println(msg.what());
    }

    for(int i = 0; i < 4; i++) {
        if(this->nextDOW[i] != nullptr) {
            delete this->nextDOW[i];
            this->nextDOW[i] = nullptr;
        }
    }

    this->truncate[trunc::dayOfWeek] = false;
}

TimetableContainer::~TimetableContainer()
{
    Serial.println("TimetableContainer::~TimetableContainer()");
    for(int i = 0; i < 4; i++) {
        delete this->nextDOW[i];
        this->nextDOW[i] = nullptr;
    }
}