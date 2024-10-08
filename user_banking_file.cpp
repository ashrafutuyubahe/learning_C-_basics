#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 40

struct fileDetails {
    char userName[MAX_LENGTH];
    double accountNumber;
};

void writeToFile(FILE *fptr, struct fileDetails *fileDetails) {
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fptr, "user name: %s\n", fileDetails->userName);
    fprintf(fptr, "account number: %.2lf\n", fileDetails->accountNumber);
    fclose(fptr);
}

void readAccountDetailsFile() {
    struct fileDetails dataFromAccount_detailsfile;
    FILE *FileOpenPtr = fopen("account_details.txt", "r");

    if (FileOpenPtr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fscanf(FileOpenPtr, "user name: %s", dataFromAccount_detailsfile.userName);
    fscanf(FileOpenPtr, "account number: %lf", &dataFromAccount_detailsfile.accountNumber);

    printf("Your user name is %s and your account number is %.2lf\n",
           dataFromAccount_detailsfile.userName, dataFromAccount_detailsfile.accountNumber);

    fclose(FileOpenPtr);
}

void printOnConsole() {
    printf("1. Create account\n");
    printf("2. View account details\n");
    printf("3. Exit\n");
}

void createAccount(char *userName, double *accountNumber, struct fileDetails *fileDetails) {
    printf("Enter your User Name:\n");
    scanf("%s", userName);

    printf("Enter your Account Number:\n");
    scanf("%lf", accountNumber);

    strcpy(fileDetails->userName, userName);
    fileDetails->accountNumber = *accountNumber;

    printf("You have successfully created an account.\n%s and %.2lf are your account credentials and all data are documented in a file.\n",
           userName, *accountNumber);
}

int main() {
    char userName[MAX_LENGTH];
    int userInput;
    double accountNumber;
    struct fileDetails fileDetails;

    while (1) {
        printOnConsole();

        printf("Enter your choice: ");
        scanf("%d", &userInput);

        if (userInput == 3) {
            printf("Exiting the program.\n");
            break;
        }

        FILE *fptr = NULL;
        if (userInput == 1) {
            fptr = fopen("account_details.txt", "w");
            createAccount(userName, &accountNumber, &fileDetails);
            writeToFile(fptr, &fileDetails);
        } else if (userInput == 2) {
            readAccountDetailsFile();
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
