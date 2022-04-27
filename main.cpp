#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <fstream>

#include "functions.h"

using namespace std;


Penduduk dataPenduduk[STORAGE];


int main(){
    bool running = true;
    string warning = "";

    while (true) {
        system("cls");
        konfigurasiData();

        cout << "Selamat Datang!" << endl;

        color(12); cout << warning << endl; color(7);

        cout << "Masuk sebagai :                \n"
             << "[1] Pemerintah    [2] Penduduk \n\n";
        char mode = getche();

        switch (mode) {

            case '1':
                // login ke pemerintah
                break;

            case '2':
                menuMasukPenduduk();
                break;

            default:
                warning = "Opsi tidak tersedia!";
                continue;
                break;
        }

        warning = "";
    }

    cout << "Program dihentikan" << endl;

    return 0;

}



