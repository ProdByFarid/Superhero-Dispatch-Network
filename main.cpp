#include <iostream>
#include <string>

using namespace std;

// Fungsi bantuan untuk mensimulasikan Menu Login
void menuLogin() {
    cout << "-----------------------------------" << endl;
    cout << "Masuk ke Sub-Menu: MENU LOGIN" << endl;
    cout << "-----------------------------------" << endl;
}

int main() {
    int pilihan;

    do {
        // 1. Tampilkan Menu Utama
        cout << "\n======= MENU UTAMA =======" << endl;
        cout << "1. Head of SDN" << endl;
        cout << "2. Dispatcher" << endl;
        cout << "0. Keluar" << endl;
        
        // 2. Input Pilihan
        cout << "Pilihan: ";
        cin >> pilihan;

        // 3. Logika Percabangan sesuai Flowchart
        if (pilihan == 1) {
            // Pilihan == 1 ? Ya
            menuLogin();
            // Kembali ke Menu Utama (melalui loop)
        } 
        else if (pilihan == 2) {
            // Pilihan == 2 ? Ya
            menuLogin();
            // Kembali ke Menu Utama (melalui loop)
        } 
        else if (pilihan == 0) {
            // Pilihan == 0 ? Ya
            cout << "Terimakasih Telah Menggunakan Program Ini" << endl;
            // Program akan keluar dari loop dan menuju End
        } 
        else {
            // Pilihan Tidak Valid!
            cout << "Pilihan Tidak Valid!" << endl;
            // Kembali ke Menu Utama (melalui loop)
        }

    } while (pilihan != 0); // Loop berlanjut selama pilihan bukan 0

    // End
    cout << "Program Selesai." << endl;

    return 0;
}