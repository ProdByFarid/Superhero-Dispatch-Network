// login.cpp
#include "login.h"
#include <iostream>

using namespace std;

bool prosesLogin() {
    int percobaan = 0;
    string user, pass;
    // Contoh data akun sederhana
    string validUser = "admin";
    string validPass = "123";

    while (percobaan < 3) {
        cout << "\n=== HALAMAN LOGIN ===" << endl;
        cout << "Username: "; cin >> user;
        cout << "Password: "; cin >> pass;

        if (user == validUser && pass == validPass) {
            cout << "Login Berhasil!" << endl;
            return true;
        } else {
            percobaan++;
            cout << "Username/Password Salah! Percobaan: " << percobaan << endl;
        }
    }
    cout << "Akses Ditolak!" << endl;
    return false;
}