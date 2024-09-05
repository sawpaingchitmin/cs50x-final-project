#include "coin.h"

void adminLogin() {
    int admin_id;   // Variable to store the logged-in admin's ID
    char admin_email[MAX_LENGTH];   // Variable to store the admin's email
    char admin_password[MAX_PASSWORD_HASH_LENGTH];  // Variable to store the admin's password

    printf("\n=== Admin Login ===\n");

    // Prompt the admin for their email
    printf("Enter Admin Email: ");
    scanf(" %[^\n]", admin_email);

    // Prompt the admin for their password
    printf("Enter Admin Password: ");
    scanf(" %[^\n]", admin_password);

    // Check the provided admin credentials
    adminLoginChecking(admin_email, admin_password);

    if (g_user_login_check != -1) {
        int admin_index = g_user_login_check;  // Store the index of the matching admin

        if (admin_index != -1) {
             printf("Reading Data...\n");
            // Admin login successful
            printf("Admin login Successful. Admin ID: %d User name: %s\n\n",
                   data[admin_index].user_id, data[admin_index].user_name);
            admin_id = data[admin_index].user_id;   // Store the admin's ID
            adminMenu(admin_id - 1);    // Navigate to the admin menu
        } else {
            // Invalid admin credentials
            printf("Invalid admin credentials\n");
        }
    } else {
        // Admin login failed
        printf("Admin login failed!\n");
    }
}

void adminMenu(int admin_id){
    while(1){
        int admin_option;   // Variable to store the admin's menu selection
        int suspend_id;     // Variable to store the ID of the user to be suspended
        int delete_id;      // Variable to store the ID of the user to be deleted

        // Display menu options to the admin
        printf("Press 1 for Suspend/un-suspend user\n");
        printf("Press 2 for Delete user\n");
        printf("Press 3 for Update password\n");
        printf("Press 4 for Logout\n");
        if (admin_id == 0)
             printf("Press 5 for Add admin\n");
        printf("Enter: ");
        scanf("%d",&admin_option);
        
        // Handle the admin's selection
        switch(admin_option){
            case 1:
                printf("Enter user ID to suspend/un-suspend:");
                scanf("%d",&suspend_id);
                suspendUser(admin_id, suspend_id -1 );  // Suspend or un-suspend the user
                break;
            case 2:
                printf("Enter user ID to delete:");
                scanf("%d",&delete_id);
                deleteUser(delete_id -1);   // Delete the user
                break;
            case 3:
                readData('a');      // Read admin data
                updatePassword(admin_id);   // Update the admin's password
                writeData('a'); // Write the updated data to the database
                break;
            case 4:
                printf("Admin logout Successfully!\n");
                return; // Log out the admin
            case 5:
                switch(admin_id) {
                    case 0:
                        readData('a');      // Read admin data
                        registration('a');  // Register a new admin
                        writeData('a');     // Write the updated data to the database
                        break;
                    default:
                        printf("Wrong option!Please try again.\n\n");
                }
                break;
            default:
                printf("Wrong option!Please try again.\n\n");
        }
    }
}

void suspendUser(int admin_id,int suspend_id){
    readData('u');  // Read user data

    // Check if the user ID is valid
    if (suspend_id >= 0 && suspend_id < g_user_count){
        data[suspend_id].suspended = !data[suspend_id].suspended;   // Toggle the suspension status
        printf("User ID %d has been %s by Admin ID %d.\n",data[suspend_id].user_id,
               data[suspend_id].suspended ? "suspended" : "un-suspended",data[admin_id].user_id);
        writeData('u'); // Write the updated data to the database
    }else{
        printf("Invalid user ID!\n\n");
    }
}

void deleteUser(int delete_id) {
    sqlite3 *db;    // SQLite database connection
    char *err_msg = 0;  // Error message variable
    char *sql;  // SQL query string
    int rc; // SQLite return code

    // Read user data
    readData('u');

    // Check if the user ID is valid
    if (delete_id >= 0 && delete_id < g_user_count) {

        printf("Deleting User ID %d...\n", data[delete_id].user_id);

        // Open the SQLite database
        rc = sqlite3_open("coin.db", &db);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
            return;
        }

        // Prepare the SQL DELETE statement for the specific user
        sql = sqlite3_mprintf("DELETE FROM users WHERE id = %d;", data[delete_id].user_id);

        // Execute the SQL DELETE statement
        rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
        } else {
            printf("User deleted from database successfully!\n");
        }

        sqlite3_free(sql);

        // Remove the user from the local array
        for (int i = delete_id; i < g_user_count - 1; i++) {
            data[i] = data[i + 1]; // Shift the user data down to fill the gap
            data[i].user_id -= 1; // Adjust the user ID
        }

        g_user_count--; // Decrement the user count

        // Clear the last user struct in the array
        memset(&data[g_user_count], 0, sizeof(account));

        // Remove all data from the users table
        sql = "DELETE FROM users;";
        rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
        }

        // Write the updated data back to the database
        writeData('u');

        // Close the database connection
        sqlite3_close(db);

    } else {
        printf("Invalid User ID!\n\n");
    }
}

void adminLoginChecking(char checkEmail[MAX_LENGTH],char checkPass[MAX_PASSWORD_HASH_LENGTH]){
    g_user_login_check = -1;    // Reset the global login check variable

    // Loop through all registered users
    for(int i = 0; i < g_user_count; i++){
        int email_check = stringCompare(data[i].user_email,checkEmail); // Compare input email with stored emails

        if(email_check == 1){   // If email matches
            // Verify the provided password with the stored hashed password
            if (crypto_pwhash_str_verify(data[i].user_password, checkPass, stringLength(checkPass)) == 0) {
                g_user_login_check = i; // Set the global variable to the index of the logged-in admin
                break;  // Exit the loop after a successful login
            } else {
                int pass_check = stringCompare(data[i].user_password,checkPass);    // Compare passwords directly
                if(pass_check == 1){
                    g_user_login_check = i;
                    break;  // Exit the loop after a successful login
                }
            }
        }
    }
}

void updatePassword(int admin_id) {
        char newPassword[MAX_LENGTH];   // Variable to store the new password
        int valid_password = 0;
        printf("\n=== Update password ===\n");

        // Loop until a valid password is provided
        while (!valid_password) {
            printf("Enter new password (at least 6 characters with uppercase, lowercase, number, and special character):");
            scanf(" %[^\n]", newPassword);

            // Check password strength
            int len = 0, has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
            while (newPassword[len] != '\0') {
                if (isUpperCase(newPassword[len])) {
                    has_upper = 1;
                } else if (isLowerCase(newPassword[len])) {
                    has_lower = 1;
                } else if (isDigit(newPassword[len])) {
                    has_digit = 1;
                } else if (isSpecialChar(newPassword[len])) {
                    has_special = 1;
                }
                len++;
            }

            // Check if the password meets the criteria
            if (len >= 6 && has_upper && has_lower && has_digit && has_special) {
                valid_password = 1; // Mark password as valid
            } else {
                printf("Invalid password! Please ensure it meets the criteria.\n");
            }
        }

        // Clear the previous password
        for(int i = 0; i < MAX_LENGTH; i++){
            data[admin_id].user_password[i] = '\0';
        }

        // Copy the new password into the user's password field
        stringCopy(data[admin_id].user_password,newPassword);
        printf("Password updated successfully!");
}
