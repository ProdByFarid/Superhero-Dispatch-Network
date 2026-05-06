// LIBRARY

#include <iostream>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include "json.hpp"

// LIBRARY

using namespace std;
using json = nlohmann::json;

// UTILITAS

#define putih   "\033[0m"
#define merah   "\033[31m"
#define biru    "\033[34m"
#define hijau   "\033[32m"
#define cyan    "\033[36m"
#define magenta "\033[35m"
#define abu     "\033[90m"
#define emas    "\033[38;5;220m"

string title = R"(
                                    =====================================================================================
                                    |...................................................................................|
                                    |........[][][][][][][][][][].....[][][][][][][]............[][][]........[][][][]..|
                                    |......[][][][][][][][][][][]....[][][][][][][][][][]......[][][][][]....[][][][]...|
                                    |....[][][][][][][][][][][]....[][][][][][][][][][][].....[][][][][][]..[][][][]....|
                                    |....[][][][]..................[][][][][]...[][][][][]...[][][][][][][].[][][][]....|
                                    |...[][][][][][][][][].........[][][][]......[][][][]....[][][][][][][][][][][].....|
                                    |....[][][][][][][][][][].....[][][][]......[][][][][]..[][][][][][][][][][][]......|
                                    |......[][][][][][][][][][]...[][][][].....[][][][][]..[][][][].[][][][][][][]......|
                                    |..............[][][][][][]...[][][][]....[][][][][]...[][][][]..[][][][][][].......|
                                    |....[][][][][][][][][][][]..[][][][][][][][][][][]...[][][][].....[][][][].........|
                                    |..[][][][][][][][][][][]....[][][][][][][][][][].....[][][][].....[][][][].........|
                                    |..[][][][][][][][][][].....[][][][][][][][].........[][][][].......[][][]..........|
                                    |...................................................................................|
                                    =====================================================================================
)";


void pause() {
    cout << "\n[Tekan enter untuk melanjutkan...]" << endl;
    getch();
}

void clearScreen() {
    system("cls");
}

void loadingScreen() {
    clearScreen();
    cout << cyan << "\nSuperhero Dispathing Network [Versi 10.7.100829.1]" << endl;
    Sleep(500);
    cout << "[C] SDN. Semua hak dilindung undang-undang" << endl;
    Sleep(500);
    cout << "C:/Branches/Torrance>" << putih << endl;
    Sleep(1500);

    cout << emas << title << putih << endl;
}

void loadingBar() {
    int bar = 15;
    cout << "\n Hero Mobilisasi..." << endl;
    

    for (int i = 0; i <= bar; i++) {
        cout << "\r[";
        for (int j = 0; j < bar; ++j) {
            if (j < i) {
                cout << (char)219; //
            } else {
                cout << (char)176; //
            }
        }
        cout << "] " << (i * 100 / bar) << "%";
        cout.flush();
        Sleep(100);
    }
    cout << endl;
    Sleep(100);
    cout << "\nSelesai!" << endl;
}

void menuUtama() {
    cout << cyan << "Selamat Datang Di Superhero Dispatch Network! Silahkan Login!" << endl;
    cout << "\n [1]. Head of SDN" << endl;
    cout << " [2]. Dispatcher" << endl;
    cout << " [0]. Logout" << putih << endl;
}
void menuAdmin() {
    clearScreen();
    string header(55, '=');

    cout << header << endl;
    cout << "|                                                     |" << endl;
    cout << header << endl;
    cout << "| [1]. Pengelolaan Superhero                          |" << endl;
    cout << "| [2]. Pengelolaan Dispatcher                         |" << endl;
    cout << "| [0]  Logout                                         |" << endl;
    cout << header << endl;
}

// UTILITAS

// LOGIN

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

// LOGIN

// ADMIN

void tampilkanHero() {
    ifstream file("superhero.json");

    if (!file.is_open()) {
        cout << "Gagal membuka file superhero.json\n";
        return;
    }

    json data;
    file >> data;

    cout << "\n===== PENGELOLAAN SUPERHERO =====\n";

    for (auto &hero : data["heroes"]) {
        cout << "Nama     : " << hero["name"] << endl;
        cout << "Points   : " << hero["points"] << endl;

        cout << "Combat   : " << hero["stats"]["combat"] << endl;
        cout << "Vigor    : " << hero["stats"]["vigor"] << endl;
        cout << "Mobility : " << hero["stats"]["mobility"] << endl;
        cout << "Charisma : " << hero["stats"]["charisma"] << endl;
        cout << "Intellect: " << hero["stats"]["intellect"] << endl;

        cout << "------------------------\n";
    }
}

void menuAdmin() {
    int pilihan;


    do {
        cout << "\n===== MENU ADMIN =====\n";
        cout << "1. Pengelolaan Superhero\n";
        cout << "2. Pengelolaan Dispatcher\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 1) {
            tampilkanHero();
        }
        else if (pilihan == 2) {
            cout << "\n=== PENGELOLAAN DISPATCHER ===\n";
            cout << "Fitur masih dalam pengembangan...\n";
        }
        else if (pilihan == 0) {
            cout << "Anda akan keluar dari menu ini...\n";
        }
        else {
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 0);
}

// ADMIN


// MAIN
int main() {
    loadingBar();

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