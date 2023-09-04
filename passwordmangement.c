#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a password entry
typedef struct {
    char website[100];
    char username[50];
    char password[50];
} PasswordEntry;

// Function to add a new password entry
void addPassword(PasswordEntry *database, int *count) {
    if (*count >= 100) {
        printf("Password database is full.\n");
        return;
    }

    printf("Enter website: ");
    scanf("%s", database[*count].website);
    printf("Enter username: ");
    scanf("%s", database[*count].username);
    printf("Enter password: ");
    scanf("%s", database[*count].password);

    (*count)++;
    printf("Password added successfully.\n");
}

// Function to search for a password entry by website
void searchPassword(PasswordEntry *database, int count, const char *website) {
    for (int i = 0; i < count; i++) {
        if (strcmp(database[i].website, website) == 0) {
            printf("Website: %s\n", database[i].website);
            printf("Username: %s\n", database[i].username);
            printf("Password: %s\n", database[i].password);
            return;
        }
    }

    printf("Website not found.\n");
}

// Function to modify a password entry
void modifyPassword(PasswordEntry *database, int count, const char *website) {
    for (int i = 0; i < count; i++) {
        if (strcmp(database[i].website, website) == 0) {
            printf("Enter new username: ");
            scanf("%s", database[i].username);
            printf("Enter new password: ");
            scanf("%s", database[i].password);
            printf("Password modified successfully.\n");
            return;
        }
    }

    printf("Website not found.\n");
}

// Function to delete a password entry
void deletePassword(PasswordEntry *database, int *count, const char *website) {
    for (int i = 0; i < *count; i++) {
        if (strcmp(database[i].website, website) == 0) {
            for (int j = i; j < *count - 1; j++) {
                database[j] = database[j + 1];
            }
            (*count)--;
            printf("Password deleted successfully.\n");
            return;
        }
    }

    printf("Website not found.\n");
}

int main() {
    PasswordEntry database[100];
    int count = 0;
    int choice;
    char website[100];

    while (1) {
        printf("\nPassword Manager Menu:\n");
        printf("1. Add Password\n");
        printf("2. Search Password\n");
        printf("3. Modify Password\n");
        printf("4. Delete Password\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPassword(database, &count);
                break;
            case 2:
                printf("Enter website to search: ");
                scanf("%s", website);
                searchPassword(database, count, website);
                break;
            case 3:
                printf("Enter website to modify: ");
                scanf("%s", website);
                modifyPassword(database, count, website);
                break;
            case 4:
                printf("Enter website to delete: ");
                scanf("%s", website);
                deletePassword(database, &count, website);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
