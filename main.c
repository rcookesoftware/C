#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"

int main()
{
    Customer* top = NULL;
    Login logins[3];
    int loginCount = 0;
    int menuType, choice;

    loadLogins(logins, &loginCount);//calling loadLogins()
    loadFromFile(&top, "Customer.txt");

    printf("Enter 1 to enter as Bank clerk or 2 to enter as customer\nEnter Choice: ");
    scanf("%d", &menuType);

    if (menuType == 1)
    {
        //fail safe is loginSystem doesn't work
        if (loginSystem(logins, loginCount)) {
            do
            {
                printf("\n--- Bank Menu System ---\n");
                printf("Enter 1 to add a new customer\n");
                printf("Enter 2 to print all customers\n");
                printf("Enter 3 to view customer's balance\n");
                printf("Enter 4 to withdraw money\n");
                printf("Enter 5 to lodge money\n");
                printf("Enter 6 to delete a customer\n");
                printf("Enter 7 to see credit users' scores\n");
                printf("Enter 8 to repay customer debt\n");
                printf("Enter -1 to exit\n");
                printf("Enter choice: ");
                scanf("%d", &choice);

                getchar();

                switch (choice)
                {
                case 1: addCustomer(&top); break;
                case 2: printCustomers(top); break;
                case 3: viewBalance(top); break;
                case 4: withdraw(top); break;
                case 5: lodge(top); break;
                case 6: deleteCustomer(&top); break;
                case 7:simulateMonth(top); break;
                case 8: repayDebt(top); break;
                case -1: saveToFile(top, "Customer.txt"); return;
                default:
                    printf("Invalid entry. Please choose 1, 2, 3, 4, 5, 6, 7, 8 or -1.\n");
                }
            } while (choice != -1);
            return 1;
        }
        else
        {
            printf("Exiting program...\n");
            return 0;
        }
    }
    else if (menuType == 2)
    {
        //fail safe if customerLoginSystem doesn't work
        if (customerLoginSystem(top, "Customer.txt")) 
        {
            do
            {
                printf("\n--- Bank Menu System ---\n");
                printf("Enter 1 to withdraw money\n");
                printf("Enter 2 to lodge money\n");
                printf("Enter 3 to view your balance\n");
                printf("Enter -1 to exit\n");
                printf("Enter choice: ");
                scanf("%d", &choice);

                getchar();

                switch (choice)
                {
                case 1: withdraw(top); break;
                case 2: lodge(top); break;
                case 3: viewBalance(top); break;
                case -1: return;
                default:
                    printf("Invalid entry. Please choose 1, 2, 3, or -1.\n");
                }
            } while (choice != -1);
            return 1;
        }
        else
        {
            printf("Exiting program...\n");
            return 0;
        }
    }
}