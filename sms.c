```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n");
        printf("====================================================\n");
        printf("        🎓 STUDENT MANAGEMENT SYSTEM 🎓\n");
        printf("====================================================\n");
        printf("1. ➕ Add Student\n");
        printf("2. 📋 Display All Students\n");
        printf("3. 🔍 Search Student\n");
        printf("4. ✏️ Update Student\n");
        printf("5. ❌ Delete Student\n");
        printf("6. 🚪 Exit\n");
        printf("====================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("\nThank you for using Student Management System!\n");
                exit(0);
            default:
                printf("\n❌ Invalid Choice! Try Again.\n");
        }
    }

    return 0;
}

// Add Student
void addStudent() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "ab");

    printf("\nEnter Student ID    : ");
    scanf("%d", &s.id);

    printf("Enter Student Name  : ");
    scanf(" %[^\n]", s.name);

    printf("Enter Age           : ");
    scanf("%d", &s.age);

    printf("Enter Marks         : ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("\n✅ Student Record Added Successfully!\n");
}

// Display Students
void displayStudents() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("\n⚠ No Records Found!\n");
        return;
    }

    printf("\n");
    printf("+------+----------------------+------+---------+\n");
    printf("| ID   | Name                 | Age  | Marks   |\n");
    printf("+------+----------------------+------+---------+\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("| %-4d | %-20s | %-4d | %-7.2f |\n",
               s.id, s.name, s.age, s.marks);
    }

    printf("+------+----------------------+------+---------+\n");

    fclose(fp);
}

// Search Student
void searchStudent() {
    FILE *fp;
    struct Student s;
    int id, found = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("\n⚠ No Records Found!\n");
        return;
    }

    printf("\nEnter Student ID to Search: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("\n🎯 Student Found!\n");
            printf("--------------------------------\n");
            printf("ID    : %d\n", s.id);
            printf("Name  : %s\n", s.name);
            printf("Age   : %d\n", s.age);
            printf("Marks : %.2f\n", s.marks);
            printf("--------------------------------\n");

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n❌ Student Not Found!\n");
    }

    fclose(fp);
}

// Update Student
void updateStudent() {
    FILE *fp;
    struct Student s;
    int id, found = 0;

    fp = fopen("students.dat", "rb+");

    if (fp == NULL) {
        printf("\n⚠ No Records Found!\n");
        return;
    }

    printf("\nEnter Student ID to Update: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {

        if (s.id == id) {

            printf("\nEnter New Name  : ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Age   : ");
            scanf("%d", &s.age);

            printf("Enter New Marks : ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            printf("\n✅ Record Updated Successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n❌ Student Not Found!\n");
    }

    fclose(fp);
}

// Delete Student
void deleteStudent() {

    FILE *fp, *temp;
    struct Student s;
    int id, found = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("\n⚠ No Records Found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    printf("\nEnter Student ID to Delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {

        if (s.id == id) {
            found = 1;
            continue;
        }

        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("\n✅ Record Deleted Successfully!\n");
    else
        printf("\n❌ Student Not Found!\n");
}
```
