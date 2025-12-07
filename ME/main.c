#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERFILE "credentials.txt"
#define DATAFILE "students.txt"

struct Student {
    int roll;
    char name[50];
    float marks;
};

void adminMenu();
void staffMenu();
void guestMenu();

int login(char *role);

/* ======================= MAIN ========================== */

int main() {
    char role[20];

    if (login(role)) {
        if (strcmp(role, "ADMIN") == 0)
            adminMenu();
        else if (strcmp(role, "STAFF") == 0)
            staffMenu();
        else
            guestMenu();
    } else {
        printf("\nLogin failed.\n");
    }

    return 0;
}

/* ======================= LOGIN ========================== */

int login(char *role) {
    char u[30], p[30], fileU[30], fileP[30], fileRole[20];

    printf("\n=== LOGIN ===\n");
    printf("Username: ");
    scanf("%s", u);
    printf("Password: ");
    scanf("%s", p);

    FILE *fp = fopen(USERFILE, "r");
    if (!fp) {
        printf("Error: login.txt missing\n");
        return 0;
    }

    while (fscanf(fp, "%s %s %s", fileU, fileP, fileRole) == 3) {
        if (strcmp(u, fileU) == 0 && strcmp(p, fileP) == 0) {
            strcpy(role, fileRole);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

/* ======================= FILE OPS ========================== */

void addStudent() {
    struct Student s;

    FILE *fp = fopen(DATAFILE, "a");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nEnter Roll No: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    fclose(fp);

    printf("Student added successfully.\n");
}

void viewStudents() {
    struct Student s;

    FILE *fp = fopen(DATAFILE, "r");
    if (!fp) {
        printf("No data available.\n");
        return;
    }

    printf("\nROLL\tNAME\tMARKS\n");
    printf("-----------------------------\n");

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        printf("%d\t%s\t%.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    int r, found = 0;
    struct Student s;

    FILE *fp = fopen(DATAFILE, "r");
    if (!fp) {
        printf("Error opening file\n");
        return;
    }

    printf("\nEnter Roll No: ");
    scanf("%d", &r);

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == r) {
            printf("FOUND: %d %s %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");

    fclose(fp);
}

void updateStudent() {
    int r, found = 0;
    struct Student s;

    FILE *fp = fopen(DATAFILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("\nEnter Roll No to update: ");
    scanf("%d", &r);

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == r) {
            printf("Enter new name: ");
            scanf("%s", s.name);
            printf("Enter new marks: ");
            scanf("%f", &s.marks);
            found = 1;
        }
        fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove(DATAFILE);
        rename("temp.txt", DATAFILE);
        printf("Updated successfully.\n");
    } else {
        printf("Roll number not found.\n");
        remove("temp.txt");
    }
}

void deleteStudent() {
    int r, found = 0;
    struct Student s;

    FILE *fp = fopen(DATAFILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("\nEnter Roll No to delete: ");
    scanf("%d", &r);

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == r) {
            found = 1;
            continue;
        }
        fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove(DATAFILE);
        rename("temp.txt", DATAFILE);
        printf("Deleted successfully.\n");
    } else {
        printf("Roll No not found.\n");
        remove("temp.txt");
    }
}

/* ======================= MENUS ========================== */

void adminMenu() {
    int ch;

    do {
        printf("\n=== ADMIN MENU ===\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search\n");
        printf("4. Update\n");
        printf("5. Delete\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: return;
            default: printf("Invalid choice\n");
        }
    } while (1);
}

void staffMenu() {
    int ch;

    do {
        printf("\n=== STAFF MENU ===\n");
        printf("1. View Students\n");
        printf("2. Search\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: viewStudents(); break;
            case 2: searchStudent(); break;
            case 3: return;
            default: printf("Invalid\n");
        }
    } while (1);
}

void guestMenu() {
    printf("\n=== GUEST MODE ===\n");
    printf("Only viewing allowed.\n\n");
    viewStudents();
}
