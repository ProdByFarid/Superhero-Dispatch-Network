#ifndef AUTH_H
#define AUTH_H

#include "struct.h"
#include "utilities.h"

string prosesLogin() {
    int percobaan = 0;
    string inputUser, inputPass;
    Akun akunManager = {237218, "blazer", "blazer123", "manager"};

    while (percobaan < 3) {
        clearScreen();
        cout << emas << titleB << putih << endl;
        inputUser = getValidatedLine("Username: ", "Username", false, false);
        inputPass = getValidatedLine("Password: ", "Password", false, true);

        if (inputUser == akunManager.username && inputPass == akunManager.password) {
            cout << hijau << "\n✅ Login Berhasil. Selamat Datang, Head Of SDN!" << putih << endl;
            pause();
            return akunManager.role;
        } 

        try {
            json dataDisp = bacaDatabaseDispatcher();
            if (!dataDisp["dispatchers"].empty()) {
                for (const auto& disp : dataDisp["dispatchers"]) {
                    if (disp["username"] == inputUser && disp["password"] == inputPass) {
                        cout << hijau << "\n✅ Login Berhasil. Selamat Datang, Dispatcher!" << putih << endl;
                        pause();
                        return "dispatcher"; 
                    }
                }
            }
        } catch (const exception& e) {
            cerr << kuning << "⚠️ Warning: Gagal membaca database dispatcher: " << e.what() << putih << endl;
            pause();
        }

        percobaan++;
        cout << merah << "\n❌ Username atau Password Salah!\n" << putih << endl;
        cout << kuning << "⚠️  Warning: Jumlah percobaan: " << percobaan << endl;

        if (percobaan == 3) {
            cout << merah << "\n❌ Login Gagal! Akses Ditolak." << putih << endl; 
        }
        pause();
    }
    return "invalid";
}

#endif