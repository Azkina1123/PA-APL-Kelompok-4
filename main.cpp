#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <fstream>

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
    string gender;
    string agama;
    string golDar;
    string status;
};


void color(unsigned short kodeWarna);
void menuMasukPenduduk(string warning="");
void logInPenduduk();
void signUpPenduduk();
int savedDataTxt();
void konfigurasiData();

void saveToTxt(Penduduk penduduk);

void buatDataPenduduk();

Penduduk dataPenduduk[STORAGE];

int main(){
    bool running = true;
    string warning = "";

    while (true) {
        system("cls");
        konfigurasiData();

        cout << "Selamat Datang!" << endl;

        cout << dataPenduduk[0].namaLengkap << dataPenduduk[0].nik << dataPenduduk[0].password << endl;

        color(12); cout << warning << endl; color(7);

        cout << "Masuk sebagai : [A] Pemerintah    [B] Penduduk\n"
             << ">> ";
        char mode = getche();

        switch (mode) {

            case 'A':
            case 'a':
                // login ke pemerintah
                break;

            case 'B':
            case 'b':
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

/* ----------------------------------- FUNGSI ----------------------------------- */
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

void errorStrToInt(){
    cin.clear(); 
    cin.ignore(); 
    fflush(stdin);
}

int banyakData() {
    for (int i=0; i<STORAGE; i++){
        if (dataPenduduk[i].namaLengkap == ""){
            return i;
        }
    }

    return STORAGE;
}

bool logInBerhasil(string nik, string password) {
    for (int i=0; i<banyakData(); i++){
        if (
            dataPenduduk[i].nik == nik
            && dataPenduduk[i].password == password
        ){
            return true;
        }
    }

    return false;
}


/* ----------------------------------- TAMPILAN ----------------------------------- */

void menuMasukPenduduk(string warning) {
    system("cls");

    color(14);
    cout << "Tekan angka pada menu di bawah ini" << endl;
    color(12);
    cout << warning << endl;
    color(7);

    cout << "[1] Log In        [2] Sign Up \n\n"
         << "<= Kembali \n";

    char opsi, opsi2;
    opsi = getch();

    switch (opsi) {
        case '1':
            logInPenduduk();
            break;

        case '2':
            signUpPenduduk();
            break;

        case -32:
            opsi2 = getch();
            if (opsi2 == 75) {
                break;
            }

        default:
            menuMasukPenduduk("Opsi tidak tersedia!");
            break;
    }
}

void signUpPenduduk() {
    system("cls");
    Penduduk pendudukBaru;

    cout << "Nama Lengkap : "; getline(cin, pendudukBaru.namaLengkap); fflush(stdin);
    cout << "NIK          : "; cin >> pendudukBaru.nik;                fflush(stdin);
    cout << "Password     : "; getline(cin, pendudukBaru.password);    fflush(stdin);
    
    saveToTxt(pendudukBaru);

    cout << "Akun telah berhasil didaftarkan!" << endl;

    getch();

}

void logInPenduduk() {
    system("cls");
    string nik, password;

    cout << "NIK      : "; cin >> nik;             fflush(stdin);
    cout << "Password : "; getline(cin, password); fflush(stdin);

    if (logInBerhasil(nik, password)){
        cout << "YESS";
    }
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

void menuMasukPenduduk(){

}

/* ----------------------------------- FILE TXT ----------------------------------- */

int savedDataTxt() {
    ifstream file;

    file.open("data.txt");

    string baris;
    int jumlah = -1;

    while (!file.eof()) {
        getline(file, baris);
        jumlah ++;
    }

    file.close();
    return jumlah;


}

void saveToTxt(Penduduk penduduk) {
    ofstream file;

    file.open("data.txt", std::ios::app);
    file << penduduk.namaLengkap << "|"
         << penduduk.nik << "|"
         << penduduk.password << "|"
         << penduduk.ttl << "|"
         << penduduk.usia << "|"
         << penduduk.gender << "|"
         << penduduk.agama << "|"
         << penduduk.golDar << "|"
         << penduduk.status << "\n";

    konfigurasiData();
}

void inputFromTxt(int index) {
    ifstream file;

    file.open("data.txt");

    string baris;
    getline(file, baris);

    int lengthBaris = baris.length();
    char barisToChar[lengthBaris+1];

    strcpy(barisToChar, baris.c_str());

    Penduduk data;

    int kolom = 0;
    string usia;

    // per karaker
    for (int i=0; i<lengthBaris; i++){
        if (barisToChar[i] == '|') {
            kolom++;
            continue;
        }

        if (kolom == 0) {
            data.namaLengkap += barisToChar[i];
        
        } else if (kolom == 1) {
            data.nik += barisToChar[i];
        
        } else if (kolom == 2) {
            data.password += barisToChar[i];
        
        } else if (kolom == 3) {
            data.ttl += barisToChar[i];
        
        } else if (kolom == 4) {
            usia += barisToChar[i]; 
        
        } else if (kolom == 5) {
            data.gender += barisToChar[i];
        
        } else if (kolom == 6) {
            data.agama += barisToChar[i];        
        
        } else if (kolom == 7) {
            data.golDar += barisToChar[i];

        } else if (kolom == 8) {
            data.status += barisToChar[i];
        }
    }

    data.usia = atoi(usia.c_str());
    dataPenduduk[index] = data;    

}

void konfigurasiData(){
    for (int i=0; i<savedDataTxt(); i++){
        inputFromTxt(i);
    }
}

