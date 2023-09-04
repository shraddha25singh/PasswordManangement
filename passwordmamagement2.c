#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a password entry
typedef struct {
    char website[100];
    char username[50];
    char password[50];
} PasswordEntry;

// Function to add a new password entry to a file
void addPasswordToFile(const char *filename, const PasswordEntry *entry) {
    FILE *file = fopen(filename, "ab");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    fwrite(entry, sizeof(PasswordEntry), 1, file);
    fclose(file);
    printf("Password added successfully.\n");
}

// Function to delete a password entry from a file
void deletePasswordFromFile(const char *filename, const char *website) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "wb");
    if (tempFile == NULL) {
        printf("Error opening the temporary file.\n");
        fclose(file);
        return;
    }

    PasswordEntry entry;
    int deleted = 0;

    while (fread(&entry, sizeof(PasswordEntry), 1, file)) {
        if (strcmp(entry.website, website) != 0) {
            fwrite(&entry, sizeof(PasswordEntry), 1, tempFile);
        } else {
            deleted = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (deleted) {
        remove(filename); // Delete the original file
        rename("temp.txt", filename); // Rename the temporary file to the original filename
        printf("Password deleted successfully.\n");
    } else {
        remove("temp.txt"); // Delete the temporary file if password not found
        printf("Website not found.\n");
    }
}

// Function to modify a password entry in a file
void modifyPasswordInFile(const char *filename, const char *website, const PasswordEntry *newEntry) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "wb");
    if (tempFile == NULL) {
        printf("Error opening the temporary file.\n");
        fclose(file);
        return;
    }

    PasswordEntry entry;
    int modified = 0;

    while (fread(&entry, sizeof(PasswordEntry), 1, file)) {
        if (strcmp(entry.website, website) == 0) {
            fwrite(newEntry, sizeof(PasswordEntry), 1, tempFile);
            modified = 1;
        } else {
            fwrite(&entry, sizeof(PasswordEntry), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (modified) {
        remove(filename); // Delete the original file
        rename("temp.txt", filename); // Rename the temporary file to the original filename
        printf("Password modified successfully.\n");
    } else {
        remove("temp.txt"); // Delete the temporary file if password not found
        printf("Website not found.\n");
    }
}

// Function to show all passwords in the file
void showPasswords(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    PasswordEntry entry;

    printf("Stored Passwords:\n");

    while (fread(&entry, sizeof(PasswordEntry), 1, file)) {
        printf("Website: %s\n", entry.website);
        printf("Username: %s\n", entry.username);
        printf("Password: %s\n\n", entry.password);
    }

    fclose(file);
}

int main() {
    int choice;
    char website[100];
    PasswordEntry entry;
    const char *filename = "passwords.txt";

    while (1) {
        printf("\nPassword Manager Menu:\n");
        printf("1. Add Password\n");
        printf("2. Delete Password\n");
        printf("3. Modify Password\n");
        printf("4. Show Passwords\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter website: ");
                scanf("%s", entry.website);
                printf("Enter username: ");
                scanf("%s", entry.username);
                printf("Enter password: ");
                scanf("%s", entry.password);
                addPasswordToFile(filename, &entry);
                break;
            case 2:
                printf("Enter website to delete: ");
                scanf("%s", website);
                deletePasswordFromFile(filename, website);
                break;
            case 3:
                printf("Enter website to modify: ");
                scanf("%s", website);
                printf("Enter new username: ");
                scanf("%s", entry.username);
                printf("Enter new password: ");
                scanf("%s", entry.password);
                modifyPasswordInFile(filename, website, &entry);
                break;
            case 4:
                showPasswords(filename);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
