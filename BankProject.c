#include<stdio.h>
#include<string.h> 
""" user (to store user information) """
struct user
{
	char fName[12], lName[12];
	int ID;
};

""" date (to store dates) """
struct date 
{
    int day, month, year;
};

""" bank_account (to represent bank accounts) """
struct bank_account
{
    struct user *theUser;
    int bank_number;
	float amount;
	int oppNum;
};

""" deposit_withdrawal (to store deposit/withdrawal operations) """ 
struct deposit_withdrawal
{
    struct date theDate;
    float amount;
    char name_essense[40];
	float resultBalance;
};

""" users_data_base (to store user data) """
struct users_data_base
{
    int number_of_users;
    struct user clients[100];
    } users_db;

""" bank_data_base (to store bank account data) """
struct bank_data_base
{
    int number_of_account;
    struct bank_account accounts[250];
	} bank_db;

""" _memory (to store transaction history) """
struct _memory
{
	int counter, numAcc;
	struct deposit_withdrawal P[1000];
}memory[250];

""" inputUser function reads user information from the console and returns a user structure """
struct user inputUser(void)
{
	struct user newUser;
	printf("\nFirst & Last Name - ");
	scanf("%s %s", newUser.fName, newUser.lName);
	printf("ID No. - ");
	scanf("%d",&newUser.ID);
	return newUser;
}

""" FindUser function searches for a user with a given ID in the users_db database and returns a pointer to the user if found, or NULL otherwise """
struct user *FindUser(int numOfID)
{
	for (int i = 0 ; i < 100 ; ++i)
	{
		if(numOfID == users_db.clients[i].ID) 
				return &users_db.clients[i];
	}
	return NULL;
}

""" addUser function prompts for user information, checks if the ID already exists, adds the user to the users_db database, and increments the user count """
void addUser(void)
{
	struct user newUser = inputUser();
	if (FindUser(newUser.ID))
	{
		printf("\nThe ID number exists, please Enter a new ID number\n");
		return;
	}
	int nextUser = users_db.number_of_users;
	users_db.clients[nextUser] = newUser;
	users_db.number_of_users++;
	printf("\nThe customer was successfully added !\n");
}

""" findAcc function searches for a bank account with a given account number in the bank_db database and returns a pointer to the account if found, or NULL otherwise """
struct bank_account *findAcc(int accountNumber)
{
	for (int i=0 ; i < 250 ; ++i)
	{
		if(accountNumber == bank_db.accounts[i].bank_number)
			return &bank_db.accounts[i];
	}
	return NULL;
}

""" addAccount function prompts for a user ID, finds the corresponding user, assigns a new bank account to the user, initializes the account's properties, and increments the account count """
void addAccount(void)
{
	int numOfID=0;
	struct user *newUser;
	printf("ID No. - ");
	scanf("%d",&numOfID);
	newUser = FindUser(numOfID);
	if(newUser)
	{
		printf("\nWelcome to your new bank account. Your account number is - %d\n",bank_db.number_of_account);
		bank_db.accounts[bank_db.number_of_account].theUser = newUser;
		bank_db.accounts[bank_db.number_of_account].bank_number = bank_db.number_of_account;
		memory[bank_db.number_of_account].numAcc = bank_db.number_of_account;
		bank_db.accounts[bank_db.number_of_account].amount = 0.00;
		bank_db.number_of_account++;	
	}
	else
	{
		printf("\nNo customer found, first add a new customer\n");
		return;
	}
}

""" checkDate function validates the day, month, and year values for a valid date and returns 1 if valid, or 0 otherwise """
int checkDate(int day, int month, int year)
{
	if(day > 0 && day <= 31 && month > 0 && month <= 12 && year > 0)
		return 1;
	return 0;
}

""" eposit_withdrawal function handles deposit and withdrawal operations for a given account.
 It prompts for account number, date, amount, and name/essence, 
 performs the transaction, updates the transaction history, and increments the operation counter. """
void deposit_withdrawal(int n)
{
	int id, dd, mm, yy;
	float cash;
	printf("\nPlease enter your account No. - ");
	scanf("%d", &id);
	struct bank_account *myAccount = findAcc(id);
	if(myAccount == NULL)
	{
		printf("\nERROR! Account could not be found\n");
		return;
	}
	if(memory[myAccount->bank_number].counter > 1000)
	{
		printf("\nAccount has to many operations\n");
		return;
	}
	printf("Please enter date (dd mm yyyy) - ");
	scanf("%d %d %d", &dd, &mm, &yy);
	while(checkDate(dd, mm, yy)==0)
	{
			printf("Invalid date,\nPlease enter date (dd mm yyyy) - ");
			scanf("%d %d %d", &dd, &mm, &yy);
	}
	memory[myAccount->bank_number].P[myAccount->oppNum].theDate.day = dd;
	memory[myAccount->bank_number].P[myAccount->oppNum].theDate.month = mm;
	memory[myAccount->bank_number].P[myAccount->oppNum].theDate.year = yy;
	printf("Enter amount ($) - ");
	scanf("%f",&cash);
	if(cash < 0)
	{
		printf("Amount is not legal, has to be positive\n");
		return;
	}
	if(n == 1)
	{
		printf("Enter your name - ");
	} else{
		printf("Enter the essence - ");
	}
	scanf("%s",memory[myAccount->bank_number].P[myAccount->oppNum].name_essense);
	myAccount->amount += n*cash;
	memory[myAccount->bank_number].counter++;
	memory[myAccount->bank_number].P[myAccount->oppNum].amount = n*cash;
	memory[myAccount->bank_number].P[myAccount->oppNum].resultBalance = myAccount->amount;
	printf("Your current balance is %.2f$\n",myAccount->amount);
	myAccount->oppNum++;
	return;
}

""" The customerList function displays a list of customers and their associated accounts with the current balances """
void customerList(void)
{
	for(int i=0; i<users_db.number_of_users; i++)
	{
		printf("Name - %s %s\t\tID No. - %d\n",users_db.clients[i].fName, users_db.clients[i].lName, users_db.clients[i].ID);
		for(int j=0; j<bank_db.number_of_account; j++)
		{
			if(bank_db.accounts[j].theUser->ID == users_db.clients[i].ID)
				printf("Account No. - %d\t\tCurrent balance - %.2f$\n", bank_db.accounts[j].bank_number,bank_db.accounts[j].amount);
		}
	}
}

""" checkOpp function checks if an account has any operations recorded in the transaction history and returns 1 if there are any, or 0 otherwise """
int checkOpp (struct bank_account *acc)
{
	int counter = 0;
	for(int i=0; i<bank_db.number_of_account; i++)
	{
		if(memory[i].counter>0 && acc->bank_number == memory[i].numAcc)
			return 1;
	}
	return 0;
}

""" isInRange function checks if a given date range (from and until) encompasses a transaction's date and returns 1 if it does, or 0 otherwise """
int isInRange (int dds, int mms, int yys, int ddl, int mml, int yyl, struct deposit_withdrawal dw)
{
	struct date td = dw.theDate;
	if(yys > td.year || yyl < td.year)
		return 0;
	if(yys == td.year)
	{
		if(mms > td.month)
			return 0;
		if(mms == td.month)
		{
			if(dds > td.day)
				return 0;
		}
	}
	if(yyl == td.year)
	{
		if(mml < td.month)
			return 0;
		if(mml == td.month)
		{
			if(ddl < td.day)
				return 0;
		}
	}
	return 1;				
}

""" accountActivity function displays the transaction history for a specific account within a specified date range """
void accountActivity(void)
{
	int accNumber, dd1, mm1, yy1, dd2, mm2, yy2, dd, mm, yy;
	struct bank_account *ba;
	printf("\nPlease enter your account No. - ");
	scanf("%d", &accNumber);
	ba = findAcc(accNumber);
	if(ba != NULL)
	{
		if(checkOpp(ba) == 0)
		{
			printf("\nNo activity in the account\n");
			return;
		}
		printf("From (dd mm yyyy) - ");
		scanf("%d %d %d", &dd1, &mm1, &yy1);
		while(checkDate(dd1, mm1, yy1)==0)
		{
			printf("Invalid date, enter again\nFrom (dd mm yyyy) - ");
			scanf("%d %d %d", &dd1, &mm1, &yy1);
		}
		printf("Until (dd mm yyyy) - ");
		scanf("%d %d %d", &dd2, &mm2, &yy2);
		while(checkDate(dd2, mm2, yy2)==0)
		{
			printf("Invalid date, enter again\nUntil (dd mm yyyy) - ");
			scanf("%d %d %d", &dd2, &mm2, &yy2);
		}
		printf("Date\t\t\tDeposit\t\t\tWithdrawal\t\tBalance\n");
		for(int i=0; i<memory[accNumber].counter; i++)
		{
			if(isInRange(dd1, mm1, yy1, dd2, mm2, yy2, memory[accNumber].P[i]) == 1)
			{
				dd = memory[accNumber].P[i].theDate.day;
				mm = memory[accNumber].P[i].theDate.month;
				yy = memory[accNumber].P[i].theDate.year;
				if(memory[accNumber].P[i].amount > 0)
				{				
					printf("%d/%d/%d\t\t%.2f\t\t\t******\t\t\t%.2f\n",dd, mm, yy, memory[accNumber].P[i].amount, memory[accNumber].P[i].resultBalance);
				}
				else 
					printf("%d/%d/%d\t\t******\t\t\t%.2f\t\t%.2f\n",dd, mm, yy, memory[accNumber].P[i].amount, memory[accNumber].P[i].resultBalance);
			}
		}
	}
	else
		printf("\nNo account found\n");
}

""" main function presents a menu-driven interface for the banking management system, 
allowing users to perform various operations such as:
adding customers, adding accounts, making deposits/withdrawals, viewing customer lists, and viewing account activity. """
void main(void)
{
    int option;
    char c;
    for(;;)
	{
    	printf("\n\tWelcome to banking management system\n");
		printf("\n\t\t\tMenu\n\n");
		printf("1 - Add New Customer \t\t4 - Withdrawal\n2 - Add Account\t\t\t5 - Customer list\n3 - Deposit\t\t\t6 - Account Activity\n");
		printf("\n\t\t7 - End\tSelect --> ");
		scanf("%d", &option);
		c = getchar();
		switch (option)
		{
			case 1:
				addUser();
				break;
			case 2:
				addAccount();
				break;
			case 3:
				deposit_withdrawal(1);
				break;
			case 4:
				deposit_withdrawal(-1);
				break;
			case 5:
				customerList();
				break;
			case 6:
				accountActivity();
				break;
			case 7:
				return;
		}
	}
}