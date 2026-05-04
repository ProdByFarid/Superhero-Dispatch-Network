#include "login.h"

using namespace std;

bool prosesLogin() {
    int percobaan = 0;
    string inputUser, inputPass;
    
    string usernameBenar = "admin";
    string passwordBenar = "123";

    while (percobaan < 3) {
        cout << "\n--- SILAHKAN LOGIN ---" << endl;
        cout << "Username: "; cin >> inputUser;
        cout << "Password: "; cin >> inputPass;

        if (inputUser == usernameBenar && inputPass == passwordBenar) {
            cout << "Login Berhasil!" << endl;
            return true; 
        } else {
            percobaan++;
            cout << "Username atau Password Salah!" << endl;
            cout << "Sisa percobaan: " << 3 - percobaan << endl;
        }
    }

    cout << "\nLogin Gagal! Akses Ditolak." << endl;
    return false; 
}