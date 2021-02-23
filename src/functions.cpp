#include "functions.h"
#include "configs/global/DbConn.h"
#include "configs/global/PinsValue.h"

bool setDatabaseAndSockets() {

    try {
        String q = String("CREATE TABLE dayOfWeek (")
            + String("id TEXT NOT NULL,")
            + String("socket INTEGER NOT NULL,")
            + String("day INTEGER NOT NULL,")
            + String("time TEXT NOT NULL,")
            + String("state BOOLEAN NOT NULL);");
        db_exec(g_DbConn,  const_cast<const char*>(q.c_str()), (void *)"Create new table: dayOfWeek");
    } catch (const std::runtime_error & msg) {}

    try {
        String q = String("CREATE TABLE startup (")
            + String("id INTEGER NOT NULL,")
            + String("state BOOLEAN NOT NULL);")
            + String("INSERT INTO startup (id, state) VALUES (0, 0);")
            + String("INSERT INTO startup (id, state) VALUES (1, 0);")
            + String("INSERT INTO startup (id, state) VALUES (2, 0);")
            + String("INSERT INTO startup (id, state) VALUES (3, 0);");
        db_exec(g_DbConn,  const_cast<const char*>(q.c_str()), (void *)"Create new table: startup");
    } catch (const std::runtime_error & msg) {}

    DynamicJsonDocument * startup = new DynamicJsonDocument(1024);

    try {
        db_exec(g_DbConn,  const_cast<const char*>(String("SELECT * FROM startup;").c_str()), startup, db_getJson);
        String resp = "";
        serializeJson(*startup, resp);
        Serial.println(resp);
        Serial.println("Setup sockets state startup");
        for(int i = 0; i < 4; i++) {
            if((*startup)[String(i)]["state"] == "0") {
                gPinsValue->Write(i, false);
                //digitalWrite(socketGetGpio(i), false);
            }
            else {
                gPinsValue->Write(i, true);
                //digitalWrite(socketGetGpio(i), true);
            }
        }
    } catch (const std::runtime_error& msg) {
        Serial.println("SQL: " + String(msg.what()));
        delete startup;
        
        // Serial.println("Database error, hard reset SPIFFS volume");
        // File root = SPIFFS.open("/");
        // File file = root.openNextFile();
        // while (file) {
        //     Serial.println(file.name());
        //     SPIFFS.remove(file.name());
        //     file = root.openNextFile();
        // }
        // return false;
    }

    delete startup;

    return true;
}

SocketClient::SocketClient(WiFiClient& _client, SocketClient * _next)
{
    this->client = _client;
    this->next = _next;
}

WiFiClient SocketClient::getClient()
{
    return this->client;
}

SocketClient * SocketClient::getNext()
{
    return this->next;
}

void SocketClient::setNext(SocketClient * p)
{
    this->next = p;
}