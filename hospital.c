#include <stdio.h>
#include <string.h>

/* Definition of record of type patient */
typedef struct {
    int id, age, prate, bpress;
    char fname[20], lname[20], symptoms[100], blood_type[3];
    float temp, balance;    
} patient;

/* Global data variable */
FILE *file;

/* Function prototypes */
void insert_patient();
void write_patient();
void update_patient();
int find_patient();
void remove_patient();
int all_patient();
void display();


int main() {
    int option;
    do {
    menu: printf("\nNile Hospital Records\n");
    printf("1. Create a record for a new patient\n");
    printf("2. Modify the record of a current/former patient\n");
    printf("3. Search for the record of a current/former patient\n");
    printf("4. Delete a patient's record\n");
    printf("5. Display the records of all patients\n");
    printf("0. Exit the program\n");
    printf("\nPlease enter any numbered option to continue: ");
    scanf("%1d", &option);

    switch(option) {
        case 1:
        write_patient();
        break;

        case 2:
        update_patient();
        break;

        case 3:
        find_patient();
        break;

        case 4:
        remove_patient();
        break;

        case 5:
        all_patient();
        break;

        case 0:
        break;

        default:
        printf("Unknown\n");
        goto menu;
        break;
    }
    } while (option != 0);

    return 0;
}

/*function definitions*/

void insert_patient(patient *ind) {
    
    printf("\nEnter the patient's id: ");
    scanf("%d", &ind->id);
    printf("\nEnter the patient's first name: ");
    scanf("%s", ind->fname);
    printf("\nEnter the patient's last name: ");
    scanf("%s", ind->lname);
    printf("\nEnter the patient's age: ");
    scanf("%d", &ind->age);
    printf("\nEnter the patient's body temperature in celsius degrees: ");
    scanf("%f", &ind->temp);
    printf("\nEnter the patient's pulse rate: ");
    scanf("%d", &ind->prate);
    printf("\nEnter the patient's blood pressure: ");
    scanf("%d", &ind->bpress);
    printf("\nEnter the patient's symptoms(delimited by only comma without white spaces): ");
    scanf("%s", ind->symptoms);
    printf("\nEnter the patient's blood type: ");
    scanf("%s", ind->blood_type);
    printf("\nEnter the patient's hospital fees balance: ");
    scanf("%f", &ind->balance);
    printf("\n");
}

void write_patient() {
    patient ind;
    file = fopen("hosp.txt", "at");
    printf("\nPatient Record Creation");
    insert_patient(&ind);
    fprintf(file, "%d\t%s\t%s\t%d\t%f\t%d\t%d\t%s\t%s\t%f\n", ind.id, ind.fname, ind.lname, ind.age, ind.temp, ind.prate, ind.bpress, ind.symptoms, ind.blood_type, ind.balance);
    fclose(file);
    printf("\nNew patient's record has been successfully created\n");
}

void update_patient() {
    patient ind;
    FILE *file2;
    int id, found = 0;
    
    printf("\nPatient Record Modification");
    file = fopen("hosp.txt", "rt+");

    printf("\nEnter the patient's id to find the required record: ");
    scanf("%d", &id);

    file = fopen("hosp.txt", "rt");
    file2 = fopen("temporary.txt", "wt");



    while (fscanf(file, "%d %s %s %d %f %d %d %s %s %f", &ind.id, ind.fname, ind.lname, &ind.age, &ind.temp, &ind.prate, &ind.bpress, ind.symptoms, ind.blood_type, &ind.balance) != EOF)
    {
        if (ind.id != id) {
            fprintf(file2, "%d\t%s\t%s\t%d\t%f\t%d\t%d\t%s\t%s\t%f\n", ind.id, ind.fname, ind.lname, ind.age, ind.temp, ind.prate, ind.bpress, ind.symptoms, ind.blood_type, ind.balance);
        } else if (ind.id == id) {
            insert_patient(&ind);
            fprintf(file2, "%d\t%s\t%s\t%d\t%f\t%d\t%d\t%s\t%s\t%f\n", ind.id, ind.fname, ind.lname, ind.age, ind.temp, ind.prate, ind.bpress, ind.symptoms, ind.blood_type, ind.balance);
        }
    }

    fclose(file2);
    fclose(file);
    remove("hosp.txt");
    rename("temporary.txt", "hosp.txt");
}

int find_patient() {
    int id, flag;
    patient ind;
    printf("\nEnter the patient's id: ");
    scanf("%d", &id);
    file = fopen("hosp.txt", "rt");
    if (file == NULL) {
        printf("An error was encountered\n;");
        return 1;
    }
    while (fscanf(file, "%d %s %s %d %f %d %d %s %s %f", &ind.id, ind.fname, ind.lname, &ind.age, &ind.temp, &ind.prate, &ind.bpress, ind.symptoms, ind.blood_type, &ind.balance) != EOF) {
        if (ind.id == id) {
            display(ind);
            flag = 1;
        }
    }
    fclose(file);
    if (flag != 1) {
        printf("\nPatient's record requested does not exist\n");
    }
    return 0;
} 

void remove_patient() {
    int id;
    patient ind;
    FILE *file2;

    printf("\n\nPatient Record Deletion");
    printf("\nEnter the patient's id: ");
    scanf("%d", &id);

    file = fopen("hosp.txt", "rt");
    file2 = fopen("temporary.txt", "wt");

    while (fscanf(file, "%d %s %s %d %f %d %d %s %s %f", &ind.id, ind.fname, ind.lname, &ind.age, &ind.temp, &ind.prate, &ind.bpress, ind.symptoms, ind.blood_type, &ind.balance) != EOF)
    {
        if (ind.id != id)
        {
            fprintf(file2, "%d\t%s\t%s\t%d\t%f\t%d\t%d\t%s\t%s\t%f\n", ind.id, ind.fname, ind.lname, ind.age, ind.temp, ind.prate, ind.bpress, ind.symptoms, ind.blood_type, ind.balance);
        }
    }

    fclose(file2);
    fclose(file);
    remove("hosp.txt");
    rename("temporary.txt", "hosp.txt");
    printf("\nPatient's record successfully deleted\n");
}

int all_patient() {
    patient ind;
    printf("\n\nNile Hospital Records for all Patients\n");
    file = fopen("hosp.txt", "rt");
    if (file == NULL) {
        printf("An error was encountered");
        return 1;
    }
    while (fscanf(file, "%d %s %s %d %f %d %d %s %s %f", &ind.id, ind.fname, ind.lname, &ind.age, &ind.temp, &ind.prate, &ind.bpress, ind.symptoms, ind.blood_type, &ind.balance) != EOF)
    {
        display(ind);
        printf("\n\n");
    }
    
    fclose(file);
    return 0;
}

void display(patient ind) {
    printf("\nPatient's id: %d", ind.id);
    printf("\nPatient's first name: %s", ind.fname);
    printf("\nPatient's last name: %s", ind.lname);
    printf("\nPatient's age: %d", ind.age);
    printf("\nPatient's body temperature in celsius degrees: %f", ind.temp);
    printf("\nPatient's pulse rate: %d", ind.prate);
    printf("\nPatient's blood pressure: %d", ind.bpress);
    printf("\nPatient's symptoms: %s", ind.symptoms);
    printf("\nPatient's blood type: %s", ind.blood_type);
    printf("\nPatient's hospital fees balance: %0.2f\n", ind.balance);
}

