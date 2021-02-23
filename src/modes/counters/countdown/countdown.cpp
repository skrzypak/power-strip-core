#include "countdown.h"
#include "../../../configs/global/CountersContainer.h"
#include "configs/global/PinsValue.h"

Countdown::Countdown(const SOCKET& _socket, const int& _countdown, const bool &  _state) {
    socket = _socket;
    countdown = _countdown;
    state = _state;
    gPinsValue->Write(socket, state);
    // if(state)
    //     digitalWrite(socketGetGpio(socket), HIGH);
    // else digitalWrite(socketGetGpio(socket), LOW);
}
SOCKET Countdown::getSocketType() {
    return socket;
}
int Countdown::getCountdown() {
    return countdown;
}
void Countdown::update() {
    Serial.println("COUNTDOWN socket: " + String(socket) + " state: " + String(state) + " countdown: " + String(countdown));
    countdown = countdown - 1;
}

void Countdown::putToJson(DynamicJsonDocument& json) {
    json["counters"][String(socket)]["countdown"]["time"] = String(countdown);
}

Countdown::~Countdown() {
    Serial.println("~Countdown()");
    // if(state)
    //     digitalWrite(socketGetGpio(socket), LOW);
    // else digitalWrite(socketGetGpio(socket), HIGH);
    if(state) gPinsValue->Write(socket, LOW);
    else gPinsValue->Write(socket, HIGH);
}