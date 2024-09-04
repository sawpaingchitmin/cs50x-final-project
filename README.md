# PROJECT TITLE - COIN

## Video Demo:  https://youtu.be/0ZnSz0qCxVE

## Operating System: Linux Ubuntu

## Installation
1. **Install GCC compiler:**
    - sudo apt install gcc

2. **Install SQLite3:**
    - sudo apt install sqlite3

3. **Install libsodium:**
    - sudo apt install libsodium-dev

## Compile the Project:
- gcc main.c transaction.c registration.c admin.c update.c email.c user.c phone.c login.c readWrite.c function.c transfer.c database.c -lsqlite3 -lsodium -o coin

## Run the Application:
- ./coin

## Description
**COIN** is a C-based coin management system that allows users to log in, register, transfer coins, and manage their accounts securely. Admins have full control over user accounts, including the ability to suspend, unsuspend, or delete users.

### User Role:
- If a user does not have an account, they must register to log in. During registration, users can choose from one of 10 different email domains:
    - `gmail.com`
    - `yahoo.com`
    - `outlook.com`
    - `hotmail.com`
    - `aol.com`                                                                                                                               
    - `icloud.com`
    - `mail.com`
    - `zoho.com`
    - `protonmail.com`
    - `yandex.com`                          
                                                                                                        
- Users cannot use an existing email or phone number in the database to register.

- Passwords must be at least 6 characters long and include an uppercase letter, a lowercase letter, a number, and a special character. Passwords are securely hashed before being stored in the database.    

- After successful registration, the user’s information is displayed, including the amount of coins they receive, but excluding their email and password. Their information is stored in the `users` table in `coin.db`.

- The `coin.db` database consists of three tables: `admins`, `transactions`, and `users`. 

- Ensure to include `<sodium.h>` to hash passwords and `<sqlite3.h>` to use the SQLite3 database. 

### Logging In:
- Users must log in using their email and password. Upon successful login, users are granted 1000 coins and can choose from several operations:

1. **Transfer Coins:**
    - Users can transfer coins to another user by correctly entering the recipient's phone number. A 10% transaction fee is applied to the sender. If the transfer amount is below 10 coins, the transaction fee will still be 1 coin.

    - After the transfer, the successful transaction details are displayed, and the transaction is stored in the `transactions` table.

2. **Display Transactions:**
    - Users can view their transaction history.

3. **Account Information:**
    - Users can view their account details, excluding their email and password.

4. **Update Information:**
    - Users can update their personal information one field at a time.

5. **Logout:**
    - Users can log out of their account.

6. **Exit:**
    - Users can exit the program.

### Admin Role:
Admins can control user accounts by suspending, unsuspending, or deleting them.

- To use admin functions, an admin account is required. The first admin must be manually added to the `admins` table via an SQL command. 
#### Example:
**INSERT INTO admins (id, username, email, password, phone, address, postalcode)** 
**VALUES (1, 'michael', 'michael@yahoo.com', 'Michael123!', '09555444333', 'michael street', '1234');**

- Initially, the password is stored in plain text. The admin should log in and update the password to have it securely hashed in `coin.db`.

- After logging in, admins have the following options:
1. **Suspend/Unsuspend User:**
    - By entering the correct user ID, an admin can suspend or unsuspend a user. Initially, the user is unsuspended. The first input of the user ID suspends the user, and the second input unsuspends them.

2. **Delete User:**
    - Admins can delete a user by entering the correct user ID.

3. **Update Password:**
    - Admins can update their password if they wish to change it.

4. **Logout:**
    - Admins can log out of their account.

5. **Add Another Admin:**
    - Only the first admin has the authority to register other admins.
    - The admin registration process and conditions are the same as the user registration process.
    - After successful registration, the admin's information is displayed, excluding their email and password. Their information is stored in the `admins` table in `coin.db`.
    - Admins do not receive coins upon registration, as they do not need to perform coin transfer operations.

### Notes for Users:
 - **User Limit:** The maximum number of registered users is limited to 100. If this limit is reached, no new users can register until some are deleted, the `MAX_USER` limit is increased, or dynamic memory allocation is implemented instead of a static array.

 - **Suspended Users:** Suspended users cannot perform any operations. Additionally, users cannot transfer coins to another user who has been suspended by an admin.
