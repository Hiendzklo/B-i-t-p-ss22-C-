#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//cau truc Account
struct Account {
    char username[50];
    char password[50];
};
//Ðoc danh sach tai khoan tu file accounts.dat vao mang accounts
void loadAccounts(struct Account accounts[], int *count) {
    FILE *file = fopen("accounts.dat", "rb");
    if (file) {
        *count = fread(accounts, sizeof(struct Account), 100, file);
        fclose(file);
    } else {
        *count = 0; 
    }
}
//Luu danh sach tai khoan tu mang accounts vao file accounts.dat
void saveAccounts(struct Account accounts[], int count) {
    FILE *file = fopen("accounts.dat", "wb");
    if (file) {
        fwrite(accounts, sizeof(struct Account), count, file);
        fclose(file);
    }
}
//Kiem tra xem ten tai khoan da ton tai hay chua
int checkUsername(struct Account accounts[], int count, char *username) {
    for (int i = 0; i < count; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            return 1;
        }
    }
    return 0; 
}
//Cho phep nguoi dung dang ky tai khoan moi
void registerAccount(struct Account accounts[], int *count) {
    if (*count >= 100) { 
        printf("\nKhong the dang ky. Da dat gioi han so luong tai khoan.\n");
        return;
    }

    struct Account newAccount;
    char confirmPassword[50];

    printf("\nNhap ten tai khoan: ");
    scanf("%s", newAccount.username);

    if (checkUsername(accounts, *count, newAccount.username)) {
        printf("\nTen tai khoan da ton tai. Vui long chon ten tai khoan khac.\n");
        return;
    }

    printf("Nhap mat khau: ");
    scanf("%s", newAccount.password);

    printf("Xac nhan mat khau: ");
    scanf("%s", confirmPassword);

    if (strcmp(newAccount.password, confirmPassword) != 0) {
        printf("\nMat khau xac nhan khong khop. Vui long thu lai.\n");
        return;
    }

    accounts[*count] = newAccount;
    (*count)++;
    saveAccounts(accounts, *count);

    printf("\nDang ky tai khoan thanh cong.\n");
}
//Cho phep nguoi dung dang nhap vao he thong.
void login(struct Account accounts[], int count) {
    char username[50], password[50];

    printf("\nNhap ten tai khoan: ");
    scanf("%s", username);
    printf("Nhap mat khau: ");
    scanf("%s", password);

    for (int i = 0; i < count; i++) {
        if (strcmp(accounts[i].username, username) == 0 &&
            strcmp(accounts[i].password, password) == 0) {
            printf("\nDang nhap thanh cong.\n");
            return;
        }
    }
    printf("\nDang nhap that bai. Vui long kiem tra lai ten tai khoan va mat khau.\n");
}
//Giao dien chinh cho chuong trinh quan ly tai khoan.
int main() {
    struct Account accounts[100];
    int count;

    loadAccounts(accounts, &count);

    while (1) {
        printf("\nMENU\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login(accounts, count);
                break;
            case 2:
                registerAccount(accounts, &count);
                break;
            case 3:
                printf("\nThoat chuong trinh.\n");
                return 0;
            default:
                printf("\nLua chon khong hop le. Vui long thu lai.\n");
        }
    }
}

