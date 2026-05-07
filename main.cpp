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
#include <algorithm> 
#include <cctype>    
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
#define kuning  "\033[33m" 

struct Akun {
    int id;
    string username;
    string password;
    string role;
};

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

string titleA = R"(
===============================================
|                                             |
|               WELCOME TO SDN                |
|       Silahkan Pilih Role Untuk Login       |
|                                             |
===============================================
)";

string titleB = R"(
==============================================
|                                            |
|              SIGN IN TO SDN                |
|    Gunakan Username Dan Password Anda      |
|                                            |
==============================================
)";

string titleC = R"(
=============================================
|                                           |
|                HEAD OF SDN                |
|    Silahkan Pilih Yang Ingin Dikelola     |
|                                           |
=============================================
|                                           |
|  [1]. Kelola Data Superhero               |
|  [2]. Kelola Data Dispatcher              |
|  [0]. Keluar                              |
|                                           |
=============================================
)";

string titleD = R"(
=============================================
|                                           |
|                DISPATCHER                 |
|        Mau Memulai Shift Hari Ini?        |
|                                           |
=============================================
)";

string titleE = R"(
===========================================
|                                         |
|          PENGELOLAAN SUPERHERO          |
|                                         |
===========================================
|                                         |
|  [1]. Tambah Superhero                  |
|  [2]. Lihat Database                    |
|  [3]. Update Data Superhero             |
|  [4]. Pecat Superhero                   |
|  [0]. Keluar Menu                       |
|                                         |
===========================================
)";

string titleF = R"(
===========================================
|                                         |
|           SUPERHERO DATABASE            |
|                                         |
===========================================
|                                         |
|  [1]. Lihat Semua Data                  |
|  [2]. Urutkan Data                      |
|  [3]. Cari Superhero                    |
|  [0]. Kembali ke Menu Utama             |
|                                         |
===========================================
)";

void pause() {
    cout << cyan << "\n[Tekan enter untuk melanjutkan...]" << putih << endl;
    getch();
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
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
                cout << (char)219; 
            } else {
                cout << (char)176; 
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

// UTILITAS 

// LOGIN

string prosesLogin() {
    int percobaan = 0;
    string inputUser, inputPass;

    Akun daftarAkun[] = {
        {237218, "manager", "123", "manager"},
        {5318008, "user", "123", "dispatcher"}
    };

    int jumlahAkun = sizeof(daftarAkun) / sizeof(daftarAkun[0]);

    if (jumlahAkun == 0) {
        cout << "Belum ada akun yang terdaftar!\n";
        return "no_account";
    }

    while (percobaan < 3) {
        clearScreen();
        cout << emas << titleB << putih << endl;
        cout << cyan << "Username: ";
        cin >> inputUser;
        cout << "Password: ";
        cin >> inputPass;

        bool ditemukan = false;

        for (int i = 0; i < jumlahAkun; i++) {
            if (daftarAkun[i].username == inputUser &&
                daftarAkun[i].password == inputPass) {

                cout << hijau << "\n[+] Login Berhasil. ";

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

// GGG: HELPER DATABASE

json bacaDatabase() {
    ifstream file("superhero.json");
    if (!file.is_open()) {
        json j;
        j["heroes"] = json::array();
        return j;
    }
    json data;
    file >> data;
    file.close();
    return data;
}

void simpanDatabase(const json& data) {
    ofstream file("superhero.json");
    if (file.is_open()) {
        file << setw(4) << data << endl; 
        file.close();
    } else {
        cout << merah << "Gagal menyimpan database!" << putih << endl;
    }
}

// GGG: Helper Manual Lowercase
string toLowerManual(string s) {
    string result = s;
    for (int i = 0; i < result.length(); i++) {
        result[i] = tolower(result[i]);
    }
    return result;
}

// GGG: FUNGSI SUB-MENU LIHAT DATABASE
void menuLihatDatabase() {
    string header(68, '=');
    int pilihan;
    int no = 1;
    do {
        clearScreen();
        cout << emas << titleF << cyan << endl;
        cout << "\nMasukkan Pilihan: ";
        cin >> pilihan;

        json data = bacaDatabase();
        
        if (pilihan == 1) {
            if (data["heroes"].empty()) {
                cout << "\n <|     DAFTAR SUPERHEROES KOSONG     |>" << endl;
            } else {
                clearScreen();
                cout << emas << "\n                 <|     BILLBOARD SUPERHEROES     |>" << putih << endl;
                cout << endl;
                cout << header << endl;
                cout << "| " << cyan << setw(3) << left << "NO" << putih 
                << "| " << cyan << setw(20) << left << "NAMA SUPERHERO" << putih 
                << "| " << biru << setw(30) << left << "ALIASES" << putih 
                << "| " << emas << setw(5) << left << "POIN" << putih << " |" << endl;
                cout << header << endl;
                for (const auto &hero : data["heroes"]) {
                cout << "| " << setw(3) << left << no
                << "| " << setw(20) << left << hero["name"].get<string>()
                << "| " << setw(30) << left << hero["aliases"].get<string>()
                << "| " << setw(5) << left << hero["points"].get<int>() << " |" <<endl;

                no++;
                }
                cout << header << endl;

            }
            pause();
        } 
        else if (pilihan == 2) {
            // SORTING
            int sortType;
            cout << "Urutkan Berdasarkan: \n[1]. Nama (A-Z)\n[2]. Total Poin Stats (Tertinggi)\nPilihan: ";
            cin >> sortType;

            if (sortType == 1) {
                std::sort(data["heroes"].begin(), data["heroes"].end(), [](const json& a, const json& b) {
                    return a["name"].get<string>() < b["name"].get<string>();
                });
                cout << hijau << "Data diurutkan berdasarkan Nama." << putih << endl;
            } else if (sortType == 2) {
                // GGG: PERBAIKAN ERROR DI SINI (.get<int>())
                std::sort(data["heroes"].begin(), data["heroes"].end(), [](const json& a, const json& b) {
                    int totalA = 0, totalB = 0;
                    if(a.contains("stats")) {
                        totalA = a["stats"]["combat"].get<int>() + a["stats"]["vigor"].get<int>() + a["stats"]["mobility"].get<int>() + a["stats"]["charisma"].get<int>() + a["stats"]["intellect"].get<int>();
                    }
                    if(b.contains("stats")) {
                        totalB = b["stats"]["combat"].get<int>() + b["stats"]["vigor"].get<int>() + b["stats"]["mobility"].get<int>() + b["stats"]["charisma"].get<int>() + b["stats"]["intellect"].get<int>();
                    }
                    return totalA > totalB; 
                });
                cout << hijau << "Data diurutkan berdasarkan Total Poin Stats." << putih << endl;
            }
            
            simpanDatabase(data); 
            pause();
        } 
        else if (pilihan == 3) {
            // SEARCHING
            string cari;
            cout << "Masukkan Nama Superhero: ";
            cin.ignore(); 
            getline(cin, cari);

            bool ditemukan = false;
            string cariLower = toLowerManual(cari); 

            for (const auto &hero : data["heroes"]) {
                string namaHero = hero["name"];
                string namaLower = toLowerManual(namaHero); 

                if (namaLower.find(cariLower) != string::npos) {
                    clearScreen();
                    cout << cyan << "=== HASIL PENCARIAN ===" << putih << endl;
                    cout << "Nama: " << hero["name"] << endl;
                    cout << "Deskripsi: " << hero["description"] << endl;
                    if (hero.contains("stats")) {
                        cout << "Combat: " << hero["stats"]["combat"] << endl;
                        cout << "Vigor: " << hero["stats"]["vigor"] << endl;
                        cout << "Mobility: " << hero["stats"]["mobility"] << endl;
                        cout << "Charisma: " << hero["stats"]["charisma"] << endl;
                        cout << "Intellect: " << hero["stats"]["intellect"] << endl;
                    }
                    ditemukan = true;
                    break;
                }
            }
            if (!ditemukan) {
                cout << merah << "Superhero tidak ditemukan." << putih << endl;
            }
            pause();
        }
    } while (pilihan != 0);
}

// ADMIN

// GGG: IMPLEMENTASI LENGKAP KELOLA SUPERHERO
void kelolaSuperhero() {
    int pilihan;
    do {
        clearScreen();
        cout << emas << titleE << cyan << endl;
        cout << "Masukkan Pilihan: ";
        cin >> pilihan;

        json data; 

        if (pilihan == 1) {
            // TAMBAH SUPERHERO
            cout << cyan << "=== TAMBAH SUPERHERO BARU ===" << putih << endl;
            
            json newHero;
            string inputStr;
            int inputInt;

            // Input Biografi
            cout << "Nama: "; cin.ignore(); getline(cin, inputStr); newHero["name"] = inputStr;
            
            cout << "Tagline: "; getline(cin, inputStr); newHero["tagline"] = inputStr;
            
            cout << "Profile Type (misal: Hero/Villain): "; getline(cin, inputStr); newHero["profileType"] = inputStr;
            
            cout << "Umur: "; cin >> inputInt; newHero["umur"] = inputInt;
            
            cout << "Tinggi (cm): "; cin >> inputInt; newHero["tinggi"] = inputInt;
            
            cout << "Kemampuan Utama: "; cin.ignore(); getline(cin, inputStr); newHero["primary"] = inputStr;
            
            cout << "Tempat Lahir: "; getline(cin, inputStr); newHero["tempatLahir"] = inputStr;
            
            cout << "Deskripsi: "; getline(cin, inputStr); newHero["description"] = inputStr;
            
            cout << "Kejahatan (Jika ada, else '-'): "; getline(cin, inputStr); newHero["kejahatan"] = inputStr;

            // Input Statistik
            cout << "\n--- Input Statistik (0-100) ---" << endl;
            json stats;
            cout << "Combat: "; cin >> inputInt; stats["combat"] = inputInt;
            cout << "Vigor: "; cin >> inputInt; stats["vigor"] = inputInt;
            cout << "Mobility: "; cin >> inputInt; stats["mobility"] = inputInt;
            cout << "Charisma: "; cin >> inputInt; stats["charisma"] = inputInt;
            cout << "Intellect: "; cin >> inputInt; stats["intellect"] = inputInt;
            
            newHero["stats"] = stats;
            
            // GGG: PERBAIKAN ERROR DI SINI (.get<int>())
            int totalPoints = stats["combat"].get<int>() + stats["vigor"].get<int>() + stats["mobility"].get<int>() + stats["charisma"].get<int>() + stats["intellect"].get<int>();
            newHero["points"] = totalPoints;

            data = bacaDatabase();
            data["heroes"].push_back(newHero);
            simpanDatabase(data);
            
            cout << hijau << "\nSuperhero berhasil ditambahkan!" << putih << endl;
            pause();
        } 
        else if (pilihan == 2) {
            // LIHAT DATABASE (Sub Menu)
            menuLihatDatabase();
        } 
        else if (pilihan == 3) {
            // UPDATE DATA
            clearScreen();
            cout << cyan << "=== UPDATE DATA SUPERHERO ===" << putih << endl;
            cout << "Masukkan Nama Superhero yang ingin diupdate: ";
            cin.ignore(); 
            string namaCari;
            getline(cin, namaCari);

            data = bacaDatabase();
            bool found = false;
            
            for (auto &hero : data["heroes"]) {
                if (hero["name"] == namaCari) {
                    found = true;
                    cout << hijau << "Ditemukan: " << hero["name"] << putih << endl;
                    cout << "Apa yang ingin diupdate?" << endl;
                    cout << "[1]. Biografi" << endl;
                    cout << "[2]. Statistik" << endl;
                    cout << "Pilihan: ";
                    int updatePilih;
                    cin >> updatePilih;

                    if (updatePilih == 1) {
                        // Update Biografi
                        cout << "Edit Nama (Enter untuk skip): "; 
                        cin.ignore(); string temp; getline(cin, temp); 
                        if(!temp.empty()) hero["name"] = temp;

                        cout << "Edit Tagline: "; getline(cin, temp); if(!temp.empty()) hero["tagline"] = temp;
                        
                        cout << "Edit Deskripsi: "; getline(cin, temp); if(!temp.empty()) hero["description"] = temp;
                        
                        cout << "Biografi diperbarui." << endl;
                    } 
                    else if (updatePilih == 2) {
                        // Update Statistik
                        cout << "Edit Combat: "; cin >> hero["stats"]["combat"];
                        cout << "Edit Vigor: "; cin >> hero["stats"]["vigor"];
                        cout << "Edit Mobility: "; cin >> hero["stats"]["mobility"];
                        cout << "Edit Charisma: "; cin >> hero["stats"]["charisma"];
                        cout << "Edit Intellect: "; cin >> hero["stats"]["intellect"];
                        
                        // GGG: PERBAIKAN ERROR DI SINI (.get<int>())
                        int total = hero["stats"]["combat"].get<int>() + hero["stats"]["vigor"].get<int>() + hero["stats"]["mobility"].get<int>() + hero["stats"]["charisma"].get<int>() + hero["stats"]["intellect"].get<int>();
                        hero["points"] = total;
                        
                        cout << "Statistik diperbarui." << endl;
                    }
                    simpanDatabase(data);
                    break;
                }
            }
            if (!found) {
                cout << merah << "Nama tidak ditemukan!" << putih << endl;
            }
            pause();
        } 
        else if (pilihan == 4) {
            // PECAT / HAPUS
            clearScreen();
            cout << cyan << "=== PECAT SUPERHERO ===" << putih << endl;
            cout << "Masukkan Nama Superhero: ";
            cin.ignore();
            string namaHapus;
            getline(cin, namaHapus);

            data = bacaDatabase();
            
            auto it = data["heroes"].begin();
            bool found = false;
            while (it != data["heroes"].end()) {
                if ((*it)["name"] == namaHapus) {
                    found = true;
                    cout << kuning << "Apakah kamu yakin ingin memecat " << (*it)["name"] << "? (y/n): " << putih;
                    char konfirmasi;
                    cin >> konfirmasi;
                    
                    if (konfirmasi == 'y' || konfirmasi == 'Y') {
                        it = data["heroes"].erase(it); 
                        simpanDatabase(data);
                        cout << hijau << "Superhero telah dipecat/dihapus." << putih << endl;
                    } else {
                        cout << "Pembatalan penghapusan." << endl;
                    }
                    break;
                } else {
                    ++it;
                }
            }

            if (!found) {
                cout << merah << "Nama tidak ditemukan!" << putih << endl;
            }
            pause();
        } 
        else if (pilihan == 0) {
            cout << "Kembali ke menu utama..." << endl;
        } 
        else {
            cout << merah << "Pilihan tidak valid!" << putih << endl;
            pause();
        }

    } while (pilihan != 0);
}

// CRUD SUPERHERO //

// ADMIN


void menuAdmin() {
    int pilihan;

    do {
        clearScreen();
        cout << emas << titleC << cyan << endl;
        cout << "Masukkan Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            kelolaSuperhero();
        }
        else if (pilihan == 2) {
            cout << emas << titleD << cyan << endl;
            cout << "Fitur masih dalam pengembangan...\n";
            pause();
        }
        else if (pilihan == 0) {
            cout << "Anda akan keluar dari menu ini...\n";
            break;
        }
        else {
            cout << merah << "\n[!] Error: Pilihan tidak valid!" << endl;
            pause();
        }

    } while (pilihan != 0);

}

// ADMIN


// MENU UTAMA

void menuUtama() {
    int pilihan;

    do {
        clearScreen();
        cout << emas << titleA << cyan << endl;
        cout << "[1]. Head of SDN" << endl;
        cout << "[2]. Dispatcher" << endl;
        cout << "[0]. Keluar" << endl;
        cout << endl;
        cout << "Masukkan Pilihan: ";
        cin >> pilihan;


        if (pilihan == 1 || pilihan == 2) {

            string role = prosesLogin();

            if (role == "manager") {
                cout << "Selamat Datang, Head Of SDN!" << endl;
                pause();
                menuAdmin();
            }
            else if (role == "dispatcher") {
                cout << "Selamat Datang, Dispatcher!" << endl;
                pause();
            }
            else {
                cout << merah << "\n[-] Login gagal. Kembali ke Menu Utama..." << endl;
                pause();
            }
        }
        else if (pilihan == 0) {
            cout << "\nTerimakasih Telah Menggunakan Program Ini" << endl;
            pause();
        }
        else {
            cout << merah << "\n[!] Error: Pilihan Tidak Valid!" << putih << endl;
            pause();
        }

    } while (pilihan != 0);

}

// MENU UTAMA

// MAIN
int main() {
    // loadingScreen();
    // pause();
    menuUtama();

    return 0;
}

// MAIN