#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 10



typedef struct doctor {
    char name[20];
    char address[20];
    char specialty[20];
    char visita[];
}doctor;

struct doctors {
    doctor arr[MAX_SIZE];
};
typedef struct patient {
    char name[20];
    char username[20];
    char password[20];
    bool signed_in;
}patient;
struct patients {
    patient arr[MAX_SIZE];
};
//TODO: importing data from files
bool import_users_data(struct patients p) {
    FILE *fp;
    fp = fopen("users database.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return false;
    }
    //TODO: loop through the patients in file to extract data.... problem in determining the number of iterations
}
bool import_data(struct doctors p) {
    FILE *fp;
    fp = fopen("doctors database.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return false;
    }
    for (int i = 0; i < MAX_SIZE; i++) {
        fscanf(fp,
            "%[^\t]\t%[^\t]\t%[^t]\t%[^\n]%*c",
            p.arr[i].name, p.arr[i].address, p.arr[i].specialty, p.arr[i].visita);
    }
    fclose(fp);
    return true;
}

//DONE: erasing file data
void erase_file() {
    FILE *fp;
    fp = fopen("users database.txt", "w");
    fclose(fp);
}

bool is_word(char word[]) {
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        if (!isalpha(word[i]) && !isspace(word[i])) {
            return false;
        }
    }
    return true;
}

//TODO: printing the main menu
void print_main_menu() {
    printf("\033[2J\033[H");
    printf("enter the number corresponding to the required operation: \n");
    printf("1. Sign up\n"
           "2. Log in\n");
}

//TODO: printing menu
//TODO: the functionalities here
void print_menu() {

    printf("\033[2J\033[H");
    printf("enter the number corresponding to the required operation: \n");
    printf("1. search a specialty\n"
           "2. view all available doctors\n"
           "3. Book an appointment");
}

//DONE: check if username exists
bool username_exists(char username[], struct patients p) {
    bool exists = false;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (strcmp(p.arr[i].username, username) == 0) {
            exists = true;
        }
    }
    return exists;
}
//DONE: check if the user's password is correct
bool correct_password(char username[], char password[], struct patients p) {
    bool correct = false;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (strcmp(p.arr[i].username, username) == 0) {
            if (strcmp(p.arr[i].password, password) == 0) {
                correct = true;
            }
        }
    }
    return correct;
}
int index_of_patient (char username[], struct patients p) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (strcmp(p.arr[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

//DONE: sign up
bool sign_up(struct patients p) {
    printf("Enter your full name: ");
    char full_name[50];
    do {
        scanf("%[^\n]%*c", full_name);
    } while (!is_word(full_name));
    printf("Enter your username: ");
    char username[50];
    bool tried = false;
    do {
        if (tried) {
            printf("This username already exists. TRY AGAIN: ");
        }
        scanf("%s%*c", username);

        tried = true;
    } while (username_exists(username, p));
    printf("Enter your password: ");
    char password1[50];
    scanf("%s%*c", password1);
    printf("ReEnter your password: ");
    char password2[50];
    tried = false;
    do {
        if (tried) {
            printf("The two passwords don't match, try again: ");
        }
        scanf("%s%*c", password2);

        tried = true;
    } while (strcmp(password1, password2) != 0);


    //check if username exists: done while taking input

    //DONE: write to file
    FILE *fp;
    fp = fopen("users database.txt", "a");
    if (fp == NULL) {
        printf("Unable to open file");
        return false;
    }
    fprintf(fp, "%s\t%s\t%s\n", full_name, username, password1);
    fclose(fp);
    return true;
}
//DONE: log in
bool log_in(struct patients p) {
    printf("Enter your username: ");
    char username[50];
    bool tried = false;
    do {
        if (tried) {
            printf("Unable to find this username, make sure it is written correctly: ");
        }
        scanf("%[^\n]%*c", username);

        tried = true;
    } while (username_exists(username, p));


    printf("Enter your password: ");
    char password[50];
    tried = false;
    do {
        if (tried) {
            printf("Wrong password, try again: ");
        }
        scanf("%[^\n]%*c", password);

        tried = true;
    } while(!correct_password(username, password, p));

    //check if username exists: done while taking input

    //check if password is correct: done while taking input

    //flag the user as logged in
    int idx = index_of_patient(username, p);
    p.arr[idx].signed_in = true;
    return true;
}


//TODO: printing doctors data

//read from file


//clear screen function
void clrscr()
{
    system("@cls||clear");
}

int main() {
    struct doctors doctors;
    struct patients patients;

    if(!import_data(doctors)) {
        printf("Error importing data\n");

    }
    //print main menu
    print_main_menu();
    char op;
    do {
        scanf("%c%*c", &op);
    } while (op < '0' || op > '3');

    //TODO: after logging in , show menu
    switch (op) {
        case '1':
            sign_up(patients);
            break;
        case '2':
            if(log_in(patients)) {
                printf("Logged in\n");
            }
            break;
        //TODO: case 3 if exists
        case '3':

            break;
        default:
            break;
    }
    //add functionality here


//clearing screen test: all three working on vs code but not clion 😢
// printf("heelo");
    // printf("\033[2J\033[H");
    // system("cls");
    // clrscr();
    // printf("hai");
}
