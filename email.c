#include "coin.h"

int emailExist(char to_check_email[MAX_LENGTH]){
    int email_exist_or_not;

    // If there are no users in the system, the email cannot exist
    if(g_user_count == 0){
        return 1;  // Email does not exist
    } else {
         // Loop through all registered users to check if the email exists
        for(int i = 0;i < g_user_count;i++){
            email_exist_or_not = stringCompare(data[i].user_email,to_check_email);
            if(email_exist_or_not == 1){
                return -1;  // Email exists in the system
            }
        }
    }
    return 1;   // Email does not exist
}

int emailValid(char to_valid_email[MAX_LENGTH]) {
    // Define valid email domains
    char* valid_domains[] = {
                                "gmail.com",
                                "yahoo.com",
                                "outlook.com",
                                "hotmail.com",
                                "aol.com",
                                "icloud.com",
                                "mail.com",
                                "zoho.com",
                                "protonmail.com",
                                "yandex.com"
                            };
    int num_valid_domains = 10;  // The number of valid domains

    // Find the '@' character in the email
    char* at_position = stringCharacter(to_valid_email, '@');
    if (at_position == NULL) {
        return -1;  // '@' not found, invalid email
    }

    // Extract the domain part after the '@'
    char second_part[MAX_LENGTH];
    stringCopy(second_part, at_position + 1);  // Copy the domain part

    // Check if the domain is in the list of valid domains
    int valid_domain_found = 0;
    for (int i = 0; i < num_valid_domains; ++i) {
        if (stringCompare(second_part, valid_domains[i]) == 1) {
            valid_domain_found = 1; // Valid domain found
            break;
        }
    }

    // Return the result of the email validation
    return valid_domain_found ? 1 : -1; // 1 if valid, -1 if invalid
}