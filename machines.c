#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // for _getch()
#include "machines.h"

/* Helper: Validate email format
   function returns 1 if format is correct else it returns 0*/
int isValidEmail(const char* email) {
    if (strstr(email, "@") && strstr(email, ".") && strstr(email, "com")) {
        return 1;
    }
    return 0;
}

// Add Machine
void addMachine(Machinery** head) {
    //Inistialising newMachne
    Machinery* newMachine = (Machinery*)malloc(sizeof(Machinery));
    if (!newMachine) {
        printf("Memory allocation failed!\n");
        return;
    }

    getchar(); // clear buffer
    printf("\n--- Add New Machine ---\n");

    //Getting user to enter in details for each variable of Machinery
    printf("Chassis Number: ");
    fgets(newMachine->chassisNum, sizeof(newMachine->chassisNum), stdin);
    newMachine->chassisNum[strcspn(newMachine->chassisNum, "\n")] = '\0';

    //Fail safe in case chassis number already exists
    Machinery* temp = *head;
    while (temp) {
        if (strcmp(temp->chassisNum, newMachine->chassisNum) == 0) {
            printf("Chassis number already exists! Machine not added.\n");
            free(newMachine);
            return;
        }
        temp = temp->next;
    }

    //Continuation of adding data
    printf("Make: ");
    fgets(newMachine->make, sizeof(newMachine->make), stdin);
    newMachine->make[strcspn(newMachine->make, "\n")] = '\0';

    printf("Model: ");
    fgets(newMachine->model, sizeof(newMachine->model), stdin);
    newMachine->model[strcspn(newMachine->model, "\n")] = '\0';

    printf("Year: ");
    scanf("%d", &newMachine->year);

    printf("Cost: ");
    scanf("%f", &newMachine->cost);

    printf("Valuation: ");
    scanf("%f", &newMachine->valuation);

    printf("Mileage: ");
    scanf("%f", &newMachine->mileage);

    printf("Next Service Mileage: ");
    scanf("%f", &newMachine->nextServiceMileage);

    getchar(); // clear buffer

    printf("Owner Name: ");
    fgets(newMachine->ownerName, sizeof(newMachine->ownerName), stdin);
    newMachine->ownerName[strcspn(newMachine->ownerName, "\n")] = '\0';

    //Calling isValid() to ensure correct email format is entered
    do {
        printf("Owner Email: ");
        fgets(newMachine->ownerEmail, sizeof(newMachine->ownerEmail), stdin);
        newMachine->ownerEmail[strcspn(newMachine->ownerEmail, "\n")] = '\0';
        if (!isValidEmail(newMachine->ownerEmail))
            printf("Invalid email format! Try again.\n");
    } while (!isValidEmail(newMachine->ownerEmail));

    printf("Owner Phone: ");
    fgets(newMachine->ownerPhone, sizeof(newMachine->ownerPhone), stdin);
    newMachine->ownerPhone[strcspn(newMachine->ownerPhone, "\n")] = '\0';

    printf("Machine Type (Tractor/Excavator/Roller/Crane/Mixer): ");
    fgets(newMachine->machineType, sizeof(newMachine->machineType), stdin);
    newMachine->machineType[strcspn(newMachine->machineType, "\n")] = '\0';

    printf("Breakdown Status (Never / Less than 3 times / Less than 5 times / More than 5 times): ");
    fgets(newMachine->breakdownStatus, sizeof(newMachine->breakdownStatus), stdin);
    newMachine->breakdownStatus[strcspn(newMachine->breakdownStatus, "\n")] = '\0';

    newMachine->next = NULL;

    if (*head == NULL || strcmp(newMachine->chassisNum, (*head)->chassisNum) < 0) {
        newMachine->next = *head;
        *head = newMachine;
    }
    else {
        Machinery* current = *head;
        while (current->next != NULL && strcmp(current->next->chassisNum, newMachine->chassisNum) < 0) {
            current = current->next;
        }
        newMachine->next = current->next;
        current->next = newMachine;
    }

    printf("Machine added successfully!\n");
}

// Display All Machines
void displayAllMachines(Machinery* head) {
    //Checks to see if there are any machines in the list
    if (head == NULL) {
        printf("\nNo machines found!\n");
        return;
    }

    //Prints the list of machines if machines are found
    printf("\n--- All Machines ---\n");
    int count = 1;
    Machinery* temp = head;
    while (temp != NULL) {
        printf("\nMachine #%d\n", count++);
        printf("Chassis Number: %s\n", temp->chassisNum);
        printf("Make: %s\n", temp->make);
        printf("Model: %s\n", temp->model);
        printf("Year: %d\n", temp->year);
        printf("Cost: %.2f\n", temp->cost);
        printf("Valuation: %.2f\n", temp->valuation);
        printf("Mileage: %.2f\n", temp->mileage);
        printf("Next Service Mileage: %.2f\n", temp->nextServiceMileage);
        printf("Owner Name: %s\n", temp->ownerName);
        printf("Owner Email: %s\n", temp->ownerEmail);
        printf("Owner Phone: %s\n", temp->ownerPhone);
        printf("Machine Type: %s\n", temp->machineType);
        printf("Breakdown Status: %s\n", temp->breakdownStatus);

        temp = temp->next;
    }
}

// Display Specific Machine Details
void displayMachineDetails(Machinery* head) {
    //Checks to see if there are any machines in the list
    if (head == NULL) {
        printf("\nNo machines found!\n");
        return;
    }

    //Get clarification of which machine is to be displayed
    char searchChassis[20];
    getchar();
    printf("\nEnter the chassis number to search: ");
    fgets(searchChassis, sizeof(searchChassis), stdin);
    searchChassis[strcspn(searchChassis, "\n")] = '\0';

    //Displays machine's details if chassis number was found
    Machinery* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->chassisNum, searchChassis) == 0) {
            printf("\n--- Machine Details ---\n");
            printf("Chassis Number: %s\n", temp->chassisNum);
            printf("Make: %s\n", temp->make);
            printf("Model: %s\n", temp->model);
            printf("Year: %d\n", temp->year);
            printf("Cost: %.2f\n", temp->cost);
            printf("Valuation: %.2f\n", temp->valuation);
            printf("Mileage: %.2f\n", temp->mileage);
            printf("Next Service Mileage: %.2f\n", temp->nextServiceMileage);
            printf("Owner Name: %s\n", temp->ownerName);
            printf("Owner Email: %s\n", temp->ownerEmail);
            printf("Owner Phone: %s\n", temp->ownerPhone);
            printf("Machine Type: %s\n", temp->machineType);
            printf("Breakdown Status: %s\n", temp->breakdownStatus);
            return;
        }
        temp = temp->next;
    }

    //prints error message if chassis number was not found
    printf("Machine with chassis number %s not found!\n", searchChassis);
}

// Update Machine Details
void updateMachine(Machinery* head) {
    //Checks to see if there are any machines in the list
    if (head == NULL) {
        printf("\nNo machines to update!\n");
        return;
    }

    //Get clarification of which machine is to be updated
    char searchChassis[20];
    getchar();
    printf("\nEnter the chassis number to update: ");
    fgets(searchChassis, sizeof(searchChassis), stdin);
    searchChassis[strcspn(searchChassis, "\n")] = '\0';

    //Allows user to enter updated data
    Machinery* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->chassisNum, searchChassis) == 0) {
            printf("\n--- Update Machine Details ---\n");

            printf("New Valuation: ");
            scanf("%f", &temp->valuation);

            printf("New Mileage: ");
            scanf("%f", &temp->mileage);

            printf("New Next Service Mileage: ");
            scanf("%f", &temp->nextServiceMileage);

            printf("Machine updated successfully!\n");
            return;
        }
        temp = temp->next;
    }

    //prints error message if chassis number was not found
    printf("Machine with chassis number %s not found!\n", searchChassis);
}

// Delete Machine
void deleteMachine(Machinery** head) {
    //Checks to see if there are any machines in the list
    if (*head == NULL) {
        printf("\nNo machines to delete!\n");
        return;
    }

    //Get clarification of which machine is to be deleted
    char searchChassis[20];
    getchar();
    printf("\nEnter the chassis number to delete: ");
    fgets(searchChassis, sizeof(searchChassis), stdin);
    searchChassis[strcspn(searchChassis, "\n")] = '\0';

    Machinery* temp = *head;
    Machinery* prev = NULL;

    //deletes machine
    while (temp != NULL) {
        if (strcmp(temp->chassisNum, searchChassis) == 0) {
            if (prev == NULL) {
                *head = temp->next;
            }
            else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Machine deleted successfully!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    //prints error message if chassis number was not found
    printf("Machine with chassis number %s not found!\n", searchChassis);
}

// Save Machines to File
void saveMachinesToFile(Machinery* head, const char* filename) {
    //opens file and sets file mode to write - also checks if file exists
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Error saving file");
        return;
    }

    //Saves machines details to file
    Machinery* temp = head;
    while (temp != NULL) {
        fprintf(file, "%s,%s,%s,%d,%.2f,%.2f,%.2f,%.2f,%s,%s,%s,%s,%s\n",
            temp->chassisNum, temp->make, temp->model, temp->year,
            temp->cost, temp->valuation, temp->mileage, temp->nextServiceMileage,
            temp->ownerName, temp->ownerEmail, temp->ownerPhone,
            temp->machineType, temp->breakdownStatus);
        temp = temp->next;
    }

    //closes file
    fclose(file);
}

// Load Machines from File
void loadMachinesFromFile(Machinery** head, const char* filename) {
    //opens file and sets file mode to read - also checks if file exists
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Warning: No fleet file found. Starting fresh.\n");
        return;
    }

    //Reads in machine details - as well as ensuring a newMachine has been intialised correctly
    Machinery* newMachine;
    while (!feof(file)) {
        newMachine = (Machinery*)malloc(sizeof(Machinery));
        if (!newMachine) {
            perror("Memory allocation failed!\n");
            fclose(file);
            return;
        }

        //stores machine data into newMachine
        int read = fscanf(file, "%19[^,],%49[^,],%49[^,],%d,%f,%f,%f,%f,%49[^,],%99[^,],%19[^,],%19[^,],%29[^\n]\n",
            newMachine->chassisNum, newMachine->make, newMachine->model, &newMachine->year,
            &newMachine->cost, &newMachine->valuation, &newMachine->mileage, &newMachine->nextServiceMileage,
            newMachine->ownerName, newMachine->ownerEmail, newMachine->ownerPhone,
            newMachine->machineType, newMachine->breakdownStatus);

        if (read == 13) {
            newMachine->next = NULL;
            if (*head == NULL) {
                *head = newMachine;
            }
            else {
                Machinery* current = *head;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = newMachine;
            }
        }
        else {
            //deletes newMachine once data has been loaded in to save duplication
            free(newMachine);
        }
    }

    fclose(file);
}

void generateStatistics(Machinery* head) {
    if (head == NULL) {
        printf("\nNo machines to generate statistics!\n");
        return;
    }

    const char* types[] = { "Tractor", "Excavator", "Roller", "Crane", "Mixer" };
    int numTypes = sizeof(types) / sizeof(types[0]);

    printf("\n--- Breakdown Statistics by Machine Type ---\n");

    for (int t = 0; t < numTypes; t++) {
        int total = 0, never = 0, less3 = 0, less5 = 0, more5 = 0;

        Machinery* temp = head;
        while (temp != NULL) {
            if (strcmp(temp->machineType, types[t]) == 0) {
                total++;
                if (strcmp(temp->breakdownStatus, "Never") == 0)
                    never++;
                else if (strcmp(temp->breakdownStatus, "Less than 3 times") == 0)
                    less3++;
                else if (strcmp(temp->breakdownStatus, "Less than 5 times") == 0)
                    less5++;
                else if (strcmp(temp->breakdownStatus, "More than 5 times") == 0)
                    more5++;
            }
            temp = temp->next;
        }

        printf("\n%s:\n", types[t]);
        if (total == 0) {
            printf("  No machines of this type.\n");
        }
        else {
            printf("  Never broke down: %.2f%%\n", (never * 100.0) / total);
            printf("  Less than 3 times: %.2f%%\n", (less3 * 100.0) / total);
            printf("  Less than 5 times: %.2f%%\n", (less5 * 100.0) / total);
            printf("  More than 5 times: %.2f%%\n", (more5 * 100.0) / total);
        }
    }
}


void printReport(Machinery* head, const char* reportFilename) {
    FILE* file = fopen(reportFilename, "w");
    if (!file) {
        perror("Error creating report file");
        return;
    }

    // Print machine details
    Machinery* temp = head;
    fprintf(file, "--- Machine Details ---\n");
    while (temp != NULL) {
        fprintf(file, "%s,%s,%s,%d,%.2f,%.2f,%.2f,%.2f,%s,%s,%s,%s,%s\n",
            temp->chassisNum, temp->make, temp->model, temp->year,
            temp->cost, temp->valuation, temp->mileage, temp->nextServiceMileage,
            temp->ownerName, temp->ownerEmail, temp->ownerPhone,
            temp->machineType, temp->breakdownStatus);
        temp = temp->next;
    }

    // Add breakdown statistics per machine type
    const char* types[] = { "Tractor", "Excavator", "Roller", "Crane", "Mixer" };
    int numTypes = sizeof(types) / sizeof(types[0]);

    fprintf(file, "\n--- Breakdown Statistics by Machine Type ---\n");

    for (int t = 0; t < numTypes; t++) {
        int total = 0, never = 0, less3 = 0, less5 = 0, more5 = 0;

        Machinery* scan = head;
        while (scan != NULL) {
            if (strcmp(scan->machineType, types[t]) == 0) {
                total++;
                if (strcmp(scan->breakdownStatus, "Never") == 0)
                    never++;
                else if (strcmp(scan->breakdownStatus, "Less than 3 times") == 0)
                    less3++;
                else if (strcmp(scan->breakdownStatus, "Less than 5 times") == 0)
                    less5++;
                else if (strcmp(scan->breakdownStatus, "More than 5 times") == 0)
                    more5++;
            }
            scan = scan->next;
        }

        fprintf(file, "\n%s:\n", types[t]);
        if (total == 0) {
            fprintf(file, "  No machines of this type.\n");
        }
        else {
            fprintf(file, "  Never broke down: %.2f%%\n", (never * 100.0) / total);
            fprintf(file, "  Less than 3 times: %.2f%%\n", (less3 * 100.0) / total);
            fprintf(file, "  Less than 5 times: %.2f%%\n", (less5 * 100.0) / total);
            fprintf(file, "  More than 5 times: %.2f%%\n", (more5 * 100.0) / total);
        }
    }

    fclose(file);
}


// List Machines by Valuation
void listMachinesByValuation(Machinery* head) {
    //checks if there are nay machines in the list
    if (head == NULL) {
        printf("\nNo machines found!\n");
        return;
    }

    //counts number of machines in list
    int count = 0;
    Machinery* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }

    //creates an array to store validated machines in
    Machinery** array = malloc(count * sizeof(Machinery*));
    temp = head;
    for (int i = 0; i < count; i++) {
        array[i] = temp;
        temp = temp->next;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (array[i]->valuation < array[j]->valuation) {
                Machinery* temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    //prints out validated machines
    printf("\n--- Machines by Valuation ---\n");
    for (int i = 0; i < count; i++) {
        printf("%s (%s %s) - Valuation: %.2f\n",
            array[i]->chassisNum, array[i]->make, array[i]->model, array[i]->valuation);
    }

    free(array);
}

// Load Login Details
void loadLogins(Login logins[], int* loginCount) {
    //opens file and sets file mode to read - also checks if file exists
    FILE* file = fopen("login.txt", "r");
    if (!file) {
        perror("Error opening login.txt\n");
        exit(1);
    }

    //counts a tracks the number of different usernames and passwords that have access to login system
    *loginCount = 0;
    while (fscanf(file, "%19[^,],%19s\n", logins[*loginCount].username, logins[*loginCount].password) == 2) {
        (*loginCount)++;
    }

    fclose(file);
}

// Login System
int loginSystem(Login logins[], int loginCount) {
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