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
    string alamat;
    string telepon;
    int usia = -1;
    short int gender = -1;       // index GENDER
    short int agama = -1;        // index AGAMA
    short int golDar = -1;       // index GOLDAR
    short int status = -1;       // index STATUS
};

// data tersimpan
Penduduk dataPenduduk[STORAGE];

// fungsi yg digunakan
void color(unsigned short kodeWarna);
tm *timeNow();
int random();
void clearBuffer();
bool logInBerhasil(string nik, string password);
void dekorasi(int ascii, int jumlah);
int banyakData();
void diagram(int jumlah, unsigned int kodeWarna=7);

// sorting & searching
void insertionSortNIK(string mode="ASC");
int binarySearch(string nik);

// tampilan mode penduduk
void menuMasukPenduduk();
void logInPenduduk();
void signUpPenduduk();
void menuPenduduk(Penduduk penduduk);
Penduduk isiFormulirBio(Penduduk penduduk);
void tampilkanData(Penduduk penduduk);

// tampilan mode pemerintah
void logInPemerintah();
void menuPemerintah();
void tampilkanDiagram();

// diagram
void diagramGender();
void diagramUsia();

// write & read txt
void importFromTxt();
void appendToTxt(Penduduk penduduk);
void deleteToTxt(Penduduk penduduk);
void updateToTxt(Penduduk penduduk);

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
        importFromTxt();

        dekorasi(177, 41);
        cout << "\n\t    PENDATAAN PENDUDUK KOTA SAMARINDA  \n\n";
        
        color(12); 
        cout << setw(38) << warning << endl; 
        color(7);
        
        cout << "\n\t       Jalankan program sebagai :      \n\n";
        color(opsi1); cout << "\t   [1] Pemerintah  ";
        color(opsi2); cout << "     [2] Penduduk\n\n"; 
        
        color(7); cout << endl;

        dekorasi(177, 41);
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

tm *timeNow() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    return ltm;
}

string hariIni() {
    time_t hariIni = time(0);

    return ctime(&hariIni); // mengonversi dari time_t
}

int random() {
    return rand()%9;
}

void clearBuffer() {
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

bool isDigit(string str) {
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

void dekorasi(int ascii, int jumlah) {
    cout << "\t";
    for (int i=0; i<jumlah; i++) {
        cout << char(ascii);
    }
    cout << endl << endl;
}

void diagram(int jumlah, unsigned int kodeWarna) {
    color(kodeWarna); 
    for (int i=0; i<jumlah; i++) {
        cout << char(219);
    }
    color(7);
}


/* ----------------------------------- SORT & SEARCH ----------------------------------- */

void insertionSortNIK(string mode) {
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
void bubbleSortTanggal(const char* mode) {
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

        dekorasi(177, 41);
        cout << "\n\t                PENDUDUK               \n";

        cout << "\n\t              Pilih opsi :             \n";

        cout << endl;
        color(12); cout << setw(38) << warning << endl; color(7);
        cout << endl;

        color(opsi0); cout << "\t [0] Kembali";
        color(opsi1); cout << "   [1] Log In";
        color(opsi2); cout << "   [2] Sign Up \n\n"; 
        color(7); cout << endl;

        dekorasi(177, 41);

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
    dekorasi(177, 41);

    Penduduk pendudukBaru;

    cout << "\n\t                  -*- SIGN UP PENDUDUK\n\n";

    cout << "\t   Nama Lengkap : "; getline(cin, pendudukBaru.namaLengkap); fflush(stdin);
    cout << "\t   NIK          : "; cin >> pendudukBaru.nik;                fflush(stdin);
    cout << "\t   Password     : "; getline(cin, pendudukBaru.password);    fflush(stdin);
    
    // gagal sign up - nik sudah ada
    if (binarySearchNIK(pendudukBaru.nik) != -1) {
        color(12);
        cout << "\n\t         NIK telah terdaftar!        \n" << endl;
    
    // gagal sign up - nik salah
    } else if (!isDigit(pendudukBaru.nik)) {
        color(12);
        cout << "\n\t    NIK yang dimasukkan tidak valid! \n" << endl;

    // berhasil sign up
    } else {

        // dataPenduduk[banyakData()] = pendudukBaru;
        pendudukBaru.tanggalPembaruan = hariIni();  // tgl data diri diubah
        appendToTxt(pendudukBaru);

        color(10);
        cout << "\n\t    Akun telah berhasil didaftarkan! \n" << endl;
    }

    color(7); cout << endl;

    dekorasi(177, 41);
    getch();

}

void logInPenduduk() {
    system("cls");
    cout << endl << endl << endl;
    dekorasi(177, 41);

    string nik, password;

    cout << "\n\t                  -*- LOGIN PENDUDUK\n\n";

    cout << "\t   NIK      : "; cin >> nik;             fflush(stdin);
    cout << "\t   Password : "; getline(cin, password); fflush(stdin);

    cout << endl << endl;

    if (logInBerhasil(nik, password)){

        color(10);
        cout << "\t            Log in berhasil!             \n\n" << endl; 
        color(7); 

        dekorasi(177, 41); getch();

        int index = binarySearchNIK(nik);
        menuPenduduk(dataPenduduk[index]);
    
    } else {
        color(12);
        cout << "\t              Log in gagal!              \n\n" << endl; 
        color(7); 

        dekorasi(177, 41); getch();
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

        dekorasi(240, 41);

        cout << "\t   Selamat datang, " << penduduk.namaLengkap << "! " << char(2) << endl;

        cout << endl;
        color(12); cout << setw(33) << warning << endl; color(7);
        cout << endl;

        color(opsi0); cout << "\t       [0] Keluar                \n";
        color(opsi1); cout << "\t       [1] Isi data diri         \n";
        color(opsi2); cout << "\t       [2] Tampilkan data diri   \n";
        color(opsi3); cout << "\t       [3] Ubah data diri        \n\n\n"; color(7);
        
        dekorasi(240, 41);

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
                    penduduk = isiFormulirBio(penduduk);

                // tampilkan data diri
                } else if (opsi2 == SELECT) {
                    // tampilkan data diri
                    tampilkanData(penduduk);

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

Penduduk isiFormulirBio(Penduduk penduduk){
    bool openPage = true;
    int page = 1;

    while (openPage) {
        system("cls");
        cout << endl << endl << endl;

        cout << "\t         FORMULIR BIODATA PENDUDUK           \n" << endl;
        
        switch (page) {

            // halaman 1
            case 1:
                cout << "\tNama Lengkap \t: " << penduduk.namaLengkap << endl;  // nama lengkap
                cout << "\tNIK \t\t: "        << penduduk.nik         << endl;  // NIK

                if (penduduk.ttl == "") {   // ttl belum diisi
                    // TTL
                    string tempat;
                    int tanggal, bulan, tahun, 
                        thnNow = timeNow()->tm_year + 1900;

                    cout << "\n\tTempat/Tanggal Lahir" << endl;
                    cout << "  \t   Tempat    : "; 
                    color(11); getline(cin, tempat); fflush(stdin); 
                    
                    color(8); 
                    cout << "\n\t     -- isi di bawah ini dengan angka \n\n"; color(7);

                    cout << "  \t   Tanggal   : "; color(11); cin >> tanggal; color(7); clearBuffer();
                    cout << "  \t   Bulan     : "; color(11); cin >> bulan;   color(7); clearBuffer();
                    cout << "  \t   Tahun     : "; color(11); cin >> tahun;   color(7); clearBuffer();

                    if (
                        tempat == "" 
                        || tanggal < 1 || tanggal > 31
                        || bulan   < 1 || bulan   > 12
                        || tahun   < 0 || tahun   > thnNow
                    ) {
                        ;
                    } else {
                        penduduk.ttl = tempat + ", " + to_string(tanggal) + "/" + to_string(bulan) + "/" + to_string(tahun);
                        penduduk.usia = timeNow()->tm_year + 1900 - tahun; // usia
                    }
                    
                } else {    // ttl sudah diisi
                
                    cout << "\n\tTempat/Tanggal Lahir" << endl;
                    cout << "  \t   Tempat    : "; color(14); cout << "sudah diisi." << endl; color(7);
                    
                    color(8); cout << "\n\t   -- isi di bawah ini dengan angka   \n" << endl; color(7);

                    cout << "  \t   Tanggal   : "; color(14); cout << "sudah diisi." << endl; color(7);
                    cout << "  \t   Bulan     : "; color(14); cout << "sudah diisi." << endl; color(7);
                    cout << "  \t   Tahun     : "; color(14); cout << "sudah diisi." << endl; color(7);
                }

                cout << endl;

                break;

            // halaman 2
            case 2:
                cout << "\tAlamat Lengkap\t: ";
                if (penduduk.alamat == "") { 
                    color(11); getline(cin, penduduk.alamat); color(7); fflush(stdin); 
                } else { 
                    color(14); cout << "sudah diisi" << endl; color(7); 
                }

                cout << "\tNo. Telepon\t: ";
                if (penduduk.telepon == "") { 
                    color(11); getline(cin, penduduk.telepon); color(7); fflush(stdin); 
                } else { 
                    color(14); cout << "sudah diisi" << endl;; color(7); 
                }

                color(8); 
                cout << "\n\t-- isi dengan memilih angka pada opsi\n"; color(7);
                
                // gender
                cout << "\n\tJenis Kelamin \n"       
                    << "\t     [1] Laki-laki     [2] Perempuan           \n"   
                    << "\t     : "; 
                
                if (penduduk.gender == -1) { 
                    color(11); cin >> penduduk.gender; color(7);

                    if (penduduk.gender < 1 || penduduk.gender > 2) {
                        penduduk.gender = -1;
                    } else {
                        penduduk.gender -= 1;
                    }

                } else { 
                    color(14); cout << "sudah diisi"; color(7); 
                }

                cout << endl;

                // agama
                cout << "\n\tAgama \n"
                    << "\t     [1] Islam     [3] Katolik   [5] Buddha    \n"
                    << "\t     [2] Kristen   [4] Hindu     [6] Konghuchu \n"
                    << "\t     : ";

                if (penduduk.agama == -1) { 
                    color(11); cin >> penduduk.agama; color(7);

                    if (penduduk.agama < 1 || penduduk.agama > 4) {
                        penduduk.agama = -1;
                    } else {
                        penduduk.agama -= 1;
                    }

                } else { 
                    color(14); cout << "sudah diisi"; color(7); 
                }

                break;

            case 3:
                // golongan darah
                cout << "\tGolongan Darah                               \n"
                    << "\t     [1] A         [3] AB                     \n"
                    << "\t     [2] B         [4] O                      \n"
                    << "\t     : ";

                if (penduduk.golDar == -1) { 
                    color(11); cin >> penduduk.golDar; color(7);

                    if (penduduk.golDar < 1 || penduduk.golDar > 4) {
                        penduduk.golDar = -1;
                    } else {
                        penduduk.golDar -= 1;
                    }

                } else { 
                    color(14); cout << "sudah diisi"; color(7); 
                }

                cout << endl;

                // status
                cout << "\n\tStatus \n"
                    << "\t     [1] Belum kawin    [3] Cerai hidup      \n"
                    << "\t     [2] Kawin          [4] Cerai mati       \n"
                    << "\t     : ";

                if (penduduk.status == -1) { 
                    color(11); cin >> penduduk.status; color(7);

                    if (penduduk.status < 1 || penduduk.status > 4) {
                        penduduk.status = -1;
                    } else {
                        penduduk.status -= 1;
                    }

                } else { 
                    color(14); cout << "sudah diisi"; color(7); 
                }

                cout << endl << endl << endl << endl;

                break;

        } 

        penduduk.tanggalPembaruan = hariIni();  // tgl data pembaruan diubah

        updateToTxt(penduduk);
        
        cout << endl; 
        color(10);    cout << "\n\t       Formulir telah berhasil diisi!    \n"; color(7);
        color(SELECT); cout << "\n\t<= Kembali                     "; 
        
        if (page == 1 || page == 2) { cout << "Berikutnya =>"; }

        color(7); cout << endl << endl;
        
        char opsi, pilih;
        opsi = getch();

        if (opsi == -32) {
            pilih = getch();

            if (pilih == LEFT && page == 1) {
                openPage = false;
                break;
            } else if (pilih == LEFT && page == 2) {
                page = 1;
            } else if (pilih == RIGHT && page == 1 || pilih == LEFT && page == 3) {
                page = 2;
            } else if (pilih == RIGHT && page == 2) {
                page = 3;
            }
        }   

    }


    return penduduk;
}

void tampilkanData(Penduduk penduduk) {
    system("cls");
    cout << "Gender " << GENDER[penduduk.gender] << endl; 
    cout << "Agama " << AGAMA[penduduk.agama] << endl; 
    cout << "GolDar " << GOLDAR[penduduk.golDar] << endl; 
    cout << "Status " << STATUS[penduduk.status] << endl; 
    getch();   
}


// pemerintah ::::::::::::::::::::
void logInPemerintah() {
    system("cls");
    cout << endl << endl << endl;
    dekorasi(177, 41);

    cout << "\n\t  LOGIN PEMERINTAH -*-\n" << endl;

    string username, password;
    cout << "\t      Username   : "; cin >> username; fflush(stdin);
    cout << "\t      Password   : "; cin >> password; fflush(stdin);

    // berhasil masuk
    if (username == "p" && password == "p") {
        color(10);
        cout << "\n\t            Log in berhasil!             \n\n\n" << endl; color(7);
        
        dekorasi(177, 41);
        getch();

        menuPemerintah();

    // gagal masuk
    } else {

        color(12);
        cout << "\n\t              Log in gagal!              \n\n\n" << endl; color(7);

        dekorasi(177, 41);
        getch();
    }

    
}

void menuPemerintah() {
    bool openPage = true;
    string warning = "";
    int opsi0 = SELECT,
        opsi1 = UNSELECT,
        opsi2 = UNSELECT,
        opsi3 = UNSELECT;

    while(openPage) {
        system("cls");
        cout << endl << endl << endl;

        dekorasi(240, 41);

        cout << "\n\t   Selamat datang, Pemerintah! " << char(2) << endl;

        cout << endl;
        color(12); cout << setw(33) << warning << endl; color(7);
        cout << endl;

        color(opsi0); cout << "\t       [0] Keluar                   \n";
        color(opsi1); cout << "\t       [1] Tampilkan data penduduk  \n";
        color(opsi2); cout << "\t       [2] Ubah data penduduk       \n";
        color(opsi3); cout << "\t       [3] Tampilkan hasil pendataan\n\n\n"; color(7);
        
        dekorasi(240, 41);

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
                    tampilkanDiagram();
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

void tampilkanDiagram() {
    bool openPage = true;
    string kategori = "Jenis Kelamin";
    int page = 1;

    while (openPage) {
        system("cls");
        cout << endl << endl << endl;

        cout << "\t      HASIL PENDATAAN PENDUDUK    \n\n";
        cout << "\t" << kategori << endl << endl;

        if (page == 1) {
            diagramGender();
        } else if (page == 2) {
            diagramUsia();
        }

        cout << "\n\n\t  Data tersimpan : " << banyakData()
             << endl << endl;
        
        color(SELECT); 
        cout << "\n\t<= Kembali                     "; 
        if (page == 1 || page == 2) { 
            cout << "Berikutnya =>"; 
        } color(7);

        char opsi, pilih;
        opsi = getch();

        if (opsi == -32) {
            pilih = getch();

            if (pilih == LEFT && page == 1) {
                openPage = false;
                break;

            } else if (pilih == LEFT && page == 2) {
                page = 1; kategori = "Jenis Kelamin";

            } else if (pilih == RIGHT && page == 1 || pilih == LEFT && page == 3) {
                page = 2; kategori = "Usia";

            }
        }
    }

}

void diagramGender() {
    int diagramL,
        diagramP,
        persentaseL,
        persentaseP,
        totalL = 0,
        totalP = 0,
        total = banyakData();

    // hitung jumlah data per gender
    for (int i=0; i<total; i++) {
        if (dataPenduduk[i].gender == 0) {
            totalL++;
        } else if (dataPenduduk[i].gender == 1) {
            totalP++;
        }
    }

    diagramL = (totalL*45)/total;
    diagramP = (totalP*45)/total;

    persentaseL = (totalL*100)/total;
    persentaseP = (totalP*100)/total;

    cout << "\t  " << char(221) << endl; 
    cout << "\t  " << char(221); 
    
    diagram(diagramL, 9); cout << " " << persentaseL << "%" << endl;
    
    cout << "\t  " << char(221) << endl;
    cout << "\t  " << char(221) << endl;
    cout << "\t  " << char(221) << endl; 
    cout << "\t  " << char(221); 
    
    diagram(diagramP, 13); cout << " " << persentaseP << "%" << endl;
    
    cout << "\t  " << char(221) << endl;

    cout << endl << endl;

    color(9);  cout << "\t  " << char(254); color(7); cout << " Laki-laki";
    color(13); cout << "\t  " << char(254); color(7); cout << " Perempuan";

}

void diagramUsia() {
    short int total1 = 0,
              total2 = 0,
              total3 = 0,
              total4 = 0,
              total5 = 0,
              total6 = 0,
              total = banyakData();

    // hitung jumlah data per usia
    for (int i=0; i<total; i++) {
        if (dataPenduduk[i].usia <= 9) {
            total1++;
        } else if (dataPenduduk[i].usia >= 10 && dataPenduduk[i].usia <= 19) {
            total2++;
        } else if (dataPenduduk[i].usia >= 20 && dataPenduduk[i].usia <= 29) {
            total3++;
        } else if (dataPenduduk[i].usia >= 30 && dataPenduduk[i].usia <= 39) {
            total4++;
        } else if (dataPenduduk[i].usia >= 40 && dataPenduduk[i].usia <= 49) {
            total5++;
        } else if (dataPenduduk[i].usia >= 50) {
            total6++;
        } 
    }

    cout << "\t  " << char(221); diagram((total6*45)/total, 14); 
    cout << " " << (total6*100)/total << "%" << endl;
    
    cout << "\t  " << char(221); diagram((total5*45)/total, 13); 
    cout << " " << (total5*100)/total << "%" << endl;
    
    cout << "\t  " << char(221); diagram((total4*45)/total, 12); 
    cout << " " << (total4*100)/total << "%" << endl;
    
    cout << "\t  " << char(221); diagram((total3*45)/total, 10); 
    cout << " " << (total3*100)/total << "%" << endl;
    
    cout << "\t  " << char(221); diagram((total2*45)/total, 9); 
    cout << " " << (total2*100)/total << "%" << endl;
    
    cout << "\t  " << char(221); diagram((total1*45)/total, 8); 
    cout << " " << (total1*100)/total << "%" << endl;
    
    cout << endl << endl;

    color(8);  cout << "\t  " << char(254); color(7); cout << " 0-9 tahun";
    color(12); cout << "\t  " << char(254); color(7); cout << " 30-39 tahun\n";
    color(9);  cout << "\t  " << char(254); color(7); cout << " 10-20 tahun";
    color(13); cout << "\t  " << char(254); color(7); cout << " 40-49 tahun\n";
    color(10);  cout << "\t  " << char(254); color(7); cout << " 20-29 tahun";
    color(14); cout << "\t  " << char(254); color(7); cout << " 50+ tahun";

}

/* ----------------------------------- FILE TXT ----------------------------------- */

void importFromTxt() {
    ifstream input;
    input.open("data.txt");

    Penduduk penduduk;
    string baris;
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
        // alamat
        } else if (kolom == 6) {
            penduduk.alamat = baris;
        // telepon
        } else if (kolom == 7) {
            penduduk.telepon = baris;
        // usia
        } else if (kolom == 8) {
            penduduk.usia = stoi(baris); 
        // gender
        } else if (kolom == 9) {
            penduduk.gender = stoi(baris);
        // agama
        } else if (kolom == 10) {
            penduduk.agama = stoi(baris);
        // golongan darah
        } else if (kolom == 11) {
            penduduk.golDar = stoi(baris);
        // status
        } else if (kolom == 12) {
            penduduk.status = stoi(baris);

            dataPenduduk[index] = penduduk;

            index++;
            kolom = 1;
            continue;
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
         << penduduk.alamat << "\n"
         << penduduk.telepon << "\n"
         << penduduk.usia << "\n"
         << penduduk.gender << "\n"
         << penduduk.agama << "\n"
         << penduduk.golDar << "\n"
         << penduduk.status << "\n";

    file.close();

    importFromTxt();
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

void updateToTxt(Penduduk penduduk) {
    deleteFromTxt(penduduk);
    appendToTxt(penduduk);
    
}
