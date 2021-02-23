#ifndef _sqlite_h_
#define _sqlite_h_

#include <sqlite3.h>
#include <SPI.h>
#include <FS.h>
#include "SPIFFS.h"
#include "configs/pins.h"
#include <ArduinoJson.h>

int db_checkExists(void *handler, int argc, char **argv, char **azColName);
int db_getJson(void *handler, int argc, char **argv, char **azColName);
int db_print(void *handler, int argc, char **argv, char **azColName);
void db_exec(sqlite3 * db, const char *sql, void * handler, int (*callback)(void *, int, char **, char **) = db_print);

int refreshTimetableCallback(void *handler, int argc, char **argv, char **azColName);

#endif