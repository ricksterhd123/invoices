#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

int main()
{
    sqlite3 *db = (sqlite3 *) malloc(sizeof(sqlite3 *));
    char *tableSchema = "CREATE TABLE IF NOT EXISTS contacts (contact_id INTEGER PRIMARY KEY, first_name TEXT NOT NULL, last_name TEXT NOT NULL, email TEXT NOT NULL UNIQUE, phone TEXT NOT NULL UNIQUE)";
    
    if (sqlite3_open("file.db", &db) == SQLITE_OK)
    {
        char * errmsg = NULL;
        sqlite3_exec(db, tableSchema, NULL, NULL, &errmsg);
        if (errmsg)
        {
            printf(errmsg);
            sqlite3_free(errmsg);
        } else {
            printf("Created table successfully...");
        }
        sqlite3_close(db);
    }
    
    return 0;
}