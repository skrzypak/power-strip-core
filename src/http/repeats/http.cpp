#include "http.h"
#include "../../configs/global/CountersContainer.h"

void httpGetRepeats(AsyncWebServerRequest *request)
{
    Serial.println("void httpGetRepeats(AsyncWebServerRequest *request)");

    DynamicJsonDocument jsonResp(1024);

    for(int i = 0; i < 4; i++) {
        Repeats * pom = g_CountersContainer->getStopAndGo(getSocketFromInt(i));
        if(pom != nullptr) pom->putToJson(jsonResp);
    }

    String resp = "";
    serializeJson(jsonResp, resp);
    jsonResp.clear();
    request->send(200, "application/json;charset=UTF-8", resp);
}

void httpInitRepeats(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    Serial.println("void httpInitRepeats(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)");

    StaticJsonDocument<4096> jsonDoc;
    deserializeJson(jsonDoc, data);

    int success = 0;
    int err = 0;
    DynamicJsonDocument jsonResp(4096);

    String logParam = "";
    serializeJson(jsonDoc, logParam);
    Serial.println("void httpInitRepeats(): json params: " + logParam);

    for(int i = 0; i < jsonDoc.size(); i++) {
        try {
            String inx = String(i);
            SOCKET socket = getSocketFromInt(jsonDoc[inx]["socket"].as<int>());
            if(socket != SOCKET::ERR) {
                JsonArray zones = jsonDoc[inx]["zones"].as<JsonArray>();
                if(g_CountersContainer->addRepeats(socket, zones, jsonDoc[inx]["state"].as<bool>(), jsonDoc[inx]["repeats"].as<int>())) {
                    jsonResp["success"][success]["index"] = i;
                    jsonResp["success"][success]["socket"] = jsonDoc[inx]["socket"].as<int>();
                    jsonResp["success"][success]["zones"] = jsonDoc[inx]["zones"].as<JsonArray>();
                    jsonResp["success"][success]["state"] = jsonDoc[inx]["state"].as<int>();
                    jsonResp["success"][success++]["repeats"] = jsonDoc[inx]["repeats"].as<int>();
                } else {
                    jsonResp["error"][err]["index"] = i;
                    jsonResp["error"][err]["socket"] = jsonDoc[inx]["socket"].as<int>();
                    jsonResp["error"][err++]["msg"] = "Stop-and-go already exists";
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

void httpDeleteRepeats(AsyncWebServerRequest *request)
{
    Serial.println("void httpDeleteRepeats(AsyncWebServerRequest *request)");

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
                if(g_CountersContainer->removeRepeats(socket)) {
                    jsonResp["success"][success]["param"] = i;
                    jsonResp["success"][success++]["socket"] = p->value().toInt();
                } else {
                    jsonResp["error"][err]["param"] = i;
                    jsonResp["error"][err++]["msg"] = "Repeats for socket " + String(p->value().toInt()) + String(" not exists");
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
