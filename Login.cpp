#include <iostream>
#include <string>
#include "login.h"

using namespace std;

struct Akun {
    string username;
    string password;
    string role;
};

string prosesLogin() {
    int percobaan = 0;
    string inputUser, inputPass;

    Akun daftarAkun[] = {
        {"admin", "123", "admin"},
        {"user", "123", "user"}
    };

    int jumlahAkun = sizeof(daftarAkun) / sizeof(daftarAkun[0]);

    if (jumlahAkun == 0) {
        cout << "Belum ada akun yang terdaftar!\n";
        return "no_account";
    }

    while (percobaan < 3) {
        cout << "\n--- SILAHKAN LOGIN ---\n";
        cout << "Username: ";
        cin >> inputUser;
        cout << "Password: ";
        cin >> inputPass;

        bool ditemukan = false;

        for (int i = 0; i < jumlahAkun; i++) {
            if (daftarAkun[i].username == inputUser &&
                daftarAkun[i].password == inputPass) {

                cout << "Login Berhasil!\n";

                return daftarAkun[i].role; 
            }
        }

        percobaan++;
        cout << "Username atau Password Salah!\n";
        cout << "Sisa percobaan: " << 3 - percobaan << endl;
    }

    cout << "\nLogin Gagal! Akses Ditolak.\n";
    return "invalid";
}