#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 10
#define CHAR_SIZE 50



typedef struct doctor {
    char name[CHAR_SIZE];
    char address[CHAR_SIZE];
    char specialty[CHAR_SIZE];
    char visita[CHAR_SIZE];
}doctor;

struct doctors {
    doctor arr[MAX_SIZE];
};
typedef struct patient {
    char name[CHAR_SIZE];
    char username[CHAR_SIZE];
    char password[CHAR_SIZE];
}patient;
struct patients {
    patient arr[MAX_SIZE];
    int number_of_patients;
};
//DONE: importing data from files
bool import_users_data(struct patients *p) {
    FILE *fp;
    fp = fopen("users database.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return false;
    }
    fscanf(fp, "%d%*c", &(p->number_of_patients));
    for (int i = 0; i < p->number_of_patients; i++) {
        if(fscanf(fp,
            "%[^\t]\t%[^\t]\t%[^\n]%*c",
            p->arr[i].name, p->arr[i].username, p->arr[i].password) != 3) {
            printf("Error reading data\n");
            return false;
        }
    }
    fclose(fp);
    //DONE: loop through the patients in file to extract data
    return true;
}
bool import_data(struct doctors *p) {
    FILE *fp;
    fp = fopen("doctors database.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return false;
    }
    for (int i = 0; i < MAX_SIZE; i++) {
        fscanf(fp,
            "%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]%*c",
            p->arr[i].name, p->arr[i].address, p->arr[i].specialty, p->arr[i].visita);
    }
    fclose(fp);
    return true;
}

//DONE: erasing file data
void erase_file() {
    FILE *fp;
    fp = fopen("users database.txt", "w");
    fprintf(fp, "%d\n", 0);
    fclose(fp);
}


void sanitize_input(char input[]) {
    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        if (input[i] == '\t' || input[i] == '\\') {
            input[i] = ' ';
        }
    }
}

bool is_word(char word[]) {//the name should be free from special characters
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        if (!isalpha(word[i]) && !isspace(word[i])) {
            return false;
        }
    }
    return true;
}

//DONE: printing the main menu
void print_main_menu() {
    printf("\n\n\t\t\t\t\t\t\t\t******* WELCOME *******\n");
    printf("enter the number corresponding to the required operation: \n");
    printf("1. Sign up\n"
           "2. Log in\n"
           "3. Exit\n");
}
//DONE: printing menu
void print_menu() {

    printf("enter the number corresponding to the required operation: \n");
    printf("1. search a specialty\n"
           "2. view all available doctors\n"
           "3. Log out\n");
}

bool available_speciality(char speciality[], struct doctors p) {
    bool correct = false;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (strcmp(strlwr(p.arr[i].specialty), strlwr(speciality)) == 0) {
            correct = true;
        }
    }
    return correct;
}

void search_speciality(struct doctors p) {
    printf("Enter the required speciality: ");
    char speciality[CHAR_SIZE];
    bool tried = false;
    do {
        if (tried) {
            printf("This speciality is not available.");
        }
        scanf("%[^\n]%*c", speciality);

        tried = true;
    } while(!available_speciality(speciality, p));
    printf("The available doctors for %s: \n", speciality);

    for (int i = 0; i < MAX_SIZE; i++) {
        if(strcmp(strlwr(p.arr[i].specialty), strlwr(speciality)) == 0){
            printf("%s\t%s\t%s\n", p.arr[i].name, p.arr[i].address, p.arr[i].visita);
        }
    }
}

//DONE: check if username exists
bool username_exists(char username[], struct patients p) {
    bool exists = false;
    for (int i = 0; i < p.number_of_patients; i++) {
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

//DONE: sign up
bool sign_up(struct patients p) {

    if(p.number_of_patients >= MAX_SIZE) {
        printf("Limit exceeded. Can not sign you up");
        return false;
    }


    printf("Enter your full name: ");
    char full_name[CHAR_SIZE];
    bool tried = false;
    do {
        if (tried) {
            printf("your name shouldn't include special characters");
        }
        scanf("%49[^\n]%*c", full_name);

        sanitize_input(full_name);
        tried = true;
    } while (!is_word(full_name));

    printf("Enter your username: ");
    char username[CHAR_SIZE];
    tried = false;
    do {
        if (tried) {
            printf("This username already exists.\n TRY AGAIN: ");
        }
        scanf("%49s%*c", username);
        sanitize_input(username);
        tried = true;
    } while (username_exists(username, p));

    printf("Enter your password: ");
    char password1[CHAR_SIZE];
    scanf("%49s%*c", password1);
    sanitize_input(password1);
    printf("ReEnter your password: ");
    char password2[CHAR_SIZE];
    tried = false;
    do {
        if (tried) {
            printf("The two passwords don't match, try again: ");
        }
        scanf("%49s%*c", password2);
        sanitize_input(password2);
        tried = true;
    } while (strcmp(password1, password2) != 0);


    //check if username exists: done while taking input

    //DONE: write to file
    //add 1 to current number of patients
    FILE *fp;
    fp = fopen("users database.txt", "r+");
    if (fp == NULL) {
        printf("Error opening file\n");
        return false;
    }
    int number_of_patients;
    fscanf(fp, "%d%*c", &number_of_patients);
    rewind(fp);
    fprintf(fp, "%d", ++number_of_patients);
    fseek(fp, 0, SEEK_END);

    fprintf(fp, "%s\t%s\t%s\n", full_name, username, password1);
    fclose(fp);
    return true;
}
//DONE: log in
bool log_in(struct patients p) {
    printf("Enter your username: ");
    char username[CHAR_SIZE];
    bool tried = false;
    do {
        if (tried) {
            printf("Unable to find this username, make sure it is written correctly: ");
        }
        scanf("%49[^\n]%*c", username);
        sanitize_input(username);
        tried = true;
    } while (!username_exists(username, p));


    printf("Enter your password: ");
    char password[CHAR_SIZE];
    tried = false;
    do {
        if (tried) {
            printf("Wrong password, try again: ");
        }
        scanf("%49[^\n]%*c", password);
        sanitize_input(password);
        tried = true;
    } while(!correct_password(username, password, p));

    //check if username exists: done while taking input

    //check if password is correct: done while taking input


    return true;
}


//DONE: printing doctors data
void print_all_doctors(struct doctors p) {
    printf("%-30s|%-30s|%-20s|%-15s\n", "doctor name", "address", "specialty", "visita");
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%-30s\t%-30s\t%-20s\t%-15s\n", p.arr[i].name, p.arr[i].address, p.arr[i].specialty, p.arr[i].visita);
    }
}

void print_all_patients(struct patients p) {
    for (int i = 0; i < p.number_of_patients; i++) {
        printf("%s\t%s\t%s\n", p.arr[i].name, p.arr[i].username, p.arr[i].password);
    }
}


//clear screen function
void clrscr()
{
    system("cls||clear");
}

int main() {
    //erase_file();
    //print_all_patients(patients);

    bool log;
    while(true) {
        log = true;

        struct doctors doctors;
        struct patients patients;
        if(!import_data(&doctors)) {
            printf("Error importing data\n");
        }
        if(!import_users_data(&patients)) {
            printf("Error importing data\n");
        }

        print_main_menu();
        char op;
        do {
            scanf("%c%*c", &op);
        } while (op < '0' || op > '3');
        switch (op) {
            case '1':
                if(!sign_up(patients)) {
                    continue;
                }
            break;
            case '2':
                if(log_in(patients)) {
                    clrscr();
                    printf("Logged in\n");
                }
            break;
            case '3':
                return 0;
            default:
                break;
        }
        while(log){
            print_menu();
            char op2;
            do {
                scanf("%c%*c", &op2);
            } while (op2 < '0' || op2 > '3');
            switch (op2) {
                case '1':
                    search_speciality(doctors);
                break;
                case '2':
                    print_all_doctors(doctors);
                break;
                case '3':
                    log = false;
                break;
            }
        }
    }
}
