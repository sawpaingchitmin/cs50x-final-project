#include "coin.h"

void displayTransaction() {
    sqlite3 *db;            // SQLite database connection
    sqlite3_stmt *stmt;     // Prepared statement for SQL execution
    // SQL query to retrieve transactions
    const char *sql = "SELECT sender_id, sender_name, receiver_id, receiver_name, coin, charge, time FROM transactions ORDER BY time DESC;";    
    int rc;     // SQLite return code                 

    // Open SQLite database
    rc = sqlite3_open("coin.db", &db);

    if (rc != SQLITE_OK) {
        // Print an error message if the database cannot be opened
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Prepare the SQL statement to retrieve transactions
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        // Print an error message if SQL preparation fails
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Execute the SQL statement and display the transactions
    printf("\n=== Coin Transactions ===\n");

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Retrieve values from the current row
        int sender_id = sqlite3_column_int(stmt, 0);                        // Sender's ID
        const unsigned char *sender_name = sqlite3_column_text(stmt, 1);    // Sender's name
        int receiver_id = sqlite3_column_int(stmt, 2);                      // Receiver's ID
        const unsigned char *receiver_name = sqlite3_column_text(stmt, 3);  // Receiver's name
        int coin = sqlite3_column_int(stmt, 4);                             // Amount of coins transferred
        int charge = sqlite3_column_int(stmt, 5);                           // Transaction charge
        const unsigned char *time = sqlite3_column_text(stmt, 6);           // Transaction time

        // Print transaction details
        printf("Transaction time: %s\n", time);
        printf("Sender ID: %d - %s is transferring %d coin(s) to %s\n",
               sender_id, sender_name, coin, receiver_name);
        printf("Receiver ID: %d - %s received %d coin(s) from %s\n",
               receiver_id, receiver_name, coin, sender_name);
        printf("Charges to sender: %d coin(s)\n\n", charge);
    }

    // Finalize the statement to clean up resources
    sqlite3_finalize(stmt);

    // Close the database connection
    sqlite3_close(db);
}
