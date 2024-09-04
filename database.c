#include "coin.h"

void initializeDatabase(sqlite3 **db) {
    char *err_msg = 0;

    // Open the SQLite database file named "coin.db"
    int rc = sqlite3_open("coin.db", db);

    // If the database fails to open, print an error message and close the database
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
        sqlite3_close(*db);
        return;
    }

    // SQL command to create the users table if it doesn't already exist
    char *sql_user = "CREATE TABLE IF NOT EXISTS users("
                     "id INT PRIMARY KEY, "
                     "username TEXT, "
                     "email TEXT, "
                     "password TEXT, "
                     "phone TEXT, "
                     "address TEXT, "
                     "postalcode TEXT, "
                     "coin INT, "
                     "suspended INT);";

    // SQL command to create the admins table if it doesn't already exist
    char *sql_admin = "CREATE TABLE IF NOT EXISTS admins("
                      "id INT PRIMARY KEY, "
                      "username TEXT, "
                      "email TEXT, "
                      "password TEXT, "
                      "phone TEXT, "
                      "address TEXT, "
                      "postalcode TEXT);";
    
    // SQL command to create the transactions table if it doesn't already exist
    char *sql_transactions = "CREATE TABLE IF NOT EXISTS transactions(" 
                             "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                             "sender_id INT, "
                             "sender_name TEXT, "
                             "receiver_id INT, "
                             "receiver_name TEXT, "
                             "coin INT, "
                             "charge INT, "
                             "time TEXT);";

    // Execute the SQL command to create the users table
    rc = sqlite3_exec(*db, sql_user, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        // If there is an error, print the error message and free the error message memory
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    // Execute the SQL command to create the admins table
    rc = sqlite3_exec(*db, sql_admin, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        // If there is an error, print the error message and free the error message memory
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    // Execute the SQL command to create the transactions table
    rc = sqlite3_exec(*db, sql_transactions, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        // If there is an error, print the error message and free the error message memory
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}
