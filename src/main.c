#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sqlite3.h"
#include "input.h"
#include "contact.h"

// open/create file
// create tables if they don't exist
// 
int main()
{
    contact* contacts = NULL;
    sqlite3 *db = (sqlite3 *) malloc(sizeof(sqlite3 *));
    assert(db);

    if (sqlite3_open("file.db", &db) == SQLITE_OK)
    {
        if (create_contact_table(db)) 
        {
            char* first_name = "John";
            char* last_name = "Doe";
            char* email_address = "John.Doe@example.com";
            char* phone_number = "07222555555";

            // test validation
            printf("%s = %i\n", email_address, is_email_address(email_address, strlen(email_address)));
            printf("%s = %i\n", phone_number, is_phone_number(phone_number, strlen(phone_number)));


            int success = add_contact(db, "John", "Doe", email_address, phone_number);
            if (success)
                printf("Added entry\n");
            
            int no_contacts = get_contacts(db, &contacts);
            if (no_contacts != -1)
            {
                //printf("%i", sizeof(contacts)/sizeof(contacts[0]));
                for (int i = 0; i < no_contacts; i++)
                {
                    printf("%i\t%s\t%s\t%s\t%s\n", contacts[i].id, contacts[i].first_name, contacts[i].last_name, contacts[i].email, contacts[i].phone_number);
                }
            }
            contacts = 0;
            free(contacts);
        } else {
            printf("Could not create table...");
        }
        sqlite3_close(db);
    }
    
    return 0;
}