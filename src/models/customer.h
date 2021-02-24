typedef struct customer {
    int id;
    char* first_name;
    char* last_name;
    char* email;
    char* phone_number;
} customer;

int create_customer_table(sqlite3* db);
int add_customer(sqlite3* db, char* fname, char* lname, char* email, char* phone);
int del_customer(sqlite3* db, int id);
int get_customers(sqlite3* db, customer** customers);