#include <iostream>
#include "login.h"

using namespace std;

string prosesLogin() {
    int percobaan = 0;
    string inputUser, inputPass;

    while (percobaan < 3) {
        cout << "\n--- SILAHKAN LOGIN ---" << endl;
        cout << "Username: "; cin >> inputUser;
        cout << "Password: "; cin >> inputPass;

        // ADMIN
        if (inputUser == "admin" && inputPass == "123") {
            cout << "Login Admin Berhasil!" << endl;
            return "admin";
        }

        // USER
        else if (inputUser == "user" && inputPass == "123") {
            cout << "Login User Berhasil!" << endl;
            return "user";
        }

        else {
            percobaan++;
            cout << "Username atau Password Salah!" << endl;
            cout << "Sisa percobaan: " << 3 - percobaan << endl;
        }
    }

    cout << "\nLogin Gagal! Akses Ditolak." << endl;
    return "invalid";
}