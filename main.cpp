#include "mainMenu.h"
#include "utilities.h"

using namespace std;
using json = nlohmann::json;

std::vector<ShiftHero> heroShift;
std::vector<ActiveMission> daftarMisi;
int currentShift = 1;

int main() {
    SetConsoleOutputCP(65001);
    srand(time(0));
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