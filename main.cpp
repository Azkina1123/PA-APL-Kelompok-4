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

// fungsi yg digunakan
void color(unsigned short kodeWarna);
tm *timeNow();
int random();
void clearBuffer();
bool logInBerhasil(string nik, string password);
void decor(int decor, int jumlah);
int banyakData();

// sorting & searching
void insertionSortNIK(string mode="ASC");
int binarySearch(string nik);

// tampilan mode penduduk
void menuMasukPenduduk();
void logInPenduduk();
void signUpPenduduk();
void menuPenduduk(Penduduk penduduk);
void isiFormulirData(Penduduk penduduk);

// tampilan mode pemerintah
void logInPemerintah();
void menuPemerintah();

// write & read txt


/*----------------------------------- MAIN PROGRAM -----------------------------------*/

int main(){
    // default
    bool running = true;
    string warning = "";
    int opsi1 = SELECT, 
        opsi2 = UNSELECT;

    while (running) {
        system("cls");
        cout << endl << endl << endl;

        // ambil data dari txt


        decor(177, 41);
        cout << "\t    PENDATAAN PENDUDUK KOTA SAMARINDA    \n";
        
        cout << endl;
        color(12); cout << setw(38) << warning << endl; color(7);
        cout << endl;
        
        cout << "\t       Jalankan program sebagai :      \n\n";
        color(opsi1); cout << "\t   [1] Pemerintah  ";
        color(opsi2); cout << "     [2] Penduduk\n\n"; color(7);

        decor(177, 41);
        // pilih mode
        char mode, pilih;
        mode = getch();

        // opsi yg tersedia
        switch (mode) {

            // tekan ENTER
            case ENTER:
                
                // mode pemerintah
                if (opsi1 == SELECT) {
                    logInPemerintah();
                
                // mode penduduk
                } else if (opsi2 = SELECT) {
                    menuMasukPenduduk();
                }

                break;
            
            // tekan RIGHT || LEFT
            case -32:
                pilih = getch();

                // pilih opsi 1
                if (pilih == LEFT){
                    opsi1 = SELECT;
                    opsi2 = UNSELECT;
                    
                // pilih opsi 2  
                } else if (pilih == RIGHT){
                    opsi1 = UNSELECT;
                    opsi2 = SELECT;
                }

                break;

            // opsi tidak ada
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

string hariIni() {
    time_t hariIni = time(0);

    return ctime(&hariIni); // mengonversi dari time_t
}

int random(){
    return rand()%9;
}

void clearBuffer(){
    cin.clear(); 
    cin.ignore(); 
    fflush(stdin);
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

bool isNIK(string str) {
    int length = str.length();

    char strChar[length];
    strcpy(strChar, str.c_str());

    int isInteger = 0;
    for (int i=0; i<length; i++) {
        int cek = (int)strChar[i] - 48;

        if (0 <= cek && cek <= 9) {
            isInteger += 1;
        }
    }

    if (isInteger == length) {
        return true;
    } else {
        return false;
    }

}

int banyakData(){
    for (int i=0; i<STORAGE; i++) {
        if (dataPenduduk[i].nik == "") {
            return i;
        }
    }
    return STORAGE;
}

void decor(int decor, int jumlah) {
    cout << "\t";
    for (int i=0; i<jumlah; i++) {
        cout << char(decor);
    }
    cout << endl << endl;
}


/* ----------------------------------- SORT & SEARCH ----------------------------------- */

void insertionSortNIK(string mode){
    Penduduk key;
    int i, j,
        length = banyakData();

    for (i = 1; i < length; i++) {

        key = dataPenduduk[i];
        j = i-1;

        // ascending
        if (mode == "ASC") {
            while (j >= 0 && dataPenduduk[j].nik.compare(key.nik) > 0){
                dataPenduduk[j+1] = dataPenduduk[j];
                j = j-1;
            }

        // descending
        } else {
            while (j >= 0 && dataPenduduk[j].nik.compare(key.nik) < 0){
                dataPenduduk[j+1] = dataPenduduk[j];
                j = j-1;
            }
        }

        dataPenduduk[j+1] = key;
    }
}

int binarySearchNIK(string nik) {
    insertionSortNIK();

    int index = -1,
        beg = 0,
        end = banyakData()-1;

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

// sorting berdasarkan judul
void bubbleSortTanggal(const char* mode){
    Penduduk temp;
    int length = banyakData();
    for (int i=0; i<length-1; i++){
        for (int j=0; j<length-1; j++){
            // ascending
            if(
                dataPenduduk[j].tanggalPembaruan.compare(dataPenduduk[j+1].tanggalPembaruan) > 0
                && mode == "ASC"
            ){
                temp = dataPenduduk[j];
                dataPenduduk[j] = dataPenduduk[j+1];
                dataPenduduk[j+1] = temp;
            }

            // descending
            if (
                dataPenduduk[j].tanggalPembaruan.compare(dataPenduduk[j+1].tanggalPembaruan) < 0
                && mode == "DESC"
            ){
                temp = dataPenduduk[j];
                dataPenduduk[j] = dataPenduduk[j+1];
                dataPenduduk[j+1] = temp;
            } // end if
        } // end for
    } // end for 
} // end function

/* ----------------------------------- TAMPILAN ----------------------------------- */
// penduduk ::::::::::::::::::::::
void menuMasukPenduduk() {
    bool openPage = true;
    string warning = "";
    int opsi0 = SELECT,
        opsi1 = UNSELECT,
        opsi2 = UNSELECT;

    while (openPage) {
        system("cls");
        cout << endl << endl << endl;

        decor(177, 41);
        cout << "\t                PENDUDUK             \n\n";

        cout << "\t              Pilih opsi :             \n";

        cout << endl;
        color(12); cout << setw(38) << warning << endl; color(7);
        cout << endl;

        color(opsi0); cout << "\t [0] Kembali ";
        color(opsi1); cout << "  [1] Log In ";
        color(opsi2); cout << "  [2] Sign Up \n\n"; color(7);

        decor(177, 41);

        char menu, pilih;
        menu = getch();

        // opsi yg tersedia
        switch (menu) {

            // tekan ENTER
            case ENTER:

                // kembali
                if (opsi0 == SELECT) {
                    openPage = false;

                // log in
                } else if (opsi1 == SELECT) {
                    logInPenduduk();

                // sign up
                } else if (opsi2 == SELECT) {
                    signUpPenduduk();
                }

                break;

            // tekan RIGHT || LEFT
            case -32:
                pilih = getch();

                // pilih opsi 0
                if (
                    pilih == LEFT && opsi1 == SELECT
                    || pilih == LEFT && opsi0 == SELECT
                ) {
                    opsi0 = SELECT;
                    opsi1 = UNSELECT;
                    opsi2 = UNSELECT;
                } 
                
                // pilih opsi 1
                else if (
                    pilih == RIGHT && opsi0 == SELECT 
                    || pilih == LEFT && opsi2 == SELECT
                ) {
                    opsi0 = UNSELECT;
                    opsi1 = SELECT;
                    opsi2 = UNSELECT;

                // pilih opsi 2
                } else if (
                    pilih == RIGHT && opsi1 == SELECT 
                    || pilih == RIGHT && opsi2 == SELECT
                ) {
                    opsi0 = UNSELECT;
                    opsi1 = UNSELECT;
                    opsi2 = SELECT;
                }
                
                break;

            default:
                warning = "Opsi tidak tersedia!";
                continue;
                break;
        }

        warning = "";

    }
}

void signUpPenduduk() {
    system("cls");
    cout << endl << endl << endl;
    decor(177, 41);

    Penduduk pendudukBaru;

    cout << "\t                  -*- SIGN UP PENDUDUK\n\n";

    cout << "\t   Nama Lengkap : "; getline(cin, pendudukBaru.namaLengkap); fflush(stdin);
    cout << "\t   NIK          : "; cin >> pendudukBaru.nik;                fflush(stdin);
    cout << "\t   Password     : "; getline(cin, pendudukBaru.password);    fflush(stdin);
    
    // gagal sign up - nik sudah ada
    if (binarySearchNIK(pendudukBaru.nik) != -1) {
        color(12);
        cout << "\n\t         NIK telah terdaftar!        \n" << endl; color(7);
    
    // gagal sign up - nik salah
    } else if (!isNIK(pendudukBaru.nik)) {
        color(12);
        cout << "\n\t    NIK yang dimasukkan tidak valid! \n" << endl; color(7);

    // berhasil sign up
    } else {

        dataPenduduk[banyakData()] = pendudukBaru;

        color(10);
        cout << "\n\t    Akun telah berhasil didaftarkan! \n" << endl; color(7);
    }

    decor(177, 41);

    getch();

}

void logInPenduduk() {
    system("cls");
    cout << endl << endl << endl;
    decor(177, 41);

    string nik, password;

    cout << "\t                  -*- LOGIN PENDUDUK\n\n";

    cout << "\t   NIK      : "; cin >> nik;             fflush(stdin);
    cout << "\t   Password : "; getline(cin, password); fflush(stdin);


    if (logInBerhasil(nik, password)){

        color(10);
        cout << "\n\t            Log in berhasil!             \n\n\n"; color(7);
        decor(177, 41); getch();

        int index = binarySearchNIK(nik);
        menuPenduduk(dataPenduduk[index]);
    
    } else {
        color(12);
        cout << "\n\t              Log in gagal!              \n\n\n"; color(7);
        decor(177, 41); getch();
    }

}

void menuPenduduk(Penduduk penduduk){
    bool openPage = true;
    string warning = "";
    int opsi0 = SELECT,
        opsi1 = UNSELECT,
        opsi2 = UNSELECT,
        opsi3 = UNSELECT;

    while(openPage) {
        system("cls");
        cout << endl << endl << endl;

        decor(240, 41);

        cout << "\t   Selamat datang, " << penduduk.namaLengkap << "! " << char(2) << endl;

        cout << endl;
        color(12); cout << setw(33) << warning << endl; color(7);
        cout << endl;

        color(opsi0); cout << "\t       [0] Keluar                \n";
        color(opsi1); cout << "\t       [1] Isi data diri         \n";
        color(opsi2); cout << "\t       [2] Tampilkan data diri   \n";
        color(opsi3); cout << "\t       [3] Ubah data diri        \n\n"; color(7);
        
        decor(240, 41);

        char menu, pilih;
        menu = getch();

        switch (menu) {

            // tekan ENTER
            case ENTER:
                // kembali
                if (opsi0 == SELECT) {
                    openPage = false;

                // isi formulir
                } else if (opsi1 == SELECT) {
                    isiFormulirData(penduduk);

                // tampilkan data diri
                } else if (opsi2 == SELECT) {
                    // tampilkan data diri

                // ubah data diri
                } else if (opsi3 == SELECT) {
                    // ubah data diri
                }
                break;

            // tekan UP || DOWN
            case -32:
                pilih = getch();

                // pilih opsi 0
                if (
                    pilih == UP && opsi0 == SELECT
                    || pilih == UP && opsi1 == SELECT
                ) {
                    opsi0 = SELECT; 
                    opsi1 = UNSELECT; 
                    opsi2 = UNSELECT; 
                    opsi3 = UNSELECT;
                
                // pilih opsi 1
                } else if (
                    pilih == DOWN && opsi0 == SELECT
                    || pilih == UP && opsi2 == SELECT
                ) {
                    opsi0 = UNSELECT; 
                    opsi1 = SELECT; 
                    opsi2 = UNSELECT; 
                    opsi3 = UNSELECT;
                
                // pilih opsi 2
                } else if (
                    pilih == DOWN && opsi1 == SELECT
                    || pilih == UP && opsi3 == SELECT
                ) {
                    opsi0 = UNSELECT; 
                    opsi1 = UNSELECT; 
                    opsi2 = SELECT; 
                    opsi3 = UNSELECT;
                
                // pilih opsi 3
                } else if (
                    pilih == DOWN && opsi2 == SELECT
                    || pilih == DOWN && opsi3 == SELECT
                ) {
                    opsi0 = UNSELECT; 
                    opsi1 = UNSELECT; 
                    opsi2 = UNSELECT; 
                    opsi3 = SELECT;
                }

                break;

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
    cout << endl << endl << endl;
    
    cout << "\tNama Lengkap \t: " << penduduk.namaLengkap << endl;  // nama lengkap
    cout << "\tNIK \t\t: " << penduduk.nik << endl;                 // NIK

    // TTL
    string tempat;
    int tanggal, bulan, tahun, 
        thnNow = timeNow()->tm_year + 1900;

    cout << "\n\tTempat/Tanggal Lahir" << endl;
    cout << "\t     Tempat\t: "; getline(cin, tempat)  ; fflush(stdin); color(8); 
    cout << "\t     -- isi di bawah ini dengan angka\n";              color(7);
    cout << "\t     Tanggal\t: "; cin >> tanggal; clearBuffer();
    cout << "\t     Bulan\t: ";   cin >> bulan;   clearBuffer();
    cout << "\t     Tahun\t: ";   cin >> tahun;   clearBuffer();

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
    penduduk.gender = getche() -1;
    cout << endl;

    // agama
    cout << "\n\tAgama \n"
         << "\t     [1] Islam     [3] Katolik   [5] Buddha   \n"
         << "\t     [2] Kristen   [4] Hindu     [6] Konghuchu\n"
         << "\t     : ";
    penduduk.agama = getche() -1;
    cout << endl;

    // golongan darah
    cout << "\n\tGolongan Darah   \n"
         << "\t     [1] A       [3] AB \n"
         << "\t     [2] B       [4] O  \n"
         << "\t     : ";
    penduduk.golDar = getche() -1;
    cout << endl;

    // status
    cout << "\n\tStatus \n"
         << "\t     [1] Belum kawin    [3] Cerai hidup \n"
         << "\t     [2] Kawin          [4] Cerai mati  \n"
         << "\t     : ";
    penduduk.status = getche() -1;
    cout << endl;


    color(10);
    cout << "\n\t    Formulir telah berhasil diisi!  " << endl; color(7);

    getch();
}


// pemerintah ::::::::::::::::::::
void logInPemerintah() {
    system("cls");
    cout << endl << endl << endl;
    decor(177, 41);

    cout << "\t  LOGIN PEMERINTAH -*-\n" << endl;

    string username, password;
    cout << "\t      Username   : "; cin >> username; fflush(stdin);
    cout << "\t      Password   : "; cin >> password; fflush(stdin);

    // berhasil masuk
    if (username == "pemerintah" && password == "123") {
        color(10);
        cout << "\n\t            Log in berhasil!             \n\n\n"; color(7);
        decor(177, 41);
        getch();

        menuPemerintah();

    // gagal masuk
    } else {

        color(12);
        cout << "\n\t              Log in gagal!              \n\n\n"; color(7);

        decor(177, 41);
        getch();
    }

    
}

void menuPemerintah(){
    bool openPage = true;
    string warning = "";
    int opsi0 = SELECT,
        opsi1 = UNSELECT,
        opsi2 = UNSELECT,
        opsi3 = UNSELECT;

    while(openPage) {
        system("cls");
        cout << endl << endl << endl;

        decor(240, 41);

        cout << "\t   Selamat datang, Pemerintah! " << char(2) << endl;

        cout << endl;
        color(12); cout << setw(33) << warning << endl; color(7);
        cout << endl;

        color(opsi0); cout << "\t       [0] Keluar                   \n";
        color(opsi1); cout << "\t       [1] Tampilkan data penduduk  \n";
        color(opsi2); cout << "\t       [2] Ubah data penduduk       \n";
        color(opsi3); cout << "\t       [3] Tampilkan hasil pendataan\n\n"; color(7);
        
        decor(240, 41);

        char menu, pilih;
        menu = getch();


        switch (menu) {
            // tekan ENTER
            case ENTER:
                // kembali
                if (opsi0 == SELECT) {
                    openPage = false;

                // tampilkan data penduduk
                } else if (opsi1 == SELECT) {
                    // tampilkan data penduduk

                // ubah data penduduk
                } else if (opsi2 == SELECT) {
                    // ubah data penduduk
                
                // tampilkan diagram
                } else if (opsi3 == SELECT) {
                    // tampilkan diagram
                }

                break;

            // tekan UP || DOWN
            case -32:
                pilih = getch();

                // pilih opsi 0
                if (
                    pilih == UP && opsi0 == SELECT
                    || pilih == UP && opsi1 == SELECT
                ) {
                    opsi0 = SELECT; 
                    opsi1 = UNSELECT; 
                    opsi2 = UNSELECT; 
                    opsi3 = UNSELECT;
                
                // pilih opsi 1
                } else if (
                    pilih == DOWN && opsi0 == SELECT
                    || pilih == UP && opsi2 == SELECT
                ) {
                    opsi0 = UNSELECT; 
                    opsi1 = SELECT; 
                    opsi2 = UNSELECT; 
                    opsi3 = UNSELECT;
                
                // pilih opsi 2
                } else if (
                    pilih == DOWN && opsi1 == SELECT
                    || pilih == UP && opsi3 == SELECT
                ) {
                    opsi0 = UNSELECT; 
                    opsi1 = UNSELECT; 
                    opsi2 = SELECT; 
                    opsi3 = UNSELECT;
                
                // pilih opsi 3
                } else if (
                    pilih == DOWN && opsi2 == SELECT
                    || pilih == DOWN && opsi3 == SELECT
                ) {
                    opsi0 = UNSELECT; 
                    opsi1 = UNSELECT; 
                    opsi2 = UNSELECT; 
                    opsi3 = SELECT;
                }

                break;

            default:
            warning = "Menu tidak tersedia!";
            continue;
            break;
        }

        warning = "";
    }

}

/* ----------------------------------- FILE TXT ----------------------------------- */

