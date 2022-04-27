#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <iomanip>
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
    short int gender;
    short int agama;
    short int golDar;
    short int status;
};

Penduduk dataPenduduk[STORAGE];

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

int main(){
    bool running = true;
    string warning = "";

    int opsi1 = 7, 
        opsi2 = 11;

    while (true) {
        system("cls");
        konfigurasiData();

        cout << endl << endl;

        cout << "\t            Selamat Datang!            \n";
        
        color(12); cout << setw(37) << warning << endl; color(7);
        
        cout << "\t       Jalankan program sebagai :      \n\n";
        color(opsi1); cout << "\t   [1] Pemerintah   ";
        color(opsi2); cout << "    [2] Penduduk    \n\n"; color(7);

        char mode, pilih;
        mode = getch();

        if (mode == 13 && opsi1 == 11) {
            // login ke pemerintah
        } else if (mode == 13 && opsi2 == 11) {
            menuMasukPenduduk();
        }

        switch (mode) {
            case -32:
                pilih = getch();
                if (pilih == 77){
                    opsi1 = 7;
                    opsi2 = 11;
                    
                } else if (pilih == 75){
                    opsi1 = 11;
                    opsi2 = 7;
                }
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


/* ----------------------------------- SORT & SEARCH ----------------------------------- */

void insertionSortNIK(){
    Penduduk key;
    int i, j,
        length = savedDataTxt();

    for (i = 1; i < length; i++) {

        key = dataPenduduk[i];
        j = i-1;

        while (j >= 0 && dataPenduduk[j].nik.compare(key.nik) > 0){
            dataPenduduk[j+1] = dataPenduduk[j];
            j = j-1;
        }

        dataPenduduk[j+1] = key;
    }
}

bool logInBerhasil(string nik, string password) {
    for (int i=0; i<savedDataTxt(); i++){
        if (
            dataPenduduk[i].nik == nik
            && dataPenduduk[i].password == password
        ){
            return true;
        }
    }
    
    return false;
}

int binarySearchNIK(string nik) {
    insertionSortNIK();

    int index = -1,
        beg = 0,
        end = savedDataTxt()-1;

    while (beg <= end){
        int mid = (end + beg)/2; 
        
        if (dataPenduduk[mid].nik == nik) { 
            index = mid;
            break;
        
        } else{
            if (nik.compare(dataPenduduk[mid].nik) > 0) { 
                beg = mid + 1;
           
            } else {
                end = mid - 1;
            }
        }
    }

    return index;
}


/* ----------------------------------- TAMPILAN ----------------------------------- */

void menuMasukPenduduk() {
    bool openPage = true;
    string warning = "";

    while (openPage) {
        system("cls");
        cout << endl << endl;

        cout << "\t           Pilih opsi :           \n";

        color(12); cout << setw(37) << warning << endl; color(7);

        cout << "\t   [1] Log In       [2] Sign Up \n\n"
             << "\t   <= Kembali \n";

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
                    openPage = false;
                    break;
                }

            default:
                warning = "Opsi tidak tersedia!";
                continue;
                break;
        }

        warning = "";

    }
}

void signUpPenduduk() {
    Penduduk pendudukBaru;

    cout << "Nama Lengkap : "; getline(cin, pendudukBaru.namaLengkap); fflush(stdin);
    cout << "NIK          : "; cin >> pendudukBaru.nik;                fflush(stdin);
    cout << "Password     : "; getline(cin, pendudukBaru.password);    fflush(stdin);
    
    saveToTxt(pendudukBaru);

    cout << "Akun telah berhasil didaftarkan!" << endl;

    getch();

}

void logInPenduduk() {
    string nik, password;

    cout << "NIK      : "; cin >> nik;             fflush(stdin);
    cout << "Password : "; getline(cin, password); fflush(stdin);


    if (logInBerhasil(nik, password)){
        int index = binarySearchNIK(nik);
        menuPenduduk(dataPenduduk[index]);
    }

}

void menuPenduduk(Penduduk penduduk){
    bool openPage = true;
    string warning = "";

    while(openPage) {
        system("cls");

        cout << "Selamat datang, " << penduduk.namaLengkap << "!" << endl;

        color(12); cout << warning << endl; color(7);

        char menu, kembali;
        cout << "[1] Isi formulir data diri\n"
             << "[2] Tampilkan data diri   \n"
             << "[3] Ubah data diri        \n"
             << "<= Keluar                 \n";
        menu = getch();

        switch (menu) {
            case '1':
                isiFormulirData(penduduk);
            case '2':
                // tampilkan data 
            case '3':
                // ubah data
            case -32:
                kembali = getch();
                if (kembali == 75) {
                    break;
                    break;
                }

            default:
            warning = "Menu tidak tersedia!";
            continue;
            break;
        }

        warning = "";
    }

}

void isiFormulirData(Penduduk penduduk){
    system("cls");
    
    // nama lengkap
    cout << "\tNama Lengkap \t: " << penduduk.namaLengkap << endl;

    // NIK
    cout << "\tNIK \t\t: " << penduduk.nik << endl;

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
    penduduk.usia = timeNow()->tm_year + 1900 - tahun;

    color(8);
    cout << "\n\t-- mulai dari sini, isi dengan menekan angka\n"
         << "\t   yang dipilih\n";
    color(7);

    // gender
    cout << "\n\tJenis Kelamin \n"       
         << "\t     [1] Laki-laki     [2] Perempuan \n"   
         << "\t     : ";
    penduduk.gender = getche();
    cout << endl;

    // agama
    cout << "\n\tAgama \n"
         << "\t     [1] Islam     [3] Katolik   [5] Buddha   \n"
         << "\t     [2] Kristen   [4] Hindu     [6] Konghuchu\n"
         << "\t     : ";
    penduduk.agama = getche();
    cout << endl;

    // golongan darah
    cout << "\n\tGolongan Darah   \n"
         << "\t     [1] A       [3] AB \n"
         << "\t     [2] B       [4] O  \n"
         << "\t     : ";
    penduduk.agama = getche();
    cout << endl;

    // status
    cout << "\n\tStatus \n"
         << "\t     [1] Belum kawin    [3] Cerai hidup \n"
         << "\t     [2] Kawin          [4] Cerai mati  \n"
         << "\t     : ";
    penduduk.agama = getche();
    cout << endl;

}


/* ----------------------------------- FILE TXT ----------------------------------- */

int savedDataTxt() {
    ifstream file;

    file.open("data.txt");

    string baris;
    int jumlah = 0;

    while (!file.eof()) {
        getline(file, baris);
        jumlah ++;
    }

    file.close();
    return jumlah-1;


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

void konfigurasiData() {
    ifstream file;

    file.open("data.txt");

    string baris;
    int index = 0;

    while (!file.eof()){
        getline(file, baris);               // ambil data per baris

        int lengthBaris = baris.length();   // banyak char satu baris
        char barisToChar[lengthBaris+1];    // tempat str dalam bentuk char

        strcpy(barisToChar, baris.c_str()); // copy baris ke tempat char

        Penduduk data;

        int kolom = 0,      // kategori data
            temp;           // tempat sementara
        string usia;        // tempat sementara utk kategori usia

        // per karakter
        for (int i=0; i<lengthBaris; i++){  // perulangan tiap 1 karakter

            if (barisToChar[i] == '|' or barisToChar[i] == '\n') {
                kolom++;
                continue;
            }

            // nama lengkap
            if (kolom == 0) {
                data.namaLengkap += barisToChar[i];
            // NIK
            } else if (kolom == 1) {
                data.nik += barisToChar[i];
            // password
            } else if (kolom == 2) {
                data.password += barisToChar[i];
            // tempat tanggal lahir
            } else if (kolom == 3) {
                data.ttl += barisToChar[i];
            // usia
            } else if (kolom == 4) {
                usia += barisToChar[i]; 
            // gender
            } else if (kolom == 5) {
                temp = int(barisToChar[i]) - 48;
                data.gender = temp;
            // agama
            } else if (kolom == 6) {
                temp = int(barisToChar[i]) - 48;
                data.agama = temp;        
            // golongan darah
            } else if (kolom == 7) {
                temp = int(barisToChar[i]) - 48;
                data.golDar = temp;
            // status
            } else if (kolom == 8) {
                temp = int(barisToChar[i]) - 48;
                data.status = temp;
            }
        }

        data.usia = atoi(usia.c_str()); // convert dari str ke int

        dataPenduduk[index] = data;     // masukkan ke array struct

        index++;                        // ke data berikutnya
    }

    file.close();

}

