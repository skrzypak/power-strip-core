#ifndef _functions_h_
#define _functions_h_

#include <Arduino.h>
#include <sqlite3.h>
#include "sqlite/sqlite.h"
#include "configs/pins.h"
#include <ESPAsyncWebServer.h>

bool setDatabaseAndSockets();

class SocketClient {
    SocketClient * next;
    WiFiClient client;

public: 
    SocketClient(WiFiClient& _client, SocketClient * _next);
    WiFiClient getClient();
    SocketClient * getNext();
    void setNext(SocketClient * p);
};

#endif