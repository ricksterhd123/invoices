#pragma once
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "sqlite3.h"
#include "customer.h"

/**
 * Description: Creates the customer table
 * Params: sqlite3* db - Database connection
 * Returns: 1 if successful, otherwise 0 and prints error message to stderr
 */
int create_customer_table(sqlite3* db)
{
    assert(db);

    char* errmsg = NULL;
    char* table_schema = "CREATE TABLE IF NOT EXISTS customers (id INTEGER PRIMARY KEY AUTOINCREMENT, first_name TEXT NOT NULL, last_name TEXT NOT NULL, email TEXT NOT NULL UNIQUE, phone TEXT NOT NULL UNIQUE, street_address TEXT NOT NULL, city TEXT NOT NULL, county TEXT NOT NULL, postcode TEXT NOT NULL);";

    sqlite3_exec(db, table_schema, NULL, NULL, &errmsg);

    if (errmsg){
        fprintf(stderr, errmsg);
        sqlite3_free(errmsg);
        return 0;
    }

    return 1;
}

//street_address TEXT NOT NULL, city TEXT NOT NULL, county TEXT NOT NULL, post_code TEXT NOT NULL
/**
 * Description: Inserts a customer into the customers table
 * Params: 
 * sqlite3* db - Database connection
 * char* fname - customer first name
 * char* lname - customer last name
 * char* email - customer email address
 * char* phone - customer phone number
 * char* street_address
 * char* city
 * char* county
 * char* postcode
 * Returns: 1 on success, 0 otherwise
 */
int add_customer(sqlite3* db, char* fname, char* lname, char* email, char* phone, char* street_address, char* city, char* county, char* postcode)
{
    sqlite3_stmt* stmt = NULL;
    char* data[] = {fname, lname, email, phone};
    char* insert_stmt = "INSERT INTO customers (id, first_name, last_name, email, phone) VALUES (null, ?, ?, ?, ?);";
    
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

int del_customer(sqlite3* db, int id)
{
    return 0;
}

/**
 * Description: Gets all customers from customers table and 
 * returns the pointer to an array of customer structs. Must free after use to avoid memory leak. 
 * Params: 
 * sqlite3* db - Database connection
 * char* fname - customer first name
 * char* lname - customer last name
 * char* email - customer email address
 * char* phone - customer phone number
 * Returns: Number of customers found, -1 error
 */
int get_customers(sqlite3* db, customer** customers)
{
    *customers = (customer*) calloc(1, sizeof(customer*));

    sqlite3_stmt* stmt = NULL;
    char* select_stmt = "SELECT * FROM customers;";

    if (sqlite3_prepare_v2(db, select_stmt, -1, &stmt, NULL) == SQLITE_OK)
    {
        int result, count;
        result = sqlite3_step(stmt);

        for (count = 0; result == SQLITE_ROW; count++) 
        {
            // extend array
            if (count+1 > ARRAY_SIZE(*customers))
            {
                *customers = (customer*) realloc(*customers, sizeof(customer*)*(count+1));
                assert(*customers);
            }

            char* fname = (char*) sqlite3_column_text(stmt, 1);
            char* lname = (char*) sqlite3_column_text(stmt, 2);
            char* email = (char*) sqlite3_column_text(stmt, 3);
            char* phone = (char*) sqlite3_column_text(stmt, 4);

            customers[count]->id = sqlite3_column_int(stmt, 0);
            customers[count]->first_name = (char*) malloc(strlen(fname)+1);
            customers[count]->last_name = (char*) malloc(strlen(lname)+1);
            customers[count]->email = (char*) malloc(strlen(email)+1);
            customers[count]->phone_number = (char*) malloc(strlen(phone)+1);

            // check for fail
            assert(customers[count]->first_name && customers[count]->last_name && \
                    customers[count]->email && customers[count]->phone_number);
            
            strcpy(customers[count]->first_name, fname);
            strcpy(customers[count]->last_name, lname);
            strcpy(customers[count]->email, email);
            strcpy(customers[count]->phone_number, phone);

            result = sqlite3_step(stmt);
        }

        if (result == SQLITE_DONE)
            return count;
        
        fprintf(stderr, "SQLite3 error code: %i", result);
        free(*customers);
    }
    return -1;
}