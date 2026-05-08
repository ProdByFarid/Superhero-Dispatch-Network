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
==============================================
                                                
             🏢 WELCOME TO SDN 🏢               
        Silahkan Pilih Role Untuk Login       
                                                
==============================================
                                            
   [1]. 👑 Head Of SDN               
   [2]. 📞 Dispatcher             
   [0]. 🔙 Keluar                              
                                            
==============================================
)";

string titleB = R"(
==============================================
                                            
            🔒 SIGN IN TO SDN 🔒             
     Gunakan Username Dan Password Anda       
                                            
==============================================
)";

string titleC = R"(
=============================================
                                            
            👑 HEAD OF SDN 👑                
    Silahkan Pilih Yang Ingin Dikelola     
                                            
=============================================
                                            
   [1]. ⚙️  Kelola Data Superhero               
   [2]. 📞 Kelola Data Dispatcher              
   [0]. 🔙 Keluar                              
                                            
=============================================
)";

string titleD = R"(
=============================================
                                            
           📞 HEY DISPATCHER! 📞             
        Mau Memulai Shift Hari Ini?        
                                            
=============================================
)";

string titleE = R"(
===========================================
                                          
        🦸 PENGELOLAAN SUPERHERO 🦸          
                                          
===========================================
                                          
   [1]. ➕ Tambah Superhero                  
   [2]. 📄 Lihat Database                    
   [3]. ✏️  Update Data Superhero             
   [4]. 🗑️  Pecat Superhero                   
   [0]. 🔙 Kembali Ke Menu Admin             
                                          
===========================================
)";

string titleF = R"(
===========================================
                                          
         🛢️ SUPERHERO DATABASE 🛢️            
                                          
===========================================
                                         
   [1]. 📄 Lihat Semua Data                  
   [2]. 🔃 Urutkan Data                      
   [3]. 🔍 Cari Superhero                    
   [0]. 🔙 Kembali ke Database               
                                         
===========================================
)";

string titleG = R"(
===========================================
                                          
          🔃 SORTING DATABASE 🔃            
                                          
===========================================
                                          
   [1]. 🔤 Urutkan Berdasarkan Nama          
   [2]. 🌟 Urutkan Berdasarkan Poin          
   [0]. 🔙 Keluar                            
                                      
===========================================
)";

string titleH = R"(
===========================================
                                          
      🧑‍💻 PENGELOLAAN DISPATCHER 🧑‍💻         
                                          
===========================================
                                         
   [1]. ➕ Tambah Dispatcher            
   [2]. 📄 Lihat Data Dispatcher             
   [3]. ✏️  Update Data Dispatcher            
   [4]. 🗑️  Pecat Dispatcher            
   [0]. 🔙 Kembali Ke Menu Admin             
                                         
===========================================
)";

void pause() {
    cout << putih << "\n[Tekan enter untuk melanjutkan...]" << endl;
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
    cout << "\n⌛ Hero Mobilisasi..." << endl;

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

json bacaDatabaseDispatcher();

string prosesLogin() {
    int percobaan = 0;
    string inputUser, inputPass;

    // Data manager tetap hardcoded sebagai akses utama
    Akun akunManager = {237218, "manager", "123", "manager"};

    while (percobaan < 3) {
        clearScreen();
        cout << emas << titleB << putih << endl;
        cout << "Username: ";
        cin >> inputUser;
        cout << "Password: ";
        cin >> inputPass;

        // 1. Cek Akun Manager
        if (inputUser == akunManager.username && inputPass == akunManager.password) {
            cout << hijau << "\n✅ Login Berhasil. ";
            return akunManager.role;
        }

        // 2. Cek Akun Dispatcher dari dispatcher.json
        json dataDisp = bacaDatabaseDispatcher();
        
        if (!dataDisp["dispatchers"].empty()) {
            for (const auto& disp : dataDisp["dispatchers"]) {
                if (disp["username"] == inputUser && disp["password"] == inputPass) {
                    cout << hijau << "\n✅ Login Berhasil. ";
                    return "dispatcher"; 
                }
            }
        }

        percobaan++;
        cout << merah << "\n❌ Username atau Password Salah!\n";
        cout << kuning << "⚠️ Warning: Sisa percobaan: " << 3 - percobaan << endl;
        pause();
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
        cout << merah << "\nGagal menyimpan database!" << putih << endl;
    }
}

// GGG: HELPER DATABASE DISPATCHER (TUGAS FITRI)
json bacaDatabaseDispatcher() {
    ifstream file("dispatcher.json");
    if (!file.is_open()) {
        json j;
        j["dispatchers"] = json::array();
        return j;
    }
    json data;
    file >> data;
    file.close();
    return data;
}

void simpanDatabaseDispatcher(const json& data) {
    ofstream file("dispatcher.json");
    if (file.is_open()) {
        file << setw(4) << data << endl; 
        file.close();
    } else {
        cout << merah << "\nGagal menyimpan database dispatcher!" << putih << endl;
    }
}

void daftarDispatcher() {
    string header(76, '=');
    json data = bacaDatabaseDispatcher();

    if (data["dispatchers"].empty()) {
        cout << emas << "\n <|     DAFTAR DISPATCHER KOSONG     |>" << putih << endl;
    } else {
        clearScreen();
        cout << emas << "\n                   <|     DATA DISPATCHER SDN     |>" << putih << endl;
        cout << endl;
        cout << header << endl;
        cout << "| " << cyan << setw(10) << left << "ID DISP." << putih 
             << "| " << cyan << setw(18) << left << "USERNAME" << putih 
             << "| " << biru << setw(18) << left << "PASSWORD" << putih 
             << "| " << emas << setw(20) << left << "STATUS KARYAWAN" << putih << " |" << endl;
        cout << header << endl;
        for (const auto &disp : data["dispatchers"]) {
            cout << "| " << setw(10) << left << disp["id"].get<string>()
                 << "| " << setw(18) << left << disp["username"].get<string>()
                 << "| " << setw(18) << left << disp["password"].get<string>()
                 << "| " << setw(20) << left << disp["status"].get<string>() << " |" << endl;
        }
        cout << header << endl;
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

void daftarSuperhero() {
    string header(68, '=');
    json data = bacaDatabase();

    if (data["heroes"].empty()) {
    cout << emas << "\n <|     DAFTAR SUPERHEROES KOSONG     |>" << endl;
    } else {
        clearScreen();
        cout << emas << "\n                <|     BILLBOARD SUPERHEROES     |>" << putih << endl;
        cout << endl;
        cout << header << endl;
        cout << "| " << cyan << setw(3) << left << "NO" << putih 
        << "| " << cyan << setw(20) << left << "NAMA SUPERHERO" << putih 
        << "| " << biru << setw(30) << left << "ALIASES" << putih 
        << "| " << emas << setw(5) << left << "POIN" << putih << " |" << endl;
        cout << header << endl;
        int no = 1;
        for (const auto &hero : data["heroes"]) {
        cout << "| " << setw(3) << left << no
        << "| " << setw(20) << left << hero["name"].get<string>()
        << "| " << setw(30) << left << hero["aliases"].get<string>()
        << "| " << setw(5) << left << hero["points"].get<int>() << " |" <<endl;
        no++;
        }
        cout << header << endl;
    }
}

void sortingHeroes() {
    json data = bacaDatabase();

    int pilihanSort;
    do {
        clearScreen();
        cout << cyan << titleG << putih << endl;
        cout << "\nMasukkan Pilihan: ";
        cin >> pilihanSort;
        // GGG: Load data setiap kali masuk ke sub-menu sorting
        json data = bacaDatabase(); 
        if (pilihanSort == 1) {
            auto mergeSortNames = [&](json& arr) {
                int n = arr.size();
                if (n <= 1) return;
                function<void(int, int)> sortHelper;
                function<void(int, int, int)> mergeHelper;
                mergeHelper = [&](int left, int mid, int right) {
                    int n1 = mid - left + 1;
                    int n2 = right - mid;
                    vector<json> L(n1), R(n2);
                    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
                    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
                    int i = 0, j = 0, k = left;
                    while (i < n1 && j < n2) {
                        string nameL = L[i]["name"].get<string>();
                        string nameR = R[j]["name"].get<string>();
                        transform(nameL.begin(), nameL.end(), nameL.begin(), ::tolower);
                        transform(nameR.begin(), nameR.end(), nameR.begin(), ::tolower);
                        if (nameL <= nameR) {
                            arr[k] = L[i];
                            i++;
                        } else {
                            arr[k] = R[j];
                            j++;
                        }
                        k++;
                    }
                    while (i < n1) { arr[k++] = L[i++]; }
                    while (j < n2) { arr[k++] = R[j++]; }
                };
                sortHelper = [&](int left, int right) {
                    if (left >= right) return;
                    int mid = left + (right - left) / 2;
                    sortHelper(left, mid);
                    sortHelper(mid + 1, right);
                    mergeHelper(left, mid, right);
                };
                sortHelper(0, n - 1);
            };
            if (!data["heroes"].empty()) {
                mergeSortNames(data["heroes"]);
            }

            simpanDatabase(data); 

            cout << hijau << "\n[+] Data berhasil diurutkan berdasarkan Nama!" << putih << endl;
            pause();
        } 
        else if (pilihanSort == 2) {
            int n = data["heroes"].size();

            for (int i = 0; i < n - 1; i++) {
                int max_idx = i;
                for (int j = i + 1; j < n; j++) {
                    // Bandingkan poin
                    if (data["heroes"][j]["points"].get<int>() > data["heroes"][max_idx]["points"].get<int>()) {
                        max_idx = j;
                    }
                }
                // Tukar posisi
                if (max_idx != i) {
                    json temp = data["heroes"][i];
                    data["heroes"][i] = data["heroes"][max_idx];
                    data["heroes"][max_idx] = temp;
                }
            }
            simpanDatabase(data);
            cout << hijau << "\n✅ Data berhasil diurutkan berdasarkan Poin!" << putih << endl;
            pause();
        } 
        else if (pilihanSort == 0) {
            cout << merah << "\n[-] Kembali ke Menu Database..." << endl;
            pause();
            break;
        } 
        else {
            cout << merah << "\n Error: Pilihan Tidak Valid!" << putih << endl;
            pause();
        }
    } while (pilihanSort != 0);
}

void searchingHeroes() {
    json data = bacaDatabase();

    daftarSuperhero();
    string cari;
    cout << emas << "\n<|     CARI DATA SUPERHERO     |>" << putih << endl;
    cout << "\nMasukkan Nama Superhero: ";
    cin.ignore(); 
    getline(cin, cari);
    bool ditemukan = false;
    string cariLower = toLowerManual(cari); 
    for (const auto &hero : data["heroes"]) {
        string namaHero = hero["name"].get<string>();
        string namaLower = toLowerManual(namaHero); 
        if (namaLower.find(cariLower) != string::npos) {
            clearScreen();
            cout << cyan << "\n<|     HASIL PENCARIAN DATA     |>" << endl;
            cout << endl;
            cout << putih << hero["name"].get<string>() << " | " 
                << (hero.contains("aliases") ? hero["aliases"].get<string>() : "-") << endl;
            
            cout << putih << "\n| " << (hero.contains("profilType") ? hero["profilType"].get<string>() : "-") << " |" << endl;
            
            cout << "\n";
            cout << left << setw(12) << "Umur"        << " : " 
                << (hero.contains("age") ? hero["age"].get<string>() : "-") << endl;
                
            cout << left << setw(12) << "Tinggi"      << " : " 
                << (hero.contains("height") ? hero["height"].get<string>() : "-") << endl;
                
            cout << left << setw(12) << "Kemampuan"   << " : " 
                << (hero.contains("abilities") ? hero["abilities"].get<string>() : "-") << endl;
                
            cout << left << setw(12) << "Tempat Lahir"  << " : " 
                << (hero.contains("birthplace") ? hero["birthplace"].get<string>() : "-") << endl;
                
            cout << left << setw(12) << "Deskripsi"   << " : " 
                << hero["description"].get<string>() << endl;
            
            cout << cyan << "\n<|     STATISTIK     |>\n" << putih << endl;
            if (hero.contains("stats")) {
                cout << "Combat    : " << hero["stats"]["combat"].get<int>() << endl;
                cout << "Vigor     : " << hero["stats"]["vigor"].get<int>() << endl;
                cout << "Mobility  : " << hero["stats"]["mobility"].get<int>() << endl;
                cout << "Charisma  : " << hero["stats"]["charisma"].get<int>() << endl;
                cout << "Intellect : " << hero["stats"]["intellect"].get<int>() << endl;
            }
            
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) {
        clearScreen();
        cout << cyan << "\n<|     HASIL PENCARIAN DATA     |>" << endl;
        cout << merah << "\n❌ Superhero tidak ditemukan!" << putih << endl;
    }
}


// GGG: FUNGSI SUB-MENU LIHAT DATABASE
void menuLihatDatabaseSuperheroes() {
    int pilihan;
    
    do {
        clearScreen();
        cout << emas << titleF << putih << endl;
        cout << "\nMasukkan Pilihan: ";
        cin >> pilihan;

        json data = bacaDatabase();
        
        if (pilihan == 1) {
            daftarSuperhero();
            pause();
        } else if (pilihan == 2) {
            sortingHeroes();
        } else if (pilihan == 3) {
            searchingHeroes();
            pause();
        } else if (pilihan == 0) {
            cout << merah << "\n Anda Akan Kembali ke Menu Pengelolaan Superhero!" << endl;
            pause();
            break;
        } else {
            cout << kuning << "\n⚠️ Error: Pilihan Tidak Valid!" << endl;
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
        cout << cyan << titleE << putih << endl;
        cout << "Masukkan Pilihan: ";
        cin >> pilihan;

        json data; 

        if (pilihan == 1) {
            cout << emas << "\n<|  TAMBAH SUPERHERO BARU  |>" << putih << endl;
            
            json newHero;
            string inputString;
            float inputNum;

            // Input Biografi
            cout << "\nNama: "; 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, inputString);
            newHero["name"] = inputString;
            
            cout << "Alias: "; 
            getline(cin, inputString); 
            newHero["aliases"] = 
            inputString;
            
            cout << "Tipe Profile: "; 
            getline(cin, inputString); 
            newHero["profileType"] = inputString;
            
            cout << "Umur: "; 
            getline(cin, inputString); 
            newHero["age"] = inputString;
            
            cout << "Tinggi (cm): "; 
            getline(cin, inputString); 
            newHero["height"] = inputString;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Kemampuan: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, inputString); 
            newHero["abilities"] = inputString;
            
            cout << "Tempat Lahir: "; 
            getline(cin, inputString); 
            newHero["birthplace"] = inputString;
            
            cout << "Deskripsi: "; 
            getline(cin, inputString); 
            newHero["description"] = inputString;

            cout << "Points: "; 
            cin >> inputNum; 
            newHero["points"] = inputNum;

            cout << emas << "\n<|  TAMBAHKAN STATISTIK  |>" << putih << endl;
            json stats;
            cout << "\nCombat: "; 
            cin >> inputNum; 
            stats["combat"] = inputNum;

            cout << "Vigor: "; 
            cin >> inputNum; 
            stats["vigor"] = inputNum;

            cout << "Mobility: "; 
            cin >> inputNum; 
            stats["mobility"] = inputNum;

            cout << "Charisma: "; 
            cin >> inputNum; 
            stats["charisma"] = inputNum;

            cout << "Intellect: "; 
            cin >> inputNum; 
            stats["intellect"] = inputNum;

            newHero["stats"] = stats;
            
            data = bacaDatabase();
            data["heroes"].push_back(newHero);
            simpanDatabase(data);
            
            cout << hijau << "\nSuperhero berhasil ditambahkan!" << putih << endl;
            pause();
        } 
        else if (pilihan == 2) {
            menuLihatDatabaseSuperheroes();
        } 
        else if (pilihan == 3) {
            // UPDATE DATA
            clearScreen();
            daftarSuperhero();
            cout << emas << "\n<|  UPDATE DATA SUPERHERO  |>" << putih << endl;
            cout << "\nMasukkan Nama Superhero yang ingin diupdate: ";
            cin.ignore(); 
            string namaCari;
            getline(cin, namaCari);

            data = bacaDatabase();
            bool found = false;
            
            for (auto &hero : data["heroes"]) {
                if (hero["name"] == namaCari) {
                    found = true;
                    cout << hijau << "\n[+] Ditemukan: " << hero["name"] << putih << endl;
                    cout << "Apa yang ingin diupdate?" << endl;
                    cout << "\n[1]. Biografi" << endl;
                    cout << "[2]. Statistik" << endl;
                    cout << "\nMasukkan Pilihan: ";
                    int updatePilih;
                    cin >> updatePilih;

                    if (updatePilih == 1) {
                        // Update Biografi
                        cout << "Edit Nama (Enter untuk skip): "; 
                        cin.ignore(); string temp; getline(cin, temp); 
                        if(!temp.empty()) hero["name"] = temp;

                        cout << "Edit Tagline: "; getline(cin, temp); 
                        if(!temp.empty()) hero["tagline"] = temp;
                        
                        cout << "Edit Deskripsi: "; getline(cin, temp); 
                        if(!temp.empty()) hero["description"] = temp;
                        
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
                cout << merah << "\n❌ Nama tidak ditemukan!" << putih << endl;
            }
            pause();
        } else if (pilihan == 4) {
            clearScreen();
            daftarSuperhero();
            cout << emas << "\n<|  PECAT SUPERHERO  |>" << putih << endl;
            cout << "\nMasukkan Nama Superhero: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            string namaHapus;
            getline(cin, namaHapus);

            data = bacaDatabase();
            
            auto it = data["heroes"].begin();
            bool found = false;
            
            while (it != data["heroes"].end()) {
                if ((*it)["name"] == namaHapus) {
                    found = true;
                    char konfirmasi;
                    bool validInput = false;
                    
                    string prompt = "\n⚠️ Warning: Apakah kamu yakin ingin memecat '" + (*it)["name"].get<string>() + "'? (y/n): ";

                    do {
                        // Cetak prompt
                        cout << kuning << prompt << putih;
                        cout.flush();

                        konfirmasi = getch(); 
                        
                        // Konversi ke lowercase
                        konfirmasi = tolower(konfirmasi);

                        if (konfirmasi == 'y' || konfirmasi == 'n') {
                            validInput = true;
                            cout << konfirmasi << endl; 
                            
                            if (konfirmasi == 'y') {
                                it = data["heroes"].erase(it); 
                                simpanDatabase(data);
                                cout << hijau << "\n✅ Superhero telah dipecat/dihapus." << putih << endl;
                            } else {
                                cout << cyan << "\n❌ Pembatalan penghapusan." << putih << endl;
                                ++it;
                            }
                        } else {
                            cout << "\r"; 
                            for(int i=0; i < prompt.length() + 5; i++) cout << " "; 
                            cout << "\r";
                        }

                    } while (!validInput);
                    
                    break;
                } else {
                    ++it;
                }
            }

            if (!found) {
                cout << merah << "\n❌ Nama tidak ditemukan!" << putih << endl;
            }
            pause();
        } else {
            cout << kuning << "\n⚠️ Error: Pilihan Tidak Valid!" << endl;
            pause();
        }

    } while (pilihan != 0);
}

// CRUD SUPERHERO //

// TUGAS FITRI: CRUD DISPATCHER
void kelolaDispatcher() {
    int pilihan;
    do {
        clearScreen();
        cout << emas << titleH << putih << endl;
        cout << "Masukkan Pilihan: ";
        cin >> pilihan;

        json data; 

        if (pilihan == 1) {
            cout << emas << "\n<|  BUAT AKUN DISPATCHER BARU  |>" << putih << endl;
            
            json newDisp;
            string inputString;

            cout << "\nID Dispatcher: "; 
            cin >> inputString;
            newDisp["id"] = inputString;
            
            cout << "Username: "; 
            cin.ignore();
            getline(cin, inputString); 
            newDisp["username"] = inputString;
            
            cout << "Password: "; 
            getline(cin, inputString); 
            newDisp["password"] = inputString;
            
            cout << "Status Karyawan (Misal: Aktif/Cuti/Training): "; 
            getline(cin, inputString); 
            newDisp["status"] = inputString;

            data = bacaDatabaseDispatcher();
            data["dispatchers"].push_back(newDisp);
            simpanDatabaseDispatcher(data);
            
            cout << hijau << "\n✅ Akun Dispatcher Berhasil Ditambahkan!" << putih << endl;
            pause();
        } 
        else if (pilihan == 2) {
            // LIHAT DATABASE DISPATCHER
            clearScreen();
            daftarDispatcher();
            pause();
        } 
        else if (pilihan == 3) {
            // UPDATE DATA DISPATCHER
            clearScreen();
            daftarDispatcher();
            cout << emas << "\n<|  UPDATE DATA DISPATCHER  |>" << putih << endl;
            cout << "\nMasukkan Username Dispatcher yang ingin diupdate: ";
            cin.ignore(); 
            string userCari;
            getline(cin, userCari);

            data = bacaDatabaseDispatcher();
            bool found = false;
            
            for (auto &disp : data["dispatchers"]) {
                if (disp["username"] == userCari) {
                    found = true;
                    cout << hijau << "\n✅ Ditemukan: " << disp["username"] << putih << endl;
                    cout << "Apa yang ingin diupdate?" << endl;
                    cout << "\n[1]. Password" << endl;
                    cout << "[2]. Status Karyawan" << endl;
                    cout << "\nMasukkan Pilihan: ";
                    int updatePilih;
                    cin >> updatePilih;

                    if (updatePilih == 1) {
                        cout << "Masukkan Password Baru: "; 
                        cin.ignore(); string temp; getline(cin, temp); 
                        if(!temp.empty()) disp["password"] = temp;
                        cout << "Password diperbarui." << endl;
                    } 
                    else if (updatePilih == 2) {
                        cout << "Masukkan Status Baru: "; 
                        cin.ignore(); string temp; getline(cin, temp); 
                        if(!temp.empty()) disp["status"] = temp;
                        cout << "Status karyawan diperbarui." << endl;
                    }
                    simpanDatabaseDispatcher(data);
                    break;
                }
            }
            if (!found) {
                cout << merah << "\n[-] Username tidak ditemukan!" << putih << endl;
            }
            pause();
        } 
        else if (pilihan == 4) {
            // DELETE / PECAT DISPATCHER
            clearScreen();
            daftarDispatcher();
            cout << emas << "\n<|  PECAT DISPATCHER  |>" << putih << endl;
            cout << "\nMasukkan Username Dispatcher yang akan dihapus: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            string userHapus;
            getline(cin, userHapus);

            data = bacaDatabaseDispatcher();
            auto it = data["dispatchers"].begin();
            bool found = false;
            
            while (it != data["dispatchers"].end()) {
                if ((*it)["username"] == userHapus) {
                    found = true;
                    char konfirmasi;
                    bool validInput = false;
                    
                    string prompt = "\n⚠️ Warning: Apakah kamu yakin ingin menghapus akun '" + (*it)["username"].get<string>() + "'? (y/n): ";

                    do {
                        cout << kuning << prompt << putih;
                        cout.flush();

                        konfirmasi = getch(); 
                        konfirmasi = tolower(konfirmasi);

                        if (konfirmasi == 'y' || konfirmasi == 'n') {
                            validInput = true;
                            cout << konfirmasi << endl; 
                            
                            if (konfirmasi == 'y') {
                                it = data["dispatchers"].erase(it); 
                                simpanDatabaseDispatcher(data);
                                cout << hijau << "\n✅ Akun Dispatcher telah dihapus." << putih << endl;
                            } else {
                                cout << merah << "\n❌ Pembatalan penghapusan." << putih << endl;
                                ++it;
                            }
                        } else {
                            cout << "\r"; 
                            for(int i=0; i < prompt.length() + 5; i++) cout << " "; 
                            cout << "\r";
                        }
                    } while (!validInput);
                    break;
                } else {
                    ++it;
                }
            }

            if (!found) {
                cout << merah << "\n❌ Username tidak ditemukan!" << putih << endl;
            }
            pause();
        }
    } while (pilihan != 0);
}

// ADMIN
void menuAdmin() {
    int pilihan;

    do {
        clearScreen();
        cout << emas << titleC << putih << endl;
        cout << "Masukkan Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            kelolaSuperhero();
        }
        else if (pilihan == 2) {
            kelolaDispatcher();
        }
        else if (pilihan == 0) {
            cout << "Anda akan keluar dari menu ini...\n";
            pause();
            break;
        }
        else {
            cout << kuning << "\n⚠️  Error: Pilihan tidak valid!" << endl;
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
        cout << titleA << putih << endl;
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

                /*
                
                TUGAS ADIT 

                Buat Menu Dispatcher dan misi-misi pake Struct

                di menu dispatcher (Setelah Login), akan ada pertanyaan dulu 
                pertanyaan nya ada di titleD, lalu ada dua pilihan:

                - Pilihan Satu: Hell Yeah (Ya)
                - Pilihan Kedua: Nah, Im good

                selain itu, akan muncul output [!] Error: Pilihan Tidak Valid

                kalau dispathcer memilih pilihan pertama, maka dia akan ke menu shift
                shift nya ini ada 4 atau lebih nanti btw :)

                Di menu shift:

                - Daftar hero sudah ditampilkan dari nama, stats dan output misinya
                - Pilihan 1, tambah hero
                - Pilihan 2, update stats
                _ Pilihan 3, kirim hero
                - Pilihan 4 hapus hero dari list
                - gada pilihan keluar, masa kerja mau keluar njir

                Misinya ada 8 biji, dan selesai 

                di pilihan 1, Dispatcher bisa tambah superhero kalau superhero bukan dari program phoenix
                di pilihan 2, Dispatcher bisa upgrade stats apabila superhero mencapai level up
                di pilihan 3, Dispatcher bisa mengirim 1 atau 2 hero untuk menyelesaikan misi
                                di misi nya ini ada judul misi, nama pemanggil, lokasi, persyaratan
                                didalam struct cuma ada judul misi, nama pemanggil, lokasi
                                persyaratan itu dipisah agar bisa highlight kebutuhan statsnya
                - Pilihan 4 hapus hero dari list, bukan berarti hapus hero dari database tapi menghapus hero yang sudah ada di dalam list
                
                setelah selesai shift pertama, dispatcher akan diarahkan ke menu istirahat, akan ada timer yang hitung mundur 15 detik
                habis 15 detik, dispatcher akan kembali ke menu utama. kalau dia login lagi, maka dia lanjut ke shift kedua
                */

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
            cout << kuning << "\n⚠️ Error: Pilihan Tidak Valid!" << putih << endl;
            pause();
        }

    } while (pilihan != 0);

}

// MENU UTAMA

// MAIN
int main() {
    SetConsoleOutputCP(65001);
    // loadingScreen();
    // pause();
    menuUtama();

    return 0;
}

// MAIN