#include "coin.h"

// Check if a phone number exists in the user data
int checkPhone(char receiver_ph[]){
    // Iterate through the list of users
    for(int i=0; i<g_user_count; i++){
        // Compare the provided phone number with each user's phone number
        if(stringCompare(data[i].phone_number,receiver_ph) == 1){
            // Return the user ID if a match is found
            return data[i].user_id;
        }
    }

    // Return -1 if the phone number does not exist
    return -1;
}

// Check if a phone number already exists among the users
int phoneNumberExist(char* phone_number){
    int phone_exists;
     // Check if there are no users
    if(g_user_count == 0){
        return 1;   // No users, so the phone number does not exist
    } else {
        // Iterate through the list of users
        for(int i = 0;i < g_user_count;i++){
            // Compare the provided phone number with each user's phone number
            phone_exists = stringCompare(data[i].phone_number,phone_number);
            if(phone_exists == 1){
                // Return -1 if the phone number already exists
                return -1;
            }
        }
    }
    
    // Return 1 if the phone number does not exist
    return 1;
}