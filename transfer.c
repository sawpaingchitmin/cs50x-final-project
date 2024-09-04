#include "coin.h"

void transferCoin(int sender_id, int receiver_id, int coin) {
    // Ensure the sender and receiver IDs are within valid range
    if (sender_id >= 0 && sender_id < g_user_count && receiver_id >= 0 && receiver_id < g_user_count) {

        // Check if the receiver's account is suspended
        if(data[receiver_id].suspended){
            printf("Coin(s) transfer to suspended user is not allowed!\n\n");
            return userInfo(sender_id); // Return to user info menu
        }

        // Calculate transaction charge (10% of the transferred coins)
        int transactionCharge = (coin * 10) / 100;

        // For transfers less than 10 coins, round up the transaction charge
        if (coin < 10)
            transactionCharge = (coin * 10) / 100 + 1;

        // Check if the sender has enough coins to cover the transfer and transaction charge
        if (data[sender_id].coin >= (coin + transactionCharge)) {
            data[sender_id].coin -= (coin + transactionCharge); // Deduct from sender's balance
            data[receiver_id].coin += coin;  // Add to receiver's balance

            // Assign transaction charge to the owner's account (assumed to be user 0)
            data[0].owner_account = transactionCharge;

            // Write updated user data to storage
            writeData('u'); 

            // Record the transaction in the database
            writeTransfer(sender_id,receiver_id,coin);

            // Display success message and details of the transaction
            printf("Coin(s) transferred successfully!\n\n");

            printf("Sender - %s is transferring %d Coin(s) to %s\n",data[sender_id].user_name,
                   coin,data[receiver_id].user_name);

            printf("Receiver - %s received %d Coin(s) from %s\n\n",data[receiver_id].user_name,
                   coin,data[sender_id].user_name);

            // Display transaction charge information
            printf("Transaction charge (10%%): %d Coin(s)\n\n",transactionCharge);

            // Provide options to go back to user information or exit
            int p_option;
            printf("Press 1 to go back user information\nPress 2 to exit\nEnter:");
            scanf("%d",&p_option);
            if(p_option == 1){
                userInfo(sender_id);    // Return to user info menu
            }
            else if(p_option == 2){
                exit(1);    // Exit the program
            }

        } else {
            // If the sender doesn't have enough coins, display an error
            printf("Insufficient Coin to transfer!\n\n");
            return userInfo(sender_id); // Return to user info menu
        }
    } else {
        // Handle invalid user IDs
        printf("Invalid user IDs!\n");
    }
}

void writeTransfer(int sender_id, int receiver_id, int coin) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    // Open SQLite database (create it if it doesn't exist)
    rc = sqlite3_open("coin.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Get the current time
    time_t rawTime;
    struct tm *timeInfo;
    time(&rawTime);
    timeInfo = localtime(&rawTime);

    // Format the time as a string
    char timeStr[50];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeInfo);

    // Prepare SQL statement to insert the transaction into the transactions table
    const char *sqlInsert = 
        "INSERT INTO transactions (sender_id, sender_name, receiver_id, receiver_name, coin, charge, time) "
        "VALUES (?, ?, ?, ?, ?, ?, ?);";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Bind the values to the SQL statement
    sqlite3_bind_int(stmt, 1, data[sender_id].user_id); // Sender ID
    sqlite3_bind_text(stmt, 2, data[sender_id].user_name, -1, SQLITE_STATIC);   // Sender name
    sqlite3_bind_int(stmt, 3, data[receiver_id].user_id);   // Receiver ID
    sqlite3_bind_text(stmt, 4, data[receiver_id].user_name, -1, SQLITE_STATIC); // Receiver name
    sqlite3_bind_int(stmt, 5, coin);    // Coins transferred
    sqlite3_bind_int(stmt, 6, data[0].owner_account);   // Transaction charge
    sqlite3_bind_text(stmt, 7, timeStr, -1, SQLITE_STATIC); // Transaction time

    // Execute the statement to insert the transaction
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        // Handle any errors that occur during the execution
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    // Finalize the statement to clean up resources
    sqlite3_finalize(stmt);

    // Close the database connection
    sqlite3_close(db);
}


