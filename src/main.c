#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "contact.h"

// open/create file
// create tables if they don't exist
// 
int main()
{
    sqlite3 *db = (sqlite3 *) malloc(sizeof(sqlite3 *));

    if (sqlite3_open("file.db", &db) == SQLITE_OK)
    {
        if (create_contact_table(db)) 
        {
            int success = add_contact(db, "John", "Doe", "John.Doe@example.com", "123456789");
            if (success)
                printf("Added entry");
        } else {
            printf("Could not create table...");
        }
        sqlite3_close(db);
    }
    
    return 0;
}