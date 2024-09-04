#include "coin.h"

// Function to read data from the database and fill the global 'data' array
void readData(char ch) {
    sqlite3 *db;    // SQLite database connection
    char *err_msg = 0;  // Error message variable
    char *sql;  // SQL query string
    sqlite3_stmt *stmt; // Prepared statement for SQL execution
    int rc; // SQLite return code

    // Open the database connection
    rc = sqlite3_open("coin.db", &db);

    if (rc != SQLITE_OK) {
        // Print an error message if the database cannot be opened
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Choose the appropriate SQL query based on the value of 'ch'
    if (ch == 'u') {
        sql = "SELECT * FROM users;";   // Query for user data
    } else if (ch == 'a'){
        sql = "SELECT * FROM admins;";  // Query for admin data
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        // Print an error message if SQL preparation fails
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    g_user_count = 0;   // Initialize user count

    // Execute the SQL statement and read the data
    while (sqlite3_step(stmt) == SQLITE_ROW) {

        if (ch == 'u') {
            // Assign user data from the database row
            data[g_user_count].user_id = sqlite3_column_int(stmt, 0);
            strncpy(data[g_user_count].user_name, (const char*)sqlite3_column_text(stmt, 1), sizeof(data[g_user_count].user_name) - 1);
            strncpy(data[g_user_count].user_email, (const char*)sqlite3_column_text(stmt, 2), sizeof(data[g_user_count].user_email) - 1);
            strncpy(data[g_user_count].user_password, (const char*)sqlite3_column_text(stmt, 3), sizeof(data[g_user_count].user_password) - 1);
            strncpy(data[g_user_count].phone_number, (const char*)sqlite3_column_text(stmt, 4), sizeof(data[g_user_count].phone_number) - 1);
            strncpy(data[g_user_count].address, (const char*)sqlite3_column_text(stmt, 5), sizeof(data[g_user_count].address) - 1);
            strncpy(data[g_user_count].postal_code, (const char*)sqlite3_column_text(stmt, 6), sizeof(data[g_user_count].postal_code) - 1);
            data[g_user_count].coin = sqlite3_column_int(stmt, 7);
            data[g_user_count].suspended = sqlite3_column_int(stmt, 8);

            g_user_count++; // Increment the user count

        } else if (ch == 'a'){
            // Assign admin data from the database row
            data[g_user_count].user_id = sqlite3_column_int(stmt, 0);
            strncpy(data[g_user_count].user_name, (const char*)sqlite3_column_text(stmt, 1), sizeof(data[g_user_count].user_name) - 1);
            strncpy(data[g_user_count].user_email, (const char*)sqlite3_column_text(stmt, 2), sizeof(data[g_user_count].user_email) - 1);
            strncpy(data[g_user_count].user_password, (const char*)sqlite3_column_text(stmt, 3), sizeof(data[g_user_count].user_password) - 1);
            strncpy(data[g_user_count].phone_number, (const char*)sqlite3_column_text(stmt, 4), sizeof(data[g_user_count].phone_number) - 1);
            strncpy(data[g_user_count].address, (const char*)sqlite3_column_text(stmt, 5), sizeof(data[g_user_count].address) - 1);
            strncpy(data[g_user_count].postal_code, (const char*)sqlite3_column_text(stmt, 6), sizeof(data[g_user_count].postal_code) - 1);

            g_user_count++; // Increment the user count
        }   
    }

    // Clean up: finalize the SQL statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

// Function to write data from the global 'data' array to the database
void writeData(char ch) {
    sqlite3 *db;
    char *err_msg = 0;
    char *sql = 0;

    // Initialize the database
    initializeDatabase(&db);

    // Initialize libsodium for password hashing
    if (sodium_init() < 0) {
        fprintf(stderr, "Failed to initialize libsodium\n");
        return;
    }

    // Check the type of data to write based on 'ch'
    if (ch == 'u') {
        printf("\nRecording User Data...\n");

        
        for (int i = 0; i < g_user_count; i++) {
            char hashed_password[MAX_PASSWORD_HASH_LENGTH];

            // Check if the password is already hashed
            if (strncmp(data[i].user_password, "$argon2id$", strlen("$argon2id$")) == 0) {
                strncpy(hashed_password, data[i].user_password, MAX_PASSWORD_HASH_LENGTH);
            } else {
                // Hash the password if it's not already hashed
                if (crypto_pwhash_str(hashed_password, data[i].user_password, 
                                      stringLength(data[i].user_password), 
                                      crypto_pwhash_OPSLIMIT_INTERACTIVE, 
                                      crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
                    fprintf(stderr, "Password hashing failed\n");
                    continue;  // Skip this user if hashing fails
                }
            }

            // Format the SQL statement to insert or replace user data
            sql = sqlite3_mprintf("INSERT OR REPLACE INTO users VALUES(%d, '%q', '%q', '%q', '%q', '%q', '%q', %d, %d);",
                                  data[i].user_id, data[i].user_name, data[i].user_email, hashed_password,
                                  data[i].phone_number, data[i].address, data[i].postal_code, data[i].coin, data[i].suspended);

            // Execute the SQL statement
            int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
            if (rc != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", err_msg); 
                sqlite3_free(err_msg);
            }
            sqlite3_free(sql);
        }
    } 

    else if (ch == 'a') {
            printf("\n\nRecording Admin Data...\n");

            for (int i = 0; i < g_user_count; i++) {
                char hashed_password[MAX_PASSWORD_HASH_LENGTH];

                // Check if the password is already hashed
                if (strncmp(data[i].user_password, "$argon2id$", strlen("$argon2id$")) == 0) {
                    strncpy(hashed_password, data[i].user_password, MAX_PASSWORD_HASH_LENGTH);
                } else {
                    // Hash the password if it's not already hashed
                    if (crypto_pwhash_str(hashed_password, data[i].user_password, 
                                        stringLength(data[i].user_password), 
                                        crypto_pwhash_OPSLIMIT_INTERACTIVE, 
                                        crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
                        fprintf(stderr, "Password hashing failed\n");
                        continue;  // Skip this admin if hashing fails
                    }
                }

                // Format the SQL statement to insert or replace admin data
                sql = sqlite3_mprintf("INSERT OR REPLACE INTO admins VALUES(%d, '%q', '%q', '%q', '%q', '%q', '%q');",
                                    data[i].user_id, data[i].user_name, data[i].user_email, hashed_password,
                                    data[i].phone_number, data[i].address, data[i].postal_code);

                // Execute the SQL statement
                int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "SQL error: %s\n", err_msg);
                    sqlite3_free(err_msg);
                }
                sqlite3_free(sql);
            }
        }

    printf("Success!\n\n");

    // Close the database connection
    sqlite3_close(db);
}

