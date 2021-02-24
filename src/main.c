#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sqlite3.h"
#include "input.h"
#include "models/customer.h"

// open/create file
// create tables if they don't exist
// 
int main()
{
    customer* customers = NULL;
    sqlite3 *db = (sqlite3 *) malloc(sizeof(sqlite3 *));
    assert(db);

    if (sqlite3_open("file.db", &db) == SQLITE_OK)
    {
        if (create_customer_table(db)) 
        {
            char* first_name = "John";
            char* last_name = "Doe";
            char* email_address = "John.Doe@example.com";
            char* phone_number = "07222555555";

            // test validation
            printf("%s = %i\n", email_address, is_email_address(email_address, strlen(email_address)));
            printf("%s = %i\n", phone_number, is_phone_number(phone_number, strlen(phone_number)));


            int success = add_customer(db, "John", "Doe", email_address, phone_number);
            if (success)
                printf("Added entry\n");
            
            int no_customers = get_customers(db, &customers);
            if (no_customers != -1)
            {
                //printf("%i", sizeof(customers)/sizeof(customers[0]));
                for (int i = 0; i < no_customers; i++)
                {
                    printf("%i\t%s\t%s\t%s\t%s\n", customers[i].id, customers[i].first_name, customers[i].last_name, customers[i].email, customers[i].phone_number);
                }
            }
            customers = 0;
            free(customers);
        } else {
            printf("Could not create table...");
        }
        sqlite3_close(db);
    }
    
    return 0;
}