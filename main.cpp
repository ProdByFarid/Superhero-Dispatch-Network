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
#include <cctype>    
#include <limits>
#include <stdexcept>
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

string toLowerManual(string s) {
    string result = s;
    for (int i = 0; i < result.length(); i++) {
        result[i] = tolower(result[i]);
    }
    return result;
}

void pause() {
    cout << putih << "\n[Tekan enter untuk melanjutkan...]" << endl;
    getch();
}

bool isEmptyInput(const string& input) {
    return input.empty() || input.find_first_not_of(' ') == string::npos;
}

bool hasSpecialChars(const string& input) {
    for (char c : input) {
        if (!isalnum(c) && c != ' ' && c != '_' && c != '-' && c != '.' && c != ',') 
            return true;
    }
    return false;
}

bool validateNumberRange(int value, int minVal, int maxVal) {
    return value >= minVal && value <= maxVal;
}

bool validateNotNegative(int value) {
    return value >= 0;
}

bool isHeroNameExists(const json& data, const string& name) {
    for (const auto& hero : data["heroes"]) {
        if (toLowerManual(hero["name"].get<string>()) == toLowerManual(name)) 
            return true;
    }
    return false;
}

bool isDispatcherExists(const json& data, const string& username) {
    for (const auto& disp : data["dispatchers"]) {
        if (toLowerManual(disp["username"].get<string>()) == toLowerManual(username)) 
            return true;
    }
    return false;
}

void showError(const string& message) {
    cout << merah << "\n❌ ERROR: " << message << putih << endl;
}

void validateStringNotEmpty(const string& input, const string& fieldName) {
    if (isEmptyInput(input)) {
        throw invalid_argument(fieldName + " tidak boleh kosong!");
    }
}

void validateStatInput(int value, const string& statName) {
    if (!validateNotNegative(value)) {
        throw invalid_argument(statName + " tidak boleh negatif!");
    }
    if (value > 30) {
        throw invalid_argument(statName + " tidak boleh lebih dari 30!");
    }
}

void validatePointsInput(int value) {
    if (!validateNotNegative(value)) {
        throw invalid_argument("Points tidak boleh negatif!");
    }
}

// ✅ MODIFIKASI: Tambahan validasi spasi
void validateMenuChoice(const string& input) {
    if (isEmptyInput(input)) {
        throw invalid_argument("Input tidak boleh kosong!");
    }
    
    // ✅ Cek apakah ada spasi di input
    for (char c : input) {
        if (isspace(c)) {
            throw invalid_argument("Input tidak boleh mengandung spasi!");
        }
    }
    
    // Cek apakah semua karakter adalah angka
    for (char c : input) {
        if (!isdigit(c)) {
            throw invalid_argument("Input hanya boleh angka!");
        }
    }
}

void validateHeroNameUnique(const json& data, const string& name) {
    if (isHeroNameExists(data, name)) {
        throw invalid_argument("Superhero dengan nama '" + name + "' sudah ada!");
    }
}

void validateDispatcherUnique(const json& data, const string& username) {
    if (isDispatcherExists(data, username)) {
        throw invalid_argument("Dispatcher dengan username '" + username + "' sudah ada!");
    }
}

void validateGenericInput(const string& input, const string& fieldName, bool allowSpecialChars = false) {
    validateStringNotEmpty(input, fieldName);
    if (!allowSpecialChars && hasSpecialChars(input)) {
        throw invalid_argument(fieldName + " tidak boleh mengandung karakter spesial!");
    }
}

string getValidatedLine(const string& prompt, const string& fieldName, bool allowEmpty = false, bool allowSpecial = false) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        
        if (allowEmpty && isEmptyInput(input)) {
            return "";
        }
        
        try {
            validateGenericInput(input, fieldName, allowSpecial);
            return input;
        } catch (const exception& e) {
            showError(e.what());
            pause();
        }
    }
}

int getValidatedInt(const string& prompt, int minVal, int maxVal, const string& fieldName) {
    string input;
    while (true) {
        cout << prompt;
        if (!(cin >> input)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            showError("Input harus berupa angka!");
            pause();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        try {
            int value = stoi(input);
            if (!validateNumberRange(value, minVal, maxVal)) {
                throw invalid_argument(fieldName + " harus antara " + to_string(minVal) + " - " + to_string(maxVal) + "!");
            }
            return value;
        } catch (const exception& e) {
            showError(e.what());
            pause();
        }
    }
}

int getValidatedIntNoLimit(const string& prompt, const string& fieldName, bool allowNegative = false) {
    string input;
    while (true) {
        cout << prompt;
        if (!(cin >> input)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            showError("Input harus berupa angka!");
            pause();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        try {
            int value = stoi(input);
            if (!allowNegative && !validateNotNegative(value)) {
                throw invalid_argument(fieldName + " tidak boleh negatif!");
            }
            return value;
        } catch (const exception& e) {
            showError(e.what());
            pause();
        }
    }
}

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
    int totalPointsEarned;
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
        Silahkan Pilih 1 Untuk Login       
                                                
==============================================
                                            
   [1]. 🔒 Login                          
   [0]. 🔙 Logout                              
                                            
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
   [2]. 🔃 Urutkan Nama Superhero                     
   [3]. 🔃 Urutkan Poin Superhero                    
   [4]. 🔍 Cari Superhero                    
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
                                          
      🧑‍ PENGELOLAAN DISPATCHER 🧑       
                                          
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

string titleK = R"(
===========================================
                                          
         ⚙️  UPDATE DATA AKUN ⚙️         
                                          
===========================================
                                          
   [1]. 📝 Ubah Username              
   [2]. 🔒 Ubah Password      
   [3]. 🟢 Ubah Status      
   [4]. 🧑 Ubah Jabatan        
   [0]. 🔙 Kembali                        
                                          
===========================================
)";

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

    system("chcp 65001 > nul");
    setlocale(LC_ALL, "en_US.UTF-8");
    for (int i = 0; i <= bar; i++) {
        cout << "\r[";
        for (int j = 0; j < bar; ++j) {
            if (j < i) cout << "█"; 
            else cout << "░";
        }
        cout << "] " << (i * 100 / bar) << "%";
        cout.flush();
        Sleep(100);
    }
    cout << endl << "\nSelesai!" << endl;
}

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

json bacaDatabaseDispatcher();

string prosesLogin() {
    int percobaan = 0;
    string inputUser, inputPass;
    Akun akunManager = {237218, "blazer", "123", "manager"};

    while (percobaan < 3) {
        clearScreen();
        cout << emas << titleB << putih << endl;
        inputUser = getValidatedLine("Username: ", "Username", false, false);
        inputPass = getValidatedLine("Password: ", "Password", false, true);

        if (inputUser == akunManager.username && inputPass == akunManager.password) {
            cout << hijau << "\n✅ Login Berhasil. Selamat Datang, Head Of SDN!";
            return akunManager.role;
        } 

        try {
            json dataDisp = bacaDatabaseDispatcher();
            if (!dataDisp["dispatchers"].empty()) {
                for (const auto& disp : dataDisp["dispatchers"]) {
                    if (disp["username"] == inputUser && disp["password"] == inputPass) {
                        cout << hijau << "\n✅ Login Berhasil. Selamat Datang, Dispatcher!";
                        return "dispatcher"; 
                    }
                }
            }
        } catch (const exception& e) {
            cerr << kuning << "⚠️ Warning: Gagal membaca database dispatcher: " << e.what() << putih << endl;
            pause();
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

// ✅ FUNGSI PENCARIAN SUPERHERO YANG DIPERBAIKI
void searchingHeroes() {
    try {
        json data = bacaDatabase();
        daftarSuperhero();
        string cari;
        cout << emas << "\n<|     CARI DATA SUPERHERO     |>" << putih << endl;
        cout << "\nMasukkan Nama Superhero: ";
        getline(cin, cari);
        
        if (isEmptyInput(cari)) {
            showError("Pencarian tidak boleh kosong!");
            pause();
            return;
        }

        // ✅ VALIDASI: Minimal 3 karakter untuk pencarian
        if (cari.length() < 3) {
            showError("Minimal 3 karakter untuk pencarian!");
            pause();
            return;
        }
        
        bool ditemukan = false;
        string cariLower = toLowerManual(cari); 
        
        // ✅ KUMPULKAN SEMUA HASIL YANG COCOK (Prefix Match)
        vector<json> hasilPencarian;
        for (const auto &hero : data["heroes"]) {
            string namaHero = hero["name"].get<string>();
            string namaLower = toLowerManual(namaHero); 
            
            // ✅ PREFIX MATCH: Hanya cocokkan jika kata kunci ada di AWAL nama
            if (namaLower.find(cariLower) == 0) {
                hasilPencarian.push_back(hero);
            }
        }

        if (!hasilPencarian.empty()) {
            clearScreen();
            cout << cyan << "\n<|     HASIL PENCARIAN (" << hasilPencarian.size() << " DITEMUKAN)     |>" << endl;
            
            for (const auto& hero : hasilPencarian) {
                cout << putih << "\n" << hero["name"].get<string>() 
                     << " | " << (hero.contains("aliases") ? hero["aliases"].get<string>() : "-") << endl;
                cout << "Poin: " << hero["points"].get<int>() << endl;
                cout << "------------------------" << endl;
            }
            cout << "\n💡 Tip: Gunakan nama lebih spesifik untuk hasil yang lebih akurat." << endl;
            ditemukan = true;
        }
        
        if (!ditemukan) {
            clearScreen();
            cout << cyan << "\n<|     HASIL PENCARIAN DATA     |>" << endl;
            cout << merah << "\n❌ Superhero tidak ditemukan!" << putih << endl;
            cout << kuning << "\n💡 Tip: Cek ejaan atau gunakan awalan nama yang berbeda." << putih << endl;
        }
        pause();
        
    } catch (const exception& e) {
        cerr << kuning << "\n[ERROR] Gagal mencari data: " << e.what() << putih << endl;
        pause();
    }
}

void menuLihatDatabase() {
    string pilihanStr;
    int pilihan;
    
    do {
        clearScreen();
        cout << emas << titleF << putih << endl;
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
                    daftarSuperhero();
                    pause();
                } else if (pilihan == 2) {
                    json data = bacaDatabase();
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
                    cout << hijau << "\n✅ Data berhasil diurutkan berdasarkan Nama!" << putih << endl;
                    pause();
                } else if (pilihan == 3) {
                    json data = bacaDatabase();
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
                } else if (pilihan == 4) {
                    searchingHeroes();
                    pause();
                }else if (pilihan == 0) {
                    cout << kuning << "\n🔙 Anda Akan Kembali ke Menu Pengelolaan Superhero!" << endl;
                    pause();
                    break;
                } else {
                    showError("Pilihan Tidak Valid!");
                    pause();
                }
            } catch (const exception& e) {
                cerr << kuning << "\n[SYSTEM ERROR] " << e.what() << putih << endl;
                pause();
            }
        }
    } while (pilihan != 0);
}

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

void kelolaSuperhero() {
    string pilihanStr;
    int pilihan;
    
    do {
        clearScreen();
        cout << cyan << titleE << putih << endl;
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
                json data; 

                if (pilihan == 1) {
                    clearScreen();
                    cout << emas << "\n<|  TAMBAH SUPERHERO BARU  |>" << putih << endl;
                    json newHero;

                    string nama = getValidatedLine("\nNama: ", "Nama Superhero", false, false);
                    data = bacaDatabase();
                    validateHeroNameUnique(data, nama);
                    newHero["name"] = nama;
                    
                    newHero["aliases"] = getValidatedLine("Alias: ", "Alias", true, true);
                    newHero["profileType"] = getValidatedLine("Tipe Profile: ", "Tipe Profile", true, true);
                    newHero["age"] = getValidatedLine("Umur: ", "Umur", true, true);
                    newHero["height"] = getValidatedLine("Tinggi (cm): ", "Tinggi", true, true);
                    newHero["abilities"] = getValidatedLine("Kemampuan: ", "Kemampuan", true, true);
                    newHero["birthplace"] = getValidatedLine("Tempat Lahir: ", "Tempat Lahir", true, true);
                    newHero["description"] = getValidatedLine("Deskripsi: ", "Deskripsi", true, true);

                    int points = getValidatedIntNoLimit("Points: ", "Points", false);
                    validatePointsInput(points);
                    newHero["points"] = points;

                    cout << emas << "\n<|  TAMBAHKAN STATISTIK  |>" << putih << endl;
                    json stats;
                    stats["combat"]   = getValidatedInt("\nCombat: ", 0, 30, "Combat");
                    stats["vigor"]    = getValidatedInt("Vigor: ", 0, 30, "Vigor");
                    stats["mobility"] = getValidatedInt("Mobility: ", 0, 30, "Mobility");
                    stats["charisma"] = getValidatedInt("Charisma: ", 0, 30, "Charisma");
                    stats["intellect"]= getValidatedInt("Intellect: ", 0, 30, "Intellect");

                    newHero["stats"] = stats;
                    
                    data = bacaDatabase();
                    data["heroes"].push_back(newHero);
                    simpanDatabase(data);
                    
                    cout << hijau << "\n✅ Superhero berhasil ditambahkan!" << putih << endl;
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
                    string namaCari;
                    getline(cin, namaCari);

                    if (isEmptyInput(namaCari)) {
                        showError("Pencarian tidak boleh kosong!");
                        pause();
                        continue;
                    }

                    data = bacaDatabase();
                    bool found = false;
                    
                    for (auto &hero : data["heroes"]) {
                        if (hero["name"] == namaCari) {
                            found = true;
                            cout << hijau << "\n[+] Ditemukan: " << hero["name"] << putih << endl;
                            cout << "Apa yang ingin diupdate?" << endl;
                            cout << "\n[1]. Biografi" << endl;
                            cout << "[2]. Statistik" << endl;
                            
                            string updateStr;
                            cout << "\nMasukkan Pilihan: ";
                            getline(cin, updateStr);
                            
                            int updatePilih;
                            try {
                                validateMenuChoice(updateStr);
                                updatePilih = stoi(updateStr);
                            } catch (const exception& e) {
                                showError(e.what());
                                pause();
                                break;
                            }

                            if (updatePilih == 1) {
                                cout << "Edit Nama (Enter untuk skip): "; 
                                string temp; 
                                getline(cin, temp); 
                                if(!temp.empty()) {
                                    try {
                                        validateGenericInput(temp, "Nama", false);
                                        if (temp != hero["name"]) {
                                            validateHeroNameUnique(data, temp);
                                        }
                                        hero["name"] = temp;
                                    } catch (const exception& e) {
                                        showError(e.what());
                                        pause();
                                        break;
                                    }
                                }

                                cout << "Edit Tagline (Enter untuk skip): "; 
                                getline(cin, temp); 
                                if(!temp.empty()) hero["tagline"] = temp;
                                
                                cout << "Edit Deskripsi (Enter untuk skip): "; 
                                getline(cin, temp); 
                                if(!temp.empty()) hero["description"] = temp;
                                
                                cout << hijau << "\n✅ Biografi diperbarui." << putih << endl;
                            } 
                            else if (updatePilih == 2) {
                                hero["stats"]["combat"] = getValidatedInt("Edit Combat: ", 0, 30, "Combat");
                                hero["stats"]["vigor"] = getValidatedInt("Edit Vigor: ", 0, 30, "Vigor");
                                hero["stats"]["mobility"] = getValidatedInt("Edit Mobility: ", 0, 30, "Mobility");
                                hero["stats"]["charisma"] = getValidatedInt("Edit Charisma: ", 0, 30, "Charisma");
                                hero["stats"]["intellect"] = getValidatedInt("Edit Intellect: ", 0, 30, "Intellect");
                                
                                int total = hero["stats"]["combat"].get<int>() + 
                                           hero["stats"]["vigor"].get<int>() + 
                                           hero["stats"]["mobility"].get<int>() + 
                                           hero["stats"]["charisma"].get<int>() + 
                                           hero["stats"]["intellect"].get<int>();
                                hero["points"] = total;
                                cout << hijau << "\n✅ Statistik diperbarui." << putih << endl;
                            }
                            simpanDatabase(data);
                            break;
                        }
                    }
                    if (!found) {
                        showError("Nama tidak ditemukan!");
                        pause();
                    }
                    pause();
                } else if (pilihan == 4) {
                    clearScreen();
                    daftarSuperhero();
                    cout << emas << "\n<|  PECAT SUPERHERO  |>" << putih << endl;
                    cout << "\nMasukkan Nama Superhero: ";
                    string namaHapus;
                    getline(cin, namaHapus);

                    if (isEmptyInput(namaHapus)) {
                        showError("Nama tidak boleh kosong!");
                        pause();
                        continue;
                    }

                    data = bacaDatabase();
                    auto it = data["heroes"].begin();
                    bool found = false;
                    
                    while (it != data["heroes"].end()) {
                        if ((*it)["name"] == namaHapus) {
                            found = true;
                            char konfirmasi;
                            bool validInput = false;
                            string prompt = "\n⚠️  Warning: Apakah kamu yakin ingin memecat '" + (*it)["name"].get<string>() + "'? (y/n): ";

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
                                        pause();
                                    } else {
                                        cout << merah << "\n❌ Pembatalan penghapusan." << putih << endl;
                                        pause();
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
                        showError("Nama tidak ditemukan!");
                        pause();
                    }
                } else {
                    showError("Pilihan Tidak Valid!");
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
    string pilihanStr;
    int pilihan;

    do {
        cout << cyan << titleJ << putih << endl;
        cout << "\nMasukkan Pilihan: ";
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
            showError("Pilihan Tidak Valid!");
            pause();
        }
    } while (pilihan != 0);
}

void kelolaDispatcher() {
    string pilihanStr;
    int pilihan;
    
    do {
        clearScreen();
        cout << emas << titleH << putih << endl;
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
                json data = bacaDatabaseDispatcher();
                if (pilihan == 1) { 
                    cout << emas << "\n<|  BUAT AKUN DISPATCHER BARU  |>" << putih << endl;
                    json newDisp;
                    
                    string id = getValidatedLine("\nID Dispatcher: ", "ID", false, true);
                    newDisp["id"] = id;
                    
                    string username = getValidatedLine("Username: ", "Username", false, false);
                    validateDispatcherUnique(data, username);
                    newDisp["username"] = username;
                    
                    string password = getValidatedLine("Password: ", "Password", false, true);
                    newDisp["password"] = password;
                    
                    string status = getValidatedLine("Status (Aktif/Training): ", "Status", false, true);
                    newDisp["status"] = status;
                    
                    newDisp["level"] = 0; 
                    newDisp["exp"] = 0; 
                    newDisp["jabatan"] = tentukanJabatan(0);
                    
                    data["dispatchers"].push_back(newDisp);
                    simpanDatabaseDispatcher(data);
                    cout << hijau << "\n✅ Akun Dispatcher Berhasil Ditambahkan!" << putih << endl;
                    pause();
                }
                else if (pilihan == 2) { 
                    string subPilihanStr;
                    int subPilihan;
                    bool backToMenu = false;
                    
                    do {
                        clearScreen();
                        cout << cyan << titleI << putih << endl;
                        cout << "Masukkan Pilihan: ";
                        getline(cin, subPilihanStr);
                        
                        try {
                            validateMenuChoice(subPilihanStr);
                            subPilihan = stoi(subPilihanStr);
                        } catch (const exception& e) {
                            showError(e.what());
                            subPilihan = -1;
                            pause(); 
                            continue; 
                        }

                        data = bacaDatabaseDispatcher(); 
                        if (subPilihan == 1) { 
                            clearScreen(); 
                            daftarDispatcher(); 
                            pause(); 
                            backToMenu = true; 
                        }
                        else if (subPilihan == 2) { 
                            sortingDispatcher();
                        }
                        else if (subPilihan == 3) { 
                            // ✅ PENCARIAN DISPATCHER YANG DIPERBAIKI
                            clearScreen(); 
                            daftarDispatcher();
                            string cari; 
                            cout << "\nMasukkan Nama Dispatcher: "; 
                            getline(cin, cari);
                            
                            if (isEmptyInput(cari)) {
                                showError("Pencarian tidak boleh kosong!");
                                pause();
                                continue;
                            }
                            
                            // ✅ VALIDASI: Minimal 3 karakter
                            if (cari.length() < 3) {
                                showError("Minimal 3 karakter untuk pencarian!");
                                pause();
                                continue;
                            }
                            
                            bool ketemu = false;
                            string cariLower = toLowerManual(cari);
                            
                            for (const auto& disp : data["dispatchers"]) {
                                string usernameLower = toLowerManual(disp["username"].get<string>());
                                // ✅ PREFIX MATCH untuk dispatcher
                                if (usernameLower.find(cariLower) == 0) {
                                    cout << hijau << "\n[Data Ditemukan]" << putih << endl;
                                    cout << "ID      : " << disp["id"].get<string>() << "\nNama    : " << disp["username"].get<string>() << endl;
                                    cout << "Jabatan : " << (disp.contains("jabatan") ? disp["jabatan"].get<string>() : "-") << "\nLevel   : " << (disp.contains("level") ? disp["level"].get<int>() : 0) << endl;
                                    ketemu = true;
                                }
                            }
                            if (!ketemu) {
                                showError("Dispatcher tidak ditemukan!");
                                cout << kuning << "\n💡 Tip: Cek ejaan atau gunakan awalan username yang berbeda." << putih << endl;
                                pause();
                            }
                            backToMenu = true;
                        } 
                        else if (subPilihan == 0) {
                            backToMenu = true;
                            cout << putih << "\n🔙 Anda akan keluar dari menu ini" << endl;
                            pause();
                        } else { 
                            showError("Pilihan tidak valid!"); 
                            pause();
                        }
                    } while (!backToMenu);
                }
                else if (pilihan == 3) { 
                    clearScreen(); 
                    daftarDispatcher();
                    cout << emas << "\n<|  UPDATE DATA DISPATCHER  |>" << putih << endl;
                    cout << "\nMasukkan Username Dispatcher yang ingin diubah: ";
                    string userCari; 
                    getline(cin, userCari);
                    
                    if (isEmptyInput(userCari)) {
                        showError("Username tidak boleh kosong!");
                        pause();
                        continue;
                    }
                    
                    bool found = false;
                    for (auto &disp : data["dispatchers"]) {
                        if (disp["username"] == userCari) {
                            found = true;
                            cout << hijau << "\n✅ Akun Ditemukan: " << disp["username"] << putih << endl;
                            pause();
                            
                            string upStr;
                            int up; 
                            do {
                                clearScreen();
                                cout << titleK << putih << endl;
                                cout << "\nMasukkan Pilihan: ";
                                getline(cin, upStr);
                                
                                try {
                                    validateMenuChoice(upStr);
                                    up = stoi(upStr);
                                } catch (const exception& e) {
                                    showError(e.what());
                                    up = -1;
                                    pause();
                                    continue;
                                }
                                
                                cin.ignore();
                                string temp;
                                switch(up) {
                                    case 1: 
                                        temp = getValidatedLine("Username Baru: ", "Username", true, false);
                                        if(!temp.empty()) {
                                            validateDispatcherUnique(data, temp);
                                            disp["username"] = temp;
                                        }
                                        break; 
                                    case 2: 
                                        temp = getValidatedLine("Password Baru: ", "Password", true, true);
                                        if(!temp.empty()) disp["password"] = temp; 
                                        break; 
                                    case 3: 
                                        temp = getValidatedLine("Status Baru: ", "Status", true, true);
                                        if(!temp.empty()) disp["status"] = temp; 
                                        break;
                                    case 4: 
                                        temp = getValidatedLine("Jabatan Baru: ", "Jabatan", true, true);
                                        if(!temp.empty()) disp["jabatan"] = temp; 
                                        break;
                                    case 0:
                                        break;
                                    default:
                                        showError("Pilihan tidak valid!");
                                        pause();
                                        continue;
                                }
                                if (up != 0) { 
                                    simpanDatabaseDispatcher(data); 
                                    cout << hijau << "\n✅ Perubahan berhasil disimpan!" << putih << endl;
                                    pause();
                                }
                                break;
                            } while (up != 0);
                        }
                    }
                    if(!found) {
                        showError("Akun dengan username tersebut tidak ditemukan!");
                        pause();
                    }
                }
                else if (pilihan == 4) { 
                    clearScreen(); 
                    daftarDispatcher();
                    cout << kuning << "\n<|  PECAT DISPATCHER  |>" << putih << endl;
                    cout << "\nMasukkan Username Dispatcher: ";
                    string hapus; 
                    getline(cin, hapus);
                    
                    if (isEmptyInput(hapus)) {
                        showError("Username tidak boleh kosong!");
                        pause();
                        continue;
                    }
                    
                    auto it = data["dispatchers"].begin();
                    bool found = false;
                    while (it != data["dispatchers"].end()) {
                        if ((*it)["username"] == hapus) {
                            found = true;
                            char konf;
                            cout << kuning << "Yakin pecat '" << hapus << "'? (y/n): " << putih;
                            konf = tolower(getch());
                            if (konf == 'y') { 
                                data["dispatchers"].erase(it); 
                                simpanDatabaseDispatcher(data); 
                                cout << hijau << "\n✅ Akun telah dihapus." << putih << endl; 
                            } 
                            else {
                                cout << cyan << "\n❌ Dibatalkan." << putih << endl;
                            }
                            break;
                        }
                        it++;
                    }
                    if (!found) {
                        showError("Username tidak ditemukan!");
                        pause();
                    }
                    pause();
                } else {
                    showError("Pilihan Tidak Valid!");
                    pause();
                }
            } catch (const exception& e) {
                cerr << kuning << "\n[ERROR] " << e.what() << putih << endl;
                pause();
            }
        }
    } while (pilihan != 0);
}

void menuAdmin() {
    string pilihanStr;
    int pilihan;
    
    do {
        clearScreen();
        cout << emas << titleC << putih << endl;
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
                if (pilihan == 1) kelolaSuperhero();
                else if (pilihan == 2) kelolaDispatcher();
                else if (pilihan == 0) { 
                    cout << "\n🔙 Anda akan keluar dari menu ini\n"; 
                    pause(); 
                    break; 
                }
                else {
                    showError("Pilihan tidak valid!");
                    pause();
                }
            } catch (const exception& e) {
                cerr << kuning << e.what() << putih << endl; 
                pause();
            }
        }
    } while (pilihan != 0);
}

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
    getline(cin, nama);

    if (isEmptyInput(nama)) {
        showError("Nama hero tidak boleh kosong!");
        pause();
        return;
    }

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
            h.totalPointsEarned = 0;

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

    if (heroShift.empty()) {
        showError("Tidak ada hero dalam shift!");
        pause();
        return;
    }

    string pilihStr;
    int pilih;

    cout << "\nPilih hero: ";
    getline(cin, pilihStr);

    try {
        validateMenuChoice(pilihStr);
        pilih = stoi(pilihStr);
    } catch (const exception& e) {
        showError(e.what());
        pause();
        return;
    }

    pilih--;

    if (pilih < 0 || pilih >= heroShift.size()) {
        showError("Hero tidak valid!");
        pause();
        return;
    }

    string statPilihanStr;
    int statPilihan;

    clearScreen();

    cout << cyan << "\n=== UPDATE STATS HERO ===\n" << putih;

    cout << "\nHero : " << heroShift[pilih].name << endl;
    Sleep(200);  

    cout << "\n[1] Combat";
    Sleep(100);
    cout << "\n[2] Vigor";
    Sleep(100);
    cout << "\n[3] Mobility";
    Sleep(100);
    cout << "\n[4] Charisma";
    Sleep(100);
    cout << "\n[5] Intellect";

    cout << "\n\nPilih stats yang ingin diupdate: ";
    getline(cin, statPilihanStr);

    try {
        validateMenuChoice(statPilihanStr);
        statPilihan = stoi(statPilihanStr);
    } catch (const exception& e) {
        showError(e.what());
        pause();
        return;
    }

    switch (statPilihan) {

        case 1:
            if (heroShift[pilih].combat >= 30) {
                showError("Combat sudah mencapai batas maksimal (30)!");
                pause();
            } else {
                heroShift[pilih].combat += 1;
                cout << hijau << "\nCombat berhasil ditingkatkan +1!\n";
                Sleep(300);  
            }
            break;

        case 2:
            if (heroShift[pilih].vigor >= 30) {
                showError("Vigor sudah mencapai batas maksimal (30)!");
                pause();
            } else {
                heroShift[pilih].vigor += 1;
                cout << hijau << "\nVigor berhasil ditingkatkan +1!\n";
                Sleep(300);  
            }
            break;

        case 3:
            if (heroShift[pilih].mobility >= 30) {
                showError("Mobility sudah mencapai batas maksimal (30)!");
                pause();
            } else {
                heroShift[pilih].mobility += 1;
                cout << hijau << "\nMobility berhasil ditingkatkan +1!\n";
                Sleep(300);  
            }
            break;

        case 4:
            if (heroShift[pilih].charisma >= 30) {
                showError("Charisma sudah mencapai batas maksimal (30)!");
                pause();
            } else {
                heroShift[pilih].charisma += 1;
                cout << hijau << "\nCharisma berhasil ditingkatkan +1!\n";
                Sleep(300);  
            }
            break;

        case 5:
            if (heroShift[pilih].intellect >= 30) {
                showError("Intellect sudah mencapai batas maksimal (30)!");
                pause();
            } else {
                heroShift[pilih].intellect += 1;
                cout << hijau << "\nIntellect berhasil ditingkatkan +1!\n";
                Sleep(300);  
            }
            break;

        default:
            showError("Pilihan stats tidak valid!");
            pause();
            break;
    }
}

struct HasilMisi {
    bool berhasil;
    int persentase;
    int points;
};

int hitungTotalStats(const ShiftHero& hero) {
    return hero.combat + hero.vigor + hero.mobility + 
           hero.charisma + hero.intellect;
}

int hitungTotalStats2Hero(const ShiftHero& hero1, const ShiftHero& hero2) {
    return (hero1.combat + hero1.vigor + hero1.mobility + 
            hero1.charisma + hero1.intellect) +
           (hero2.combat + hero2.vigor + hero2.mobility + 
            hero2.charisma + hero2.intellect);
}

int hitungRequirementStats(const Requirement& req) {
    return req.combat + req.vigor + req.mobility + 
           req.charisma + req.intellect;
}

int hitungPersentaseKeberhasilan(int statsHero, int requirementStats) {
    if (requirementStats == 0) return 100;
    
    double persentase = (double)statsHero / requirementStats * 100;
    
    if (persentase > 100) persentase = 100;
    if (persentase < 0) persentase = 0;
    
    return (int)persentase;
}

HasilMisi tentukanHasilMisi(int persentase) {
    HasilMisi hasil;
    hasil.persentase = persentase;
    
    if (persentase > 70) {
        hasil.berhasil = true;
        hasil.points = 50;
    } else {
        int random = rand() % 70; 
        
        if (random > 30) {
            hasil.berhasil = true;
            hasil.points = 30;
        } else {
            hasil.berhasil = false;
            hasil.points = 0;
        }
    }
    
    return hasil;
}

void kirimHero() {
    clearScreen();

    cout << cyan << "\n=== DAFTAR MISI ===\n" << putih;

    for (int i = 0; i < daftarMisi.size(); i++) {
        cout << "\n[" << i + 1 << "] "
             << daftarMisi[i].info.judul
             << " | Lokasi: " << daftarMisi[i].info.lokasi
             << " | Pelanggan: " << daftarMisi[i].info.caller << endl;
        Sleep(200);  
    }

    string pilihMisiStr;
    int pilihMisi;

    cout << "\nPilih misi (0 untuk batal): ";
    getline(cin, pilihMisiStr);

    try {
        validateMenuChoice(pilihMisiStr);
        pilihMisi = stoi(pilihMisiStr);
    } catch (const exception& e) {
        showError(e.what());
        pause();
        return;
    }

    if (pilihMisi == 0) {
        cout << kuning << "\nPembatalan dispatch." << putih << endl;
        pause();
        return;
    }

    pilihMisi--;

    if (pilihMisi < 0 || pilihMisi >= daftarMisi.size()) {
        showError("Misi tidak valid!");
        pause();
        return;
    }

    clearScreen();
    cout << cyan << "\n=== DAFTAR HERO DALAM SHIFT ===\n" << putih;

    tampilHeroShift();

    if (heroShift.empty()) {
        showError("Tidak ada hero dalam shift!");
        pause();
        return;
    }

    string heroStr1;
    int hero1Idx;

    cout << "\nPilih hero pertama (WAJIB): ";
    getline(cin, heroStr1);

    try {
        validateMenuChoice(heroStr1);
        hero1Idx = stoi(heroStr1);
    } catch (const exception& e) {
        showError(e.what());
        pause();
        return;
    }

    hero1Idx--;

    if (hero1Idx < 0 || hero1Idx >= heroShift.size()) {
        showError("Hero pertama tidak valid!");
        pause();
        return;
    }

    cout << "\nPilih hero kedua (tekan ENTER untuk skip): ";
    string heroStr2;
    getline(cin, heroStr2);

    int hero2Idx = -1;
    bool gunakan2Hero = false;

    if (!isEmptyInput(heroStr2)) {
        try {
            validateMenuChoice(heroStr2);
            hero2Idx = stoi(heroStr2);
        } catch (const exception& e) {
            showError(e.what());
            pause();
            return;
        }

        hero2Idx--;

        if (hero2Idx < 0 || hero2Idx >= heroShift.size()) {
            showError("Hero kedua tidak valid!");
            pause();
            return;
        }

        if (hero2Idx == hero1Idx) {
            showError("Hero yang dipilih tidak boleh sama!");
            pause();
            return;
        }

        gunakan2Hero = true;
    }

    clearScreen();
    loadingBar();

    int totalStatsHero;
    
    if (gunakan2Hero) {
        totalStatsHero = hitungTotalStats2Hero(heroShift[hero1Idx], 
                                               heroShift[hero2Idx]);
    } else {
        totalStatsHero = hitungTotalStats(heroShift[hero1Idx]);
    }

    int totalStatsRequirement = hitungRequirementStats(daftarMisi[pilihMisi].req);
    int persentase = hitungPersentaseKeberhasilan(totalStatsHero, 
                                                   totalStatsRequirement);

    HasilMisi hasil = tentukanHasilMisi(persentase);

    clearScreen();
    cout << cyan << "\n=== HASIL DISPATCH MISI ===\n" << putih;

    Sleep(500);
    cout << "\nHero Ditugaskan:\n";
    cout << "  • " << heroShift[hero1Idx].name << endl;
    Sleep(300);
    
    if (gunakan2Hero) {
        cout << "  • " << heroShift[hero2Idx].name << endl;
        Sleep(300);
    }

    cout << "\nMisi: " << daftarMisi[pilihMisi].info.judul << endl;
    Sleep(300);
    cout << "Lokasi: " << daftarMisi[pilihMisi].info.lokasi << endl;
    Sleep(300);

    cout << "\n" << emas << "--- Analisis Statistik ---" << putih << endl;
    Sleep(300);
    cout << "Total Stats Hero: " << totalStatsHero << endl;
    Sleep(300);
    cout << "Requirement Stats: " << totalStatsRequirement << endl;
    Sleep(300);
    cout << "Persentase Keberhasilan: " << persentase << "%" << endl;
    Sleep(300);

    cout << "\n" << (hasil.berhasil ? hijau : merah);
    if (hasil.berhasil) {
        cout << "✅ MISI BERHASIL!\n";
    } else {
        cout << "❌ MISI GAGAL!\n";
    }
    cout << putih;

    Sleep(500);
    cout << "\nReward Points: +" << hasil.points << " points";
    if (gunakan2Hero) {
        cout << " (per hero)";
    }
    cout << endl;

    Sleep(500);
    heroShift[hero1Idx].totalPointsEarned += hasil.points;
    
    if (gunakan2Hero) {
        heroShift[hero2Idx].totalPointsEarned += hasil.points;
    }

    if (hasil.berhasil) {
        daftarMisi.erase(daftarMisi.begin() + pilihMisi);
        cout << hijau << "\n[+] Misi dihapus dari daftar." << putih << endl;
        Sleep(300);

        if (daftarMisi.empty()) {
            cout << hijau << "\n✅ Semua misi telah diselesaikan!" << putih << endl;
            cout << "Shift akan berakhir setelah menu ini ditutup.\n";
            Sleep(500);
        }
    }
}

void hapusHeroShift() {

    tampilHeroShift();

    if (heroShift.empty()) {
        showError("Tidak ada hero dalam shift!");
        pause();
        return;
    }

    string pilihStr;
    int pilih;

    cout << "\nPilih hero yang dihapus: ";
    getline(cin, pilihStr);

    try {
        validateMenuChoice(pilihStr);
        pilih = stoi(pilihStr);
    } catch (const exception& e) {
        showError(e.what());
        pause();
        return;
    }

    pilih--;

    if (pilih < 0 || pilih >= heroShift.size()) {
        showError("Hero tidak valid!");
        pause();
        return;
    }

    heroShift.erase(heroShift.begin() + pilih);

    cout << hijau << "\nHero dihapus dari shift!\n";

    pause();
}

void menuDispatcher() {

    initMission();

    string pilihStr;
    int pilih;

    do {

        clearScreen();

        cout << cyan;
        cout << "\n=== SHIFT DISPATCHER #" << currentShift << " ===\n";
        cout << putih;

        cout << "\n" << emas << "<| HERO DALAM SHIFT |>" << putih << "\n";
        
        if (heroShift.empty()) {
            cout << merah << "  (Belum ada hero)\n" << putih;
        } else {
            for (int i = 0; i < heroShift.size(); i++) {
                cout << "  [" << i + 1 << "] " << heroShift[i].name 
                     << " | Points: " << heroShift[i].totalPointsEarned << "\n";
                Sleep(150);
            }
        }

        cout << "\n" << emas << "<| DAFTAR MISI AKTIF |>" << putih << "\n";
        
        if (daftarMisi.empty()) {
            cout << hijau << "  (Tidak ada misi - Shift akan selesai)\n" << putih;
        } else {
            for (int i = 0; i < daftarMisi.size(); i++) {
                cout << "  [" << i + 1 << "] " 
                     << daftarMisi[i].info.judul 
                     << " | " << daftarMisi[i].info.lokasi << "\n";
                Sleep(150);
            }
        }

        cout << "\n" << kuning << "=== MENU OPTIONS ===" << putih << "\n";
        cout << "[1] Tambah Hero\n";
        cout << "[2] Update Stats Hero\n";
        cout << "[3] Kirim Hero ke Misi\n";
        cout << "[4] Hapus Hero dari Shift\n";
        cout << "[0] Keluar\n";

        cout << "\nPilihan: ";
        getline(cin, pilihStr);

        try {
            validateMenuChoice(pilihStr);
            pilih = stoi(pilihStr);
        } catch (const exception& e) {
            showError(e.what());
            pilih = -1;
            pause();
            continue;
        }

        switch (pilih) {

            case 1:
                tambahHeroShift();
                break;

            case 2:
                updateStatsHero();
                break;

            case 3:
                kirimHero();
                
                if (daftarMisi.empty()) {
                    cout << hijau << "\n✅ Semua misi telah diselesaikan!" << putih << endl;
                    cout << "Shift berakhir secara otomatis.\n";
                    
                    cout << cyan << "\n<| RINGKASAN SHIFT |>\n" << putih;
                    int totalPoints = 0;
                    for (const auto& hero : heroShift) {
                        cout << hero.name << " : " << hero.totalPointsEarned << " points\n";
                        totalPoints += hero.totalPointsEarned;
                    }
                    cout << "\nTotal Points Shift: " << totalPoints << "\n";
                    
                    currentShift++;
                    heroShift.clear();
                    pause();
                    menuIstirahat();
                    return;
                }
                break;

            case 4:
                hapusHeroShift();
                break;

            case 0:
                cout << kuning << "\nMengakhiri shift...\n" << putih;
                cout << "Catatan: Shift yang belum selesai akan dihapus.\n";
                currentShift++;
                heroShift.clear();
                pause();
                return;

            default:
                showError("Pilihan tidak valid!");
                pause();
        }

    } while (true);
}

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
                        pause(); 
                        menuAdmin();
                    }
                    else if (role == "dispatcher") {
                        cout << endl;
                        pause();
                        menuDispatcher();
                    }
                    else if (role == "invalid") {
                        showError("Login gagal! Silakan coba lagi.");
                        pause();
                    }
                }
                else if (pilihan == 0) {
                    cout << emas << "\nTerimakasih Telah Menggunakan Program Ini" << endl; 
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

int main() {
    SetConsoleOutputCP(65001);
    srand(time(0));

    try {
        menuUtama();
    } catch (const exception& e) {
        cerr << "\n[FATAL SYSTEM CRASH] " << e.what() << endl;
        return 1;
    }
    return 0;
}