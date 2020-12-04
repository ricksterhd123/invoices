#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "contact.h"

// open/create file
// create tables if they don't exist
// 
int main()
{
    contact* contacts = NULL;
    sqlite3 *db = (sqlite3 *) malloc(sizeof(sqlite3 *));

    if (sqlite3_open("file.db", &db) == SQLITE_OK)
    {
        if (create_contact_table(db)) 
        {
            int success = add_contact(db, "John", "Doe", "John.Doe@example.com", "123456789");
            if (success)
                printf("Added entry");
                
            if (get_contacts(db, &contacts))
            {
                printf("%i", sizeof(contacts)/sizeof(contacts[0]));
                // for (int i = 0; i < ; i++)
                // {
                //     printf("%i\t%s\t%s\t%s\t%s\n", contacts[i].id, contacts[i].first_name, contacts[i].last_name, contacts[i].email, contacts[i].phone_number);
                // }
            }
        } else {
            printf("Could not create table...");
        }
        sqlite3_close(db);
    }
    
    return 0;
}