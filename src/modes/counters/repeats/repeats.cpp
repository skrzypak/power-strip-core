#include "repeats.h"
#include "configs/global/PinsValue.h"

Repeats::Repeats(const SOCKET& _socket, const JsonArray& _jsonZones, const bool& _state, const int& _repeats)
{
    Serial.println("Repeats::Repeats() socket: " + String(_socket) +  " state: " + String(_state) + " repeats: " + String(_repeats)); 

    String log = "";
    serializeJson(_jsonZones, log);
    Serial.println("Repeats::Repeats(): json: " + log);

    if(_jsonZones.size() <= 0) {
        this->repeats = 0;
        return;
    }

    this->socket = _socket;
    this->repeats = _repeats;
    this->state = _state;
    this->lastZoneIndex = _jsonZones.size() - 1;
    this->infinity = this->repeats >= 0 ? false : true;

    this->zones = new int[_jsonZones.size()];
    for(int i = 0; i <= this->lastZoneIndex; i++) {
        this->zones[i] = _jsonZones[i];
        Serial.println("Repeats::Repeats() countdown: " + String(this->zones[i]) +  " zone: " + String(i)); 
    }
    
    this->currZone = 0;
    this->countdown = this->zones[this->currZone];
    gPinsValue->Write(this->socket, this->state);
    // if(this->state) digitalWrite(socketGetGpio(this->socket), HIGH);
    // else digitalWrite(socketGetGpio(this->socket), LOW);
}

SOCKET Repeats::getSocketType() {
    return socket;
}

void Repeats::update() {

    Serial.println("STOP_AND_GO socket: " + String(this->socket) +  " state: " + String(this->state) + " countdown: " + String(this->countdown) + " zone: " + String(this->currZone) + " repeats: " + String(this->repeats)); 

    this->countdown = this->countdown - 1;
    
    if(this->countdown <= 0) { 
        // Update zone index and get new socket state  
        this->currZone++;
        this->state = !this->state;
        // Check wheter currZone index is out of range
        if(this->currZone <= lastZoneIndex) {
            // Get next zone counter and update socket state
            this->countdown = this->zones[this->currZone];
            gPinsValue->Write(this->socket, this->state);
            // if(this->state) digitalWrite(socketGetGpio(this->socket), HIGH);
            // else digitalWrite(socketGetGpio(this->socket), LOW);
            return;
        } else {
            // Decremate repeats
            this->repeats--;
            // Check wheter is some no running repeats
            if(this->repeats > 0 || this->infinity == true) { 
                // Start new round repeats, set first zone
                this->currZone = 0;
                this->countdown = this->zones[this->currZone];
                gPinsValue->Write(this->socket, this->state);
                // if(this->state) digitalWrite(socketGetGpio(this->socket), HIGH);
                // else digitalWrite(socketGetGpio(this->socket), LOW);
            } // else END, object should be removed in CounterContainer::update()
            return;
        }   
    }
    
}

void Repeats::putToJson(DynamicJsonDocument& json) {
    json["counters"][String(socket)]["repeat"]["state"] = this->state;
    json["counters"][String(socket)]["repeat"]["countdown"] = this->countdown;
    json["counters"][String(socket)]["repeat"]["zone"] = this->currZone;
    json["counters"][String(socket)]["repeat"]["repeats"] = this->repeats;
    for(int i = 0; i <= this->lastZoneIndex; i++) {
        json["counters"][String(socket)]["repeat"]["zones"][i] = this->zones[i];
    }
}

bool Repeats::isToRemove()
{
    if(this->repeats > 0) return false;
    return true;
}

Repeats::~Repeats() {
    Serial.println("~Repeats()");
    delete[] this->zones;
}