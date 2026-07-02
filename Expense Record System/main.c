
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Expense {
    char name[50];
    char category[30];
    char date[20];
    float amount;
};

void addExpense() {

    FILE *fp;
    struct Expense e;
    int categoryChoice;

    fp = fopen("expenses.txt", "a");

    if(fp == NULL) {
        printf("\nError Opening File!\n");
        return;
    }

    printf("\n==================================================\n");
    printf("                    ADD EXPENSE\n");
    printf("==================================================\n");

    printf("\nSelect Category:\n");
    printf("1. Food\n");
    printf("2. Travel\n");
    printf("3. Entertainment\n");
    printf("4. Others\n");

    printf("\nEnter Choice : ");
    scanf("%d", &categoryChoice);

    switch(categoryChoice)
    {
        case 1:
            strcpy(e.category, "Food");
            break;

        case 2:
            strcpy(e.category, "Travel");
            break;

        case 3:
            strcpy(e.category, "Entertainment");
            break;

        case 4:
            strcpy(e.category, "Others");
            break;

        default:
            strcpy(e.category, "Others");
    }

    printf("\nEnter Expense Name : ");
    scanf(" %[^\n]", e.name);

    printf("Enter Date : ");
    scanf(" %[^\n]", e.date);

    printf("Enter Amount : ");
    scanf("%f", &e.amount);

    fprintf(fp, "%s|%s|%s|%.2f\n",
            e.name,
            e.category,
            e.date,
            e.amount);

    fclose(fp);

    printf("\nExpense Added Successfully!\n");
}

void viewExpenses() {

    FILE *fp;
    struct Expense e;
    int found = 0;

    fp = fopen("expenses.txt", "r");

    if(fp == NULL) {
        printf("\nNo Expense Records Found!\n");
        return;
    }

    printf("\n==================================================\n");
    printf("                   ALL EXPENSES\n");
    printf("==================================================\n");

    while(fscanf(fp, " %49[^|]|%29[^|]|%19[^|]|%f\n",
                 e.name,
                 e.category,
                 e.date,
                 &e.amount) == 4) {

        found = 1;

        printf("\nExpense Name : %s\n", e.name);
        printf("Category     : %s\n", e.category);
        printf("Date         : %s\n", e.date);
        printf("Amount       : Rs. %.2f\n", e.amount);

        printf("--------------------------------------------------\n");
    }

    if(found == 0) {
        printf("\nNo Expenses Found!\n");
    }

    fclose(fp);
}

void totalExpense() {

    FILE *fp;
    struct Expense e;
    float total = 0;

    fp = fopen("expenses.txt", "r");

    if(fp == NULL) {
        printf("\nNo Expense Records Found!\n");
        return;
    }

    while(fscanf(fp, " %49[^|]|%29[^|]|%19[^|]|%f\n",
                 e.name,
                 e.category,
                 e.date,
                 &e.amount) == 4) {

        total += e.amount;
    }

    fclose(fp);

    printf("\n==================================================\n");
    printf("                   TOTAL EXPENSE\n");
    printf("==================================================\n");

    printf("\nTotal Expense = Rs. %.2f\n", total);
}

void categoryReport() {

    FILE *fp;
    struct Expense e;

    float food = 0;
    float travel = 0;
    float entertainment = 0;
    float others = 0;

    fp = fopen("expenses.txt", "r");

    if(fp == NULL) {
        printf("\nNo Expense Records Found!\n");
        return;
    }

    while(fscanf(fp, " %49[^|]|%29[^|]|%19[^|]|%f\n",
                 e.name,
                 e.category,
                 e.date,
                 &e.amount) == 4) {

        if(strcmp(e.category, "Food") == 0) {
            food += e.amount;
        }
        else if(strcmp(e.category, "Travel") == 0) {
            travel += e.amount;
        }
        else if(strcmp(e.category, "Entertainment") == 0) {
            entertainment += e.amount;
        }
        else {
            others += e.amount;
        }
    }

    fclose(fp);

    printf("\n==================================================\n");
    printf("                  CATEGORY REPORT\n");
    printf("==================================================\n");

    printf("\nFood           : Rs. %.2f\n", food);
    printf("Travel         : Rs. %.2f\n", travel);
    printf("Entertainment  : Rs. %.2f\n", entertainment);
    printf("Others         : Rs. %.2f\n", others);
}

void deleteExpense() {

    FILE *fp, *temp;
    struct Expense e;

    char searchName[50];
    int found = 0;

    fp = fopen("expenses.txt", "r");
    temp = fopen("temp.txt", "w");

    if(fp == NULL) {
        printf("\nNo Expense Records Found!\n");
        return;
    }

    printf("\n==================================================\n");
    printf("                 CURRENT EXPENSES\n");
    printf("==================================================\n");

    while(fscanf(fp, " %49[^|]|%29[^|]|%19[^|]|%f\n",
                 e.name,
                 e.category,
                 e.date,
                 &e.amount) == 4) {

        printf("\nExpense Name : %s\n", e.name);
        printf("Category     : %s\n", e.category);
        printf("Date         : %s\n", e.date);
        printf("Amount       : Rs. %.2f\n", e.amount);

        printf("--------------------------------------------------\n");
    }

    rewind(fp);

    printf("\nEnter Expense Name to Delete : ");
    scanf(" %[^\n]", searchName);

    while(fscanf(fp, " %49[^|]|%29[^|]|%19[^|]|%f\n",
                 e.name,
                 e.category,
                 e.date,
                 &e.amount) == 4) {

        if(strcmp(e.name, searchName) == 0) {
            found = 1;
        }
        else {

            fprintf(temp, "%s|%s|%s|%.2f\n",
                    e.name,
                    e.category,
                    e.date,
                    e.amount);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("expenses.txt");
    rename("temp.txt", "expenses.txt");

    if(found) {
        printf("\nExpense Deleted Successfully!\n");
    }
    else {
        printf("\nExpense Name Not Found!\n");
    }
}

void editExpense() {

    FILE *fp, *temp;
    struct Expense e;

    char searchName[50];
    int found = 0;

    fp = fopen("expenses.txt", "r");
    temp = fopen("temp.txt", "w");

    if(fp == NULL) {
        printf("\nNo Expense Records Found!\n");
        return;
    }

    printf("\n==================================================\n");
    printf("                 CURRENT EXPENSES\n");
    printf("==================================================\n");

    while(fscanf(fp, " %49[^|]|%29[^|]|%19[^|]|%f\n",
                 e.name,
                 e.category,
                 e.date,
                 &e.amount) == 4) {

        printf("\nExpense Name : %s\n", e.name);
        printf("Category     : %s\n", e.category);
        printf("Date         : %s\n", e.date);
        printf("Amount       : Rs. %.2f\n", e.amount);

        printf("--------------------------------------------------\n");
    }

    rewind(fp);

    printf("\nEnter Expense Name to Edit : ");
    scanf(" %[^\n]", searchName);

    while(fscanf(fp, " %49[^|]|%29[^|]|%19[^|]|%f\n",
                 e.name,
                 e.category,
                 e.date,
                 &e.amount) == 4) {

        if(strcmp(e.name, searchName) == 0) {

            found = 1;

            printf("\nEnter New Expense Name : ");
            scanf(" %[^\n]", e.name);

            printf("Enter New Category     : ");
            scanf(" %[^\n]", e.category);

            printf("Enter New Date         : ");
            scanf(" %[^\n]", e.date);

            printf("Enter New Amount       : ");
            scanf("%f", &e.amount);
        }

        fprintf(temp, "%s|%s|%s|%.2f\n",
                e.name,
                e.category,
                e.date,
                e.amount);
    }

    fclose(fp);
    fclose(temp);

    remove("expenses.txt");
    rename("temp.txt", "expenses.txt");

    if(found) {
        printf("\nExpense Updated Successfully!\n");
    }
    else {
        printf("\nExpense Name Not Found!\n");
    }
}

int main() {

    int choice;

    while(1) {

        system("cls");

        printf("\n==================================================\n");
        printf("     STUDENT EXPENSE TRACKER - SUJAN\n");
        printf("==================================================\n");

        printf("\n1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Total Expense\n");
        printf("4. Edit Expense\n");
        printf("5. Delete Expense\n");
        printf("6. Category Report\n");
        printf("7. Exit\n");

        printf("\nEnter Your Choice : ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                addExpense();
                break;

            case 2:
                viewExpenses();
                break;

            case 3:
                totalExpense();
                break;

            case 4:
                editExpense();
                break;

            case 5:
                deleteExpense();
                break;

            case 6:
                categoryReport();
                break;

            case 7:
                printf("\nExiting Program...\n");
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }

        printf("\n");
        system("pause");
    }

    return 0;
}
