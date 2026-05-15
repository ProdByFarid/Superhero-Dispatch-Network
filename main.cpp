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

void pause(const string& msg = "\n[Tekan enter untuk melanjutkan...]") {
    cout << putih << msg << endl;
    getch();
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void flushInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    cout << merah << "\n❌ Error: " << message << putih << endl;
}

string getValidatedLine(const string& prompt, const string& fieldName, 
                        bool allowDefaultDash = false, bool allowEmpty = false) {
    string input;
    while (true) {
        cout << putih << prompt;
        getline(cin, input);
        
        if (cin.fail()) flushInput();
        
        if (isEmptyInput(input)) {
            if (allowEmpty) {
                return "";
            } else if (allowDefaultDash) {
                cout << kuning << "\n⚠️ " << fieldName << " kosong, diisi dengan '-'." << putih << endl;
                return "-";
            } else {
                cout << merah << "\n❌ " << fieldName << " tidak boleh kosong! Silakan input ulang." << putih << endl;
                continue;
            }
        }
        return input;
    }
}

string getValidatedName(const string& prompt, const string& fieldName) {
    string input;
    while (true) {
        cout << putih << prompt;
        getline(cin, input);
        
        if (cin.fail()) flushInput();
        
        if (isEmptyInput(input)) {
            cout << merah << "\n❌ " << fieldName << " tidak boleh kosong! Silakan input ulang." << putih << endl;
            continue;
        }
        
        if (input.length() < 3) {
            cout << merah << "\n❌ " << fieldName << " minimal 3 karakter! Silakan input ulang." << putih << endl;
            continue;
        }
        
        return input;
    }
}

int getValidatedInt(const string& prompt, int minVal, int maxVal, const string& fieldName) {
    string input;
    while (true) {
        cout << putih << prompt;
        getline(cin, input);
        
        if (isEmptyInput(input)) {
            cout << merah << "\n❌ " << fieldName << " tidak boleh kosong!" << putih << endl;
            continue;
        }
        
        try {
            size_t idx = 0;
            int value = stoi(input, &idx);
            
            if (idx != input.length()) {
                throw invalid_argument("non-numeric suffix");
            }
            
            if (value < 0) {
                cout << merah << "\n❌ " << fieldName << " tidak boleh negatif!" << putih << endl;
                continue;
            }
            
            if (value > maxVal) {
                cout << merah << "\n❌ " << fieldName << " tidak boleh lebih dari " << maxVal << "!" << putih << endl;
                continue;
            }
            
            if (value < minVal) {
                cout << merah << "\n❌ " << fieldName << " tidak boleh kurang dari " << minVal << "!" << putih << endl;
                continue;
            }
            
            return value;
            
        } catch (const invalid_argument&) {
            cout << merah << "\n❌ " << fieldName << " harus berupa angka!" << putih;
        } catch (const out_of_range&) {
            cout << merah << "\n❌ " << fieldName << " terlalu besar!" << putih;
        }
        flushInput();
    }
}

int getValidatedIntNoLimit(const string& prompt, const string& fieldName, bool allowNegative = false) {
    string input;
    while (true) {
        cout << putih << prompt;
        getline(cin, input);
        
        if (isEmptyInput(input)) {
            cout << merah << "\n❌ " << fieldName << " tidak boleh kosong!" << putih << endl;
            continue;
        }
        
        try {
            size_t idx = 0;
            int value = stoi(input, &idx);
            if (idx != input.length()) {
                throw invalid_argument("non-numeric suffix");
            }
            if (!allowNegative && value < 0) {
                cout << merah << "\n❌ " << fieldName << " tidak boleh negatif!" << putih << endl;
                continue;
            }
            return value;
        } catch (const invalid_argument&) {
            cout << merah << "\n❌ " << fieldName << " harus berupa angka!" << putih << endl;
        } catch (const out_of_range&) {
            cout << merah << "\n❌ " << fieldName << " terlalu besar!" << putih << endl;
        }
        flushInput();
    }
}

void validatePointsInput(int value) {
    if (value < 0) {
        cout << merah << "\n❌ Points tidak boleh negatif!" << putih << endl;
        pause();
    }
}

string getUniqueHeroName(const json& data, const string& prompt) {
    string nama;
    while (true) {
        nama = getValidatedName(prompt, "Nama Superhero");
        if (isHeroNameExists(data, nama)) {
            cout << merah << "\n❌ Nama Superhero Sudah Terdaftar!" << putih << endl;
            pause();
            clearScreen();
            cout << emas << "\n<|  TAMBAH SUPERHERO BARU  |>" << putih << endl;
            continue;
        }
        return nama;
    }
}

string getUniqueDispatcherUsername(const json& data, const string& prompt) {
    string username;
    while (true) {
        username = getValidatedName(prompt, "Username");
        if (isDispatcherExists(data, username)) {
            cout << merah << "\n❌ Username Dispatcher Sudah Terdaftar!" << putih << endl;
            pause();
            clearScreen();
            cout << emas << "\n<|  BUAT AKUN DISPATCHER BARU  |>" << putih << endl;
            continue;
        }
        return username;
    }
}

void validateMenuChoice(const string& input) {
    if (isEmptyInput(input)) {
        throw invalid_argument("Input tidak boleh kosong!");
    }
    for (char c : input) {
        if (isspace(c)) {
            throw invalid_argument("Input tidak boleh mengandung spasi!");
        }
    }
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
    if (isEmptyInput(input)) {
        throw invalid_argument(fieldName + " tidak boleh kosong!");
    }
    if (!allowSpecialChars && hasSpecialChars(input)) {
        throw invalid_argument(fieldName + " tidak boleh mengandung karakter spesial!");
    }
}

string getValidatedLine(const string& prompt, const string& fieldName) {
    return getValidatedLine(prompt, fieldName, false, false);
}

void validateGenericInput(const string& input, const string& fieldName) {
    validateGenericInput(input, fieldName, false);
}

void showError(const string& message, bool autoPause) {
    showError(message);
    if (autoPause) {
        pause();
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
   [2]. 📶 Urutkan Nama Superhero            
   [3]. 📶 Urutkan Poin Superhero            
   [4]. 🔍 Cari Superhero                    
   [0]. 🔙 Kembali ke Database               

===========================================
)";

string titleG = R"(
===========================================

          📶 SORTING DATABASE 📶   

===========================================

   [1]. 🔤 Urutkan Berdasarkan Nama          
   [2]. 🌟 Urutkan Berdasarkan Poin          
   [0]. 🔙 Kelar                            

===========================================
)";

string titleH = R"(
===========================================

      🧑‍ PENGELOLAAN DISPATCHER 🧑 

===========================================

   [1]. ➕ Tambah Akun Dispatcher         
   [2]. 📄 Lihat Data Dispatcher      
   [3]. ✏️  Update Data Dispatcher         
   [4]. 🗑️  Pecat Dispatcher               
   [0]. 🔙 Kembali Ke Menu Admin          

===========================================
)";

string titleI = R"(
===========================================

       🛢️  DISPATCHER DATABASE 🛢️     

===========================================

   [1]. 📄 Lihat Semua Data
   [2]. 📶 Urutkan Nama
   [3]. 📶 Urutkan Berdasarkan Level
   [4]. 🔍 Cari Nama Dispatcher
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

string titleLa = R"(
===========================================

         📞  DISPATCHER MENU 📞     

===========================================

)";

string titleLb = R"(

===========================================
)";


vector<ShiftHero> heroShift;
vector<ActiveMission> daftarMisi;
int currentShift = 1;
bool shiftSelesai = false;

void loadingScreen() {
    clearScreen();
    cout << cyan << "\nSuperhero Dispatching Network [Versi 10.7.100829.1]" << endl;
    Sleep(500);
    cout << "[C] SDN. Semua hak dilindungi undang-undang" << endl;
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
    cout << cyan << "\n====================================";
    cout << "\n         MENU ISTIRAHAT";
    cout << "\n====================================\n";
    cout << putih << "\nDispatcher sedang beristirahat...\n";
    cout << "Kembali ke menu utama dalam:\n\n";
    for (int i = 15; i >= 0; i--) {
        cout << "\r" << emas << i << " detik   " << putih;
        cout.flush();
        Sleep(1000);
    }
    cout << hijau << "\n\nIstirahat selesai!\n";
    pause();
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
    string header(94, '=');
    json data = bacaDatabaseDispatcher();
    if (data["dispatchers"].empty()) {
        cout << emas << "\n <|     DAFTAR DISPATCHER KOSONG     |>" << putih << endl;
    } else {
        clearScreen();
        cout << emas << "\n                            <| DATA DISPATCHER SDN |>" << putih << endl;
        cout << endl;
        cout << header << endl;
        cout << "| " << cyan << setw(4) << left << "NO" << putih 
             << "| " << cyan << setw(10) << left << "ID" << putih 
             << "| " << cyan << setw(18) << left << "USERNAME" << putih 
             << "| " << cyan << setw(15) << left << "PASSWORD" << putih 
             << "| " << emas << setw(20) << left << "JABATAN" << putih 
             << "| " << putih << setw(13) << left << "STATUS" << " |" << endl;
        cout << header << endl;
        
        int no = 1;
        for (const auto &disp : data["dispatchers"]) {
            cout << "| " << setw(4) << left << no
                 << "| " << setw(10) << left << disp["id"].get<string>()
                 << "| " << setw(18) << left << disp["username"].get<string>()
                 << "| " << setw(15) << left << disp["password"].get<string>()
                 << "| " << setw(20) << left << (disp.contains("jabatan") ? disp["jabatan"].get<string>() : "-")
                 << "| " << setw(13) << left << disp["status"].get<string>() << " |" << endl;
            no++;
        }
        cout << header << endl;
    }
}

void daftarSuperhero() {
    string header(68, '=');
    json data = bacaDatabase();
    if (data["heroes"].empty()) {
        cout << emas << "\n <|     DAFTAR SUPERHEROES KOSONG     |>" << putih << endl;
    } else {
        clearScreen();
        cout << emas << "\n                <|     DAFTAR SUPERHEROES     |>" << putih << endl;
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
            << "| " << setw(5) << left << hero["points"].get<int>() << " |" << endl;
            no++;
        }
        cout << header << endl;
    }
}

void searchingHeroes() {
    try {
        json data = bacaDatabase();
        
        while (true) { 
            daftarSuperhero();
            string cari;
            cout << emas << "\n<|     CARI DATA SUPERHERO     |>" << putih << endl;
            cout << kuning << "💡 Input '0' untuk batal." << putih << endl;
            cout << "\nMasukkan Nama Superhero: ";
            getline(cin, cari);
            
            if (cari == "0") {
                break;
            }

            if (isEmptyInput(cari)) {
                showError("Pencarian tidak boleh kosong!");
                pause();
                continue;
            }
            
            bool ditemukan = false;
            string cariLower = toLowerManual(cari); 
            
            for (const auto &hero : data["heroes"]) {
                if (!hero.contains("name")) continue;

                string namaHero = hero["name"].get<string>();
                string namaLower = toLowerManual(namaHero); 
                
                if (namaLower.find(cariLower) != string::npos) {
                    clearScreen();
                    cout << cyan << "\n<|     HASIL PENCARIAN DATA     |>" << putih << endl;
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
                    cout << left << setw(12) << "Tempat Lahir"<< " : " 
                        << (hero.contains("birthplace") ? hero["birthplace"].get<string>() : "-") << endl;
                    
                    cout << left << setw(12) << "Deskripsi"   << " : " 
                        << (hero.contains("description") ? hero["description"].get<string>() : "-") << endl;
                    
                    cout << cyan << "\n<|     STATISTIK     |>\n" << putih << endl;
                    
                    if (hero.contains("stats") && hero["stats"].is_object()) {
                        const auto& s = hero["stats"];
                        cout << "Combat    : " << (s.contains("combat") ? s["combat"].get<int>() : 0) << endl;
                        cout << "Vigor     : " << (s.contains("vigor") ? s["vigor"].get<int>() : 0) << endl;
                        cout << "Mobility  : " << (s.contains("mobility") ? s["mobility"].get<int>() : 0) << endl;
                        cout << "Charisma  : " << (s.contains("charisma") ? s["charisma"].get<int>() : 0) << endl;
                        cout << "Intellect : " << (s.contains("intellect") ? s["intellect"].get<int>() : 0) << endl;
                    } else {
                        cout << kuning << "(Statistik tidak tersedia)" << putih << endl;
                    }

                    ditemukan = true;
                    pause();
                    break;
                }
            }

            if (!ditemukan) {
                clearScreen();
                cout << cyan << "\n<|     HASIL PENCARIAN DATA     |>" << putih << endl;
                cout << merah << "\n❌ Superhero tidak ditemukan!" << putih << endl;
                pause();
            }
        }
    } catch (const exception& e) {
        cerr << kuning << "\n[ERROR CRITICAL] " << e.what() << putih << endl;
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
                            int n1 = mid - left + 1, n2 = right - mid;
                            vector<json> L(n1), R(n2);
                            for (int i = 0; i < n1; i++) L[i] = arr[left + i];
                            for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
                            int i = 0, j = 0, k = left;
                            while (i < n1 && j < n2) {
                                string nameL = L[i]["name"].get<string>(), nameR = R[j]["name"].get<string>();
                                transform(nameL.begin(), nameL.end(), nameL.begin(), ::tolower);
                                transform(nameR.begin(), nameR.end(), nameR.begin(), ::tolower);
                                if (nameL <= nameR) { arr[k++] = L[i++]; } else { arr[k++] = R[j++]; }
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
                } else if (pilihan == 0) {
                    cout << kuning << "\n🔙 Kembali ke menu sebelumnya." << putih << endl;
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

                    data = bacaDatabase();
                    string nama = getUniqueHeroName(data, "\nNama: ");
                    newHero["name"] = nama;
                    
                    newHero["aliases"]     = getValidatedLine("Alias: ", "Alias", false, false);
                    newHero["profilType"] = getValidatedLine("Tipe Profile: ", "Tipe Profile", false, false);
                    newHero["age"]         = getValidatedLine("Umur: ", "Umur", false, false);
                    newHero["height"]      = getValidatedLine("Tinggi (cm): ", "Tinggi", false, false);
                    newHero["abilities"]   = getValidatedLine("Kemampuan: ", "Kemampuan", false, false);
                    newHero["birthplace"]  = getValidatedLine("Tempat Lahir: ", "Tempat Lahir", false, false);
                    newHero["description"] = getValidatedLine("Deskripsi: ", "Deskripsi", false, false);

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
                    while (true) {
                        clearScreen();
                        data = bacaDatabase();
                        
                        if (data["heroes"].empty()) {
                            cout << kuning << "\n⚠️ Database kosong! Tidak ada superhero untuk diupdate." << putih << endl;
                            pause();
                            break; 
                        }

                        daftarSuperhero(); 
                        cout << emas << "\n<|  UPDATE DATA SUPERHERO  |>" << putih << endl;
                        cout << kuning << "💡 Input '0' untuk batal dan kembali ke menu Kelola." << putih << endl;
                        cout << "\nMasukkan NOMOR superhero yang ingin diupdate: ";
                        
                        string inputNomor;
                        getline(cin, inputNomor);

                        if (isEmptyInput(inputNomor)) {
                            showError("Input tidak boleh kosong!");
                            pause();
                            continue;
                        }

                        if (inputNomor == "0") {
                            break; 
                        }

                        int indexArray = -1;
                        bool validIndex = false;

                        try {
                            size_t idx = 0;
                            int pilihanUser = stoi(inputNomor, &idx);
                            
                            if (idx != inputNomor.length()) {
                                throw invalid_argument("Input harus berupa angka murni");
                            }

                            indexArray = pilihanUser - 1;

                            if (indexArray < 0 || indexArray >= (int)data["heroes"].size()) {
                                throw out_of_range("Nomor tidak valid! Pilih antara 1 - " + to_string(data["heroes"].size()));
                            }
                            validIndex = true;

                        } catch (const invalid_argument&) {
                            showError("Input harus berupa angka!");
                            pause();
                            continue; 
                        } catch (const out_of_range& e) {
                            showError(e.what());
                            pause();
                            continue; 
                        } catch (...) {
                            showError("Terjadi kesalahan pada input!");
                            pause();
                            continue;
                        }

                        if (!validIndex) continue;

                        auto& heroToUpdate = data["heroes"][indexArray];
                        cout << hijau << "\n✅ Hero Terpilih: " << heroToUpdate["name"].get<string>() << putih << endl;
                        pause();

                        bool updateSelesai = false;
                        while (!updateSelesai) {
                            clearScreen();
                            cout << cyan << "\n<|  PILIH YANG INGIN DIUPDATE  |>\n" << putih << endl;
                            cout << "[1]. Biografi (Nama, Alias, Deskripsi, dll)" << endl;
                            cout << "[2]. Statistik (Combat, Vigor, dll)" << endl;
                            cout << "[0]. Batal / Ganti Hero Lain" << endl;
                            cout << "\nPilihan: ";

                            string subPilihanStr;
                            getline(cin, subPilihanStr);
                            int subPilihan = -1;

                            try {
                                if (isEmptyInput(subPilihanStr)) throw invalid_argument("Input kosong");
                                validateMenuChoice(subPilihanStr);
                                subPilihan = stoi(subPilihanStr);
                            } catch (const exception& e) {
                                showError("Input tidak valid! Masukkan angka.");
                                pause();
                                continue;
                            }

                            if (subPilihan == 0) {
                                updateSelesai = true;
                                break;
                            }

                            if (subPilihan == 1) {
                                cout << "\n--- EDIT BIOGRAFI ---\n";
                                
                                cout << "Edit Nama (Enter untuk skip): "; 
                                string temp; 
                                getline(cin, temp); 
                                if(!temp.empty()) {
                                    try {
                                        if (temp.length() < 3) throw invalid_argument("Minimal 3 karakter");
                                        validateGenericInput(temp, "Nama", false);

                                        if (temp != heroToUpdate["name"]) {
                                            validateHeroNameUnique(data, temp);
                                        }
                                        heroToUpdate["name"] = temp;
                                    } catch (const exception& e) {
                                        showError(string("Gagal ubah nama: ") + e.what());
                                    }
                                }

                               
                                cout << "Edit Alias (Enter untuk skip): "; 
                                getline(cin, temp); 
                                if(!temp.empty()) {
                                    heroToUpdate["aliases"] = temp;
                                }

                                cout << "Edit Profile Type (Enter untuk skip): "; 
                                getline(cin, temp); 
                                if(!temp.empty()) {
                                    heroToUpdate["profilType"] = temp;
                                }

                                cout << "Edit Umur (Enter untuk skip): "; 
                                getline(cin, temp); 
                                if(!temp.empty()) {
                                    heroToUpdate["age"] = temp;
                                }

                                cout << "Edit Tinggi (Enter untuk skip): "; 
                                getline(cin, temp); 
                                if(!temp.empty()) {
                                    heroToUpdate["height"] = temp;
                                }

                                cout << "Edit Tempat lahir (Enter untuk skip): "; 
                                getline(cin, temp); 
                                if(!temp.empty()) {
                                    heroToUpdate["birthplace"] = temp;
                                }

                                cout << "Edit Tempat lahir (Enter untuk skip): "; 
                                getline(cin, temp); 
                                if(!temp.empty()) {
                                    heroToUpdate["birthplace"] = temp;
                                }
                                
                                cout << "Edit Deskripsi (Enter untuk skip): ";
                                getline(cin, temp); 
                                if(!temp.empty()) {
                                    heroToUpdate["description"] = temp;
                                }

                                cout << "Edit Kemampuan (Enter untuk skip): ";
                                getline(cin, temp); 
                                if(!temp.empty()) {
                                    heroToUpdate["abilities"] = temp;
                                }

                                cout << "Edit Poin (Enter untuk skip): ";
                                getline(cin, temp); 
                                if(!temp.empty()) {
                                    heroToUpdate["points"] = temp;
                                }
                                
                                cout << hijau << "\n✅ Biografi diperbarui." << putih << endl;
                                updateSelesai = true;
                            } 
                            else if (subPilihan == 2) {
                                cout << "\n--- EDIT STATISTIK ---\n";
                                
                                heroToUpdate["stats"]["combat"] = getValidatedInt("Edit Combat (0-30): ", 0, 30, "Combat");
                                heroToUpdate["stats"]["vigor"] = getValidatedInt("Edit Vigor (0-30): ", 0, 30, "Vigor");
                                heroToUpdate["stats"]["mobility"] = getValidatedInt("Edit Mobility (0-30): ", 0, 30, "Mobility");
                                heroToUpdate["stats"]["charisma"] = getValidatedInt("Edit Charisma (0-30): ", 0, 30, "Charisma");
                                heroToUpdate["stats"]["intellect"] = getValidatedInt("Edit Intellect (0-30): ", 0, 30, "Intellect");
                                
                                int total = heroToUpdate["stats"]["combat"].get<int>() + 
                                           heroToUpdate["stats"]["vigor"].get<int>() + 
                                           heroToUpdate["stats"]["mobility"].get<int>() + 
                                           heroToUpdate["stats"]["charisma"].get<int>() + 
                                           heroToUpdate["stats"]["intellect"].get<int>();
                                heroToUpdate["points"] = total;
                                
                                cout << hijau << "\n✅ Statistik diperbarui." << putih << endl;
                                updateSelesai = true;
                            } else {
                                showError("Pilihan tidak valid!");
                                pause();
                            }
                        } 
                        simpanDatabase(data);
                        pause();
                        
                    } 
                } 
                else if (pilihan == 4) {

                    clearScreen();
                    
                    while (true) {
                        daftarSuperhero();
                        cout << emas << "\n<|  PECAT SUPERHERO  |>" << putih << endl;
                        cout << kuning << "💡 Input '0' untuk batal dan kembali ke menu sebelumnya." << putih << endl;
                        
                        data = bacaDatabase();
                        if (data["heroes"].empty()) {
                            cout << kuning << "\n⚠️  Tidak ada superhero untuk dipecat!" << putih << endl;
                            pause();
                            break;
                        }
                        
                        cout << "\nMasukkan nomor superhero yang ingin dipecat (0 untuk batal): ";
                        string inputNomor;
                        getline(cin, inputNomor);
                        
                        if (isEmptyInput(inputNomor)) {
                            showError("Input tidak boleh kosong!");
                            continue;
                        }
                        
                        if (inputNomor == "0") {
                            cout << kuning << "\n🔙 Kembali ke menu sebelumnya." << putih << endl;;
                            pause();
                            break;
                        }
                        
                        int pilihanHapus;
                        try {
                            size_t idx = 0;
                            pilihanHapus = stoi(inputNomor, &idx);
                            if (idx != inputNomor.length()) {
                                throw invalid_argument("non-numeric suffix");
                            }
                        } catch (const invalid_argument&) {
                            showError("Input harus berupa angka, bukan string!");
                            continue;
                        } catch (const out_of_range&) {
                            showError("Nomor terlalu besar!");
                            continue;
                        }
                        
                        int indexArray = pilihanHapus - 1;
                        if (indexArray < 0 || indexArray >= (int)data["heroes"].size()) {
                            showError("Nomor tidak valid! Pilih antara 1 - " + to_string(data["heroes"].size()));
                            continue;
                        }
                        
                        string namaHero = data["heroes"][indexArray]["name"].get<string>();
                        char konfirmasi;
                        bool validInput = false;
                        string prompt = "\n⚠️  Warning: Apakah kamu yakin ingin memecat '" + namaHero + "'? (y/n): ";

                        do {
                            cout << kuning << prompt << putih;
                            cout.flush();
                            konfirmasi = getch(); 
                            konfirmasi = tolower(konfirmasi);

                            if (konfirmasi == 'y' || konfirmasi == 'n') {
                                validInput = true;
                                cout << konfirmasi << endl; 
                                if (konfirmasi == 'y') {
                                    data["heroes"].erase(data["heroes"].begin() + indexArray);
                                    simpanDatabase(data);
                                    cout << hijau << "\n✅ Superhero '" << namaHero << "' telah dipecat/dihapus." << putih << endl;
                                    pause();
                                    break; 
                                } else {
                                    cout << merah << "\n❌ Pembatalan penghapusan." << putih << endl;
                                    pause();
                                }
                            } else {
                                cout << "\r"; 
                                for(int i=0; i < (int)prompt.length() + 5; i++) cout << " "; 
                                cout << "\r";
                            }
                        } while (!validInput);
                        
                    }
                    
                } else if (pilihan == 0 ) {
                    cout << kuning << "\n🔙 Kembali ke menu sebelumnya." << putih << endl;
                    pause(); 
                    break;
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
            cout << kuning << "\n🔙 Kembali ke menu sebelumnya." << putih << endl;
            pause(); 
            break; 
        } else {
            showError("Pilihan Tidak Valid!");
            pause();
        }
    } while (pilihan != 0);
}

void menuLihatDatabaseDispatcher() {
    string subPilihanStr;
    int subPilihan;

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

        if (subPilihan >= 0) {
            json data = bacaDatabaseDispatcher(); 
            
            if (subPilihan == 1) { 
                clearScreen();
                daftarDispatcher(); 
                pause(); 
            }
            else if (subPilihan == 2) { 
                int n = data["dispatchers"].size();
                for(int i = 0; i < n-1; i++) {
                    for(int j = 0; j < n-i-1; j++) {
                        if(toLowerManual(data["dispatchers"][j]["username"]) > toLowerManual(data["dispatchers"][j+1]["username"])) {
                            swap(data["dispatchers"][j], data["dispatchers"][j+1]);
                        }
                    }
                }
                simpanDatabaseDispatcher(data);
                cout << hijau << "\n✅ Data berhasil diurutkan berdasarkan Nama!" << putih << endl; 
                pause(); 
            }
            else if (subPilihan == 3) { 
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
                cout << hijau << "\n✅ Data berhasil diurutkan berdasarkan Level Tertinggi!" << putih << endl; 
                pause();
            }
            else if (subPilihan == 4) { 
                while (true) {
                    clearScreen();
                    daftarDispatcher();
                    cout << emas << "\n<|  CARI DATA DISPATCHER  |>" << putih << endl;
                    cout << kuning << "💡 Input '0' untuk batal dan kembali." << putih << endl;
                    
                    string cari; 
                    cout << "\nMasukkan Nama Dispatcher: "; 
                    getline(cin, cari);
                    
                    if (cari == "0") {
                        cout << kuning << "\n🔙 Kembali ke menu sebelumnya." << putih << endl;
                        pause();
                        break;
                    }
                    
                    if (isEmptyInput(cari)) {
                        showError("Pencarian tidak boleh kosong!");
                        pause();
                        continue;
                    }
                    if (cari.length() < 3) {
                        showError("Minimal 3 karakter untuk pencarian!");
                        pause();
                        continue;
                    }
                    
                    bool ketemu = false;
                    string cariLower = toLowerManual(cari);
                    
                    clearScreen();
                    cout << cyan << "\n<|  HASIL PENCARIAN DITEMUKAN  |>" << putih << endl;
                    for (const auto& disp : data["dispatchers"]) {
                        string usernameLower = toLowerManual(disp["username"].get<string>());
                        if (usernameLower.find(cariLower) == 0) {
                            cout << putih << "\nID      : " << disp["id"].get<string>() << "\nNama    : " << disp["username"].get<string>() << endl;
                            cout << "Jabatan : " << (disp.contains("jabatan") ? disp["jabatan"].get<string>() : "-") << endl;
                            cout << "Status  : " << disp["status"].get<string>() << endl;
                            cout << "------------------------" << endl;
                            ketemu = true;
                        }
                    }
                    if (!ketemu) {
                        clearScreen();
                        showError("Dispatcher tidak ditemukan!");
                        cout << kuning << "\n💡 Tip: Cek ejaan atau gunakan awalan username yang berbeda." << putih << endl;
                    }
                    pause();
                }
            } 
            else if (subPilihan == 0) {
                cout << kuning << "\n🔙 Kembali ke menu sebelumnya." << putih << endl;
                pause();
                break;
            } else { 
                showError("Pilihan tidak valid!"); 
                pause();
            }
        }
    } while (subPilihan != 0);
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
                    clearScreen();
                    cout << emas << "\n<|  BUAT AKUN DISPATCHER BARU  |>" << putih << endl;
                    json newDisp;
                    
                    string idStr;
                    while (true) {
                        idStr = getValidatedLine("\nID Dispatcher (Wajib 7 Angka): ", "ID", false, false);
                        if (idStr.length() != 7) {
                            showError("ID harus tepat 7 digit angka!");
                            continue;
                        }
                        bool isAllDigits = true;
                        for (char c : idStr) {
                            if (!isdigit(c)) {
                                isAllDigits = false;
                                break;
                            }
                        }
                        if (!isAllDigits) {
                            showError("ID hanya boleh berisi angka!");
                            continue;
                        }
                        break;
                    }
                    newDisp["id"] = idStr;
                    
                    string username;
                    while (true) {
                        username = getValidatedLine("Username (Min 5 Karakter): ", "Username", false, false);
                        if (username.length() < 5) {
                            showError("Username minimal 5 karakter!");
                            continue;
                        }
                        if (isDispatcherExists(data, username)) {
                            showError("Username Dispatcher Sudah Terdaftar!");
                            continue;
                        }
                        break;
                    }
                    newDisp["username"] = username;
                    
                    string password;
                    while (true) {
                        password = getValidatedLine("Password (Min 8 Karakter): ", "Password", false, true);
                        if (password.length() < 8) {
                            showError("Password minimal 8 karakter!");
                            continue;
                        }
                        break;
                    }
                    newDisp["password"] = password;
                    
                    string status = getValidatedLine("Status (Aktif/Training): ", "Status", false, false);
                    newDisp["status"] = status;
                    
                    string jabatan = getValidatedLine("Jabatan: ", "Jabatan", false, false);
                    newDisp["jabatan"] = jabatan;
                    newDisp["level"] = 0;
                    
                    data["dispatchers"].push_back(newDisp);
                    simpanDatabaseDispatcher(data);
                    cout << hijau << "\n✅ Akun Dispatcher Berhasil Ditambahkan!" << putih << endl;
                    pause();
                }
                
                else if (pilihan == 2) { 
                    menuLihatDatabaseDispatcher();
                }
                
                else if (pilihan == 3) { 
                    clearScreen();
                    while (true) {
                        daftarDispatcher();
                        cout << emas << "\n<|  UPDATE DATA DISPATCHER  |>" << putih << endl;
                        cout << kuning << "💡 Input '0' untuk batal." << putih << endl;
                        
                        data = bacaDatabaseDispatcher();
                        if (data["dispatchers"].empty()) {
                            cout << kuning << "\n⚠️  Tidak ada data untuk diupdate!" << putih << endl;
                            pause();
                            break;
                        }

                        cout << "\nMasukkan Nomor Dispatcher yang ingin diubah: ";
                        string inputNomor;
                        getline(cin, inputNomor);
                        
                        if (isEmptyInput(inputNomor)) {
                            showError("Input tidak boleh kosong!");
                            pause();
                            continue;
                        }
                        if (inputNomor == "0") {
                            cout << kuning << "\n🔙 Kembali ke menu sebelumnya." << putih << endl;
                            pause();
                            break;
                        }

                        int indexArray;
                        try {
                            size_t idx = 0;
                            int pilihanEdit = stoi(inputNomor, &idx);
                            if (idx != inputNomor.length()) throw invalid_argument("non-numeric");
                            
                            indexArray = pilihanEdit - 1;
                            if (indexArray < 0 || indexArray >= (int)data["dispatchers"].size()) {
                                showError("Nomor tidak valid! Pilih antara 1 - " + to_string(data["dispatchers"].size()));
                                pause();
                                continue;
                            }
                        } catch (...) {
                            showError("Input harus berupa angka!");
                            pause();
                            continue;
                        }
                        
                        auto &disp = data["dispatchers"][indexArray];
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
                            
                            string temp;
                            switch(up) {
                                case 1: 
                                    cout << "Username Baru (Min 5 Karakter) [Enter untuk skip]: ";
                                    getline(cin, temp);
                                    if(!temp.empty()) {
                                        if (temp.length() < 5) {
                                            showError("Username minimal 5 karakter!");
                                            pause();
                                            break;
                                        }
                                        if (temp != disp["username"]) {
                                            try {
                                                validateDispatcherUnique(data, temp);
                                            } catch (const exception& e) {
                                                showError(e.what());
                                                pause();
                                                break;
                                            }
                                        }
                                        disp["username"] = temp;
                                    }
                                    break; 
                                case 2: 
                                    cout << "Password Baru (Min 8 Karakter) [Enter untuk skip]: ";
                                    getline(cin, temp);
                                    if(!temp.empty()) {
                                        if (temp.length() < 8) {
                                            showError("Password minimal 8 karakter!");
                                            pause();
                                            break;
                                        }
                                        disp["password"] = temp; 
                                    }
                                    break; 
                                case 3: 
                                    cout << "Status Baru (Aktif/Training) [Enter untuk skip]: ";
                                    getline(cin, temp);
                                    if(!temp.empty()) disp["status"] = temp; 
                                    break;
                                case 4: 
                                    cout << "Jabatan Baru [Enter untuk skip]: ";
                                    getline(cin, temp);
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
                        } while (up != 0);
                    }
                }
                
                else if (pilihan == 4) { 
                    clearScreen(); 
                    while (true) {
                        daftarDispatcher();
                        cout << kuning << "\n<|  PECAT DISPATCHER  |>" << putih << endl;
                        cout << kuning << "💡 Input '0' untuk batal." << putih << endl;
                        
                        data = bacaDatabaseDispatcher();
                        if (data["dispatchers"].empty()) {
                            cout << kuning << "\n⚠️  Tidak ada dispatcher untuk dipecat!" << putih << endl;
                            pause();
                            break;
                        }

                        cout << "\nMasukkan Nomor Dispatcher yang ingin dipecat: ";
                        string inputNomor; 
                        getline(cin, inputNomor);
                        
                        if (isEmptyInput(inputNomor)) {
                            showError("Input tidak boleh kosong!");
                            pause();
                            continue;
                        }
                        if (inputNomor == "0") {
                            cout << kuning << "\n🔙 Kembali ke menu sebelumnya." << putih << endl;
                            pause();
                            break;
                        }

                        int indexArray;
                        try {
                            size_t idx = 0;
                            int pilihanHapus = stoi(inputNomor, &idx);
                            if (idx != inputNomor.length()) throw invalid_argument("non-numeric");
                            
                            indexArray = pilihanHapus - 1;
                            if (indexArray < 0 || indexArray >= (int)data["dispatchers"].size()) {
                                showError("Nomor tidak valid! Pilih antara 1 - " + to_string(data["dispatchers"].size()));
                                pause();
                                continue;
                            }
                        } catch (...) {
                            showError("Input harus berupa angka!");
                            pause();
                            continue;
                        }
                        
                        string namaDisp = data["dispatchers"][indexArray]["username"].get<string>();
                        char konf;
                        bool validInput = false;
                        
                        do {
                            cout << kuning << "\n⚠️  Yakin memecat '" << namaDisp << "'? (y/n): " << putih;
                            konf = tolower(getch());
                            if (konf == 'y' || konf == 'n') {
                                validInput = true;
                                cout << konf << endl;
                                if (konf == 'y') { 
                                    data["dispatchers"].erase(data["dispatchers"].begin() + indexArray); 
                                    simpanDatabaseDispatcher(data); 
                                    cout << hijau << "\n✅ Akun '" << namaDisp << "' telah dihapus." << putih << endl; 
                                    pause();
                                    break; 
                                } else {
                                    cout << cyan << "\n❌ Dibatalkan." << putih << endl;
                                    pause();
                                }
                            }
                        } while (!validInput);
                        
                        if (konf == 'y') break;
                    }
                } 
                else if (pilihan == 0) {
                    cout << kuning << "\n🔙 Kembali ke menu sebelumnya." << putih << endl;
                    pause(); 
                    break;
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
                    cout << kuning << "\n🔙 Kembali ke menu sebelumnya." << putih << endl; 
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

bool isHeroInShift(const string& name) {
    for (const auto& h : heroShift) {
        if (toLowerManual(h.name) == toLowerManual(name)) {
            return true;
        }
    }
    return false;
}

void tampilkanTabelHeroShift() {
    string header(64, '=');
    cout << emas << "\n                <|     YOUR SUPERHEROES     |>" << putih << endl;
    
    if (heroShift.empty()) {
        cout << kuning << "\n(Belum ada hero di shift)" << putih << endl;
    } else {
        cout << endl;
        cout << header << endl;
        cout << "| " << cyan << setw(3) << left << "NO" << putih 
             << "| " << cyan << setw(20) << left << "NAMA SUPERHERO" << putih 
             << "| " << biru << setw(5) << left << "COM" << putih 
             << "| " << biru << setw(5) << left << "VIG" << putih 
             << "| " << biru << setw(5) << left << "MOB" << putih 
             << "| " << biru << setw(5) << left << "CHA" << putih 
             << "| " << biru << setw(5) << left << "INT" << putih << " |" << endl;
        cout << header << endl;
        
        int no = 1;
        for (const auto &h : heroShift) {

            cout << "| " << setw(3) << left << no
                 << "| " << setw(20) << left << h.name
                 << "| " << setw(5) << left << h.combat 
                 << "| " << setw(5) << left << h.vigor
                 << "| " << setw(5) << left << h.mobility
                 << "| " << setw(5) << left << h.charisma
                 << "| " << setw(5) << left << h.intellect << " |" << endl;
            no++;
        }
        cout << header << endl;
    }
}

int getValidHeroIndex(const string& prompt, bool isOptional, int maxIndex) {
    string input;
    while (true) {
        cout << putih << prompt;
        getline(cin, input);

        if (isOptional && isEmptyInput(input)) {
            return -1;
        }

        if (isEmptyInput(input)) {
            showError("Input tidak boleh kosong! Silakan masukkan nomor hero.");
            continue;
        }

        try {
            validateMenuChoice(input);
            int idx = stoi(input) - 1;

            if (idx < 0 || idx > maxIndex) {
                showError("Nomor hero tidak valid! Pilih antara 1 - " + to_string(maxIndex + 1));
                continue;
            }
            
            return idx;
        } catch (const exception& e) {
            showError("Input harus berupa angka! Silakan coba lagi.");
            continue;
        }
    }
}

void updateStatsHero() {
    while (true) {
        if (heroShift.empty()) {
            showError("Tidak ada hero dalam shift!");
            pause();
            return;
        }

        clearScreen();
        cout << cyan << "\n=== UPDATE STATS HERO ===\n" << putih;
        tampilkanTabelHeroShift(); 

        cout << "\nPilih Nomor Hero yang ingin di-upgrade (0 untuk batal): ";
        string pilihStr;
        getline(cin, pilihStr);

        int pilih = -1;
        bool validInputHero = false;

        try {
            if (isEmptyInput(pilihStr)) {
                throw invalid_argument("Input tidak boleh kosong");
            }
            
            if (pilihStr == "0") {
                return;
            }

            validateMenuChoice(pilihStr);
            pilih = stoi(pilihStr) - 1;

            if (pilih < 0 || pilih >= (int)heroShift.size()) {
                throw out_of_range("Nomor hero tidak tersedia di list");
            }
            validInputHero = true;
        } catch (const exception& e) {
            showError(string("Error Input Hero: ") + e.what());
            pause();
            continue;
        }

        if (!validInputHero) continue;

        while (true) { 
            clearScreen();
            cout << cyan << "\n=== UPGRADE STATS: " << heroShift[pilih].name << " ===\n" << putih;
            cout << "Stats Saat Ini:" << endl;
            cout << "Combat   : " << heroShift[pilih].combat << "/30" << endl;
            cout << "Vigor    : " << heroShift[pilih].vigor << "/30" << endl;
            cout << "Mobility : " << heroShift[pilih].mobility << "/30" << endl;
            cout << "Charisma : " << heroShift[pilih].charisma << "/30" << endl;
            cout << "Intellect: " << heroShift[pilih].intellect << "/30" << endl;
            cout << "Total Poin : " << heroShift[pilih].totalPointsEarned << endl;
            
            cout << "\nPilih Stat untuk Ditingkatkan (+1):" << endl;
            cout << "[1] Combat" << endl;
            cout << "[2] Vigor" << endl;
            cout << "[3] Mobility" << endl;
            cout << "[4] Charisma" << endl;
            cout << "[5] Intellect" << endl;
            cout << "[0] Batal / Kembali" << endl;
            cout << "\nPilihan: ";

            string statPilihanStr;
            getline(cin, statPilihanStr);
            int statPilihan = -1;

            try {
                if (isEmptyInput(statPilihanStr)) {
                    throw invalid_argument("Input tidak boleh kosong");
                }
                
                if (statPilihanStr == "0") {
                    break;
                }

                validateMenuChoice(statPilihanStr);
                statPilihan = stoi(statPilihanStr);

                if (statPilihan < 1 || statPilihan > 5) {
                    throw out_of_range("Pilihan hanya 1-5");
                }
            } catch (const exception& e) {
                showError(string("Error Input Stat: ") + e.what());
                pause();
                continue;
            }

            bool upgraded = false;
            switch (statPilihan) {
                case 1:
                    if (heroShift[pilih].combat >= 30) {
                        showError("Combat sudah maksimal (30)!");
                    } else {
                        heroShift[pilih].combat += 1;
                        upgraded = true;
                    }
                    break;
                case 2:
                    if (heroShift[pilih].vigor >= 30) {
                        showError("Vigor sudah maksimal (30)!");
                    } else {
                        heroShift[pilih].vigor += 1;
                        upgraded = true;
                    }
                    break;
                case 3:
                    if (heroShift[pilih].mobility >= 30) {
                        showError("Mobility sudah maksimal (30)!");
                    } else {
                        heroShift[pilih].mobility += 1;
                        upgraded = true;
                    }
                    break;
                case 4:
                    if (heroShift[pilih].charisma >= 30) {
                        showError("Charisma sudah maksimal (30)!");
                    } else {
                        heroShift[pilih].charisma += 1;
                        upgraded = true;
                    }
                    break;
                case 5:
                    if (heroShift[pilih].intellect >= 30) {
                        showError("Intellect sudah maksimal (30)!");
                    } else {
                        heroShift[pilih].intellect += 1;
                        upgraded = true;
                    }
                    break;
            }

            if (upgraded) {
                cout << hijau << "\n✅ Stats berhasil ditingkatkan!" << putih << endl;
                Sleep(500);
                pause();
                break;
            } else {
                pause();
            }
        }
    }
}

struct HasilMisi {
    bool berhasil;
    int persentase;
    int points;
};

int hitungTotalStats(const ShiftHero& hero) {
    return hero.combat + hero.vigor + hero.mobility + hero.charisma + hero.intellect;
}

int hitungTotalStats2Hero(const ShiftHero& hero1, const ShiftHero& hero2) {
    return hitungTotalStats(hero1) + hitungTotalStats(hero2);
}

int hitungRequirementStats(const Requirement& req) {
    return req.combat + req.vigor + req.mobility + req.charisma + req.intellect;
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
    if (heroShift.empty()) {
        showError("Tidak ada hero dalam shift! Tambahkan hero terlebih dahulu.");
        pause();
        return;
    }
    if (daftarMisi.empty()) {
        cout << hijau << "\n✅ Tidak ada misi aktif. Shift selesai!" << putih << endl;
        pause();
        return;
    } 

    ActiveMission& misiAktif = daftarMisi[0];

    int maxHeroIdx = (int)heroShift.size() - 1;
    int hero1Idx = getValidHeroIndex("\n" + string(cyan) + "Pilih Hero Pertama (Wajib): " + string(putih), false, maxHeroIdx);
    int hero2Idx = getValidHeroIndex("\nPilih Hero Kedua (Opsional, Enter untuk skip): ", true, maxHeroIdx);

    bool gunakan2Hero = (hero2Idx != -1);

    if (gunakan2Hero && hero2Idx == hero1Idx) {
        showError("Hero kedua tidak boleh sama dengan hero pertama!");
        pause();
        return;
    }

    loadingBar();
    Sleep(500);

    ShiftHero combinedStats;
    if (gunakan2Hero) {
        combinedStats.combat   = heroShift[hero1Idx].combat + heroShift[hero2Idx].combat;
        combinedStats.vigor    = heroShift[hero1Idx].vigor + heroShift[hero2Idx].vigor;
        combinedStats.mobility = heroShift[hero1Idx].mobility + heroShift[hero2Idx].mobility;
        combinedStats.charisma = heroShift[hero1Idx].charisma + heroShift[hero2Idx].charisma;
        combinedStats.intellect= heroShift[hero1Idx].intellect + heroShift[hero2Idx].intellect;
    } else {
        combinedStats = heroShift[hero1Idx];
    }

    auto hitungPersen = [](int heroStat, int misiStat) -> int {
        if (misiStat <= 0) return 100;
        double persen = ((double)heroStat / misiStat) * 100.0;
        if (persen > 100) persen = 100;
        return (int)persen;
    };

    int pCombat   = hitungPersen(combinedStats.combat,   misiAktif.req.combat);
    int pVigor    = hitungPersen(combinedStats.vigor,    misiAktif.req.vigor);
    int pMobility = hitungPersen(combinedStats.mobility, misiAktif.req.mobility);
    int pCharisma = hitungPersen(combinedStats.charisma, misiAktif.req.charisma);
    int pIntellect= hitungPersen(combinedStats.intellect,misiAktif.req.intellect);

    int avgPersentase = (pCombat + pVigor + pMobility + pCharisma + pIntellect) / 5;
    
    HasilMisi hasil = tentukanHasilMisi(avgPersentase);

    clearScreen();
    cout << cyan << "\n=== HASIL DISPATCH MISI ===\n" << putih;
    Sleep(500);
    
    cout << "\n Hero Ditugaskan:" << endl;
    cout << "   • " << hijau << heroShift[hero1Idx].name << putih;
    if (gunakan2Hero) {
        cout << " & " << hijau << heroShift[hero2Idx].name << putih;
    }
    cout << endl;
    Sleep(200);

    cout << "\n🎯 Misi: " << misiAktif.info.judul << endl;
    cout << "📍 Lokasi: " << misiAktif.info.lokasi << endl;

    cout << "\n" << emas << "--- Perbandingan Statistik ---\n" << putih << endl;
    

    cout << left << setw(11) << "Stats Misi" << " | " << setw(15) << "Stats Hero" << endl;
    cout << string(29, '-') << endl;

    auto printStatRow = [&](const string& label, int mVal, int hVal) {
        cout << left << setw(4) << label << ": " << setw(3) << mVal 
             << "   |   " 
             << setw(4) << label << ": " << setw(3) << hVal << endl;
    };

    printStatRow("COM", misiAktif.req.combat,   combinedStats.combat);
    printStatRow("VIG", misiAktif.req.vigor,    combinedStats.vigor);
    printStatRow("MOB", misiAktif.req.mobility, combinedStats.mobility);
    printStatRow("CHA", misiAktif.req.charisma, combinedStats.charisma);
    printStatRow("INT", misiAktif.req.intellect,combinedStats.intellect);

    cout << string(35, '-') << endl;
    cout << "Rata-rata Kecocokan: " << kuning << avgPersentase << "%" << putih << endl;

    Sleep(500);
    cout << "\n" << (hasil.berhasil ? hijau : merah);
    if (hasil.berhasil) {
        cout << "✅ MISI BERHASIL DISELESAIKAN!" << endl;
    } else {
        cout << "❌ MISI GAGAL! Hero perlu latihan lagi." << endl;
    }
    cout << putih << endl;

    cout << "🏆 Reward Points: +" << hasil.points << " points";
    if (gunakan2Hero) cout << " (masing-masing hero)";
    cout << endl;
    Sleep(500);

    heroShift[hero1Idx].totalPointsEarned += hasil.points;
    if (gunakan2Hero) {
        heroShift[hero2Idx].totalPointsEarned += hasil.points;
    }

    if (hasil.berhasil) {
        daftarMisi.erase(daftarMisi.begin());
        
        if (daftarMisi.empty()) {
            cout << cyan << "\n🎉 SELAMAT! Semua misi telah selesai!" << putih << endl;
            cout << "Shift akan berakhir setelah Anda menekan Enter." << endl;
        }
    } else {
        cout << kuning << "\n⚠️ Misi belum selesai. Coba lagi dengan hero yang lebih kuat!" << putih << endl;
    }

    pause();
}

void hapusHeroShift() {
    while (true) {
        if (heroShift.empty()) {
            showError("Tidak ada hero dalam shift!");
            pause();
            return;
        }

        clearScreen();
        cout << cyan << "\n=== HAPUS HERO DARI SHIFT ===\n" << putih;
        tampilkanTabelHeroShift();
        
        cout << "\nPilih Nomor Hero yang ingin dihapus (0 untuk batal): ";
        string pilihStr;
        getline(cin, pilihStr);

        int indexArray = -1;
        bool validInputIndex = false;

        try {
            if (isEmptyInput(pilihStr)) {
                throw invalid_argument("Input tidak boleh kosong");
            }

            if (pilihStr == "0") {
                return; 
            }

            validateMenuChoice(pilihStr);
            indexArray = stoi(pilihStr) - 1;

            if (indexArray < 0 || indexArray >= (int)heroShift.size()) {
                throw out_of_range("Nomor hero tidak tersedia di list");
            }
            validInputIndex = true;
        } catch (const exception& e) {
            showError(string("Error Input: ") + e.what());
            pause();
            continue; 
        }

        if (!validInputIndex) continue;

        string namaHero = heroShift[indexArray].name;
        char konf;
        bool validInputKonf = false;

        do {
            cout << kuning << "\n⚠️  Yakin menghapus '" << namaHero << "' dari shift? (y/n): " << putih;
            konf = tolower(getch());
            
            if (konf == 'y' || konf == 'n') {
                validInputKonf = true;
                cout << konf << endl;
                
                if (konf == 'y') { 
                    heroShift.erase(heroShift.begin() + indexArray); 
                    cout << hijau << "\n✅ Hero '" << namaHero << "' telah dihapus dari shift." << putih << endl; 
                    pause();
                    break; 
                } else {
                    cout << cyan << "\n❌ Penghapusan dibatalkan." << putih << endl;
                    pause();
                    break;
                }
            }
        } while (!validInputKonf);
        
        break;
    }
}

bool tambahHeroShift() {
    json data = bacaDatabase();
    
    while (true) {
        clearScreen();
        cout << emas << "<|   PILIH HERO UNTUK SHIFT   |>" << putih << endl;
        
        cout << cyan << "\n--- DATABASE SUPERHERO (TERSEDIA) ---" << putih << endl;
        if (data["heroes"].empty()) {
            cout << merah << "\nDatabase kosong!" << putih << endl;
            pause();
        } else {
            daftarSuperhero();
        }

        tampilkanTabelHeroShift();

        cout << "\n" << kuning << "💡 Ketik nama hero persis seperti di database." << putih << endl;
        cout << putih << "\nMasukkan Nama Superhero: ";
        string namaInput;
        getline(cin, namaInput);

        if (isEmptyInput(namaInput)) {
            showError("Input tidak boleh kosong!");
            pause();
            continue;
        }

        if (isHeroInShift(namaInput)) {
            showError("Hero '" + namaInput + "' sudah ada di dalam shift!");
            pause();
            continue;
        }

        bool found = false;
        for (auto &hero : data["heroes"]) {
            if (toLowerManual(hero["name"].get<string>()) == toLowerManual(namaInput)) {
                found = true;
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
                cout << hijau << "\n✅ Hero '" << h.name << "' berhasil ditambahkan ke shift!" << putih << endl;
                pause();
                return true;
            }
        }
        
        if (!found) {
            showError("Hero '" + namaInput + "' tidak ditemukan di database!");
            pause();
        }
    }
}

void pauseAndClear(const string& msg = "\n[Tekan enter untuk melanjutkan...]") {
    cout << putih << msg << endl;
    getch(); 
    
    cout << "\r";
    
    for(int i = 0; i < 60; i++) { 
        cout << " "; 
    }
    
    cout << "\r"; 
}


void tutorialShift() {
    daftarMisi.clear();
    daftarMisi.push_back({{"Serangan di Tempat Persembunyian", "Sipil", "S Hill St"}, {5, 4, 3, 3, 1}, false});
    daftarMisi.push_back({{"Balon", "Sipil", "S Hill St"}, {5, 4, 3, 3, 1}, false}); // misi yang perlu di ganti
    daftarMisi.push_back({{"Balon", "Sipil", "S Hill St"}, {5, 4, 3, 3, 1}, false}); // misi yang perlu di ganti

    heroShift.clear(); 
    heroShift.push_back({"Sonar",       2, 1, 2, 3, 4, true, 71});
    heroShift.push_back({"Flambae",     4, 2, 3, 1, 1, true, 107});
    heroShift.push_back({"Punch Up",    3, 4, 1, 3, 1, true, 97});
    heroShift.push_back({"Invisigal",   3, 2, 3, 1, 2, true, 97});
    heroShift.push_back({"Prism",       4, 1, 1, 4, 2, true, 85});
    heroShift.push_back({"Malevola",    3, 4, 1, 3, 1, true, 101});
    heroShift.push_back({"Golem",       3, 4, 1, 3, 1, true, 91});

    string tutorialHeader = "<|   DISPATCHING TUTORIAL   |>";

    clearScreen();
    Sleep(200);
    cout << "\n" << emas << tutorialHeader << putih << endl;
    clearScreen();
    cout << "\n" << emas << tutorialHeader << putih << endl;
    cout << emas << "\n👋 Selamat Datang di Dispatcher SDN 👋" << putih << endl;
    cout << "\nSalam dan selamat datang di simulasi pelatihan ini!"
         << "\nKita mungkin superhero tapi kita bukan apa-apa tanpa"
         << "\npahlawan SDN yang sebenarnya;" << cyan << " The Dispatcher" << putih << endl;
    pause();
    Sleep(100);

    while (true) {
        clearScreen();
        cout << "\n" << emas << tutorialHeader << putih << endl;
        cout << cyan << "\n[#] Langkah Pertama: ➕ Tambah Superhero" << endl;
        cout << "    Anda WAJIB menambahkan 1 hero ke dalam shift untuk melanjutkan." << putih << endl;
        
        cout << magenta << titleLa
             << "   [1]. ➕ Tambah Hero Ke Shift"; 
        cout << titleLb << putih;
        
        cout << "\nMasukkan Pilihan: ";

        try {
            string inputStr;
            getline(cin, inputStr);

            if (isEmptyInput(inputStr)) {
                throw invalid_argument("Input tidak boleh kosong!");
            }
            validateMenuChoice(inputStr);
            int pilih = stoi(inputStr);

            if (pilih == 1) {
                bool success = tambahHeroShift();
                if (success) {
                    break; 
                }
            } else {
                throw out_of_range("Pilihan tidak valid");
            }

        } catch (const invalid_argument& e) {
            showError(e.what());
            pause();
        } catch (const out_of_range& e) {
            showError(e.what());
            pause();
        } catch (const exception& e) {
            showError(string("Terjadi kesalahan: ") + e.what());
            pause();
        }
    } 

    clearScreen();
    Sleep(200);
    
    cout << "\n" << emas << tutorialHeader << putih << endl;
    cout << cyan << "\n[#] Langkah Kedua: ⭕ Selesaikan Misi" << putih << endl;
    cout << "    Sepertinya kita mendapat " << emas << "Panggilan " << putih << "dari seorang" << emas << " Pelanggan." << putih << endl;
    cout << "    Kamu akan menerima " << emas << "Persyaratan " << putih << "untuk menentukan" << endl << emas 
         << "    Hero " << putih << " mana yang akan dikirim" << endl;
    
    // -= Misi Mulai  =-
    if (!daftarMisi.empty()) {
        cout << "\n=========================" << endl;
        cout << "\n📢 : " << daftarMisi[0].info.judul << endl; 
        cout << "📍 : " << daftarMisi[0].info.lokasi << endl;
        cout << "📞 : " << daftarMisi[0].info.caller << endl;
    } else {
        cout << merah << "\n⚠️ Tidak ada misi aktif!" << putih << endl;
    }

    cout << "\nAku melihat beberapa pria menakutkan" << endl 
         << "dan menakutkan tadi siang meninggalkan bioskop tua" << endl;
    
    pauseAndClear();

    cout << "\n📋 Persyaratan:" << endl;
    cout << "🔹 " << emas << "Serang " << putih << "markas operasi devils yang " << emas << "Dibentengi" << putih << endl;
    cout << "🔹 " << emas << "Pertahankan " << putih << "dirimu melawan musuh " << emas << "Bersenjata" << putih << endl;

    tampilkanTabelHeroShift();
    cout << "\n💡 Hint: Input Nomor Superhero untuk mengirim!" << endl;

    kirimHero();

    // -= Misi Selesai =-
    clearScreen();
    Sleep(200);
    
    
    while (true) {
        clearScreen();
        
        cout << "\n" << emas << tutorialHeader << putih << endl;
        cout << cyan << "\n[#] Langkah Ketiga: ✏️ Upgrade Stats Hero" << putih << endl;
        cout << "    Setelah menyelesaikan " << emas << "Misi" << putih << ", kamu bisa mengupgrade" << emas << " Stats" << putih << endl;
        cout << "    Superhero yang telah kamu dispatch tadi" << endl;
        
        cout << magenta << titleLa
             << "   [1]. ➕ Tambah Superhero Ke Shift\n" 
             << "   [2]. ✏️  Upgrade Stats Superhero"; 
        cout << titleLb << putih;
        
        cout << "\nMasukkan Pilihan: ";

        try {
            string inputStr;
            getline(cin, inputStr);

            if (isEmptyInput(inputStr)) {
                throw invalid_argument("Input tidak boleh kosong!");
            }
            validateMenuChoice(inputStr);
            int pilih = stoi(inputStr);

            if (pilih == 2) {
                updateStatsHero();
                break; 
            } else {
                throw out_of_range("Pilihan tidak valid. Anda harus memilih pilihan 2");
            }

        } catch (const invalid_argument& e) {
            showError(e.what());
            pause();
        } catch (const out_of_range& e) {
            showError(e.what());
            pause();
        } catch (const exception& e) {
            showError(string("Terjadi kesalahan: ") + e.what());
            pause();
        }
    }

    while (true) {
        clearScreen();
        
        cout << "\n" << emas << tutorialHeader << putih << endl;
        cout << cyan << "\n[#] Langkah Keempat: 🗑️ Hapus Hero" << putih << endl;
        cout << "    Kamu dapat menghapus " << emas << "Superhero" << putih << ", apabila kamu tidak" << emas << " Memerlukannya " << putih << "lagi" << endl;
        
        cout << magenta << titleLa
             << "   [1]. ➕ Tambah Superhero Ke Shift\n" 
             << "   [2]. ✏️  Upgrade Stats Superhero\n" 
             << "   [3]. 🗑️  Hapus Superhero"; 
        cout << titleLb << putih;
        
        cout << "\nMasukkan Pilihan: ";

        try {
            string inputStr;
            getline(cin, inputStr);

            if (isEmptyInput(inputStr)) {
                throw invalid_argument("Input tidak boleh kosong!");
            }
            validateMenuChoice(inputStr);
            int pilih = stoi(inputStr);

            if (pilih == 3) {
                hapusHeroShift();
                break; 
            } else {
                throw out_of_range("Pilihan tidak valid. Anda harus memilih pilihan 3");
            }

        } catch (const invalid_argument& e) {
            showError(e.what());
            pause();
        } catch (const out_of_range& e) {
            showError(e.what());
            pause();
        } catch (const exception& e) {
            showError(string("Terjadi kesalahan: ") + e.what());
            pause();
        }
    }

    cout << "\n" << emas << tutorialHeader << putih << endl;
    cout << cyan << "\n[#] Langkah Kelima: ✅ Selesaikan Semua Misi" << putih << endl;
    cout << "    " << endl;

    pause();
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
                        menuAdmin();
                    }
                    else if (role == "dispatcher") {
                        cout << endl;
                        tutorialShift();
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

int main() {
    SetConsoleOutputCP(65001);
    srand(time(0));
    try {
        loadingScreen();
        menuUtama();
    } catch (const exception& e) {
        cerr << "\n[FATAL SYSTEM CRASH] " << e.what() << endl;
        return 1;
    }
    return 0;
}