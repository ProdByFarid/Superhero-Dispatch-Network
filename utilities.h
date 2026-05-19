#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <cctype>    
#include <conio.h>
#include <ctime>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <string>
#include <windows.h>

#include "json.hpp"
#include "struct.h"

using json = nlohmann::json;
using namespace std;

#define putih   "\033[0m"
#define merah   "\033[31m"
#define biru    "\033[34m"
#define hijau   "\033[32m"
#define cyan    "\033[36m"
#define magenta "\033[35m"
#define abu     "\033[90m"
#define emas    "\033[38;5;220m"
#define kuning  "\033[33m" 

extern std::vector<ShiftHero> heroShift;
extern std::vector<ActiveMission> daftarMisi;
extern int currentShift;

void showError(const string& message);
void pause(const string& msg = "\n[Tekan enter untuk melanjutkan...]");
void clearScreen();
void flushInput();
bool isEmptyInput(const string& input);
string toLowerManual(string s);
void validateMenuChoice(const string& input);
int getValidHeroIndex(const string& prompt, bool isOptional, int maxIndex);
string getValidatedLine(const string& prompt, const string& fieldName, bool allowDefaultDash = false, bool allowEmpty = false);
int getValidatedInt(const string& prompt, int minVal, int maxVal, const string& fieldName);
json bacaDatabase();
json bacaDatabaseDispatcher();
void loadingBar();

string toLowerManual(string s) {
    string result = s;
    for (int i = 0; i < result.length(); i++) {
        result[i] = tolower(result[i]);
    }
    return result;
}

void pause(const string& msg) {
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

bool isHeroInShift(const string& name) {
    for (const auto& h : heroShift) {
        if (toLowerManual(h.name) == toLowerManual(name)) {
            return true;
        }
    }
    return false;
}

void showError(const string& message) {
    cout << merah << "\n❌ Error: " << message << putih << endl;
}

string getValidatedLine(const string& prompt, const string& fieldName, bool allowDefaultDash, bool allowEmpty) { 
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
   [3]. 📶 Urutkan Berdasarkan ID
   [4]. 🔍 Cari Nama Dispatcher
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

#endif