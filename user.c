#include "coin.h"

void userInfo(int user_id){
    int m_option = -1;

    // Display the user's current coin balan
    printf("Your have: %d coin(s)\n", data[user_id].coin);
    
    // Display the menu options for the user
    printf("\n=== Choose what you want to do ===\n"
           "Press 1 for Transfer Coin to another user\nPress 2 for Display Coin Transactions record\nPress 3 for Account Information\nPress 4 for Update Account Information\nPress 5 for Logout \nPress 6 for Exit\nEnter:");
    scanf("%d",&m_option);
    
    // Option 1: Transfer coins to another user
    if(m_option == 1){
        int receiver_id, coin;
        char receiver_ph[MAX_LENGTH];

        // Prompt user to enter the receiver's phone number
        printf("Enter receiver phone number of the user:");
        scanf(" %[^\n]", receiver_ph);

        // Check if the phone number exists in the system
        receiver_id = checkPhone(receiver_ph);

        // If the phone number is valid, proceed with the coin transfer
        if(receiver_id != -1){
            printf("Enter the number of coin(s) to transfer:");
            scanf("%d", &coin);
            transferCoin(user_id, receiver_id - 1, coin);
        }else{
            // If the phone number is invalid, display an error message
            printf("This phone number is not available in our system!\n\n");
            return;
        }

    }

    // Option 2: Display the user's coin transaction record
    else if(m_option == 2){
        displayTransaction();   // Display the user's coin transaction record

        // Provide options to go back to the user information menu or exit
        printf("Press 1 to go back user information\nPress 2 to exit\nEnter: ");
        scanf("%d",&m_option);

        if(m_option == 1){
            userInfo(user_id);  // Go back to user information menu
        }
        else if(m_option == 2){
            exit(1);    // Exit the program
        }
    }

    // Option 3: Display the user's account information
    else if(m_option == 3) {
        // Display the user's account information
        printf("\nID: %d\n",data[user_id].user_id);
        printf("User name: %s\n",data[user_id].user_name);
        printf("Phone number: %s\n",data[user_id].phone_number);
        printf("Address: %s\n",data[user_id].address);
        printf("Postal code: %s\n\n",data[user_id].postal_code);

        // Provide options to go back to the user information menu or exit
        printf("Press 1 to go back user information\nPress 2 to exit\nEnter: ");
        scanf("%d",&m_option);

        if(m_option == 1){
            userInfo(user_id);  // Go back to user information menu
        }
        else if(m_option == 2){
            exit(1);    // Exit the program
        }
    }

    // Option 4: Update the user's account information
    else if(m_option == 4){
        updateUserInfo(user_id);    // Update the user's account information
        writeData('u'); // Write the updated data back to the database

        // Provide options to go back to the user information menu or exit
        printf("Press 1 to go back user information\nPress 2 to exit\nEnter: ");
        scanf("%d",&m_option);

        if(m_option == 1){
            userInfo(user_id);  // Go back to user information menu
        }
        else if(m_option == 2){
            exit(1);    // Exit the program
        }
    }

    // Option 5: Logout the user and return to the main menu
    else if(m_option == 5){
        menu(); // Return to the main menu
    }

    // Option 6: Exit the program
    else if(m_option == 6){
        exit(1);    // Exit the program
    }

    // Handle invalid menu options
    else{
        printf("\nWrong Option!Exit The program.\n");
        exit(1);    // Exit the program due to invalid input
    }
}