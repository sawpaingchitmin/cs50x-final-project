#include "coin.h"

void registration(char ch){
    // Variables to store registration details
    char r_userName[MAX_LENGTH];
    char r_userEmail[MAX_LENGTH];
    char r_userPassword[MAX_LENGTH];
    char r_userPhoneNumber[MAX_LENGTH];
    char r_userAddress[MAX_LENGTH];
    char r_postalCode[MAX_LENGTH];

    // Check if the maximum number of users has been reached
    if (ch == 'u') {
        if(g_user_count >= MAX_USER) {
            printf("Warning: Maximum user count reached!You can not register.\n");
            return;
        }
    }

    printf("\n=== This is Register ===\n");

    // Get user name input
    printf("Enter user name to Register:");
    scanf(" %[^\n]",r_userName);

    int email_exist = -1;
    int email_validation = -1;

    // Loop until a valid, non-duplicate email is entered
    while(email_exist == -1 || email_validation == -1){
        printf("Enter email to Register:");
        scanf(" %[^\n]",r_userEmail);

        // Check if the email already exists
        email_exist = emailExist(r_userEmail);  
        if(email_exist == -1){
            printf("Your email => %s <= is already register!\n",r_userEmail);
            continue;
        }
        
        // Validate email format
        email_validation = emailValid(r_userEmail);   
        if (email_validation == -1) {
            printf("Invalid email format. Please try again.\n");
        } 
    }

    // Reset email_validation before the next attempt
    email_validation = -1;

    // Loop to validate password
    int valid_password = 0;
    while (!valid_password) {
        printf("Enter password to Register (at least 6 characters with uppercase, lowercase, number, and special character):");
        scanf(" %[^\n]", r_userPassword);

        // Check password strength
        int len = 0, has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
        while (r_userPassword[len] != '\0') {
            if (isUpperCase(r_userPassword[len])) {
                has_upper = 1;
            } else if (isLowerCase(r_userPassword[len])) {
                has_lower = 1;
            } else if (isDigit(r_userPassword[len])) {
                has_digit = 1;
            } else if (isSpecialChar(r_userPassword[len])) {
                has_special = 1;
            }
            len++;
        }

        // Validate if the password meets all criteria
        if (len >= 6 && has_upper && has_lower && has_digit && has_special) {
            valid_password = 1;
        } else {
            printf("Invalid password! Please ensure it meets the criteria.\n");
        }
    }

    // Loop to validate phone number
    int phone_exists = -1;
    while(phone_exists == -1){
        printf("Enter phone number to Register:");
        scanf(" %[^\n]",r_userPhoneNumber);

        phone_exists = phoneNumberExist(r_userPhoneNumber);   // Check if the phone number already exists
        if(phone_exists == -1){
            printf("Your phone number => %s <= is already register!\n",r_userPhoneNumber);
            printf("Enter new phone number!\n");
        }
    }

    // Get the remaining registration details
    printf("Enter address to Register:");
    scanf(" %[^\n]",r_userAddress);

    printf("Enter postal code to Register:");
    scanf(" %[^\n]",r_postalCode);

    // Store the registration details in the data array
    data[g_user_count].user_id = g_user_count + 1;
    printf("\nID: %d",data[g_user_count].user_id);

    stringCopy(data[g_user_count].user_name,r_userName);
    printf("\nUser name: %s",data[g_user_count].user_name);

    stringCopy(data[g_user_count].user_email,r_userEmail);

    stringCopy(data[g_user_count].user_password,r_userPassword);
   
    stringCopy(data[g_user_count].phone_number,r_userPhoneNumber);
    printf("\nPhone number: %s",data[g_user_count].phone_number);

    stringCopy(data[g_user_count].address,r_userAddress);
    printf("\nAddress: %s",data[g_user_count].address);

    stringCopy(data[g_user_count].postal_code,r_postalCode);
    printf("\nPostal code: %s",data[g_user_count].postal_code);

    // Initialize user coins to 1000 if registering a new user
    if (ch == 'u') {    
        data[g_user_count].coin = 1000;
        printf("\nCoin: %d coins\n", data[g_user_count].coin);        
    }

    // Increment the global user count
    g_user_count++; 
}