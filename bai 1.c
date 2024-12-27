#include <stdio.h>
#include <string.h>

//Cau truc Student
struct Student {
    int id;
    char name[100];
    int age;
};
// Ðoc du lieu tu file nhi phan students.dat và luu vao mang students
void loadStudents(struct Student students[], int *count) {
    FILE *file = fopen("students.txt", "rb");
    if (file) {
        *count = fread(students, sizeof(struct St udent), 100, file);
        fclose(file);
    } else {
        *count = 0;
    }
}
//Luu danh sach sinh vien tu mang students vao file students.dat
void saveStudents(struct Student students[], int count) {
    FILE *file = fopen("students.txt", "wb");
    if (file) {
        fwrite(students, sizeof(struct Student), count, file);
        fclose(file);
    }
}
//Hien thi danh sach sinh vien trong mang students.
void printStudents(struct Student students[], int count) {
    printf("\nDanh sach sinh vien:\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
    }
}
//Them mot sinh vien moi vao mang students.
void addStudent(struct Student students[], int *count) {
    if (*count >= 100) {
        printf("\nKhong the them sinh vien. Bo nho day.\n");
        return;
    }
    printf("\nNhap ID: ");
    scanf("%d", &students[*count].id);
    printf("Nhap Ten: ");
    getchar(); 
    fgets(students[*count].name, sizeof(students[*count].name), stdin);
    students[*count].name[strcspn(students[*count].name, "\n")] = '\0';
    printf("Nhap Tuoi: ");
    scanf("%d", &students[*count].age);
    (*count)++;
    saveStudents(students, *count);
    printf("\nSinh vien da duoc them thanh cong.\n");
}
//Cap nhat thong tin cua sinh vien dua tren ID.
void updateStudent(struct Student students[], int count) {
    int id;
    printf("\nNhap ID sinh vien can sua: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Nhap Ten moi: ");
            getchar(); 
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0'; 
            printf("Nhap Tuoi moi: ");
            scanf("%d", &students[i].age);
            saveStudents(students, count);
            printf("\nCap nhat thong tin thanh cong.\n");
            return;
        }
    }
    printf("\nKhong tim thay sinh vien voi ID nay.\n");
}
//Xoa sinh vien khoi danh sach dua tren ID.
void deleteStudent(struct Student students[], int *count) {
    int id;
    printf("\nNhap ID sinh vien can xoa: ");
    scanf("%d", &id);
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            saveStudents(students, *count);
            printf("\nSinh vien da duoc xoa thanh cong.\n");
            return;
        }
    }
    printf("\nKhong tim thay sinh vien voi ID nay.\n");
}
//Tim kiem sinh vien theo ten.
void findStudent(struct Student students[], int count) {
    char name[100];
    printf("\nNhap ten sinh vien can tim: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; 
    printf("\nKet qua tim kiem:\n");
    for (int i = 0; i < count; i++) {
        if (strstr(students[i].name, name)) {
            printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
        }
    }
}
//Sap xep danh sach sinh vien theo tuoi tang dan.
void sortStudents(struct Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (students[i].age > students[j].age) {
                struct Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    saveStudents(students, count);
    printf("\nDanh sach sinh vien da duoc sap xep theo tuoi.\n");
}

int main() {
    struct Student students[100];
    int count;
    loadStudents(students, &count);

    while (1) {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printStudents(students, count);
                break;
            case 2:
                addStudent(students, &count);
                break;
            case 3:
                updateStudent(students, count);
                break;
            case 4:
                deleteStudent(students, &count);
                break;
            case 5:
                findStudent(students, count);
                break;
            case 6:
                sortStudents(students, count);
                break;
            case 7:
                printf("\nThoat chuong trinh.\n");
                return 0;
            default:
                printf("\nLua chon khong hop le. Vui long chon lai.\n");
        }
    }
}

