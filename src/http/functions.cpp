#include "functions.h"
#include "configs/global/DbConn.h"
#include "configs/global/PinsValue.h"

void httpGetStartupSockets(AsyncWebServerRequest *request)
{
  Serial.println("void httpGetStartupSockets(AsyncWebServerRequest *request");
  DynamicJsonDocument * json = new DynamicJsonDocument(1024);
  
  try {
      db_exec(g_DbConn,  const_cast<const char*>(String("SELECT * FROM startup;").c_str()), json, db_getJson);
  } catch (const std::runtime_error& msg) {
      Serial.println("SQL error: " + String(msg.what()));
      request->send(400, "text/plain", String(msg.what()));
      return;
  }

  String resp = "";
  serializeJson(*json, resp);
  delete json;
  request->send(200, "application/json;charset=UTF-8", resp);
}

void httpChangeStartupsSocketsOn(AsyncWebServerRequest *request)
{
  Serial.println("void httpChangeStartupsSocketsOn(AsyncWebServerRequest *request)");
  
   AsyncWebParameter* p = request->getParam(0);
    try {
        if(p->isPost() != false && p->name() == "socket" && p->value() != "") {

          String q = String("UPDATE startup SET state=1 WHERE id=")
              + String(p->value())
              + String(";");
          void * handler = 0;
          db_exec(g_DbConn,  const_cast<const char*>(q.c_str()), handler, db_print);
          
          request->send(200, "application/json;charset=UTF-8", "{}");
          return;

        } else {
          request->send(400, "text/plain", "Wrong params");
          return;
        }

    } catch (const std::runtime_error& msg) {
      request->send(400, "text/plain", msg.what());
      return;
    }
}

void httpChangeStartupsSocketsOff(AsyncWebServerRequest *request)
{
  Serial.println("void httpChangeStartupsSocketsOn(AsyncWebServerRequest *request)");

  AsyncWebParameter* p = request->getParam(0);
    try {
        if(p->isPost() != false && p->name() == "socket" && p->value() != "") {

          String q = String("UPDATE startup SET state=0 WHERE id=")
              + String(p->value())
              + String(";");
          void * handler = 0;
          db_exec(g_DbConn,  const_cast<const char*>(q.c_str()), handler, db_print);
          
          request->send(200, "application/json;charset=UTF-8", "{}");
          return;

        } else {
          request->send(400, "text/plain", "Wrong params");
          return;
        }

    } catch (const std::runtime_error& msg) {
      request->send(400, "text/plain", msg.what());
      return;
    }
}

void httpGetSocketsState(AsyncWebServerRequest *request)
{
    Serial.println("void httpGetSocketsState(AsyncWebServerRequest *request)");

    DynamicJsonDocument json(1024);

    //json["0"]["state"] = String(digitalRead(socketGetGpio(SOCKET::USB)));
    // json["1"]["state"] = String(digitalRead(socketGetGpio(SOCKET::FIRST)));
    // json["2"]["state"] = String(digitalRead(socketGetGpio(SOCKET::SECOND)));
    // json["3"]["state"] = String(digitalRead(socketGetGpio(SOCKET::THIRD)));

    json["0"]["state"] = String(gPinsValue->Read(SOCKET::USB));
    json["1"]["state"] = String(gPinsValue->Read(SOCKET::FIRST));
    json["2"]["state"] = String(gPinsValue->Read(SOCKET::SECOND));
    json["3"]["state"] = String(gPinsValue->Read(SOCKET::THIRD));

    String resp = "";
    serializeJson(json, resp);
    request->send(200, "application/json;charset=UTF-8", resp);
}

void httpNotFound(AsyncWebServerRequest *request)
{
  Serial.println("void httpNotFound(AsyncWebServerRequest *request)");
  request->send(404, "text/plain", "URL no found");
}

void httpChangeSocketsOn(AsyncWebServerRequest *request)
{
  Serial.println("void httpChangeSocketsOn(AsyncWebServerRequest *request)");
  
  DynamicJsonDocument jsonResp(100);

  if(changeSocketState(request, HIGH) == false) {
    jsonResp["error"]["msg"] = "Found wrongs params, aboart()";
  }

  String resp = "";
  serializeJson(jsonResp, resp);
  request->send(200, "application/json;charset=UTF-8", resp);
}

void httpChangeSocketsOff(AsyncWebServerRequest *request)
{
  Serial.println("void httpChangeSocketsOff(AsyncWebServerRequest *request)");
  
  DynamicJsonDocument jsonResp(100);

  if(changeSocketState(request, LOW) == false) {
    jsonResp["error"]["msg"] = "Found wrongs params, aboart()";
  }

  String resp = "";
  serializeJson(jsonResp, resp);
  request->send(200, "application/json;charset=UTF-8", resp);
}

bool changeSocketState(AsyncWebServerRequest *request, int state)
{
  if(request->params() > 8) return false;

  bool tmp[4] = {false};

  for(int i=0;i<request->params();i++)
  {
      try {
        AsyncWebParameter* p = request->getParam(i);
        if(p->isPost() && p->name() == "socket" && p->value() != "" && 
          (p->value().toInt() >= 0 && p->value().toInt() <= 3)
        ) {
          tmp[p->value().toInt()] = true;
        }
        else return false;
      } catch(...) {
        return false;
      }
  }

  for(int i = 0; i < 4; i++) {
    if(tmp[i]) {
      gPinsValue->Write(i, state);
      //digitalWrite(socketGetGpio(i), state);
    }
      
  }

  return true;
}