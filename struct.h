#ifndef STRUCT_H
#define STRUCT_H

#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

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

struct HasilMisi {
    bool berhasil;
    int persentase;
    int points;
};

struct ActiveMission {
    Mission info;
    Requirement req;
    bool selesai;
    string narasi;                  
    vector<string> objectives;       
    ActiveMission() : selesai(false) {}
    ActiveMission(Mission _info, Requirement _req, string _narasi, 
                  vector<string> _obj, bool _selesai = false) 
        : info(_info), req(_req), narasi(_narasi), objectives(_obj), selesai(_selesai) {}
};

#endif