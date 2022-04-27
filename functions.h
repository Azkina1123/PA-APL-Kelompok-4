#include <string>
using namespace std;

const int STORAGE = 1000;
const string GENDER[] = {"Laki-Laki", "Perempuan"};
const string AGAMA[] = {"Islam", "Kristen", "Katolik", "Hindu", "Buddha", "Konghuchu"};
const string GOLDAR[] = {"A", "B", "AB", "O"};
const string STATUS[] = {"Belum kawin", "Kawin", "Cerai hidup", "Cerai mati"};

struct Penduduk{
    string namaLengkap;
    string nik;
    string password;
    string ttl;
    int usia;
    short int gender;
    short int agama;
    short int golDar;
    short int status;
};

void color(unsigned short kodeWarna);
int binarySearch(string nik);

void menuMasukPenduduk();
void logInPenduduk();
void signUpPenduduk();
void menuPenduduk(Penduduk penduduk);
void isiFormulirData(Penduduk penduduk);


void saveToTxt(Penduduk penduduk);
int savedDataTxt();
void konfigurasiData();

void buatDataPenduduk();