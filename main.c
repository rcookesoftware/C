#define _CRT_SECURE_NO_WARNINGS
#include "machines.h"//calling machines header file

int main() {
    //initialising variables and struct pointers
    Machinery* head = NULL;
    Login logins[3];
    int loginCount = 0;
    int choice;

    loadLogins(logins, &loginCount);//calling loadLogins()

    //fail safe is loginSystem doesn't work
    if (!loginSystem(logins, loginCount)) {
        printf("Exiting program...\n");
        return 0;
    }

    loadMachinesFromFile(&head, "fleet.txt");

    //Menus system
    do {
        printf("\n--- Machinery Management Menu ---\n");
        printf("1. Add Machine\n");
        printf("2. Display All Machines\n");
        printf("3. Display Machine Details\n");
        printf("4. Update Machine Details\n");
        printf("5. Delete Machine\n");
        printf("6. Generate Statistics\n");
        printf("7. Print Report to File\n");
        printf("8. List Machines by Valuation\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        //switch statement importing menu systems functions
        switch (choice) {
        case 1: addMachine(&head); break;
        case 2: displayAllMachines(head); break;
        case 3: displayMachineDetails(head); break;
        case 4: updateMachine(head); break;
        case 5: deleteMachine(&head); break;
        case 6: generateStatistics(head); break;
        case 7: printReport(head, "report.txt"); break;
        case 8: listMachinesByValuation(head); break;
        case 9: saveMachinesToFile(head, "fleet.txt"); printf("Exiting program...\n"); break;
        default: printf("Invalid choice, try again.\n");
        }
    } while (choice != 9);//condition set for sentinel loop

    return 0;
}