# banking-management-system-in-C
banking management system implemented in C


The code begins with the inclusion of necessary header files (stdio.h and string.h).

Several structures are defined: user (to store user information), date (to store dates), bank_account (to represent bank accounts), deposit_withdrawal (to store deposit/withdrawal operations), users_data_base (to store user data), bank_data_base (to store bank account data), and _memory (to store transaction history).
The inputUser function reads user information from the console and returns a user structure.

The FindUser function searches for a user with a given ID in the users_db database and returns a pointer to the user if found, or NULL otherwise.

The addUser function prompts for user information, checks if the ID already exists, adds the user to the users_db database, and increments the user count.

The findAcc function searches for a bank account with a given account number in the bank_db database and returns a pointer to the account if found, or NULL otherwise.

The addAccount function prompts for a user ID, finds the corresponding user, assigns a new bank account to the user, initializes the account's properties, and increments the account count.

The checkDate function validates the day, month, and year values for a valid date and returns 1 if valid, or 0 otherwise.

The deposit_withdrawal function handles deposit and withdrawal operations for a given account. It prompts for account number, date, amount, and name/essence, performs the transaction, updates the transaction history, and increments the operation counter.

The customerList function displays a list of customers and their associated accounts with the current balances.

The checkOpp function checks if an account has any operations recorded in the transaction history and returns 1 if there are any, or 0 otherwise.

The isInRange function checks if a given date range (from and until) encompasses a transaction's date and returns 1 if it does, or 0 otherwise.

The accountActivity function displays the transaction history for a specific account within a specified date range.

The main function presents a menu-driven interface for the banking management system, allowing users to perform various operations such as adding customers, adding accounts, making deposits/withdrawals, viewing customer lists, and viewing account activity.

