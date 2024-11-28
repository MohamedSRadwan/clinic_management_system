#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 10


//TODO: importing data from files
typedef struct doctor {
    char name[20];
    char address[20];
    char specialty[20];
    int visita;
}doctor;

struct doctors {
    doctor arr[MAX_SIZE];
};
typedef struct patient {
    char name[20];
    char username[20];
    char password[20];
}patient;
struct patients {
    patient arr[MAX_SIZE];
};


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

//TODO: sign up
bool sign_up() {
    printf("\033[2J\033[H");
    printf("Enter your full name: ");
    char full_name[50];
    do {
        scanf("%[^\n]%*c", full_name);
    } while (!is_word(full_name));
    printf("Enter your username: ");
    char username[50];
    do {
        scanf("%s%*c", username);
    } while (!is_word(username) || username_exists(username, patients));
    printf("Enter your password: ");
    char password1[50];
    scanf("%s%*c", password1);
    printf("ReEnter your password: ");
    char password2[50];
    scanf("%s%*c", password2);
    if (strcmp(password1, password2) != 0) {
        return false;
    }

    //check if username exists: done while taking input

    //TODO: write to file

    return true;
}
//TODO: log in
bool log_in() {
    printf("\033[2J\033[H");
    printf("Enter your username: ");
    char username[50];
    do {
        scanf("%s%*c", username);
    } while (!is_word(username) || username_exists(username, patients));


    printf("Enter your password: ");
    char password[50];
    do {
        scanf("%s%*c", password);
    } while(!correct_password(username, password, patients));

    //check if username exists: done while taking input

    //check if password is correct: done while taking input

}
//TODO: printing doctors data

//read from file


//clear screen function
void clrscr()
{
    system("@cls||clear");
}

int main() {
    //print main menu
    // print_main_menu();
    // char op;
    // do {
    //     scanf("%c%*c", &op);
    // } while (op < '0' || op > '3');
    // switch (op) {
    //     case '1':
    //         sign_up();
    //         break;
    //     case '2':
    //         log_in();
    //         break;
    //     case '3':
    //
    //         break;
    //     default:
    //         break;
    // }
    //clearing screen test: all three working on vs code but not clion 😢

    printf("heelo");
    // printf("\033[2J\033[H");
    // system("cls");
    clrscr();
    printf("hai");
    // FILE *fp;
    // fp = fopen("users database.txt", "w");
    // if (fp == NULL) {
    //     printf("Error opening file");
    //     return 1;
    // }
    // char text[2000] = "";
    // fprintf(fp, "%s\n", text);

    //take operation sign up or log in


}
