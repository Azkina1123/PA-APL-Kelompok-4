#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <conio.h>

using namespace std;

const int STORAGE = 1000;
const string GENDER[] = {"Laki-Laki", "Perempuan"};
const string AGAMA[] = {"Islam", "Kristen", "Katolik", "Hindu", "Buddha", "Konghuchu"};
const string GOLDAR[] = {"A", "B", "AB", "O"};
const string STATUS[] = {"Belum kawin", "Kawin", "Cerai hidup", "Cerai mati"};

struct Penduduk{
    char id[6];
    string password;

    string namaLengkap;
    unsigned long int nik;
    string ttl;
    short int usia;
    short int gender;
    short int agama;
    short int golDar;
    short int status;
};

int banyakData();

void color(unsigned short kodeWarna);
void buatDataPenduduk();

// data tersimpan



int main(){
    Penduduk dataPenduduk[STORAGE];
    system("cls");
    // buatDataPenduduk();
    dataPenduduk[0].id = "HUHU";
    dataPenduduk[1].id = "HIHI";
    cout << banyakData() << endl;
    cout << dataPenduduk[3].id << " <<--";

    return 0;
}

void color(unsigned short kodeWarna) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, kodeWarna);
}

tm *timeNow(){
    time_t now = time(0);
    tm *ltm = localtime(&now);

    return ltm;
}

int random(){
    return rand()%9;
}

int banyakData(){
    for (int i=0; i<STORAGE; i++){
        if (dataPenduduk[i].id == " "){
            return i;
        }
    }
    return STORAGE;
}


void errorStrToInt(){
    cin.clear(); 
    cin.ignore(); 
    fflush(stdin);
}

void buatDataPenduduk(){
    Penduduk data;
    
    // nama lengkap
    cout << "\tNama Lengkap \t: ";
    getline(cin, data.namaLengkap); 

    // NIK
    cout << "\tNIK \t\t: ";
    cin >> data.nik; 
    errorStrToInt();

    // TTL
    string tempat;
    int tanggal, bulan, tahun, 
        thnNow = timeNow()->tm_year + 1900;

    cout << "\n\tTempat/Tanggal Lahir" << endl;
    cout << "\t     Tempat\t: "; getline(cin, tempat); fflush(stdin); color(8); 
    cout << "\t     -- isi di bawah ini dengan angka" << endl;        color(7);
    cout << "\t     Tanggal\t: "; cin >> tanggal; errorStrToInt();
    cout << "\t     Bulan\t: "; cin >> bulan;     errorStrToInt();
    cout << "\t     Tahun\t: "; cin >> tahun;     errorStrToInt();

    // usia
    data.usia = timeNow()->tm_year + 1900 - tahun;

    color(8);
    cout << "\n\t-- mulai dari sini, isi dengan menekan angka\n"
         << "\t   yang dipilih\n";
    color(7);

    // gender
    cout << "\n\tJenis Kelamin \n"       
         << "\t     [1] Laki-laki     [2] Perempuan \n"   
         << "\t     : ";
    data.gender = getche();
    cout << endl;

    // agama
    cout << "\n\tAgama \n"
         << "\t     [1] Islam     [3] Katolik   [5] Buddha   \n"
         << "\t     [2] Kristen   [4] Hindu     [6] Konghuchu\n"
         << "\t     : ";
    data.agama = getche();
    cout << endl;

    // golongan darah
    cout << "\n\tGolongan Darah   \n"
         << "\t     [1] A       [3] AB \n"
         << "\t     [2] B       [4] O  \n"
         << "\t     : ";
    data.agama = getche();
    cout << endl;

    // status
    cout << "\n\tStatus \n"
         << "\t     [1] Belum kawin    [3] Cerai hidup \n"
         << "\t     [2] Kawin          [4] Cerai mati  \n"
         << "\t     : ";
    data.agama = getche();
    cout << endl;


}


