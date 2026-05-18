#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <windows.h>

#include "struct.h" 
#include "utilities.h"

using namespace std;
using json = nlohmann::json;

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

void tampilkanListHeroDariJSON(const json& data) {
    string header(68, '=');
    if (data["heroes"].empty()) {
        cout << kuning << "\nDatabase kosong!" << putih << endl;
    } else {
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

void tampilkanBriefingMisi(const ActiveMission& misi) {
    clearScreen();
    Sleep(100);
    
    cout << "\n" << emas << "<|   🚨 MISSION BRIEFING 🚨   |>" << putih << endl;
    cout << cyan << "═══════════════════════════════════════" << putih << endl << endl;
    
    cout << emas << "📢 " << putih << misi.info.judul << endl << endl;
    
    cout << cyan << "📍 " << putih << misi.info.lokasi << endl;
    
    cout << cyan << "📞 " << putih << misi.info.caller << endl << endl;
    
    cout << putih << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << cyan << "📜 INTEL BRIEFING:" << putih << endl;
    
    if (!misi.narasi.empty()) {
        cout << "   " << kuning << "\"" << misi.narasi << "\"" << putih << endl;
    } else {
        cout << "   " << abu << "(Tidak ada intel tambahan)" << putih << endl;
    }
    cout << endl;
    
    cout << putih << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << cyan << "📋 Persyaratan:" << putih << endl;
    
    if (!misi.objectives.empty()) {
        for (const string& obj : misi.objectives) {
            cout << "   🔹 " << putih << obj << endl;
        }
    } else {
        cout << "   " << abu << "(Tidak ada persyaratan khusus)" << putih << endl;
    }
    cout << endl;
    
    cout << cyan << "═══════════════════════════════════════" << putih << endl;
    cout << kuning << "💡 Pilih hero yang memenuhi persyaratan untuk hasil optimal!" << putih << endl;
    
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
        showError("❌ Tidak ada hero dalam shift! Tambah hero terlebih dahulu.");
        pause();
        return;
    }
    if (daftarMisi.empty()) {
        cout << hijau << "\n✅ Tidak ada misi aktif. Shift selesai!" << putih << endl;
        pause();
        return;
    } 

    int indexMisiTerpilih = 0;
    if (daftarMisi.size() > 1) {
        while (true) {
            clearScreen();
            cout << "\n" << emas << "<| 🎯 PILIH MISI AKTIF |>" << putih << endl;
            cout << cyan << "Pilih misi yang akan dikerjakan:" << putih << endl << endl;
            
            for (int i = 0; i < (int)daftarMisi.size(); i++) {
                cout << "  [" << i + 1 << "] " << emas << daftarMisi[i].info.judul << putih << endl;
                cout << "      📍 " << daftarMisi[i].info.lokasi << " | 📞 " << daftarMisi[i].info.caller << endl;
                if (i < (int)daftarMisi.size() - 1) cout << "  " << cyan << "---" << putih << endl;
            }
            cout << "\n  [0] Batal Kembali ke Menu" << endl;
            cout << "\n" << kuning << "Masukkan Nomor Misi: " << putih;
            
            string inputMisi;
            getline(cin, inputMisi);
            
            if (inputMisi == "0" || isEmptyInput(inputMisi)) {
                cout << kuning << "⚠️  Pemilihan misi dibatalkan." << putih << endl;
                pause();
                return;
            }
            
            try {
                validateMenuChoice(inputMisi);
                int pilih = stoi(inputMisi);
                if (pilih < 1 || pilih > (int)daftarMisi.size()) throw out_of_range("Nomor tidak valid");
                indexMisiTerpilih = pilih - 1;
                break;
            } catch (const exception& e) {
                showError("Input tidak valid! Masukkan angka 1-" + to_string(daftarMisi.size()));
                pause();
            }
        }
    }

    ActiveMission& misiTerpilih = daftarMisi[indexMisiTerpilih];

    tampilkanBriefingMisi(misiTerpilih);

    cout << "\n" << emas << "<| 🦸 PILIH HERO UNTUK MISI |>" << putih << endl;
    cout << cyan << "Misi: " << putih << misiTerpilih.info.judul << endl;
    cout << cyan << "📍 " << misiTerpilih.info.lokasi << putih << endl << endl;
    
    tampilkanTabelHeroShift();
    
    int maxHeroIdx = (int)heroShift.size() - 1;
    int hero1Idx = -1, hero2Idx = -1;
    bool gunakan2Hero = false;

    while (true) {
        hero1Idx = getValidHeroIndex("\n" + string(cyan) + "👉 Pilih Hero Pertama (Wajib): " + string(putih), false, maxHeroIdx);
        break;
    }

    while (true) {
        hero2Idx = getValidHeroIndex("\n👉 Pilih Hero Kedua (Opsional, tekan Enter jika cukup 1 hero): ", true, maxHeroIdx);
        
        if (hero2Idx == -1) {
            gunakan2Hero = false;
            break;
        }
        if (hero2Idx == hero1Idx) {
            showError("⚠️  Hero kedua tidak boleh sama dengan hero pertama!");
            continue;
        }
        gunakan2Hero = true;
        break;
    }

    loadingBar();
    Sleep(300);

    ShiftHero combinedStats = heroShift[hero1Idx];
    if (gunakan2Hero) {
        combinedStats.combat   += heroShift[hero2Idx].combat;
        combinedStats.vigor    += heroShift[hero2Idx].vigor;
        combinedStats.mobility += heroShift[hero2Idx].mobility;
        combinedStats.charisma += heroShift[hero2Idx].charisma;
        combinedStats.intellect+= heroShift[hero2Idx].intellect;
    }

    auto hitungPersen = [](int heroStat, int misiStat) -> int {
        if (misiStat <= 0) return 100;
        double persen = ((double)heroStat / misiStat) * 100.0;
        return (int)(persen > 100 ? 100 : persen);
    };

    int pCombat   = hitungPersen(combinedStats.combat,   misiTerpilih.req.combat);
    int pVigor    = hitungPersen(combinedStats.vigor,    misiTerpilih.req.vigor);
    int pMobility = hitungPersen(combinedStats.mobility, misiTerpilih.req.mobility);
    int pCharisma = hitungPersen(combinedStats.charisma, misiTerpilih.req.charisma);
    int pIntellect= hitungPersen(combinedStats.intellect,misiTerpilih.req.intellect);

    int avgPersentase = (pCombat + pVigor + pMobility + pCharisma + pIntellect) / 5;
    HasilMisi hasil = tentukanHasilMisi(avgPersentase);

    clearScreen();
    cout << cyan << "\n=== 🎬 HASIL DISPATCH MISI ===\n" << putih;
    Sleep(300);
    
    cout << "\n 🦸 Hero Ditugaskan: " << hijau << heroShift[hero1Idx].name << putih;
    if (gunakan2Hero) cout << " & " << hijau << heroShift[hero2Idx].name << putih;
    cout << endl;

    cout << "\n 🎯 Misi: " << misiTerpilih.info.judul << endl;
    cout << " 📍 Lokasi: " << misiTerpilih.info.lokasi << endl;

    cout << "\n" << emas << "--- 📊 Perbandingan Statistik ---\n" << putih << endl;
    cout << left << setw(12) << "Stats Misi" << " | " << setw(15) << "Stats Hero" << endl;
    cout << string(30, '-') << endl;

    auto printStatRow = [&](const string& label, int mVal, int hVal) {
        cout << left << setw(4) << label << ": " << setw(3) << mVal << "   |   " << setw(4) << label << ": " << setw(3) << hVal << endl;
    };
    printStatRow("COM", misiTerpilih.req.combat,   combinedStats.combat);
    printStatRow("VIG", misiTerpilih.req.vigor,    combinedStats.vigor);
    printStatRow("MOB", misiTerpilih.req.mobility, combinedStats.mobility);
    printStatRow("CHA", misiTerpilih.req.charisma, combinedStats.charisma);
    printStatRow("INT", misiTerpilih.req.intellect,combinedStats.intellect);

    cout << string(35, '-') << endl;
    cout << "📈 Rata-rata Kecocokan: " << kuning << avgPersentase << "%" << putih << endl;

    Sleep(400);
    cout << "\n" << (hasil.berhasil ? hijau : merah);
    cout << (hasil.berhasil ? "✅ MISI BERHASIL DISELESAIKAN!" : "❌ MISI GAGAL! Hero perlu latihan lagi.") << endl;
    cout << putih << "\n🏆 Reward Points: +" << hasil.points << " points";
    if (gunakan2Hero) cout << " (masing-masing hero)";
    cout << endl;

   heroShift[hero1Idx].totalPointsEarned += hasil.points;
    if (gunakan2Hero) heroShift[hero2Idx].totalPointsEarned += hasil.points;

    if (hasil.berhasil) {
        cout << cyan << "\n📦 Misi '" << misiTerpilih.info.judul << "' telah diselesaikan!" << putih << endl;
        
        daftarMisi.erase(daftarMisi.begin() + indexMisiTerpilih);
        
        if (daftarMisi.empty()) {
            cout << hijau << "\n Semua misi telah diselesaikan!" << putih << endl;
        } else {
            cout << kuning << "\n⚡ Sisa misi: " << daftarMisi.size() << " misi aktif" << putih << endl;
        }
    } else {
        cout << kuning << "\n⚠️ Coba lagi dengan hero yang lebih kuat!" << putih << endl;
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
        
        tampilkanListHeroDariJSON(data);

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
                if(hero.contains("stats")) {
                    h.combat = hero["stats"]["combat"];
                    h.vigor = hero["stats"]["vigor"];
                    h.mobility = hero["stats"]["mobility"];
                    h.charisma = hero["stats"]["charisma"];
                    h.intellect = hero["stats"]["intellect"];
                } else {
                    h.combat = 0; h.vigor = 0; h.mobility = 0; h.charisma = 0; h.intellect = 0;
                }
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
    {
        Mission infoTutorial = {"Serangan di Tempat Persembunyian", "Sipil", "S Hill St"};
        Requirement reqTutorial = {5, 4, 3, 3, 1};
        string narasiTutorial = "Laporan darurat: kelompok bersenjata menguasai lokasi. Warga sipil membutuhkan bantuan segera!";
        vector<string> objTutorial = {
            "Serang markas operasi devils yang Dibentengi",
            "Pertahankan dirimu melawan musuh Bersenjata"
        };
        daftarMisi.push_back(ActiveMission(infoTutorial, reqTutorial, narasiTutorial, objTutorial, false));
    }

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
        
        cout << magenta << titleLa << "   [1]. ➕ Tambah Hero Ke Shift"; 
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

    pause();

    kirimHero();

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
        cout << cyan << "\n[#] Langkah Keempat: 🗑️  Hapus Hero" << putih << endl;
        cout << "    Kamu dapat menghapus " << emas << "Superhero" << putih << ", apabila kamu tidak" << emas << " Memerlukannya " << putih << "lagi" << endl;
        cout << "    Tetapi jika kamu tetap" << emas << " Memerlukannya " << putih << "kamu bisa tekan" <<  " '0' " << "Untuk membatalkannya" << endl;

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
    clearScreen();  
    cout << "\n" << emas << tutorialHeader << putih << endl;
    cout << cyan << "\n[#] Langkah Kelima: ✅ Selesaikan Semua Misi" << putih << endl;
}

void inisialisasiMisiDispatcher() {
    daftarMisi.clear();  
    
    {
        Mission info1 = {"Cepat kejar dan tangkap Lightningstruck", "Alarm SDN", "Toko Donat Granny"};
        Requirement req1 = {5, 4, 4, 3, 1};
        string narasi1 = "[suara erangan dan suara tabrakan]";
        vector<string> obj1 = {
            "Cepat menuju Granny Donut",
            "Tangkap Lightningstruck"
        };
        daftarMisi.push_back(ActiveMission(info1, req1, narasi1, obj1, false));
    }
    
    {
        Mission info2 = {"Penyergapan dan penyamaran ke markas narkoba", "Anonim", "Gedung terbengkalai dibelakang bioskop"};
        Requirement req2 = {2, 2, 1, 4, 5};
        string narasi2 = "ada transaksi mencurigakan di belakang bioskop,sepertinya berhubungan dengan narkoba";
        vector<string> obj2 = {
            "lakukan penyamaran dengan hati hati",
            "sebaiknya orang yang memiliki IQ tinggi dan pintar negosiasi"
        };
        daftarMisi.push_back(ActiveMission(info2, req2, narasi2, obj2, false));
    }
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

void menuDispatcher() {
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

#endif