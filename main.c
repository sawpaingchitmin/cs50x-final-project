#include "coin.h"       // Include the header file with function prototypes and structure definitions

account data[MAX_USER]; // Global array to store account information for up to MAX_USER accounts

// Global variables
int email_validation = -1;
int g_user_count = 0;
int g_user_login_check = -1;

int main(){

    menu();     // Call the menu function to start the program

    return 0;   // Return 0 to indicate successful completion
}

void menu(){

    // Infinite loop to keep the menu active until the user exits
    while(1){
        int option = 0; // Variable to store the user's menu choice

        // Display the menu options to the user
        printf("\n=== Welcome to COIN ===\nChoose your option:\n");
        printf("Press 1 for User Login\nPress 2 for Register\nPress 3 for Admin Login\nPress 4 for Exit\nEnter:");
        scanf("%d", &option);   // Read the user's choice from input
        
         // Handle the user's choice
        if(option == 1){
            readData('u');  // Read user-specific data
            login();        // Call the login function for users   
        }

        else if(option == 2){
            readData('u');      // Read user-specific data
            registration('u');  // Call the registration function for users
            writeData('u');     // Write user data to database
        }

        else if(option == 3){
            readData('a');    // Read admin-specific data
            adminLogin();     // Call the admin login function
        }

        else if(option == 4){
            exit(1);    // Exit the program
        }
        else{
            // Handle invalid menu options
            printf("\nWrong option!Exit the program!\n");
            exit(1);
        }

    }
}




