#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <iomanip>
#include <fstream>

using namespace std;

// key pada keyboard
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

// menu yang dipilih
#define SELECT 11
#define UNSELECT 7
#define ENTER 13

// penyimpanan data
#define STORAGE 1000

// pilihan utk isi formulir
const string GENDER[] = {"Laki-Laki", "Perempuan"};
const string AGAMA[] = {"Islam", "Kristen", "Katolik", "Hindu", "Buddha", "Konghuchu"};
const string GOLDAR[] = {"A", "B", "AB", "O"};
const string STATUS[] = {"Belum kawin", "Kawin", "Cerai hidup", "Cerai mati"};

// struct penduduk
struct Penduduk{
    string tanggalPembaruan;
    string namaLengkap;
    string nik;
    string password;
    string ttl;
    int usia;
    short int gender;       // index GENDER
    short int agama;        // index AGAMA
    short int golDar;       // index GOLDAR
    short int status;       // index STATUS
};

// data tersimpan
Penduduk dataPenduduk[STORAGE];

void importFromTxt() {
    ifstream input;
    input.open("data.txt");

    Penduduk penduduk;
    string baris, 
           usia,
           gender,
           agama,
           golDar,
           status;
    int index = 0, kolom = 1;

    while (!input.eof()) {
        getline(input, baris);

        // tanggal update
        if (kolom == 1){
            penduduk.tanggalPembaruan = baris;
        // nama lengkap
        } else if (kolom == 2) {
            penduduk.namaLengkap = baris;
        // NIK
        } else if (kolom == 3) {
            penduduk.nik = baris;
        // password
        } else if (kolom == 4) {
            penduduk.password = baris;
        // tempat tanggal lahir
        } else if (kolom == 5) {
            penduduk.ttl = baris;
        // usia
        } else if (kolom == 6) {
            usia = baris; 
        // gender
        } else if (kolom == 7) {
            gender = baris;
        // agama
        } else if (kolom == 8) {
            agama = baris;
        // golongan darah
        } else if (kolom == 9) {
            golDar = baris;
        // status
        } else if (kolom == 10) {
            status = baris;
        }

        if (kolom == 10) {
            penduduk.usia   = atoi(usia.c_str());         // convert dari str ke int
            penduduk.gender = atoi(gender.c_str());
            penduduk.agama  = atoi(agama.c_str());
            penduduk.golDar = atoi(golDar.c_str());
            penduduk.status = atoi(status.c_str());

            dataPenduduk[index] = penduduk;

            index++;
            kolom = 1;
        }

        kolom++;
    }
    input.close();
}

void appendToTxt(Penduduk penduduk) {
    ofstream file;

    file.open("data.txt", ios::app);

    penduduk.tanggalPembaruan = hariIni();  // tgl data diri diubah

    file << penduduk.tanggalPembaruan
         << penduduk.namaLengkap << "\n"
         << penduduk.nik << "\n"
         << penduduk.password << "\n"
         << penduduk.ttl << "\n"
         << penduduk.usia << "\n"
         << penduduk.gender << "\n"
         << penduduk.agama << "\n"
         << penduduk.golDar << "\n"
         << penduduk.status << "\n";

    file.close();
}

void updateToTxt(Penduduk penduduk) {
    deleteFromTxt(penduduk);
    appendToTxt(penduduk);
}

void deleteFromTxt(Penduduk penduduk) {
    int length = banyakData();
    int index = binarySearchNIK(penduduk.nik);

    ofstream output;
    output.open("data.txt");


    for (int i=0; i<STORAGE; i++) {
        if (dataPenduduk[i].nik == penduduk.nik) {
            continue;
        } else if (dataPenduduk[i].nik == "") {
            break;
        } 

        appendToTxt(dataPenduduk[i]);
    }

    output.close();

    importFromTxt();
}

int main() {
    Penduduk satu = {
        "1/1/2\n",
        "Ayam Geprek",
        "0987654321",
        "enakKali",
        "2/2/"
    };

    return 0;
}

