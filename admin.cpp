#include <iostream>
#include <fstream>
#include "admin.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

void tampilkanHero() {
    ifstream file("superhero.json");

    if (!file.is_open()) {
        cout << "Gagal membuka file superhero.json\n";
        return;
    }

    json data;
    file >> data;

    cout << "\n===== DAFTAR HERO =====\n";

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
        cout << "1. Lihat Data Hero\n";
        cout << "2. Info Sistem\n";
        cout << "0. Logout\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanHero();  
                break;

            case 2:
                cout << "Sistem Superhero Dispatch v1.0\n";
                break;

            case 0:
                cout << "Logout admin...\n";
                break;

            default:
                cout << "Pilihan tidak valid\n";
        }

    } while (pilihan != 0);
}