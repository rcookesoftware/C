#ifndef MACHINES_H
#define MACHINES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Machinery struct for singly linked list
typedef struct Machinery {
    char chassisNum[20];
    char make[50];
    char model[50];
    int year;
    float cost;
    float valuation;
    float mileage;
    float nextServiceMileage;
    char ownerName[50];
    char ownerEmail[100];
    char ownerPhone[20];
    char machineType[20];
    char breakdownStatus[30];
    struct Machinery* next;
} Machinery;

// Login struct
typedef struct Login {
    char username[20];
    char password[20];
} Login;

// Machinery Functions
void addMachine(Machinery** head);
void displayAllMachines(Machinery* head);
void displayMachineDetails(Machinery* head);
void updateMachine(Machinery* head);
void deleteMachine(Machinery** head);
void loadMachinesFromFile(Machinery** head, const char* filename);
void saveMachinesToFile(Machinery* head, const char* filename);
void generateStatistics(Machinery* head);
void printReport(Machinery* head, const char* reportFilename);
void listMachinesByValuation(Machinery* head);

// Login Functions
void loadLogins(Login logins[], int* loginCount);
int loginSystem(Login logins[], int loginCount);

// Helpers
int isValidEmail(const char* email);

#endif
#pragma once