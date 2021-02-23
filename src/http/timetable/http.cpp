#include "http.h"
#include "configs/global/TimetableContainer.h"
#include "configs/global/DbConn.h"

void httpGetTimetable(AsyncWebServerRequest *request)
{
    Serial.println("void httpGetTimetable(AsyncWebServerRequest *request)");
    DynamicJsonDocument * jsonResp = new DynamicJsonDocument(1024);

    try {
        db_exec(g_DbConn,  const_cast<const char*>(String("SELECT * FROM dayOfWeek ORDER BY socket, day, time DESC;").c_str()), jsonResp, db_getJson);
    } catch (const std::runtime_error& msg) {
        (*jsonResp)["error"]["msg"] = "SQL error: " + String(msg.what());
    }
    
    String resp = "";
    serializeJson(*jsonResp, resp);
    delete jsonResp;
    request->send(200, "application/json;charset=UTF-8", resp);
}

void httpInitTimetable(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    Serial.println("void httpInitTimetable(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)");

    StaticJsonDocument<200> jsonDoc;
    deserializeJson(jsonDoc, data);
    
    int success = 0;
    int err = 0;
    DynamicJsonDocument jsonResp(1024);

    for(int i = 0; i < jsonDoc.size(); i++) {
        try {

            time_t now;
            time(&now);
            String id = static_cast<String>(now);

            String inx = String(i);

            // Check whether is some duplicats with same socket, day and time
            try {
                String q = String("SELECT * FROM dayOfWeek WHERE socket=")
                + String(jsonDoc[inx]["socket"].as<int>())
                + String(" AND day=") + String(jsonDoc[inx]["day"].as<int>())
                + String(" AND time='") + String(jsonDoc[inx]["time"].as<String>()) + String("';");
                
                bool handler = false;
                db_exec(g_DbConn,  const_cast<const char*>(q.c_str()), &handler, db_checkExists);

                if(handler == true) {
                    jsonResp["error"][err]["index"] = i;
                    jsonResp["error"][err++]["msg"] = "This socket, day and time already exists in database";
                    continue;
                }

            } catch (const std::runtime_error& msg) {
                jsonResp["error"][err]["index"] = i;
                jsonResp["error"][err++]["msg"] = "SQL error: " + String(msg.what());
                continue;
            }

            try {
                String q = String("INSERT INTO dayOfWeek (id, socket, day, time, state) VALUES (")
                + String("'") + String(id) + String("',")
                + String(jsonDoc[inx]["socket"].as<int>()) + String(",")
                + String(jsonDoc[inx]["day"].as<int>()) + String(",")
                + String("'") + String(jsonDoc[inx]["time"].as<String>()) + String("',")
                + String(jsonDoc[inx]["state"].as<int>()) + String(");");

                void * handler = 0;
                db_exec(g_DbConn,  const_cast<const char*>(q.c_str()), handler, db_print);

                if(!g_TimetableContainer->refreshTimetable(jsonDoc[inx]["socket"].as<int>())) {
                    jsonResp["error"][err]["index"] = i;
                    jsonResp["error"][err++]["msg"] = "Can't refresh timetable";
                    continue;
                }

                jsonResp["success"][success]["index"] = i;
                jsonResp["success"][success]["id"] = id;
                jsonResp["success"][success]["socket"] = jsonDoc[inx]["socket"].as<int>();
                jsonResp["success"][success]["day"] = jsonDoc[inx]["day"].as<int>();
                jsonResp["success"][success]["time"] = jsonDoc[inx]["time"].as<String>();
                jsonResp["success"][success++]["state"] = jsonDoc[inx]["state"].as<int>();

            } catch (const std::runtime_error& msg) {
                jsonResp["error"][err]["index"] = i;
                jsonResp["error"][err++]["msg"] = "SQL error: " + String(msg.what());
                continue;
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

void httpDeleteTimetable(AsyncWebServerRequest *request)
{
    Serial.println("void httpDeleteTimetable(AsyncWebServerRequest *request)");

    int success = 0;
    int err = 0;
    DynamicJsonDocument jsonResp(1024);

    for(int i=0;i<request->params();i++)
    {
        AsyncWebParameter* p = request->getParam(i);
        try {
            if(p->isPost() == false) {
                jsonResp["error"][err]["param"] = i;
                jsonResp["error"][err++]["msg"] = "No send via POST";
                continue;
            }
            if(p->name() != "id") {
                jsonResp["error"][err]["param"] = i;
                jsonResp["error"][err++]["msg"] = "Wrong param name: " + p->name();
                continue;
            }
            if(p->value() == "") {
                jsonResp["error"][err]["param"] = i;
                jsonResp["error"][err++]["msg"] = "Empty ID value";
                continue;
            }
            String q = String("DELETE FROM dayOfWeek WHERE id='")
                + String(p->value())
                + String("';");
            void * handler = 0;
            db_exec(g_DbConn,  const_cast<const char*>(q.c_str()), handler, db_print);

            jsonResp["success"][success]["param"] = i;
            jsonResp["success"][success++]["id"] = p->value();

        } catch (const std::runtime_error& msg) {
            jsonResp["error"][err]["param"] = i;
            jsonResp["error"][err++]["msg"] = "SQL error: " + String(msg.what());
            continue;
        }
    }

    String resp = "";
    serializeJson(jsonResp, resp);
    request->send(200, "application/json;charset=UTF-8", resp);
}