#ifndef MAINMENU_H
#define MAINMENU_H

#include "admin.h"
#include "auth.h"
#include "utilities.h"
#include "user.h"

void menuUtama() {
    string pilihanStr;
    int pilihan;
    
    do {
        clearScreen();
        cout << titleA << putih << endl;
        cout << "Masukkan Pilihan: ";
        getline(cin, pilihanStr);
        
        try {
            validateMenuChoice(pilihanStr);
            pilihan = stoi(pilihanStr);
        } catch (const exception& e) {
            showError(e.what());
            pilihan = -1;
            pause();
            continue;
        }

        if (pilihan >= 0) {
            try {
                if (pilihan == 1) {
                    string role = prosesLogin();
                    if (role == "manager") {
                        cout << endl;
                        menuAdmin();
                    }
                    else if (role == "dispatcher") {
                        cout << endl;
                        tutorialShift();
                        pause();
                        inisialisasiMisiDispatcher();
                        menuDispatcher();
                    }
                    else if (role == "invalid") {
                        showError("Login gagal! Silakan coba lagi.");
                        pause();
                    }
                }
                else if (pilihan == 0) {
                    cout << emas << "\nTerimakasih Telah Menggunakan Program Ini" << putih << endl; 
                    pause();
                }
                else {
                    showError("Pilihan Tidak Valid!");
                    pause();
                }
            } catch (const exception& e) {
                cerr << kuning << e.what() << putih << endl; 
                pause();
            }
        }
    } while (pilihan != 0);
}

#endif