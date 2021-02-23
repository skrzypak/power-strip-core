#include "http.h"
#include "configs/global/CountersContainer.h"

void httpGetCountdown(AsyncWebServerRequest *request)
{
    Serial.println("void countdown::httpGetCountdown(AsyncWebServerRequest *request)");
      
    DynamicJsonDocument jsonResp(1024);

    for(int i = 0; i < 4; i++) {
        Countdown * pom = g_CountersContainer->getCountdown(getSocketFromInt(i));
        if(pom != nullptr) pom->putToJson(jsonResp);
    }

    String resp = "";
    serializeJson(jsonResp, resp);
    jsonResp.clear();
    request->send(200, "application/json;charset=UTF-8", resp);
}

void httpInitCountdown(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    Serial.println("void countdown::httpInitCountdown(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)");

    StaticJsonDocument<200> jsonDoc;
    deserializeJson(jsonDoc, data);

    int success = 0;
    int err = 0;
    DynamicJsonDocument jsonResp(1024);

    for(int i = 0; i < jsonDoc.size(); i++) {
        try {
            String inx = String(i);
            SOCKET socket = getSocketFromInt(jsonDoc[inx]["socket"].as<int>());
            if(socket != SOCKET::ERR) {
                if(g_CountersContainer->addCountdown(socket, jsonDoc[inx]["countdown"].as<int>(), jsonDoc[inx]["state"].as<bool>())) {
                    jsonResp["success"][success]["index"] = i;
                    jsonResp["success"][success]["socket"] = jsonDoc[inx]["socket"].as<int>();
                    jsonResp["success"][success]["countdown"] = jsonDoc[inx]["countdown"].as<int>();
                    jsonResp["success"][success++]["state"] = jsonDoc[inx]["state"].as<int>();
                } else {
                    jsonResp["error"][err]["index"] = i;
                    jsonResp["error"][err]["socket"] = jsonDoc[inx]["socket"].as<int>();
                    jsonResp["error"][err++]["msg"] = "Countdown already exists";
                }
            } else {
                jsonResp["error"][err]["index"] = i;
                jsonResp["error"][err]["socket"] = jsonDoc[inx]["socket"].as<int>();
                jsonResp["error"][err++]["msg"] = "Wrong socket value";
            }
        } catch(...) {
            jsonResp["error"][err++]["fatal"] = i;
            continue;
        }
    }

    String resp = "";
    serializeJson(jsonResp, resp);
    request->send(200, "application/json;charset=UTF-8", resp);
}

void httpDeleteCountdown(AsyncWebServerRequest *request)
{
    Serial.println("void countdown::httpDeleteCountdown(AsyncWebServerRequest *request)");

    int success = 0;
    int err = 0;
    DynamicJsonDocument jsonResp(1024);

    for(int i=0;i<request->params();i++)
    {
        AsyncWebParameter* p = request->getParam(i);
        if(p->isPost() == false) {
            jsonResp["error"][err]["param"] = i;
            jsonResp["error"][err++]["msg"] = "No send via POST";
            continue;
        }
        if(p->name() != "socket") {
            jsonResp["error"][err]["param"] = i;
            jsonResp["error"][err++]["msg"] = "Wrong param name: " + p->name();
            continue;
        }
        if(p->value() == "") {
            jsonResp["error"][err]["param"] = i;
            jsonResp["error"][err++]["msg"] = "Empty socket value";
            continue;
        }
        if(p->value().toInt() >= 0 && p->value().toInt() <= 3) {
            try {
                SOCKET socket = getSocketFromInt(p->value().toInt());
                if(g_CountersContainer->removeCountdown(socket)) {
                    jsonResp["success"][success]["param"] = i;
                    jsonResp["success"][success++]["socket"] = p->value().toInt();
                } else {
                    jsonResp["error"][err]["param"] = i;
                    jsonResp["error"][err++]["msg"] = "Countdown for socket " + String(p->value().toInt()) + String(" not exists");
                }
            } catch(...) {
                jsonResp["error"][err++]["fatal"] = i;
            }
        } else {
            jsonResp["error"][err]["param"] = i;
            jsonResp["error"][err++]["msg"] = "Invalid socket value: " + String(p->value().toInt());
        }
    }

    String resp = "";
    serializeJson(jsonResp, resp);
    request->send(200, "application/json;charset=UTF-8", resp);
}