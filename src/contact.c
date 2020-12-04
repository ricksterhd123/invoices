#pragma once
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#include <assert.h>
#include <stdio.h>
#include "sqlite3.h"
#include "contact.h"

/**
 * Description: Creates the contact table
 * Params: sqlite3* db - Database connection
 * Returns: 1 if successful, otherwise 0 and prints error message to stderr
 */
int create_contact_table(sqlite3* db)
{
    assert(db);

    char* errmsg = NULL;
    char* table_schema = "CREATE TABLE IF NOT EXISTS contacts (contact_id INTEGER PRIMARY KEY AUTOINCREMENT, first_name TEXT NOT NULL, last_name TEXT NOT NULL, email TEXT NOT NULL UNIQUE, phone TEXT NOT NULL UNIQUE);";

    sqlite3_exec(db, table_schema, NULL, NULL, &errmsg);

    if (errmsg){
        fprintf(stderr, errmsg);
        sqlite3_free(errmsg);
        return 0;
    }

    return 1;
}

/**
 * Description: Inserts a contact into the contacts table
 * Params: 
 * sqlite3* db - Database connection
 * char* fname - Contact first name
 * char* lname - Contact last name
 * char* email - Contact email address
 * char* phone - Contact phone number
 * Returns: 1 on success, 0 otherwise
 */
int add_contact(sqlite3* db, char* fname, char* lname, char* email, char* phone)
{
    sqlite3_stmt* stmt = NULL;
    char* data[] = {fname, lname, email, phone};
    char* insert_stmt = "INSERT INTO contacts (contact_id, first_name, last_name, email, phone) VALUES (null, ?, ?, ?, ?);";
    
    if (sqlite3_prepare_v2(db, insert_stmt, -1, &stmt, NULL) == SQLITE_OK)
    {
        int result = SQLITE_OK;

        for (int i = 0; i < 4; i++)
        {
            result = sqlite3_bind_text(stmt, i+1, data[i], -1, SQLITE_STATIC);
            assert(result == SQLITE_OK);
        }

        return sqlite3_step(stmt) == SQLITE_DONE && sqlite3_finalize(stmt) == SQLITE_OK;
    }

    return 0;
}

int del_contact(sqlite3* db, int id)
{
    return 0;
}

/**
 * Description: Gets all contacts from contacts table and 
 * returns the pointer to an array of contact structs. Must free after use to avoid memory leak. 
 * Params: 
 * sqlite3* db - Database connection
 * char* fname - Contact first name
 * char* lname - Contact last name
 * char* email - Contact email address
 * char* phone - Contact phone number
 * Returns: 1 on success otherwise 0
 */
int get_contacts(sqlite3* db, contact** contacts)
{
    *(contacts) = (contact*) malloc(sizeof(contact));

    sqlite3_stmt* stmt = NULL;
    char* select_stmt = "SELECT * FROM contacts;";

    if (sqlite3_prepare_v2(db, select_stmt, -1, &stmt, NULL) == SQLITE_OK)
    {
        int result = sqlite3_step(stmt);
        for (int count = 1; result == SQLITE_ROW; count++) 
        {
            // extend array
            if (count > ARRAY_SIZE(*contacts))
            {
                *(contacts) = (contact*) realloc(*contacts, sizeof(contact)*count);
                assert(*contacts);
            }

            contacts[count-1]->id = sqlite3_column_int(stmt, 0);
            contacts[count-1]->first_name = sqlite3_column_text(stmt, 1);
            contacts[count-1]->last_name = sqlite3_column_text(stmt, 2);
            contacts[count-1]->email = sqlite3_column_text(stmt, 3);
            contacts[count-1]->phone_number = sqlite3_column_text(stmt, 4);
            result = sqlite3_step(stmt);
        }
        if (result == SQLITE_DONE)
            return 1;
        
        fprintf(stderr, "SQLite3 error code: %i", result);
        free(*contacts);
    }
    return 0;
}