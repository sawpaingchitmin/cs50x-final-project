#include "coin.h"

void login(){
    char l_email[MAX_LENGTH];   // Variable to store the email entered by the user
    char l_password[MAX_PASSWORD_HASH_LENGTH];  // Variable to store the password entered by the user

    printf("\n=== This is Login ===\n");

    // Prompt user for email
    printf("Enter your email:");
    scanf(" %[^\n]",l_email);

    // Prompt user for password
    printf("Enter your password:");
    scanf(" %[^\n]",l_password);

    // Check the provided email and password
    loginChecking(l_email,l_password);

    // If login check was successful and user is not suspended
    if(g_user_login_check != -1){
        if(!data[g_user_login_check].suspended) {
            printf("Reading Data...\n");
            printf("Login Successful!\n\n");
            userInfo(g_user_login_check);   // Display user information
        }
    }else{
        printf("Login Failed!\n");  // Notify user of failed login attempt
    }
}

void loginChecking(char checkEmail[MAX_LENGTH], char checkPass[MAX_PASSWORD_HASH_LENGTH]){
    g_user_login_check = -1;    // Reset global variable for login check

    // Loop through all registered users
    for(int i = 0; i < g_user_count; i++){
        int email_check = stringCompare(data[i].user_email,checkEmail); // Compare input email with stored emails

        if(email_check == 1){   // If email matches
            // Verify the provided password with the stored hashed password
            if (crypto_pwhash_str_verify(data[i].user_password, checkPass, stringLength(checkPass)) == 0) {
                g_user_login_check = i; // Set the global variable to the index of the logged-in user

                // Check if the user is suspended
                if(data[g_user_login_check].suspended == 1){
                    printf("Sorry!You are suspended by admin.Operation not allowed.\n");
                    g_user_login_check = -1; // Reset login check
                }
                break;  // Exit the loop after a successful login
            } 
        }
    }
}