#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <conio.h>

using namespace std;

const string GENDER[] = {"Laki-Laki", "Perempuan"};
const string AGAMA[] = {"Islam", "Kristen", "Katolik", "Hindu", "Buddha", "Konghuchu"};
const string GOLDAR[] = {"A", "B", "AB", "O"};
const string STATUS[] = {"Belum kawin", "Kawin", "Cerai hidup", "Cerai mati"};

struct Penduduk{
    char id[6];
    string password;

    string namaLengkap;
    int nik;
    string ttl;
    int usia;
    int gender;
    int agama;
    int golDar;
    int status;
};

int main(){
    bool running = true;

    while (true) {

        char mode = getch();

        switch (mode) {

            case 'A':
            case 'a':
                // login ke pemerintah
                break;

            case 'B':
            case 'b':
                // login ke akun penduduk
        }

    }

    cout << "Program dihentikan" << endl;

    return 0;

}


