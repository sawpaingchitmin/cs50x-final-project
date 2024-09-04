#include <sodium.h>      // For cryptographic functions
#include <sqlite3.h>     // For SQLite database functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>      // For string manipulation functions
#include <time.h>        // For time-related functions

#define MAX_LENGTH 50
#define MAX_PASSWORD_HASH_LENGTH crypto_pwhash_STRBYTES // Length of hashed password
#define MAX_USER 100

// Function prototypes
int checkPhone(char receiver_ph[]);
int emailExist(char to_check_email[MAX_LENGTH]);
int emailValid(char to_valid_email[MAX_LENGTH]);
int isDigit(char ch);
int isLowerCase(char ch);
int isPasswordHashed(const char *password);
int isSpecialChar(char ch);
int isUpperCase(char ch);
int phoneNumberExist(char* phone_number);
char* stringCharacter(char str[], char ch);
int stringCompare(char destination[MAX_LENGTH],char source[MAX_LENGTH]);
int stringLength(char array[MAX_LENGTH]);
void adminLogin();
void adminLoginChecking(char checkEmail[MAX_LENGTH],char checkPass[MAX_PASSWORD_HASH_LENGTH]);
void adminMenu(int admin_id);
void deleteUser(int delete_id);
void displayTransaction();
void initializeDatabase(sqlite3 **db);
void login();
void loginChecking(char checkEmail[MAX_LENGTH],char checkPass[MAX_LENGTH]);
void menu();
void readData(char ch);
void registration(char ch);
void stringCopy(char destination[MAX_LENGTH],char source[MAX_LENGTH]);
void suspendUser(int admin_id,int suspend_id);
void transferCoin(int sender_id, int receiver_id, int coin);
void updatePassword(int admin_id);
void updateUserInfo(int user_id);
void userInfo(int user_id);
void writeData(char ch);
void writeTransfer(int sender_id,int receiver_id, int coin);

// Structure representing a user account
typedef struct{
    int coin;
    int owner_account;
    int suspended;
    int user_id;
    char address[MAX_LENGTH];
    char phone_number[MAX_LENGTH];
    char postal_code[MAX_LENGTH];
    char user_email[MAX_LENGTH];
    char user_name[MAX_LENGTH];
    char user_password[MAX_PASSWORD_HASH_LENGTH];    
}account;

extern account data[MAX_USER];      // Array to hold user data
extern int email_validation;        // Flag for email validation
extern int g_user_count;            // Global user count
extern int g_user_login_check;      // Flag for user login check


