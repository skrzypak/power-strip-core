#include "configs/pins.h"
#include "configs/network.h"
#include "configs/global/CountersContainer.h"
#include "configs/global/TimetableContainer.h"
#include "configs/global/DbConn.h"
#include "configs/global/PinsValue.h"

#include "http/functions.h"
#include "http/countdown/http.h"
#include "http/timetable/http.h"
#include "http/repeats/http.h"

#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

#include "sqlite/sqlite.h"

#include "functions.h"

AsyncWebServer server(80);
WiFiServer wifiServer(81);
TaskHandle_t handleCoreTask[2];

void coreZero(void * pvParameters)
{
  while (true)
  {
    g_CountersContainer->update();
    g_TimetableContainer->update();
    delay(1000);
  }
}

void jsonStringStatus(String &resp) {
  DynamicJsonDocument json(8096);
  
  json["heap"] = ESP.getFreeHeap();

  json["controller"]["0"] = String(gPinsValue->Read(SOCKET::USB));
  json["controller"]["1"] = String(gPinsValue->Read(SOCKET::FIRST));
  json["controller"]["2"] = String(gPinsValue->Read(SOCKET::SECOND));
  json["controller"]["3"] = String(gPinsValue->Read(SOCKET::THIRD));

  for(int i = 0; i < 4; i++) {

      Countdown * pom1 = g_CountersContainer->getCountdown(getSocketFromInt(i));
      if(pom1 != nullptr) {
        pom1->putToJson(json);
        continue;
      }

      Repeats * pom2 = g_CountersContainer->getStopAndGo(getSocketFromInt(i));
      if(pom2 != nullptr) {
        pom2->putToJson(json);
      }
      
  }

  serializeJson(json, resp);
  json.clear();
}

void connectToNetwork()
{
  int i = 0;
  bool success = false;

  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin(SSID, PASSWD);

  while(!success) {
    if(WiFi.status() == WL_CONNECTED) {
      success = true;
      break;
    }
    if(i == 5) {
      break;
    }
    i++;
    delay(1000);
  }

  if(success) {
    configTime(3600, 3600, "pool.ntp.org");
  } else {
    WiFi.mode(WIFI_MODE_AP);
    WiFi.softAP("PowerStrip_AP", "SecretPassword");
    int32_t unixtime = 946684800;
    timeval epoch = {unixtime, 0};
    settimeofday((const timeval*)&epoch, 0);
  }
}

void coreOne(void * pvParameters )
{

  int MAX_CLIENTS = 5;
  int NUM_CLIENTS = 0;

  SocketClient * head = nullptr;

  while (true)
  {
    if (wifiServer.hasClient()) {
      WiFiClient client = wifiServer.available();

      if(client) {
        if(NUM_CLIENTS <= MAX_CLIENTS) {

          // Check IP exists
          bool exists = false;
          SocketClient * pom = head;
          while(pom) {
            if(pom->getClient().remoteIP() == client.remoteIP()) {
              exists = true;
              break;
            }
            pom = pom->getNext();
          }

          if(exists == false) {
            SocketClient * p = new SocketClient(client, head);
            head = p;
            NUM_CLIENTS++;
            Serial.println("Client connected");
          }
        } else {
          client.print("_");
          client.stop();
        }
      }
    }

    // Send update data to clients 
    SocketClient * pom = head;
    SocketClient * prev = nullptr;
    while(pom) {
      if(pom->getClient().connected()) {
        String jsonString = "";
        jsonStringStatus(jsonString);
        pom->getClient().print(jsonString);
        prev = pom;
        pom = pom->getNext();
      } else {
        SocketClient * tmp = pom;
        tmp->getClient().stop();
        if(prev != nullptr) {
          prev->setNext(tmp->getNext());
          pom = prev->getNext();
        } else {
          // Remove HEAD
          pom = head->getNext();
          head = pom;
        }
        delete tmp;
        tmp = nullptr;
        NUM_CLIENTS--;
        Serial.println("Client disconnected");
      }
    }
  
    delay(250);
  }
}

void setup() {
  
  Serial.begin(9600);
  Serial.flush();
  Serial.clearWriteError();
  
  if (!SPIFFS.begin(true)) {
      Serial.println("Failed to mount file system, ESP.restart()");
      ESP.restart();
  }

  sqlite3_initialize();

  if (sqlite3_open("/spiffs/database.db", &g_DbConn) != SQLITE_OK) {
      Serial.println("Can't open database, ESP.restart()");
      ESP.restart();
  }

  connectToNetwork();

  if(setDatabaseAndSockets() == false) {
    Serial.println("Can't setup socets, ESP.restart()");
    ESP.restart();
  }

  server.on("/", HTTP_GET, httpGetSocketsState);

  server.on("/on", HTTP_PUT, httpChangeSocketsOn);
  server.on("/off", HTTP_PUT, httpChangeSocketsOff);

  server.on("/startup/sockets", HTTP_GET, httpGetStartupSockets);
  server.on("/startup/socket/on", HTTP_PUT, httpChangeStartupsSocketsOn);
  server.on("/startup/socket/off", HTTP_PUT, httpChangeStartupsSocketsOn);

  server.on("/countdown", HTTP_DELETE, httpDeleteCountdown);
  server.on("/countdown", HTTP_POST, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "SUCCESS");
  }, NULL, httpInitCountdown);

  server.on("/repeats", HTTP_POST, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "SUCCESS");
  }, NULL, httpInitRepeats);
  server.on("/repeats", HTTP_DELETE, httpDeleteRepeats);
  
  server.on("/timetable", HTTP_GET, httpGetTimetable);
  server.on("/timetable", HTTP_POST, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "SUCCESS");
  }, NULL, httpInitTimetable);
  server.on("/timetable", HTTP_DELETE, httpDeleteTimetable);

  server.on("/truncate", HTTP_DELETE, [](AsyncWebServerRequest *request) {
    g_CountersContainer->setTruncate();
    g_TimetableContainer->setTimetableTruncate();
    request->send(200, "text/plain", "Truncate request send to core");
  });

  server.begin();
  wifiServer.begin();

  xTaskCreatePinnedToCore(coreZero, "Sockets tasks", 10000, NULL, 1, &handleCoreTask[0], 0);
  xTaskCreatePinnedToCore(coreOne, "General tasks", 20000, NULL, 1, &handleCoreTask[1], 1);
}

void loop() {}