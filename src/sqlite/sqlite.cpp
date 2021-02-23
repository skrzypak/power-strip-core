#include "sqlite.h"
#include "configs/global/TimetableContainer.h"

int db_checkExists(void *handler, int argc, char **argv, char **azColName)
{
    bool * exists = static_cast<bool *>(handler);
    if(argc > 1) *exists = true;
    else *exists = false;
    return 0;
}

int db_getJson(void *handler, int argc, char **argv, char **azColName)
{
    DynamicJsonDocument * json = static_cast<DynamicJsonDocument *>(handler);
    for (int i = 1; i<argc; i++){
        (*json)[argv[0]][azColName[i]] = argv[i];
    }
    return 0;
}

int db_print(void *handler, int argc, char **argv, char **azColName) {
   Serial.printf("%s: \n", (const char*)handler);
   for (int i = 0; i<argc; i++){
       Serial.printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   return 0;
}

void db_exec(sqlite3 * db, const char *sql, void * handler, int (*callback)(void *, int, char **, char **)) {
    char *errmsg = 0;
    if (sqlite3_exec(db, sql, callback, (void *)handler, &errmsg) != SQLITE_OK) {
        Serial.println(sql);
        Serial.printf("SQL err: %s \n", errmsg);
        sqlite3_free(errmsg);
        throw std::runtime_error(errmsg);
    }
}


int refreshTimetableCallback(void *handler, int argc, char **argv, char **azColName)
{
    if(argc > 1) {
        String id = argv[0];
        SOCKET socket = getSocketFromChar(argv[1]);
        DAY day = charToDay(argv[2]);
        String time = String(argv[3]);
        bool state = strcmp(argv[4], "1") == 0 ? true : false;
        g_TimetableContainer->set(id, socket, day, time, state);
    }
    return 0;
}