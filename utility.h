#ifndef utility_h
#define utility_h

#include <iostream>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>

using namespace std;

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
    cout << "| [1]. Tambah Superhero                               |" << endl;
    cout << "| [2]. Tambah Dispatcher                              |" << endl;
    cout << "| [3]. Tampilkan Seluruh Superhero                    |" << endl;
    cout << "| [4]. Update Biografi / Status / Statistik Superhero |" << endl;
    cout << "| [5]. Pecat Superhero                                |" << endl;
    cout << "| [6]. Pecat Dispatcher                               |" << endl;
    cout << "| [7]. Instruksi                                      |" << endl;
    cout << "| [0]  Logout                                         |" << endl;
    cout << header << endl;
}

#endif