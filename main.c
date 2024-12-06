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
    char speciality[CHAR_SIZE];
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
            p->arr[i].name, p->arr[i].address, p->arr[i].speciality, p->arr[i].visita);
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
    if (len == 0) {
        return false;
    }
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
    printf("1. search a speciality\n"
           "2. view all available doctors\n"
           "3. Log out\n");
}

bool available_speciality(char speciality[], struct doctors p) {
    bool correct = false;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (strcmp(strlwr(p.arr[i].speciality), strlwr(speciality)) == 0) {
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
        scanf("%49[^\n]%*c", speciality);
        if (strlen(speciality) == 0) {
            getchar();
            return;
        }
        sanitize_input(speciality);
        tried = true;
    } while(!available_speciality(speciality, p));
    printf("The available doctors for %s: \n", speciality);

    for (int i = 0; i < MAX_SIZE; i++) {
        if(strcmp(strlwr(p.arr[i].speciality), strlwr(speciality)) == 0){
            printf("%-25s\t%-40s\t%-15s\n", p.arr[i].name, p.arr[i].address, p.arr[i].visita);
        }
    }
}

//DONE: check if username exists
bool username_exists(char username[], struct patients p) {
    bool exists = false;
    if (strlen(username) == 0) {
        return false;
    }
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
    if (strlen(password) == 0) {
        return false;
    }
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
         if (strlen(full_name) == 0) {
             getchar();
             return false;
         }
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
        scanf("%49[^\n]%*c", username);
        if (strlen(username) == 0) {
            getchar();
            return false;
        }
        sanitize_input(username);
        tried = true;
    } while (username_exists(username, p));

    printf("Enter your password: ");
    char password1[CHAR_SIZE];
    scanf("%49[^\n]%*c", password1);
    sanitize_input(password1);
    if (strlen(password1) == 0) {
        getchar();
        return false;
    }
    printf("ReEnter your password: ");
    char password2[CHAR_SIZE];
    if (strlen(password2) == 0) {
        getchar();
        return false;
    }
    tried = false;
    do {
        if (tried) {
            printf("The two passwords don't match, try again: ");
        }
        scanf("%49[^\n]%*c", password2);
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
    if (p.number_of_patients == 0) {
        printf("no users signed up, sign up first\n");
        return false;
    }
    printf("Enter your username: ");
    char username[CHAR_SIZE];
    bool tried = false;
    do {
        if (tried) {
            printf("Unable to find this username, make sure it is written correctly: ");
        }
        scanf("%49[^\n]%*c", username);
        if (strlen(username) == 0) {
            getchar();
            return false;
        }
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
        if (strlen(password) == 0) {
            getchar();
            return false;
        }
        sanitize_input(password);
        tried = true;
    } while(!correct_password(username, password, p));

    //check if username exists: done while taking input

    //check if password is correct: done while taking input


    return true;
}


//DONE: printing doctors data
void print_all_doctors(struct doctors p) {
    printf("%-25s\t|%-40s\t|%-20s\t|%-15s\n", "doctor name", "address", "speciality", "visita");
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%-25s\t%-40s\t%-20s\t%-15s\n", p.arr[i].name, p.arr[i].address, p.arr[i].speciality, p.arr[i].visita);
    }
}

void print_all_patients(struct patients p) {//for debugging, not part of code
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

    while(true) {


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
        bool tried = false;
        do {
            if(tried) {
                printf("Enter a correct operation: ");
            }
            scanf("%c", &op);
            if (op == '\n') {
                tried = true;
                continue;
            }
            while (getchar() != '\n');
            tried = true;
        } while (op < '0' || op > '3');
        switch (op) {
            case '1':
                if(!sign_up(patients)) {
                    continue;
                }
            break;
            case '2':
                if(!log_in(patients)) {
                    sign_up(patients);
                }
                printf("Logged in\n");

            break;
            case '3':
                return 0;
            default:
                break;
        }
        while(true){
            print_menu();
            char op2;
            tried = false;
            do {
                if(tried) {
                    printf("Enter a correct operation: ");
                }
                scanf("%c", &op2);
                if (op2 == '\n') {
                    tried = true;
                    continue;
                }
                while (getchar() != '\n');
                tried = true;
            } while (op2 < '0' || op2 > '3');
            switch (op2) {
                case '1':
                    search_speciality(doctors);
                break;
                case '2':
                    print_all_doctors(doctors);
                break;
                case '3':
                    return 0;
            }
        }
    }
}
