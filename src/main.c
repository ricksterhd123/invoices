#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

void sqlite3_text_destructor(char** text)
{
    free(text);
}

// open/create file
// create tables if they don't exist
// 
int main()
{
    int result;
    sqlite3 *db = (sqlite3 *) malloc(sizeof(sqlite3 *));
    char *tableSchema = "CREATE TABLE IF NOT EXISTS contacts (contact_id INTEGER PRIMARY KEY AUTOINCREMENT, first_name TEXT NOT NULL, last_name TEXT NOT NULL, email TEXT NOT NULL UNIQUE, phone TEXT NOT NULL UNIQUE);";
    
    if (sqlite3_open("file.db", &db) == SQLITE_OK)
    {
        char *errmsg = NULL;
        sqlite3_exec(db, tableSchema, NULL, NULL, &errmsg);
        if (errmsg)
        {
            printf(errmsg);
            sqlite3_free(errmsg);
        } else {
            printf("Created table successfully...");
            char *insertStmt = "INSERT INTO contacts (contact_id, first_name, last_name, email, phone) VALUES (null, ?, ?, ?, ?);";
            char *pzTail = NULL;
            sqlite3_stmt *stmt = NULL;
            result = sqlite3_prepare_v2(db, insertStmt, -1, &stmt, NULL);
            if (result == SQLITE_OK)
            {
                char *data[] = {"John",  "Doe", "John.Doe@example.com", "123456789"};

                for (int i = 0; i < 5; i++){
                    sqlite3_bind_text(stmt, i+1, data[i], -1, SQLITE_STATIC);
                }

                if (sqlite3_step(stmt) == SQLITE_DONE && sqlite3_finalize(stmt) == SQLITE_OK)
                {
                    printf("Successfully added entry to the database");
                } else
                {
                    printf("%i", result);
                }
            } else {
                printf("Could not prepare statement err %i", result);
            }
        }
        sqlite3_close(db);
    }
    
    return 0;
}