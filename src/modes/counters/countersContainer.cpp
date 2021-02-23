#include "countersContainer.h"

CountersContainer::CountersContainer() 
{
    for(int i=0; i < 4; i++) {
        countdown[i] = nullptr;
        repeats[i] = nullptr;
    }
}

Countdown * CountersContainer::getCountdown(const SOCKET& _socket)
{
    if(_socket == SOCKET::ERR) return nullptr;
    return countdown[_socket]; 
}

Repeats * CountersContainer::getStopAndGo(const SOCKET& _socket)
{
    if(_socket == SOCKET::ERR) return nullptr;
    return repeats[_socket];
}

bool CountersContainer::addCountdown(const SOCKET& _socket, const int& _counter, const bool& _state) {

    if(countdown[_socket] != nullptr || repeats[_socket] != nullptr) return false;

    countdown[_socket] = new Countdown(_socket, _counter, _state);

    return true;
}

bool CountersContainer::addRepeats(const SOCKET& _socket, const JsonArray& _jsonZones, const bool& _startState, const int& _repeats) {

    if(repeats[_socket] != nullptr || countdown[_socket] != nullptr) return false;

    repeats[_socket] = new Repeats(_socket, _jsonZones, _startState, _repeats);

    return true;
}

bool CountersContainer::removeCountdown(const SOCKET& _socket) {
    if(countdown[_socket] == nullptr) return false;
    delete countdown[_socket];
    countdown[_socket] = nullptr;
    return true;
}

bool CountersContainer::removeRepeats(const SOCKET& _socket) {
    if(repeats[_socket] == nullptr) return false;
    delete repeats[_socket];
    repeats[_socket] = nullptr;
    return true;
}

void CountersContainer::update() {

    if(this->truncate[trunc::countdown_enum] != true) {
        for(int i = 0; i < 4; i++) {
            if(countdown[i] != nullptr) {
                countdown[i]->update();
                if(countdown[i]->getCountdown() <= 0) {
                    delete countdown[i];
                    countdown[i] = nullptr;
                }
            }
        }
    } else this->truncateCountdown();

    if(this->truncate[trunc::repeats_enum] != true) {
        for(int i = 0; i < 4; i++) {
            if(repeats[i] != nullptr) {
                repeats[i]->update();
                if(repeats[i]->isToRemove()) {
                    delete repeats[i];
                    repeats[i] = nullptr;
                }
            }
        }
    } else this->truncateRepeats();

}

void CountersContainer::setCoundownTruncate()
{
    this->truncate[trunc::countdown_enum] = true;
}

void CountersContainer::setRepeatsTruncate()
{
    this->truncate[trunc::repeats_enum] = true;
}

void CountersContainer::setTruncate()
{
    this->truncate[trunc::countdown_enum] = true;
    this->truncate[trunc::repeats_enum] = true;
}

void CountersContainer::truncateCountdown()
{
    Serial.println("CountersContainer::truncateCountdown()");

    if(this->truncate[trunc::countdown_enum] == false) return;

    for(int i = 0; i < 4; i++) {
        if(this->countdown[i] != nullptr) {
            delete this->countdown[i];
            this->countdown[i] = nullptr;
        }
    }
    this->truncate[trunc::countdown_enum] = false;
}

void CountersContainer::truncateRepeats()
{
    Serial.println("CountersContainer::truncateRepeats()");

    if(this->truncate[trunc::repeats_enum] == false) return;

    for(int i = 0; i < 4; i++) {
        if(this->repeats[i] != nullptr) {
            delete this->repeats[i];
            this->repeats[i] = nullptr;
        }
    }
    this->truncate[trunc::repeats_enum] = false;
}

bool CountersContainer::isSocetCountdown(const SOCKET& s) {
    if(countdown[s] == nullptr) return false;
    return true;
}

bool CountersContainer::isSocetRepeatMode(const SOCKET& s) {
    if(repeats[s] == nullptr) return false;
    return true;
}