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
//TODO: importing data from files
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
    //DONE: loop through the patients in file to extract data.... problem in determining the number of iterations
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

bool is_word(char word[]) {
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

    system("cls");
    printf("\033[2J\033[H");
    printf("enter the number corresponding to the required operation: \n");
    printf("1. Sign up\n"
           "2. Log in\n");
}

//DONE: printing menu





//TODO: the functionalities here
bool available_speciality(char speciality[], struct doctors p) {
    bool correct = false;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (strcmp(p.arr[i].specialty, speciality) == 0) {
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
    for (int i = 0; i < MAX_SIZE; i++) {
        if(strcmp(p.arr[i].specialty, speciality) == 0){
            printf("%s\t%s\t%s\n", p.arr[i].name, p.arr[i].address, p.arr[i].visita);
        }
    }
}





void print_menu() {

    system("cls");
    //printf("\033[2J\033[H");
    printf("enter the number corresponding to the required operation: \n");
    printf("1. search a specialty\n"
           "2. view all available doctors\n"
           "3. Book an appointment\n");
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
    char full_name[CHAR_SIZE];
    bool tried = false;
    do {
        if (tried) {
            printf("your name shouldn't include special characters");
        }
        scanf("%[^\n]%*c", full_name);
        tried = true;
    } while (!is_word(full_name));
    printf("Enter your username: ");
    char username[CHAR_SIZE];
    tried = false;
    do {
        if (tried) {
            printf("This username already exists. TRY AGAIN: ");
        }
        scanf("%s%*c", username);

        tried = true;
    } while (username_exists(username, p));
    printf("Enter your password: ");
    char password1[CHAR_SIZE];
    scanf("%s%*c", password1);
    printf("ReEnter your password: ");
    char password2[CHAR_SIZE];
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
    fprintf(fp, "%d\n", ++number_of_patients);
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
        scanf("%[^\n]%*c", username);

        tried = true;
    } while (!username_exists(username, p));


    printf("Enter your password: ");
    char password[CHAR_SIZE];
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


    return true;
}


//DONE: printing doctors data
void print_all_doctors(struct doctors p) {
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%s\t%s\t%s\t%s\n", p.arr[i].name, p.arr[i].address, p.arr[i].specialty, p.arr[i].visita);
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
    system("@cls||clear");
}

int main() {
    //erase_file();
    struct doctors doctors;
    struct patients patients;
    if(!import_data(&doctors)) {
        printf("Error importing data\n");
    }
    if(!import_users_data(&patients)) {
        printf("Error importing data\n");
    }
    print_all_doctors(doctors);
    print_all_patients(patients);
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
            print_menu();
            break;
        case '2':
            if(log_in(patients)) {
                printf("Logged in\n");
                print_menu();
            }
            break;
        //TODO: case 3 if exists
        case '3':

            break;
        default:
            break;
    }

    //TODO: add functionality here
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
    }

//clearing screen test: all three working on vs code but not clion 😢
// printf("heelo");
    // printf("\033[2J\033[H");
    // system("cls");
    // clrscr();
    // printf("hai");
}
