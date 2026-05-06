#include <iostream>
#include "login.h"
#include "admin.h"

using namespace std;

int main() {
    int pilihan;

    do {
        cout << "\n======= MENU UTAMA =======" << endl;
        cout << "1. Head of SDN" << endl;
        cout << "2. Dispatcher" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1 || pilihan == 2) {

            string role = prosesLogin();

            if (role == "admin") {
                cout << "\n>>> Login sebagai ADMIN berhasil <<<" << endl;
                menuAdmin();
            }
            else if (role == "user") {
                cout << "\n>>> Login sebagai USER <<<" << endl;
                cout << "\n>>> Anda sekarang berada di fitur pilihan " << pilihan << " <<<" << endl;
            }
            else {
                cout << "Login gagal. Kembali ke Menu Utama..." << endl;
            }
        }
        else if (pilihan == 0) {
            cout << "Terimakasih Telah Menggunakan Program Ini" << endl;
        }
        else {
            cout << "Pilihan Tidak Valid!" << endl;
        }

    } while (pilihan != 0);

    return 0;
}