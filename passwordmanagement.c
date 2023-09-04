#include <stdio.h>
#include <string.h>

// Define the maximum number of passwords the system can handle
#define MAX_PASSWORDS 100

// Structure to represent a password entry
struct PasswordEntry {
    char website[100];
    char username[50];
    char password[50];
};

// Array to store password entries
struct PasswordEntry passwords[MAX_PASSWORDS];
int numPasswords = 0;

// Function to insert a new password entry
void insertPassword() {
    if (numPasswords < MAX_PASSWORDS) {
        printf("Enter website: ");
        scanf("%s", passwords[numPasswords].website);
        printf("Enter username: ");
        scanf("%s", passwords[numPasswords].username);
        printf("Enter password: ");
        scanf("%s", passwords[numPasswords].password);
        numPasswords++;
        printf("Password inserted successfully.\n");
    } else {
        printf("Password database is full.\n");
    }
}

// Function to search for a password entry
void searchPassword() {
    char searchWebsite[100];
    printf("Enter website to search for: ");
    scanf("%s", searchWebsite);

    for (int i = 0; i < numPasswords; i++) {
        if (strcmp(passwords[i].website, searchWebsite) == 0) {
            printf("Website: %s\n", passwords[i].website);
            printf("Username: %s\n", passwords[i].username);
            printf("Password: %s\n", passwords[i].password);
            return;
        }
    }

    printf("Website not found.\n");
}

// Function to modify a password entry
void modifyPassword() {
    char modifyWebsite[100];
    printf("Enter website to modify: ");
    scanf("%s", modifyWebsite);

    for (int i = 0; i < numPasswords; i++) {
        if (strcmp(passwords[i].website, modifyWebsite) == 0) {
            printf("Enter new username: ");
            scanf("%s", passwords[i].username);
            printf("Enter new password: ");
            scanf("%s", passwords[i].password);
            printf("Password modified successfully.\n");
            return;
        }
    }

    printf("Website not found.\n");
}

// Function to delete a password entry
void deletePassword() {
    char deleteWebsite[100];
    printf("Enter website to delete: ");
    scanf("%s", deleteWebsite);

    for (int i = 0; i < numPasswords; i++) {
        if (strcmp(passwords[i].website, deleteWebsite) == 0) {
            // Shift remaining passwords to fill the gap
            for (int j = i; j < numPasswords - 1; j++) {
                passwords[j] = passwords[j + 1];
            }
            numPasswords--;
            printf("Password deleted successfully.\n");
            return;
        }
    }

    printf("Website not found.\n");
}

int main() {
    int choice;

    do {
        printf("\nPassword Manager Menu\n");
        printf("1. Insert Password\n");
        printf("2. Search Password\n");
        printf("3. Modify Password\n");
        printf("4. Delete Password\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertPassword();
                break;
            case 2:
                searchPassword();
                break;
            case 3:
                modifyPassword();
                break;
            case 4:
                deletePassword();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}