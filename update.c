#include "coin.h"

void updateUserInfo(int user_id){
    int change_option;
    // Display menu options for updating user information
    printf("Press 1 to change user name\nPress 2 to change user email\nPress 3 to change password\nPress 4 to change phone number\n");
    printf("Press 5 to change address\nPress 6 to change postal code\nPress 7 to go back user information\nEnter:");
    scanf("%d",&change_option);

    if(change_option == 1){
        // Update user name
        char newUserName[MAX_LENGTH]; 
        printf("\n=== Update user name ===\n");
        printf("Enter new user name:");
        scanf(" %[^\n]",newUserName);

        // Clear previous name
        for(int i = 0; i < MAX_LENGTH; i++){
            data[user_id].user_name[i] = '\0';
        }

        // Copy new user name
        stringCopy(data[user_id].user_name,newUserName);
        printf("User name updated successfully!");

    }

    else if(change_option == 2){
        // Update user email
        char newEmail[MAX_LENGTH];
        int email_exist = -1;
        int email_validation = -1;
        printf("\n=== Update email ===\n");

        // Loop until a valid, non-duplicate email is entered
        while(email_exist == -1 || email_validation == -1){
            printf("Enter new email:");
            scanf(" %[^\n]",newEmail);

            // Check if the email already exists
            email_exist = emailExist(newEmail);
            if(email_exist == -1){
                printf("Your email => %s <= is already register!\n",newEmail);
                continue;
            }

            // Validate the email format
            email_validation = emailValid(newEmail);
            if (email_validation == -1) {
                printf("Invalid email format. Please try again.\n");
            } 
        }

        // Reset email_validation before the next attempt
        email_validation = -1;
        
        // Clear previous email
        for(int i = 0; i < MAX_LENGTH; i++){
            data[user_id].user_email[i] = '\0';
        }

        // Copy new email
        stringCopy(data[user_id].user_email,newEmail);
        printf("Email updated successfully!");
    }

    else if(change_option == 3){
        // Update user password
        char newPassword[MAX_LENGTH];
        int valid_password = 0;
        printf("\n=== Update password ===\n");

        // Loop until a valid password is entered
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

            // Validate password based on length and character types
            if (len >= 6 && has_upper && has_lower && has_digit && has_special) {
                valid_password = 1;
            } else {
                printf("Invalid password! Please ensure it meets the criteria.\n");
            }
        }

        // Clear previous password
        for(int i = 0; i < MAX_LENGTH; i++){
            data[user_id].user_password[i] = '\0';
        }

        // Copy new password
        stringCopy(data[user_id].user_password,newPassword);
        printf("Password updated successfully!");
    }

    else if (change_option == 4) {
        // Update phone number
        char newPhone[MAX_LENGTH];
        int phone_exists = -1;
        printf("\n=== Update phone number ===\n");

        // Loop until a non-duplicate phone number is entered
        while(phone_exists == -1){
            printf("Enter new phone number:");
            scanf(" %[^\n]",newPhone);

            // Check if the phone number already exists
            phone_exists = phoneNumberExist(newPhone);
            if(phone_exists == -1){
                printf("Your phone number => %s <= is already register!\n",newPhone);
                printf("Enter new phone number!\n");
            }
        }

        // Clear previous phone number
        for(int i = 0; i < MAX_LENGTH; i++){
            data[user_id].phone_number[i] = '\0';
        }

        // Copy new phone number
        stringCopy(data[user_id].phone_number,newPhone);
        printf("Update phone number successfully!");
    }

    else if(change_option == 5){
        // Update address
        char newAddress[MAX_LENGTH];
        printf("\n=== Update address ===\n");
        printf("Enter new address:");
        scanf(" %[^\n]",newAddress);

        // Clear previous address
        for(int i = 0; i < MAX_LENGTH; i++){
            data[user_id].address[i] = '\0';
        }
        
        // Copy new address
        stringCopy(data[user_id].address,newAddress);
        printf("Update address successfully!");
    }

    else if(change_option == 6){
        // Update postal code
        char newPostalCode[MAX_LENGTH];
        printf("\n=== Update postal code ===\n");
        printf("Enter new postal code:");
        scanf(" %[^\n]",newPostalCode);

        // Clear previous postal code
        for(int i = 0; i < MAX_LENGTH; i++){
            data[user_id].postal_code[i] = '\0';
        }

        // Copy new postal code
        stringCopy(data[user_id].postal_code,newPostalCode);
        printf("Update postal code successfully!");
    }

    else if(change_option == 7){
        // Go back to the user information menu
        userInfo(user_id);
    }
    
    else{
        // Handle invalid option
        printf("\nWrong Option!Exit The Program!\n");
        exit(1);
    }
}
