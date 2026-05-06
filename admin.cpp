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

    cout << "\n===== PENGELOLAAN SUPERHERO =====\n";

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
        cout << "1. Pengelolaan Superhero\n";
        cout << "2. Pengelolaan Dispatcher\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 1) {
            tampilkanHero();
        }
        else if (pilihan == 2) {
            cout << "\n=== PENGELOLAAN DISPATCHER ===\n";
            cout << "Fitur masih dalam pengembangan...\n";
        }
        else if (pilihan == 0) {
            cout << "Anda akan keluar dari menu ini...\n";
        }
        else {
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 0);
}