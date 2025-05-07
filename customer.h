#ifndef MACHINES_H
#define MACHINES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Customer {
    char bankID[20];
    char username[20];
    char password[20];
    char fullName[50];
    char address[100];
    char accountType[10]; // "credit" or "debit"
    char occupation[30];

    int verificationCode;
    int monthsInOverdraft;

    float balance;
    float overdraftLimit;
    float creditScore;
    float interestRate;

    struct Customer* next;
} Customer;

typedef struct Login {
    char username[20];
    char password[20];
}Login;

void addCustomer(Customer** top);
void setAccountDetails(Customer* c);
void printCustomers(Customer* top);
void withdraw(Customer* top);
void lodge(Customer* c);
void setInitialDeposit(Customer* c);
void saveToFile(Customer* top, const char* filename);
void loadFromFile(Customer** top, const char* filename);
void deleteCustomer(Customer** top);
void loadLogins(Login logins[], int* loginCount);
int loginSystem(Login logins[], int loginCount);
int customerLoginSystem(Customer* top, const char* filename);
void viewBalance(Customer* top);
void simulateMonth(Customer* top);
void repayDebt(Customer* top);
void recordTransaction(const char* bankID, const char* type, float amount, float newBalance);

#endif
#pragma once