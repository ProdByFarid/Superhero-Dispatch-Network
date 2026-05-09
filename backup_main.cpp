#include <iostream>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm> 
<<<<<<< HEAD
#include <cctype>  
=======
#include <cctype>    
#include <limits>
#include <stdexcept>
>>>>>>> 4231b72fbcf3efcdbebd93749b24fb2e4cd484bc
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

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

struct Mission {
    string judul;
    string caller;
    string lokasi;
};

struct Requirement {
    int combat;
    int vigor;
    int mobility;
    int charisma;
    int intellect;
};

struct ShiftHero {
    string name;
    int combat;
    int vigor;
    int mobility;
    int charisma;
    int intellect;
    bool dariPhoenix;
};

struct ActiveMission {
    Mission info;
    Requirement req;
    bool selesai;
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
                                          
         🛢️  SUPERHERO DATABASE 🛢️            
                                          
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
                                          
      🧑‍ PENGELOLAAN DISPATCHER 🧑‍💻       
                                          
===========================================
                                         
   [1]. ➕ Tambah Akun Dispatcher         
   [2]. 🔃 Lihat Data Dispatcher      
   [3]. ✏️  Update Data Dispatcher         
   [4]. 🗑️  Pecat Dispatcher               
   [0]. 🔙 Kembali Ke Menu Admin          
                                         
===========================================
)";

string titleI = R"(
===========================================
                                          
       🛢️  DISPATCHER DATABASE 🛢️         
                                          
===========================================
                                        
   [1]. 📄 Lihat Semua Data Dispatcher        
   [2]. 🔃 Urutkan Data             
   [3]. 🔍 Cari Nama Dispatcher           
   [0]. 🔙 Kembali                        
                                          
===========================================
)";

string titleJ = R"(
===========================================
                                          
          🔃 SORTING DATABASE 🔃         
                                          
===========================================
                                          
   [1]. 🔤 Urutkan Nama              
   [2]. 🌟 Urutkan Berdasarkan Level         
   [0]. 🔙 Kembali                        
                                          
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

template<typename T>
T getInputSafe(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("⚠️  Error: Input harus berupa angka!");
        }
    }
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
            if (j < i) cout << (char)219; 
            else cout << (char)176; 
        }
        cout << "] " << (i * 100 / bar) << "%";
        cout.flush();
        Sleep(100);
    }
    cout << endl << "\nSelesai!" << endl;
}

<<<<<<< HEAD
void menuIstirahat() {

    clearScreen();

    cout << cyan;
    cout << "\n====================================";
    cout << "\n         MENU ISTIRAHAT";
    cout << "\n====================================\n";
    cout << putih;

    cout << "\nDispatcher sedang beristirahat...\n";
    cout << "Kembali ke menu utama dalam:\n\n";

    for (int i = 15; i >= 0; i--) {

        cout << "\r" << emas << i << " detik   " << putih;
        cout.flush();

        Sleep(1000);
    }

    cout << hijau << "\n\nIstirahat selesai!\n";
    pause();
}
vector<ShiftHero> heroShift;
vector<ActiveMission> daftarMisi;

int currentShift = 1;
bool shiftSelesai = false;
// UTILITAS 

// LOGIN

=======
>>>>>>> 4231b72fbcf3efcdbebd93749b24fb2e4cd484bc
json bacaDatabaseDispatcher();

string prosesLogin() {
    int percobaan = 0;
    string inputUser, inputPass;
    Akun akunManager = {237218, "manager", "123", "manager"};

    while (percobaan < 3) {
        clearScreen();
        cout << emas << titleB << putih << endl;
        cout << "Username: "; cin >> inputUser;
        cout << "Password: "; cin >> inputPass;

        if (inputUser == akunManager.username && inputPass == akunManager.password) {
            cout << hijau << "\n✅ Login Berhasil. ";
            return akunManager.role;
        } 

        try {
            json dataDisp = bacaDatabaseDispatcher();
            if (!dataDisp["dispatchers"].empty()) {
                for (const auto& disp : dataDisp["dispatchers"]) {
                    if (disp["username"] == inputUser && disp["password"] == inputPass) {
                        cout << hijau << "\n✅ Login Berhasil. ";
                        return "dispatcher"; 
                    }
                }
            }
        } catch (const exception& e) {
            cerr << kuning << "⚠️ Warning: Gagal membaca database dispatcher: " << e.what() << putih << endl;
        }

        percobaan++;
        cout << merah << "\n❌ Username atau Password Salah!\n";
        cout << kuning << "⚠️  Warning: Jumlah percobaan: " << percobaan << endl;

        if (percobaan == 3) {
            cout << merah << "\n❌ Login Gagal! Akses Ditolak." << endl; 
        }
        pause();
        
    }
    
    return "invalid";
}

json bacaDatabase() {
    ifstream file("superhero.json");
    if (!file.is_open()) {
        throw runtime_error("File 'superhero.json' tidak ditemukan!");
    }
    json data;
    try {
        file >> data;
    } catch (...) {
        throw runtime_error("Format file 'superhero.json' rusak!");
    }
    file.close();
    return data;
}

void simpanDatabase(const json& data) {
    ofstream file("superhero.json");
    if (!file.is_open()) {
        throw runtime_error("Gagal menyimpan data superhero!");
    }
    file << setw(4) << data << endl; 
    file.close();
}

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
        throw runtime_error("Gagal menyimpan database dispatcher!");
    }
}

void daftarDispatcher() {
    string header(95, '=');
    json data = bacaDatabaseDispatcher();

    if (data["dispatchers"].empty()) {
        cout << emas << "\n <|     DAFTAR DISPATCHER KOSONG     |>" << putih << endl;
    } else {
        clearScreen();
        cout << emas << "\n                               <| DATA DISPATCHER SDN |>" << putih << endl;
        cout << endl;
        cout << header << endl;
        cout << "| " << cyan << setw(8) << left << "ID" << putih 
             << "| " << cyan << setw(15) << left << "USERNAME" << putih 
             << "| " << biru << setw(6) << left << "LVL" << putih 
             << "| " << biru << setw(10) << left << "EXP" << putih 
             << "| " << emas << setw(25) << left << "JABATAN" << putih 
             << "| " << putih << setw(15) << left << "STATUS" << " |" << endl;
        cout << header << endl;
        for (const auto &disp : data["dispatchers"]) {
            cout << "| " << setw(8) << left << disp["id"].get<string>()
                 << "| " << setw(15) << left << disp["username"].get<string>()
                 << "| " << setw(6) << left << (disp.contains("level") ? disp["level"].get<int>() : 0)
                 << "| " << setw(10) << left << (disp.contains("exp") ? disp["exp"].get<int>() : 0)
                 << "| " << setw(25) << left << (disp.contains("jabatan") ? disp["jabatan"].get<string>() : "-")
                 << "| " << setw(15) << left << disp["status"].get<string>() << " |" << endl;
        }
        cout << header << endl;
    }
}

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
            << "| " << setw(30) << left << (hero.contains("aliases") ? hero["aliases"].get<string>() : "-")
            << "| " << setw(5) << left << hero["points"].get<int>() << " |" <<endl;
            no++;
        }
        cout << header << endl;
    }
}

void sortingHeroes() {
    int pilihanSort;
    do {
        clearScreen();
        cout << cyan << titleG << putih << endl;
        cout << "\nMasukkan Pilihan: ";
        
        if (!(cin >> pilihanSort)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << kuning << "\n⚠️ Error: Masukkan angka!" << putih << endl;
            pilihanSort = -1;
            pause();
        }

        if (pilihanSort >= 0) {
            try {
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
                                if (nameL <= nameR) { arr[k++] = L[i++]; } 
                                else { arr[k++] = R[j++]; }
                            }
                            while (i < n1) arr[k++] = L[i++];
                            while (j < n2) arr[k++] = R[j++];
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
                    if (!data["heroes"].empty()) mergeSortNames(data["heroes"]);
                    simpanDatabase(data); 
                    cout << hijau << "\n[+] Data berhasil diurutkan berdasarkan Nama!" << putih << endl;
                    pause();
                } 
                else if (pilihanSort == 2) {
                    int n = data["heroes"].size();
                    for (int i = 0; i < n - 1; i++) {
                        int max_idx = i;
                        for (int j = i + 1; j < n; j++) {
                            if (data["heroes"][j]["points"].get<int>() > data["heroes"][max_idx]["points"].get<int>()) {
                                max_idx = j;
                            }
                        }
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
                    cout << kuning << "\n🔙 Kembali ke Menu Database..." << endl;
                    pause();
                    break;
                } 
                else {
                    cout << kuning << "\n⚠️  Error: Pilihan Tidak Valid!" << putih << endl;
                    pause();
                }
            } catch (const exception& e) {
                cerr << kuning << "\n[FATAL ERROR] " << e.what() << putih << endl;
                pause();
            }
        }
    } while (pilihanSort != 0);
}

void searchingHeroes() {
    try {
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
    } catch (const exception& e) {
        cerr << kuning << "\n[ERROR] Gagal mencari data: " << e.what() << putih << endl;
    }
}

void menuLihatDatabase() {
    int pilihan;
    do {
        clearScreen();
        cout << emas << titleF << putih << endl;
        cout << "\nMasukkan Pilihan: ";
        
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << kuning << "\n⚠️ Error: Masukkan angka!" << putih << endl;
            pilihan = -1;
            pause();
        }

        if (pilihan >= 0) {
            try {
                if (pilihan == 1) {
                    daftarSuperhero();
                    pause();
                } else if (pilihan == 2) {
                    sortingHeroes();
                } else if (pilihan == 3) {
                    searchingHeroes();
                    pause();
                } else if (pilihan == 0) {
                    cout << kuning << "\n🔙 Anda Akan Kembali ke Menu Pengelolaan Superhero!" << endl;
                    pause();
                    break;
                } else {
                    cout << kuning << "\n⚠️ Error: Pilihan Tidak Valid!" << endl;
                    pause();
                }
            } catch (const exception& e) {
                cerr << kuning << "\n[SYSTEM ERROR] " << e.what() << putih << endl;
                pause();
            }
        }
    } while (pilihan != 0);
}

<<<<<<< HEAD
void initMission() {
    daftarMisi.clear();

    daftarMisi.push_back({
        {"Penyanderaan Bank", "Kapolsek Metro", "Jakarta"},
        {70, 50, 40, 30, 20},
        false
    });

    daftarMisi.push_back({
        {"Invasi Monster", "Warga", "Bandung"},
        {80, 60, 50, 20, 30},
        false
    });

    daftarMisi.push_back({
        {"Bom Kota", "Pemerintah", "Surabaya"},
        {60, 40, 70, 50, 60},
        false
    });

    daftarMisi.push_back({
        {"Pencurian Teknologi", "Laboratorium", "Batam"},
        {40, 30, 50, 60, 90},
        false
    });

    daftarMisi.push_back({
        {"Serangan Udara", "Militer", "Papua"},
        {85, 70, 80, 40, 30},
        false
    });

    daftarMisi.push_back({
        {"Mutan Mengamuk", "Rumah Sakit", "Bekasi"},
        {75, 65, 50, 30, 20},
        false
    });

    daftarMisi.push_back({
        {"Peretasan Nasional", "Kominfo", "Jakarta"},
        {20, 20, 20, 40, 95},
        false
    });

    daftarMisi.push_back({
        {"Meteor Jatuh", "NASA Indonesia", "Kalimantan"},
        {90, 90, 60, 40, 50},
        false
    });
}
// ADMIN

// GGG: IMPLEMENTASI LENGKAP KELOLA SUPERHERO
=======
>>>>>>> 4231b72fbcf3efcdbebd93749b24fb2e4cd484bc
void kelolaSuperhero() {
    int pilihan;
    do {
        clearScreen();
        cout << cyan << titleE << putih << endl;
        cout << "Masukkan Pilihan: ";
        
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << kuning << "\n⚠️ Error: Masukkan angka!" << endl;
            pilihan = -1;
            pause();
        }

        if (pilihan >= 0) {
            try {
                json data; 

                if (pilihan == 1) {
                    cout << emas << "\n<|  TAMBAH SUPERHERO BARU  |>" << putih << endl;
                    json newHero;
                    string inputString;
                    float inputNum;

                    cout << "\nNama: "; 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, inputString);
                    newHero["name"] = inputString;
                    
                    cout << "Alias: "; getline(cin, inputString); newHero["aliases"] = inputString;
                    cout << "Tipe Profile: "; getline(cin, inputString); newHero["profileType"] = inputString;
                    cout << "Umur: "; getline(cin, inputString); newHero["age"] = inputString;
                    cout << "Tinggi (cm): "; getline(cin, inputString); newHero["height"] = inputString;

                    cout << "Kemampuan: "; getline(cin, inputString); newHero["abilities"] = inputString;
                    cout << "Tempat Lahir: "; getline(cin, inputString); newHero["birthplace"] = inputString;
                    cout << "Deskripsi: "; getline(cin, inputString); newHero["description"] = inputString;

                    cout << "Points: "; 
                    if (!(cin >> inputNum)) throw invalid_argument("Input poin harus angka!");
                    newHero["points"] = inputNum;

                    cout << emas << "\n<|  TAMBAHKAN STATISTIK  |>" << putih << endl;
                    json stats;
                    cout << "\nCombat: "; if (!(cin >> inputNum)) throw invalid_argument("Input statistik harus angka!"); stats["combat"] = inputNum;
                    cout << "Vigor: "; if (!(cin >> inputNum)) throw invalid_argument("Input statistik harus angka!"); stats["vigor"] = inputNum;
                    cout << "Mobility: "; if (!(cin >> inputNum)) throw invalid_argument("Input statistik harus angka!"); stats["mobility"] = inputNum;
                    cout << "Charisma: "; if (!(cin >> inputNum)) throw invalid_argument("Input statistik harus angka!"); stats["charisma"] = inputNum;
                    cout << "Intellect: "; if (!(cin >> inputNum)) throw invalid_argument("Input statistik harus angka!"); stats["intellect"] = inputNum;

                    newHero["stats"] = stats;
                    
                    data = bacaDatabase();
                    data["heroes"].push_back(newHero);
                    simpanDatabase(data);
                    
                    cout << hijau << "\nSuperhero berhasil ditambahkan!" << putih << endl;
                    pause();
                } 
                else if (pilihan == 2) {
                    menuLihatDatabase();
                } 
                else if (pilihan == 3) {
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
                            if (!(cin >> updatePilih)) throw invalid_argument("Input harus angka!");

                            if (updatePilih == 1) {
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
                                cout << "Edit Combat: "; if (!(cin >> hero["stats"]["combat"])) throw invalid_argument("Input harus angka!");
                                cout << "Edit Vigor: "; if (!(cin >> hero["stats"]["vigor"])) throw invalid_argument("Input harus angka!");
                                cout << "Edit Mobility: "; if (!(cin >> hero["stats"]["mobility"])) throw invalid_argument("Input harus angka!");
                                cout << "Edit Charisma: "; if (!(cin >> hero["stats"]["charisma"])) throw invalid_argument("Input harus angka!");
                                cout << "Edit Intellect: "; if (!(cin >> hero["stats"]["intellect"])) throw invalid_argument("Input harus angka!");
                                
                                int total = hero["stats"]["combat"].get<int>() + hero["stats"]["vigor"].get<int>() + hero["stats"]["mobility"].get<int>() + hero["stats"]["charisma"].get<int>() + hero["stats"]["intellect"].get<int>();
                                hero["points"] = total;
                                cout << "Statistik diperbarui." << endl;
                            }
                            simpanDatabase(data);
                            break;
                        }
                    }
                    if (!found) throw out_of_range("\n❌ Nama tidak ditemukan!");
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
                                cout << kuning << prompt << putih;
                                cout.flush();
                                konfirmasi = getch(); 
                                konfirmasi = tolower(konfirmasi);

                                if (konfirmasi == 'y' || konfirmasi == 'n') {
                                    validInput = true;
                                    cout << konfirmasi << endl; 
                                    if (konfirmasi == 'y') {
                                        it = data["heroes"].erase(it); 
                                        simpanDatabase(data);
                                        cout << hijau << "\n✅ Superhero telah dipecat/dihapus." << putih << endl;
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
                    if (!found) throw out_of_range("\n❌ Nama tidak ditemukan!");
                    pause();
                }
            } catch (const exception& e) {
                cerr << kuning << "\n[ERROR] " << e.what() << putih << endl;
                pause();
            }
        }
    } while (pilihan != 0);
}

string tentukanJabatan(int level) {
    if (level == 0) return "Asisten Dispatcher";
    if (level == 1) return "Junior Dispatcher";
    if (level == 2) return "Senior Dispatcher";
    if (level == 3) return "Chief Dispatcher";
    return "Dispatcher";
}

void sortingDispatcher() {
    clearScreen();
    json data = bacaDatabaseDispatcher();
    int pilihan;

    do {
        cout << cyan << titleJ << putih << endl;
        cout << "\nMasukkan Pilihan: ";
        
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << kuning << "\n⚠️ Error: Masukkan angka!" << putih << endl;
            pilihan = -1;
            pause();
            continue;
        }
    
        if (pilihan == 1) {
            int n = data["dispatchers"].size();
            for(int i = 0; i < n-1; i++) {
                for(int j = 0; j < n-i-1; j++) {
                    if(toLowerManual(data["dispatchers"][j]["username"]) > toLowerManual(data["dispatchers"][j+1]["username"])) {
                        swap(data["dispatchers"][j], data["dispatchers"][j+1]);
                    }
                }
            }
            simpanDatabaseDispatcher(data);
            clearScreen(); 
            daftarDispatcher();
            cout << hijau << "\n✅ Data diurutkan berdasarkan Nama!" << putih << endl; 
            pause(); 
        } else if (pilihan == 2) {
            int n = data["dispatchers"].size();
            for(int i = 0; i < n-1; i++) {
                for(int j = 0; j < n-i-1; j++) {
                    int lvlA = data["dispatchers"][j].contains("level") ? data["dispatchers"][j]["level"].get<int>() : 0;
                    int lvlB = data["dispatchers"][j+1].contains("level") ? data["dispatchers"][j+1]["level"].get<int>() : 0;
                    if(lvlA < lvlB) {
                        swap(data["dispatchers"][j], data["dispatchers"][j+1]);
                    }
                }
            }
            simpanDatabaseDispatcher(data);
            clearScreen(); 
            daftarDispatcher();
            cout << hijau << "\n✅ Data diurutkan berdasarkan Level Tertinggi!" << putih << endl; 
            pause();
        } else if (pilihan == 0) {
            cout << kuning << "\n🔙 Anda akan keluar dari menu ini\n"; 
            pause(); 
            break; 
        } else {
            cout << kuning << "\n⚠️ Error: Pilihan Tidak Valid!" << putih << endl;
            pause();
        }
    } while (pilihan != 0);
}

void kelolaDispatcher() {
    int pilihan;
    do {
        clearScreen();
        cout << emas << titleH << putih << endl;
        cout << "Masukkan Pilihan: ";
        
        if (!(cin >> pilihan)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << kuning << "\n⚠️ Error: Masukkan angka!" << endl; 
            pilihan = -1;
            pause();
        }

        if (pilihan >= 0) {
            try {
                json data = bacaDatabaseDispatcher();
                if (pilihan == 1) { 
                    cout << emas << "\n<|  BUAT AKUN DISPATCHER BARU  |>" << putih << endl;
                    json newDisp;
                    string inputString;
                    cout << "\nID Dispatcher: "; cin >> inputString; newDisp["id"] = inputString;
                    cout << "Username: "; cin.ignore(); getline(cin, inputString); newDisp["username"] = inputString;
                    cout << "Password: "; getline(cin, inputString); newDisp["password"] = inputString;
                    cout << "Status (Aktif/Training): "; getline(cin, inputString); newDisp["status"] = inputString;
                    newDisp["level"] = 0; newDisp["exp"] = 0; newDisp["jabatan"] = tentukanJabatan(0);
                    data["dispatchers"].push_back(newDisp);
                    simpanDatabaseDispatcher(data);
                    cout << hijau << "\n✅ Akun Dispatcher Berhasil Ditambahkan!" << putih << endl;
                    pause();
                }
                else if (pilihan == 2) { 
                    int subPilihan;
                    bool backToMenu = false;
                    do {
                        clearScreen();
                        cout << cyan << titleI << putih << endl;
                        cout << "Masukkan Pilihan: ";
                        if (!(cin >> subPilihan)) { 
                            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                            cout << kuning << "⚠️ Error: Masukkan angka!"; 
                            subPilihan = -1;
                            pause(); 
                            continue; 
                        }

                        data = bacaDatabaseDispatcher(); 
                        if (subPilihan == 1) { clearScreen(); daftarDispatcher(); pause(); backToMenu = true; }
                        else if (subPilihan == 2) { 
                            sortingDispatcher();
                        }
                        else if (subPilihan == 3) { 
                            clearScreen(); daftarDispatcher();
                            string cari; cout << "\nMasukkan Nama Dispatcher: "; cin.ignore(); getline(cin, cari);
                            bool ketemu = false;
                            for (const auto& disp : data["dispatchers"]) {
                                if (toLowerManual(disp["username"]).find(toLowerManual(cari)) != string::npos) {
                                    cout << hijau << "\n[Data Ditemukan]" << putih << endl;
                                    cout << "ID      : " << disp["id"].get<string>() << "\nNama    : " << disp["username"].get<string>() << endl;
                                    cout << "Jabatan : " << (disp.contains("jabatan") ? disp["jabatan"].get<string>() : "-") << "\nLevel   : " << (disp.contains("level") ? disp["level"].get<int>() : 0) << endl;
                                    ketemu = true;
                                }
                            }
                            if (!ketemu) cout << kuning << "\n⚠️ Error: Dispatcher tidak ditemukan!" << putih << endl;
                            pause(); 
                            backToMenu = true;
                        } 
                        else if (subPilihan == 0) {
                            backToMenu = true;
                            cout << putih << "🔙 Anda akan keluar dari menu ini" << endl;
                            pause();
                        } else { 
                            cout << kuning << "\n⚠️ Error: Pilihan tidak valid!" << putih << endl; 
                            pause(); 
                        }
                    } while (!backToMenu);
                }
                else if (pilihan == 3) { 
                    clearScreen(); daftarDispatcher();
                    cout << emas << "\n<|  UPDATE DATA DISPATCHER  |>" << putih << endl;
                    cout << "\nMasukkan Username Dispatcher yang ingin diubah: ";
                    string userCari; cin.ignore(); getline(cin, userCari);
                    bool found = false;
                    for (auto &disp : data["dispatchers"]) {
                        if (disp["username"] == userCari) {
                            found = true;
                            cout << hijau << "\n[+] Akun Ditemukan: " << disp["username"] << putih << endl;
                            cout << "1. Ubah Username\n2. Ubah Password\n3. Ubah Status\n4. Ubah Jabatan Manual\n0. Batal\nPilihan: ";
                            int up; cin >> up; cin.ignore();
                            string temp;
                            switch(up) {
                                case 1: cout << "Username Baru: "; getline(cin, temp); if(!temp.empty()) disp["username"] = temp; break;
                                case 2: cout << "Password Baru: "; getline(cin, temp); if(!temp.empty()) disp["password"] = temp; break;
                                case 3: cout << "Status Baru: "; getline(cin, temp); if(!temp.empty()) disp["status"] = temp; break;
                                case 4: cout << "Jabatan Baru: "; getline(cin, temp); if(!temp.empty()) disp["jabatan"] = temp; break;
                            }
                            if (up != 0) { simpanDatabaseDispatcher(data); cout << hijau << "\n✅ Perubahan berhasil disimpan!" << putih << endl; }
                            break;
                        }
                    }
                    if(!found) throw out_of_range("❌ Akun dengan username tersebut tidak ditemukan!");
                    pause();
                }
                else if (pilihan == 4) { 
                    clearScreen(); daftarDispatcher();
                    cout << kuning << "\n<|  PECAT DISPATCHER  |>" << putih << endl;
                    cout << "\nMasukkan Username Dispatcher: ";
                    string hapus; cin.ignore(); getline(cin, hapus);
                    auto it = data["dispatchers"].begin();
                    bool found = false;
                    while (it != data["dispatchers"].end()) {
                        if ((*it)["username"] == hapus) {
                            found = true;
                            char konf;
                            cout << kuning << "Yakin pecat '" << hapus << "'? (y/n): " << putih;
                            konf = tolower(getch());
                            if (konf == 'y') { data["dispatchers"].erase(it); simpanDatabaseDispatcher(data); cout << hijau << "\n✅ Akun telah dihapus." << putih << endl; } 
                            else cout << cyan << "\n❌ Dibatalkan." << putih << endl;
                            break;
                        }
                        it++;
                    }
                    if (!found) throw out_of_range("\n❌ Username tidak ditemukan!");
                    pause();
                } else {
                    throw invalid_argument("\n⚠️ Error: Pilihan Tidak Valid!");
                }
            } catch (const exception& e) {
                cerr << kuning << "\n[ERROR] " << e.what() << putih << endl;
                pause();
            }
        }
    } while (pilihan != 0);
}

void menuAdmin() {
    int pilihan;
    do {
        clearScreen();
        cout << emas << titleC << putih << endl;
        cout << "Masukkan Pilihan: ";
        
        if (!(cin >> pilihan)) { 
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << kuning << "\n⚠️  Error: Masukkan angka!"; 
            pilihan = -1;
            cout << endl;
            pause(); 
        }

        if (pilihan >= 0) {
            try {
                if (pilihan == 1) kelolaSuperhero();
                else if (pilihan == 2) kelolaDispatcher();
                else if (pilihan == 0) { 
                    cout << "\n🔙 Anda akan keluar dari menu ini\n"; 
                    pause(); 
                    break; 
                }
                else throw invalid_argument("\n⚠️  Error: Pilihan tidak valid!");
            } catch (const exception& e) {
                cerr << kuning << e.what() << putih << endl; 
                pause();
            }
        }
    } while (pilihan != 0);
}

<<<<<<< HEAD
// ADMIN

void tampilHeroShift() {
    clearScreen();

    cout << cyan << "\n=== HERO SHIFT LIST ===\n" << putih;

    if (heroShift.empty()) {
        cout << merah << "\nBelum ada hero dalam shift!\n";
        return;
    }

    for (int i = 0; i < heroShift.size(); i++) {
        cout << "\n[" << i + 1 << "] " << heroShift[i].name << endl;
        cout << "Combat    : " << heroShift[i].combat << endl;
        cout << "Vigor     : " << heroShift[i].vigor << endl;
        cout << "Mobility  : " << heroShift[i].mobility << endl;
        cout << "Charisma  : " << heroShift[i].charisma << endl;
        cout << "Intellect : " << heroShift[i].intellect << endl;
    }
}

void tambahHeroShift() {
    json data = bacaDatabase();

    daftarSuperhero();

    cout << "\nMasukkan nama hero: ";

    string nama;
    cin.ignore();
    getline(cin, nama);

    for (auto &hero : data["heroes"]) {

        if (hero["name"] == nama) {

            ShiftHero h;

            h.name = hero["name"];
            h.combat = hero["stats"]["combat"];
            h.vigor = hero["stats"]["vigor"];
            h.mobility = hero["stats"]["mobility"];
            h.charisma = hero["stats"]["charisma"];
            h.intellect = hero["stats"]["intellect"];
            h.dariPhoenix = false;

            heroShift.push_back(h);

            cout << hijau << "\nHero berhasil ditambahkan!\n";
            pause();
            return;
        }
    }

    cout << merah << "\nHero tidak ditemukan!\n";
    pause();
}


void updateStatsHero() {

    tampilHeroShift();

    int pilih;

    cout << "\nPilih hero: ";
    cin >> pilih;

    pilih--;

    if (pilih < 0 || pilih >= heroShift.size()) {
        cout << merah << "\nHero tidak valid!\n";
        pause();
        return;
    }

    int statPilihan;

    clearScreen();

    cout << cyan << "\n=== UPDATE STATS HERO ===\n" << putih;

    cout << "\nHero : " << heroShift[pilih].name << endl;

    cout << "\n[1] Combat";
    cout << "\n[2] Vigor";
    cout << "\n[3] Mobility";
    cout << "\n[4] Charisma";
    cout << "\n[5] Intellect";

    cout << "\n\nPilih stats yang ingin diupdate: ";
    cin >> statPilihan;

    switch (statPilihan) {

        case 1:
            heroShift[pilih].combat += 1;
            cout << hijau << "\nCombat berhasil ditingkatkan +1!\n";
            break;

        case 2:
            heroShift[pilih].vigor += 1;
            cout << hijau << "\nVigor berhasil ditingkatkan +1!\n";
            break;

        case 3:
            heroShift[pilih].mobility += 1;
            cout << hijau << "\nMobility berhasil ditingkatkan +1!\n";
            break;

        case 4:
            heroShift[pilih].charisma += 1;
            cout << hijau << "\nCharisma berhasil ditingkatkan +1!\n";
            break;

        case 5:
            heroShift[pilih].intellect += 1;
            cout << hijau << "\nIntellect berhasil ditingkatkan +1!\n";
            break;

        default:
            cout << merah << "\nPilihan stats tidak valid!\n";
            break;
    }

    pause();
}

void kirimHero() {

    clearScreen();

    cout << cyan << "\n=== DAFTAR MISI ===\n";

    for (int i = 0; i < daftarMisi.size(); i++) {

        cout << "\n[" << i + 1 << "] "
             << daftarMisi[i].info.judul
             << " | " << daftarMisi[i].info.lokasi
             << endl;
    }

    int pilihMisi;

    cout << "\nPilih misi: ";
    cin >> pilihMisi;

    pilihMisi--;

    if (pilihMisi < 0 || pilihMisi >= daftarMisi.size()) {

        cout << merah << "\nMisi tidak valid!\n";
        pause();
        return;
    }

    tampilHeroShift();

    int hero;

    cout << "\nPilih hero: ";
    cin >> hero;

    hero--;

    if (hero < 0 || hero >= heroShift.size()) {

        cout << merah << "\nHero tidak valid!\n";
        pause();
        return;
    }

    loadingBar();

    int persentase = rand() % 101;

    cout << cyan << "\n=== HASIL MISI ===\n" << putih;

    cout << "\nHero         : " << heroShift[hero].name;
    cout << "\nMisi         : " << daftarMisi[pilihMisi].info.judul;
    cout << "\nKeberhasilan : " << persentase << "%" << endl;

    bool berhasil;

    if (persentase >= 70) {

        berhasil = true;

    } else {

        berhasil = rand() % 2;
    }

    if (berhasil) {

        cout << hijau << "\n✅ MISI BERHASIL!\n";

        daftarMisi[pilihMisi].selesai = true;

    } else {

        cout << merah << "\n❌ MISI GAGAL!\n";
    }

    pause();
}

void hapusHeroShift() {

    tampilHeroShift();

    int pilih;

    cout << "\nPilih hero yang dihapus: ";
    cin >> pilih;

    pilih--;

    if (pilih < 0 || pilih >= heroShift.size()) {
        cout << merah << "\nHero tidak valid!\n";
        pause();
        return;
    }

    heroShift.erase(heroShift.begin() + pilih);

    cout << hijau << "\nHero dihapus dari shift!\n";

    pause();
}

void menuShiftDispatcher() {

    initMission();

    int pilih;

    do {

        clearScreen();

        cout << cyan;
        cout << "\n=== SHIFT DISPATCHER #" << currentShift << " ===\n";
        cout << putih;

        cout << "\n[1] Lihat Hero Shift";
        cout << "\n[2] Tambah Hero";
        cout << "\n[3] Update Stats Hero";
        cout << "\n[4] Kirim Hero";
        cout << "\n[5] Hapus Hero";
        cout << "\n[6] Selesaikan Shift";

        cout << "\n\nPilihan: ";
        cin >> pilih;

        switch (pilih) {

            case 1:
                tampilHeroShift();
                pause();
                break;

            case 2:
                tambahHeroShift();
                break;

            case 3:
                updateStatsHero();
                break;

            case 4:
                kirimHero();
                break;

            case 5:
                hapusHeroShift();
                break;
                case 6:

    cout << hijau << "\nShift selesai!\n";

    currentShift++;

    heroShift.clear();

    pause();

    menuIstirahat();

    return;

            default:
                cout << merah << "\nPilihan tidak valid!\n";
                pause();
        }

    } while (true);
}



// MENU UTAMA

=======
>>>>>>> 4231b72fbcf3efcdbebd93749b24fb2e4cd484bc
void menuUtama() {
    int pilihan;
    do {
        clearScreen();
        cout << titleA << putih << endl;
        cout << "Masukkan Pilihan: ";
        
        if (!(cin >> pilihan)) { 
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << kuning << "\n⚠️  Error: Masukkan angka!"; 
            pilihan = -1;
            cout << endl;
            pause(); 
        }

<<<<<<< HEAD
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

                int pilih;

                do {

                    clearScreen();

                    cout << cyan << titleD << putih << endl;

                    cout << "\n[1]. Hell Yeah";
                    cout << "\n[2]. Nah, Im Good";

                    cout << "\n\nPilihan: ";
                    cin >> pilih;

                    if (pilih == 1) {

                        menuShiftDispatcher();

                    }
                    else if (pilih == 2) {

                        cout << "\nDispatcher meninggalkan ruang kerja...\n";
                        pause();
                        break;

                    }
                    else {

                        cout << merah << "\n[!] Error: Pilihan Tidak Valid\n";
                        pause();
                    }

                } while (pilih != 2);

            }
            else {

                cout << merah << "\n[-] Login gagal. Kembali ke Menu Utama..." << endl;
=======
        if (pilihan >= 0) {
            try {
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
                }
                else if (pilihan == 0) {
                    cout << "\nTerimakasih Telah Menggunakan Program Ini" << endl; 
                    pause();
                }
                else throw invalid_argument("\n⚠️  Error: Pilihan Tidak Valid!");
            } catch (const exception& e) {
                cerr << kuning << e.what() << putih << endl; 
>>>>>>> 4231b72fbcf3efcdbebd93749b24fb2e4cd484bc
                pause();

            }

        }
<<<<<<< HEAD
        else if (pilihan == 0) {

            cout << "\nTerimakasih Telah Menggunakan Program Ini" << endl;
            pause();

        }
        else {

            cout << kuning << "\n⚠️ Error: Pilihan Tidak Valid!" << putih << endl;
            pause();

        }

=======
>>>>>>> 4231b72fbcf3efcdbebd93749b24fb2e4cd484bc
    } while (pilihan != 0);
}

int main() {

    srand(time(0));
    SetConsoleOutputCP(65001);
    try {
        loadingScreen();
        pause();
        menuUtama();
    } catch (const exception& e) {
        cerr << "\n[FATAL SYSTEM CRASH] " << e.what() << endl;
        return 1;
    }
    return 0;
}