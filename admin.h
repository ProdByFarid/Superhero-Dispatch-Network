#ifndef ADMIN_H
#define ADMIN_H

#include "utilities.h"

inline string trimInputLocal(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

void kelolaSuperhero();
void kelolaDispatcher();
void menuLihatDatabase();
void menuLihatDatabaseDispatcher();
void daftarSuperhero();
void daftarDispatcher();
void searchingHeroes();
void simpanDatabase(const json& data);
void simpanDatabaseDispatcher(const json& data);

void menuAdmin() {
    string pilihanStr;
    int pilihan;
    
    do {
        clearScreen();
        cout << emas << titleC << putih << endl;
        cout << "Masukkan Pilihan: ";
        getline(cin, pilihanStr);
        pilihanStr = trimInputLocal(pilihanStr);
        
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

void simpanDatabaseDispatcher(const json& data) {
    ofstream file("dispatcher.json");
    if (file.is_open()) {
        file << setw(4) << data << endl; 
        file.close();
    } else {
        throw runtime_error("Gagal menyimpan database dispatcher!");
    }
}

void simpanDatabase(const json& data) {
    ofstream file("superhero.json");
    if (!file.is_open()) {
        throw runtime_error("Gagal menyimpan data superhero!");
    }
    file << setw(4) << data << endl; 
    file.close();
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
            cari = trimInputLocal(cari);
            
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
        pilihanStr = trimInputLocal(pilihanStr);
        
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
        pilihanStr = trimInputLocal(pilihanStr);
        
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
                        inputNomor = trimInputLocal(inputNomor);

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
                            subPilihanStr = trimInputLocal(subPilihanStr);
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
                                
                                while (true) {
                                    cout << "Edit Nama (Enter untuk skip): "; 
                                    string rawTemp; getline(cin, rawTemp);
                                    if (rawTemp.empty()) break;
                                    string temp = trimInputLocal(rawTemp);
                                    if (temp.empty()) { showError("Input tidak boleh hanya spasi!"); continue; }
                                    if (temp.length() < 3) { showError("Minimal 3 karakter"); continue; }
                                    try {
                                        validateGenericInput(temp, "Nama", false);
                                        if (temp != heroToUpdate["name"]) validateHeroNameUnique(data, temp);
                                        heroToUpdate["name"] = temp;
                                        break;
                                    } catch (const exception& e) {
                                        showError(string("Gagal ubah nama: ") + e.what());
                                    }
                                }

                                while (true) {
                                    cout << "Edit Alias (Enter untuk skip): "; 
                                    string rawTemp; getline(cin, rawTemp);
                                    if (rawTemp.empty()) break;
                                    string temp = trimInputLocal(rawTemp);
                                    if (temp.empty()) { showError("Input tidak boleh hanya spasi!"); continue; }
                                    heroToUpdate["aliases"] = temp;
                                    break;
                                }

                                while (true) {
                                    cout << "Edit Profile Type (Enter untuk skip): "; 
                                    string rawTemp; getline(cin, rawTemp);
                                    if (rawTemp.empty()) break;
                                    string temp = trimInputLocal(rawTemp);
                                    if (temp.empty()) { showError("Input tidak boleh hanya spasi!"); continue; }
                                    heroToUpdate["profilType"] = temp;
                                    break;
                                }

                                while (true) {
                                    cout << "Edit Umur (Enter untuk skip): "; 
                                    string rawTemp; getline(cin, rawTemp);
                                    if (rawTemp.empty()) break;
                                    string temp = trimInputLocal(rawTemp);
                                    if (temp.empty()) { showError("Input tidak boleh hanya spasi!"); continue; }
                                    heroToUpdate["age"] = temp;
                                    break;
                                }

                                while (true) {
                                    cout << "Edit Tinggi (Enter untuk skip): "; 
                                    string rawTemp; getline(cin, rawTemp);
                                    if (rawTemp.empty()) break;
                                    string temp = trimInputLocal(rawTemp);
                                    if (temp.empty()) { showError("Input tidak boleh hanya spasi!"); continue; }
                                    heroToUpdate["height"] = temp;
                                    break;
                                }

                                while (true) {
                                    cout << "Edit Tempat lahir (Enter untuk skip): "; 
                                    string rawTemp; getline(cin, rawTemp);
                                    if (rawTemp.empty()) break;
                                    string temp = trimInputLocal(rawTemp);
                                    if (temp.empty()) { showError("Input tidak boleh hanya spasi!"); continue; }
                                    heroToUpdate["birthplace"] = temp;
                                    break;
                                }
                                
                                while (true) {
                                    cout << "Edit Deskripsi (Enter untuk skip): ";
                                    string rawTemp; getline(cin, rawTemp);
                                    if (rawTemp.empty()) break;
                                    string temp = trimInputLocal(rawTemp);
                                    if (temp.empty()) { showError("Input tidak boleh hanya spasi!"); continue; }
                                    heroToUpdate["description"] = temp;
                                    break;
                                }

                                while (true) {
                                    cout << "Edit Kemampuan (Enter untuk skip): ";
                                    string rawTemp; getline(cin, rawTemp);
                                    if (rawTemp.empty()) break;
                                    string temp = trimInputLocal(rawTemp);
                                    if (temp.empty()) { showError("Input tidak boleh hanya spasi!"); continue; }
                                    heroToUpdate["abilities"] = temp;
                                    break;
                                }

                                while (true) {
                                    cout << "Edit Poin (Enter untuk skip): ";
                                    string rawTemp; getline(cin, rawTemp);
                                    if (rawTemp.empty()) break;
                                    string temp = trimInputLocal(rawTemp);
                                    if (temp.empty()) { showError("Input tidak boleh hanya spasi!"); continue; }
                                    try {
                                        heroToUpdate["points"] = stoi(temp);
                                        break;
                                    } catch (...) {
                                        showError("Input Poin harus berupa angka!");
                                    }
                                }
                                
                                cout << hijau << "\n✅ Biografi diperbarui." << putih << endl;
                                updateSelesai = true;
                            } 
                            else if (subPilihan == 2) {
                                cout << "\n--- EDIT STATISTIK ---\n";
                                
                                auto editStat = [](const string& promptMsg, json& statsObj, const string& key) {
                                    while (true) {
                                        cout << promptMsg;
                                        string rawTemp; getline(cin, rawTemp);
                                        if (rawTemp.empty()) break; 
                                        string temp = trimInputLocal(rawTemp);
                                        if (temp.empty()) { showError("Input tidak boleh hanya spasi!"); continue; }
                                        try {
                                            size_t idx;
                                            int val = stoi(temp, &idx);
                                            if (idx != temp.length()) throw invalid_argument("Bukan angka murni");
                                            if (val < 0 || val > 30) { showError("Nilai harus 0-30!"); continue; }
                                            statsObj[key] = val;
                                            break;
                                        } catch (...) {
                                            showError("Input harus berupa angka!");
                                        }
                                    }
                                };

                                editStat("Edit Combat (0-30) [Enter untuk skip]: ", heroToUpdate["stats"], "combat");
                                editStat("Edit Vigor (0-30) [Enter untuk skip]: ", heroToUpdate["stats"], "vigor");
                                editStat("Edit Mobility (0-30) [Enter untuk skip]: ", heroToUpdate["stats"], "mobility");
                                editStat("Edit Charisma (0-30) [Enter untuk skip]: ", heroToUpdate["stats"], "charisma");
                                editStat("Edit Intellect (0-30) [Enter untuk skip]: ", heroToUpdate["stats"], "intellect");
                                
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
                        inputNomor = trimInputLocal(inputNomor);
                        
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
                            pause();
                            continue;
                        } catch (const out_of_range&) {
                            showError("Nomor terlalu besar!");
                            pause();
                            continue;
                        }
                        
                        int indexArray = pilihanHapus - 1;
                        if (indexArray < 0 || indexArray >= (int)data["heroes"].size()) {
                            showError("Nomor tidak valid! Pilih antara 1 - " + to_string(data["heroes"].size()));
                            pause();
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

void menuLihatDatabaseDispatcher() {
    string subPilihanStr;
    int subPilihan;

    do {
        clearScreen();
        cout << cyan << titleI << putih << endl;
        cout << "Masukkan Pilihan: ";
        getline(cin, subPilihanStr);
        subPilihanStr = trimInputLocal(subPilihanStr);

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
                        string idA = data["dispatchers"][j].contains("id") ? data["dispatchers"][j]["id"].get<string>() : "";
                        string idB = data["dispatchers"][j+1].contains("id") ? data["dispatchers"][j+1]["id"].get<string>() : "";
                        
                        if(idA > idB) {
                            swap(data["dispatchers"][j], data["dispatchers"][j+1]);
                        }
                    }
                }
                simpanDatabaseDispatcher(data);
                cout << hijau << "\n✅ Data berhasil diurutkan berdasarkan ID!" << putih << endl; 
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
                    cari = trimInputLocal(cari);
                    
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
        pilihanStr = trimInputLocal(pilihanStr);
        
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
                    
                    string status;
                    while (true) {
                        cout << putih << "\nPilih Status:\n";
                        cout << "[1] Aktif\n[2] Training\n[3] Freelance\n";
                        cout << "Pilihan: ";
                        string pStat;
                        getline(cin, pStat);
                        pStat = trimInputLocal(pStat);
                        if (pStat == "1") { status = "Aktif"; break; }
                        else if (pStat == "2") { status = "Training"; break; }
                        else if (pStat == "3") { status = "Freelance"; break; }
                        else { showError("Pilihan tidak valid!"); }
                    }
                    newDisp["status"] = status;
                    
                    string jabatan;
                    while (true) {
                        cout << putih << "\nPilih Jabatan:\n";
                        cout << "[1] Trainee\n[2] Junior\n[3] Senior\n[4] Asisten\n";
                        cout << "Pilihan: ";
                        string pJab;
                        getline(cin, pJab);
                        pJab = trimInputLocal(pJab);
                        if (pJab == "1") { jabatan = "Trainee"; break; }
                        else if (pJab == "2") { jabatan = "Junior"; break; }
                        else if (pJab == "3") { jabatan = "Senior"; break; }
                        else if (pJab == "4") { jabatan = "Asisten"; break; }
                        else { showError("Pilihan tidak valid!"); }
                    }
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
                        inputNomor = trimInputLocal(inputNomor);
                        
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
                            upStr = trimInputLocal(upStr);
                            
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
                            bool berhasil = false;
                            
                            switch(up) {
                                case 1: 
                                    while (true) {
                                        cout << "Username Baru (Min 5 Karakter) [Enter untuk skip]: ";
                                        string rawTemp;
                                        getline(cin, rawTemp);
                                        
                                        if (rawTemp.empty()) {
                                            cout << merah << "❌ Dibatalkan" << putih << endl;
                                            berhasil = false;
                                            break;
                                        }

                                        temp = trimInputLocal(rawTemp);
                                        if (temp.empty()) {
                                            showError("Input tidak boleh hanya spasi!");
                                            continue; 
                                        }

                                        if (temp.length() < 5) {
                                            showError("Username minimal 5 karakter!");
                                            continue; 
                                        }
                                        if (temp != disp["username"]) {
                                            try {
                                                validateDispatcherUnique(data, temp);
                                            } catch (const exception& e) {
                                                showError(e.what());
                                                continue; 
                                            }
                                        }
                                        disp["username"] = temp;
                                        berhasil = true;
                                        cout << hijau << "✅ Username Berhasil Diupdate" << putih << endl;
                                        break;
                                    }
                                    break; 
                                    
                                case 2: 
                                    while (true) {
                                        cout << "Password Baru (Min 8 Karakter) [Enter untuk skip]: ";
                                        string rawTemp;
                                        getline(cin, rawTemp);
                                        
                                        if (rawTemp.empty()) {
                                            cout << merah << "❌ Dibatalkan" << putih << endl;
                                            berhasil = false;
                                            break;
                                        }

                                        temp = trimInputLocal(rawTemp);
                                        if (temp.empty()) {
                                            showError("Input tidak boleh hanya spasi!");
                                            continue; 
                                        }

                                        if (temp.length() < 8) {
                                            showError("Password minimal 8 karakter!");
                                            continue; 
                                        }
                                        disp["password"] = temp; 
                                        berhasil = true;
                                        cout << hijau << "✅ Password Berhasil Diupdate" << putih << endl;
                                        break;
                                    }
                                    break; 
                                    
                                case 3: 
                                    while (true) {
                                        cout << putih << "\nPilih Status Baru [Enter/0 untuk skip]:\n";
                                        cout << "[1] Aktif\n[2] Training\n[3] Freelance\n";
                                        cout << "Pilihan: ";
                                        
                                        string rawTemp;
                                        getline(cin, rawTemp);
                                        
                                        if (rawTemp.empty()) {
                                            cout << merah << "❌ Dibatalkan" << putih << endl;
                                            berhasil = false;
                                            break;
                                        }

                                        temp = trimInputLocal(rawTemp);
                                        if (temp.empty()) {
                                            showError("Input tidak boleh hanya spasi!");
                                            continue; 
                                        }

                                        if (temp == "0") {
                                            cout << merah << "❌ Dibatalkan" << putih << endl;
                                            berhasil = false;
                                            break;
                                        }
                                        
                                        if (temp == "1") { disp["status"] = "Aktif"; berhasil = true; }
                                        else if (temp == "2") { disp["status"] = "Training"; berhasil = true; }
                                        else if (temp == "3") { disp["status"] = "Freelance"; berhasil = true; }
                                        else {
                                            showError("Pilihan tidak valid!");
                                            continue;
                                        }
                                        if (berhasil) cout << hijau << "✅ Status Berhasil Diupdate" << putih << endl;
                                        break;
                                    }
                                    break;
                                    
                                case 4: 
                                    while (true) {
                                        cout << putih << "\nPilih Jabatan Baru [Enter/0 untuk skip]:\n";
                                        cout << "[1] Trainee\n[2] Junior\n[3] Senior\n[4] Asisten\n";
                                        cout << "Pilihan: ";
                                        
                                        string rawTemp;
                                        getline(cin, rawTemp);
                                        
                                        if (rawTemp.empty()) {
                                            cout << merah << "❌ Dibatalkan" << putih << endl;
                                            berhasil = false;
                                            break;
                                        }

                                        temp = trimInputLocal(rawTemp);
                                        if (temp.empty()) {
                                            showError("Input tidak boleh hanya spasi!");
                                            continue; 
                                        }

                                        if (temp == "0") {
                                            cout << merah << "❌ Dibatalkan" << putih << endl;
                                            berhasil = false;
                                            break;
                                        }
                                        
                                        if (temp == "1") { disp["jabatan"] = "Trainee"; berhasil = true; }
                                        else if (temp == "2") { disp["jabatan"] = "Junior"; berhasil = true; }
                                        else if (temp == "3") { disp["jabatan"] = "Senior"; berhasil = true; }
                                        else if (temp == "4") { disp["jabatan"] = "Asisten"; berhasil = true; }
                                        else {
                                            showError("Pilihan tidak valid!");
                                            continue;
                                        }
                                        if (berhasil) cout << hijau << "✅ Jabatan Berhasil Diupdate" << putih << endl;
                                        break;
                                    }
                                    break;
                                    
                                case 0:
                                    break;
                                    
                                default:
                                    showError("Pilihan tidak valid!");
                                    pause();
                                    continue;
                            }
                            if (up != 0 && berhasil) { 
                                simpanDatabaseDispatcher(data); 
                                pause();
                            } else if (up != 0) {
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
                        inputNomor = trimInputLocal(inputNomor);
                        
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

#endif