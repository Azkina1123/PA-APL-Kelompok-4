#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>

using namespace std;

enum Gender {lakiLaki, perempuan};
enum Agama {islam, kristen, katolik, hindu, buddha, konghuchu};
enum GolDar {A, B, AB, O};
enum Status {belumKawin, kawin, ceraiHidup, ceraiMati};

struct Penduduk{
    char id[6];
    string password;

    string namaLengkap;
    int nik;
    string ttl;
    int usia;
    Gender gender;
    Agama agama;
    GolDar golDar;
    Status status;
};

Penduduk buatDataPenduduk();

int main(){
    system("cls");
    Penduduk satu = buatDataPenduduk();

    cout << satu.namaLengkap << endl;
    cout << satu.nik << endl;
    cout << satu.usia << endl;
    return 0;
}

tm *timeNow(){
    time_t now = time(0);
    tm *ltm = localtime(&now);

    return ltm;
}

void errorStrToInt(){
    cin.clear(); 
    cin.ignore(); 
    fflush(stdin);
}

Penduduk buatDataPenduduk(){
    Penduduk data;
    
    // nama lengkap
    cout << "\t Nama Lengkap \t: ";
    getline(cin, data.namaLengkap); 

    // NIK
    cout << "\t NIK \t\t: ";
    cin >> data.nik; 
    errorStrToInt();

    // TTL
    string tempat;
    int tanggal, bulan, tahun, 
        thnNow = timeNow()->tm_year + 1900;

    cout << "Tempat/Tanggal Lahir" << endl;
    
    cout << "\tTempat\t: "; 
    getline(cin, tempat); fflush(stdin);

    cout << "\tTanggal\t: "; 
    cin >> tanggal; errorStrToInt();
    cout << "\tBulan\t: "; 
    cin >> bulan; errorStrToInt();
    cout << "\tTahun\t: "; 
    cin >> tahun; errorStrToInt();

    data.usia = timeNow()->tm_year + 1900 - tahun;


    return data;

}