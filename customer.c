#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include "customer.h"

void addCustomer(Customer** top)
{
	Customer* newCustomer = (Customer*)malloc(sizeof(Customer));

	if (!newCustomer)
	{
		printf("Memory allocation failed!\n");
		return;
	}

	printf("\n--- Add New Customer ---\n");

	printf("Bank ID: ");
	fgets(newCustomer->bankID, sizeof(newCustomer->bankID), stdin);
	newCustomer->bankID[strcspn(newCustomer->bankID, "\n")] = '\0';

	Customer* temp = *top;
	while (temp)
	{
		if (strcmp(temp->bankID, newCustomer->bankID) == 0)
		{
			printf("Bank ID already exists!\n");
			free(newCustomer);
			return;
		}
		temp = temp->next;
	}

	printf("Username: ");
	fgets(newCustomer->username, sizeof(newCustomer->username), stdin);
	newCustomer->username[strcspn(newCustomer->username, "\n")] = '\0';

	printf("Password: ");
	fgets(newCustomer->password, sizeof(newCustomer->password), stdin);
	newCustomer->password[strcspn(newCustomer->password, "\n")] = '\0';

	printf("Verication Code: ");
	scanf("%d", &newCustomer->verificationCode);
	getchar();

	printf("Full Name: ");
	fgets(newCustomer->fullName, sizeof(newCustomer->fullName), stdin);
	newCustomer->fullName[strcspn(newCustomer->fullName, "\n")] = '\0';

	printf("Address: ");
	fgets(newCustomer->address, sizeof(newCustomer->address), stdin);
	newCustomer->address[strcspn(newCustomer->address, "\n")] = '\0';

	printf("Account Type (Debit/Credit): ");
	fgets(newCustomer->accountType, sizeof(newCustomer->accountType), stdin);
	newCustomer->accountType[strcspn(newCustomer->accountType, "\n")] = '\0';

	printf("Occupation: ");
	fgets(newCustomer->occupation, sizeof(newCustomer->occupation), stdin);
	newCustomer->occupation[strcspn(newCustomer->occupation, "\n")] = '\0';

	newCustomer->next = NULL;

	if (*top == NULL || strcmp(newCustomer->bankID, (*top)->bankID) < 0)
	{
		newCustomer->next = *top;
		*top = newCustomer;
	}
	else
	{
		Customer* current = *top;
		while (current->next != NULL && strcmp(current->next->bankID, newCustomer->bankID) < 0)
		{
			current = current->next;
		}
		newCustomer->next = current->next;
		current->next = newCustomer;
	}

	printf("Customer added successfully\n");
	setAccountDetails(newCustomer);
	if (strcmp(newCustomer->accountType, "Debit") == 0)
	{
		setInitialDeposit(newCustomer);
	}
}

void printCustomers(Customer* top) 
{
	printf("\n--- Customer List ---\n");
	while (top != NULL) {
		printf("Bank ID: %s | Name: %s\n", top->bankID, top->fullName);
		top = top->next;
	}
}

void withdraw(Customer* top) {
	float amount;
	Customer* temp = top;

	if (top == NULL) {
		printf("No customers in the system.\n");
		return;
	}

	char searchID[20];
	printf("Bank ID: ");
	fgets(searchID, sizeof(searchID), stdin);
	searchID[strcspn(searchID, "\n")] = '\0';

	while (temp != NULL) {
		if (strcmp(searchID, temp->bankID) == 0) {
			printf("%s | %s\n", temp->bankID, temp->fullName);

			printf("Please enter amount to withdraw: ");
			scanf("%f", &amount);
			getchar();

			float available = temp->balance + temp->overdraftLimit;

			if (strcmp(temp->accountType, "Debit") == 0) {
				if (temp->balance >= amount) {
					temp->balance -= amount;
					printf("Withdrawal successful. New balance: %.2f\n", temp->balance);
				}
				else {
					printf("Insufficient funds. No overdraft allowed for debit accounts.\n");
				}
			}
			else if (strcmp(temp->accountType, "Credit") == 0) {
				if (available >= amount) {
					temp->balance -= amount;
					printf("Withdrawal successful. New balance: %.2f\n", temp->balance);
					recordTransaction(temp->bankID, "Withdrawal", amount, temp->balance);
				}
				else {
					printf("Insufficient funds. Exceeds overdraft limit.\n");
				}
			}

			return; // done with withdrawal
		}
		temp = temp->next;
	}

	printf("Bank ID was not found!\n");
}

void lodge(Customer* top)
{
	float amount;
	Customer* temp = top;

	if (top == NULL) {
		printf("No customers in the system.\n");
		return;
	}

	char searchID[20];
	printf("Bank ID: ");
	fgets(searchID, sizeof(searchID), stdin);
	searchID[strcspn(searchID, "\n")] = '\0';

	while (temp != NULL)
	{
		if (strcmp(searchID, temp->bankID) == 0)
		{
			printf("%s | %s\n", temp->bankID, temp->fullName);
			printf("Please enter amount to lodge: ");
			scanf("%f", &amount);
			getchar();

			temp->balance += amount;
			printf("Lodgement successful. New balance: %.2f\n", temp->balance);
			recordTransaction(temp->bankID, "Lodgement", amount, temp->balance);
			return;
		}
		temp = temp->next;
	}

	printf("Bank ID was not found!\n");
}

void setAccountDetails(Customer* c) 
{
	float salary;

	printf("Enter salary: ");
	scanf("%f", &salary);
	getchar(); // clear newline

	if (strcmp(c->accountType, "Credit") == 0) {
		c->balance = 0;
		if (salary > 5000) {
			c->overdraftLimit = 2000;
			c->interestRate = 0.03;
		}
		else {
			c->overdraftLimit = 1000;
			c->interestRate = 0.05;
		}
		c->creditScore = 750; // starting score
		c->monthsInOverdraft = 0;
	}
	else {
		c->overdraftLimit = 0;
		c->interestRate = 0.0;
		c->creditScore = 0;
	}
}

void setInitialDeposit(Customer* c)
{
	char response;
	printf("Would you like to make an initial deposit? (y/n): ");
	scanf(" %c", &response);
	getchar();

	if (response == 'y' || response == 'Y') {
		float initialDeposit;
		printf("Enter amount to deposit: ");
		scanf("%f", &initialDeposit);
		getchar();

		c->balance = initialDeposit;
	}
	else {
		c->balance = 0.0;
	}

}

void saveToFile(Customer* top, const char* filename)
{
	if (top == NULL) {
		printf("Nothing to save. Customer list is empty.\n");
		return;
	}

	FILE* file = fopen(filename, "w");
	if (!file) {
		perror("Error saving to database\n");
		return;
	}

	Customer* temp = top;
	while (temp != NULL)
	{
		fprintf(file, "%s, %s, %s, %s, %s, %s, %s, %d, %d, %.2f, %.2f, %.2f, %.2f\n",
			temp->bankID, temp->username, temp->password, temp->fullName,
			temp->address, temp->accountType, temp->occupation,
			temp->verificationCode, temp->monthsInOverdraft,
			temp->balance, temp->overdraftLimit, temp->creditScore, temp->interestRate);
		temp = temp->next;
	}

	fclose(file);
}

void loadFromFile(Customer** top, const char* filename)
{
	FILE* file = fopen(filename, "r");
	if (!file)
	{
		perror("Error loading file\n");
		return;
	}

	while (1)
	{
		Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
		if (!newCustomer)
		{
			perror("Memory allocation failed!\n");
			fclose(file);
			return;
		}

		int read = fscanf(file, "%19[^,], %19[^,], %19[^,], %49[^,], %99[^,], %9[^,], %29[^,], %d, %d, %f, %f, %f, %f\n",
			newCustomer->bankID, newCustomer->username, newCustomer->password,
			newCustomer->fullName, newCustomer->address, newCustomer->accountType,
			newCustomer->occupation, &newCustomer->verificationCode, &newCustomer->monthsInOverdraft,
			&newCustomer->balance, &newCustomer->overdraftLimit, &newCustomer->creditScore, &newCustomer->interestRate);

		if (read == 13)
		{
			newCustomer->next = NULL;

			if (*top == NULL)
			{
				*top = newCustomer;
			}
			else
			{
				Customer* current = *top;
				while (current->next != NULL)
				{
					current = current->next;
				}
				current->next = newCustomer;
			}
		}
		else
		{
			free(newCustomer);
			break;
		}
	}

	fclose(file);
}

void deleteCustomer(Customer** top)
{
	if (*top == NULL)
	{
		printf("No customers to delete");
		return;
	}

	char searchID[20];
	printf("\nEnter Bank ID to delete: ");
	fgets(searchID, sizeof(searchID), stdin);
	searchID[strcspn(searchID, "\n")] = '\0';

	Customer* temp = *top;
	Customer* prev = NULL;

	while (temp != NULL)
	{
		if (strcmp(searchID, temp->bankID) == 0)
		{
			if (prev == NULL)
			{
				*top = temp->next;
			}
			else
			{
				prev->next = temp->next;
			}
			free(temp);
			printf("Customer deleted successfully");
			return;
		}
		prev = temp;
		temp = temp->next;
	}
}

void loadLogins(Login logins[], int* loginCount)
{
	FILE* file = fopen("Login.txt", "r");
	if (!file)
	{
		perror("Error loading file\n");
		return;
	}

	*loginCount = 0;
	while (fscanf(file, "%19[^,],%19[^\n]", logins[*loginCount].username, logins[*loginCount].password) == 2)
	{
		(*loginCount)++;
	}

	fclose(file);
}

int loginSystem(Login logins[], int loginCount)
{
	//create variables
	char username[20];
	char password[20];
	int success = 0;

	//gets user to enter username and password
	printf("\nUsername: ");
	scanf("%s", username);

	//makes sure that for each character the user enters the cmd represents it as *
	printf("Password: ");
	int i = 0;
	char ch;
	while ((ch = _getch()) != 13) {
		if (ch == 8 && i > 0) {
			i--;
			printf("\b \b");
		}
		else {
			password[i++] = ch;
			printf("*");
		}
	}
	//adds a null character at end of entered password to avoid bug
	password[i] = '\0';

	for (int j = 0; j < loginCount; j++) {
		if (strcmp(username, logins[j].username) == 0 &&
			strcmp(password, logins[j].password) == 0) {
			success = 1;
			break;
		}
	}

	//using a tenary operator again to show if login was successful or not
	printf(success ? "\nLogin successful!\n" : "\nLogin failed!\n");
	return success;
}

int customerLoginSystem(Customer* top, const char* filename)
{
	char username[20], password[20];
	int code;

	getchar();

	printf("\nUsername: ");
	fgets(username, sizeof(username), stdin);
	username[strcspn(username, "\n")] = '\0';

	printf("Password: ");
	fgets(password, sizeof(password), stdin);
	password[strcspn(password, "\n")] = '\0';

	Customer* temp = top;
	while (temp != NULL)
	{
		if (strcmp(username, temp->username) == 0 && strcmp(password, temp->password) == 0)
		{
			printf("Login Successful\n");
			return 1;
		}
		temp = temp->next;
	}

	printf("Error with login\n");
	return 0;
}

void viewBalance(Customer* top)
{
	int code;

	if (!top) {
		printf("No customers in the list\n");
		return;
	}

	printf("\nVerification Code: ");
	scanf("%d", &code);
	getchar();

	Customer* temp = top;
	while (temp != NULL)
	{
		printf("Checking: %s (%d)\n", temp->fullName, temp->verificationCode); // Debug
		if (code == temp->verificationCode)
		{
			printf("Bank ID: %s | Name: %s\n", temp->bankID, temp->fullName);
			printf("Balance: %.2f\n", temp->balance);
			return;
		}
		temp = temp->next;
	}

	printf("Customer is not in the list\n");
}

void simulateMonth(Customer* top)
{
	Customer* temp = top;

	printf("\n--- Simulating One Month ---\n");

	while (temp != NULL)
	{
		// Only affect credit users
		if (strcmp(temp->accountType, "Credit") == 0)
		{
			if (temp->balance < 0)
			{
				temp->monthsInOverdraft++;

				// Apply interest to the negative balance
				float interest = fabs(temp->balance) * temp->interestRate;
				temp->balance -= interest;  // Increase the debt

				// Drop credit score, but not below 300
				if (temp->creditScore > 300)
				{
					temp->creditScore -= 10;
					if (temp->creditScore < 300)
						temp->creditScore = 300;
				}

				printf("%s | Overdraft Month %d | New Balance: %.2f | Credit Score: %d\n",
					temp->fullName, temp->monthsInOverdraft, temp->balance, temp->creditScore);
			}
			else if (temp->monthsInOverdraft > 0)
			{
				// They've repaid the debt — reset months in overdraft
				temp->monthsInOverdraft = 0;
				printf("%s has cleared their overdraft. Status reset.\n", temp->fullName);
			}
		}

		temp = temp->next;
	}
}

void repayDebt(Customer* top)
{
	char searchID[20];
	float amount;
	Customer* temp = top;

	if (top == NULL) {
		printf("No customers in the system.\n");
		return;
	}

	printf("Enter customer Bank ID: ");
	scanf(" %[^\n]", searchID);

	while (temp != NULL)
	{
		if (strcmp(searchID, temp->bankID) == 0)
		{
			if (strcmp(temp->accountType, "Credit") != 0) {
				printf("This is not a credit account.\n");
				return;
			}

			printf("Current Balance: %.2f\n", temp->balance);

			if (temp->balance >= 0) {
				printf("No debt to repay.\n");
				return;
			}

			printf("Enter repayment amount: ");
			scanf("%f", &amount);

			if (amount <= 0) {
				printf("Repayment must be greater than 0.\n");
				return;
			}

			temp->balance += amount;

			if (temp->balance >= 0) {
				temp->monthsInOverdraft = 0;
				printf("Overdraft fully repaid. Resetting status.\n");

				// Slight credit score boost
				if (temp->creditScore < 750)
					temp->creditScore += 20;
			}
			else {
				printf("Partial repayment accepted. Remaining debt: %.2f\n", temp->balance);

				// Small score bump
				if (temp->creditScore < 750)
					temp->creditScore += 5;
			}

			printf("Updated Balance: %.2f | Credit Score: %d\n", temp->balance, temp->creditScore);
			recordTransaction(temp->bankID, "Repayment", amount, temp->balance);
			return;
		}

		temp = temp->next;
	}

	printf("Bank ID not found.\n");
}

void recordTransaction(const char* bankID, const char* type, float amount, float newBalance)
{
	FILE* file = fopen("Transactions.txt", "a");
	if (!file) {
		perror("Failed to open transaction file");
		return;
	}

	fprintf(file, "%s, %s, %.2f, New Balance: %.2f\n", bankID, type, amount, newBalance);
	fclose(file);
}
