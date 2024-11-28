#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

//TODO: check if username exists
bool username_exists() {

}

//TODO: sign up
bool sign_up() {
    printf("\033[2J\033[H");
    printf("Enter your full name: ");
    char full_name[50];
    scanf("%[^\n]%*c", full_name);
    printf("Enter your username: ");
    char username[50];
    scanf("%s%*c", username);
    printf("Enter your password: ");
    char password1[50];
    scanf("%s%*c", password1);
    printf("ReEnter your password: ");
    char password2[50];
    scanf("%s%*c", password2);
    if (strcmp(password1, password2) != 0) {
        return false;
    }

    //check if username exists
    //write to file

    return true;
}
//TODO: log in
bool log_in() {
    printf("\033[2J\033[H");
    printf("Enter your username: ");
    char username[50];
    scanf("%s%*c", username);
    printf("Enter your password: ");
    char password[50];
    scanf("%s%*c", password);

    //check if username exists

    //check if password is correct
}
//TODO: printing doctors data

//read from file

//TODO: importing data from files
typedef struct doctor {
    char name[20];
    char address[20];
    char specialty[20];
    int visita;
}doctor;

struct doctors {
    doctor arr[10];
};


int main() {
    //print main menu

    //clearing screen test

    // printf("heelo");
    // printf("\033[2J\033[H");
    // system("cls");
    // printf("hai");
    FILE *fp;
    fp = fopen("users database.txt", "w");
    if (fp == NULL) {
        printf("Error opening file");
        return 1;
    }
    char text[2000] = "";
    fprintf(fp, "%s\n", text);

    //take operation sign up or log in


}
