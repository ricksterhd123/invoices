int create_contact_table(sqlite3* db);
int add_contact(sqlite3* db, char* fname, char* lname, char* email, char* phone);
int del_contact(sqlite3* db, int id);
int get_contacts(sqlite3* db, contact** contacts);