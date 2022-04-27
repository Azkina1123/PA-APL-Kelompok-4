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

// sorting & searching
void insertionSortNIK();
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
int banyakDataTxt();
void importFromTxt();
void appendToTxt(Penduduk penduduk);
void updateToTxt(Penduduk penduduk);
void deleteFromTxt(Penduduk penduduk);

/*----------------------------------- MAIN PROGRAM -----------------------------------*/

int main(){
    // default
    bool running = true;
    string warning = "";
    int opsi1 = SELECT, 
        opsi2 = UNSELECT;

    while (running) {
        system("cls");
        cout << endl << endl;

        // ambil data dari txt
        importFromTxt();

        cout << "\t            Selamat Datang!            \n";
        
        cout << endl;
        color(12); cout << setw(37) << warning << endl; color(7);
        cout << endl;
        
        cout << "\t       Jalankan program sebagai :      \n\n";
        color(opsi1); cout << "\t   [1] Pemerintah  ";
        color(opsi2); cout << "     [2] Penduduk\n\n"; color(7);

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

int random(){
    return rand()%9;
}

void clearBuffer(){
    cin.clear(); 
    cin.ignore(); 
    fflush(stdin);
}

bool logInBerhasil(string nik, string password) {
    for (int i=0; i<banyakDataTxt(); i++){
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


/* ----------------------------------- SORT & SEARCH ----------------------------------- */

void insertionSortNIK(){
    Penduduk key;
    int i, j,
        length = banyakDataTxt();

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

int binarySearchNIK(string nik) {
    insertionSortNIK();

    int index = -1,
        beg = 0,
        end = banyakDataTxt()-1;

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
// penduduk ::::::::::::::::::::::
void menuMasukPenduduk() {
    bool openPage = true;
    string warning = "";
    int opsi0 = SELECT,
        opsi1 = UNSELECT,
        opsi2 = UNSELECT;

    while (openPage) {
        system("cls");
        cout << endl << endl;

        cout << "\t              Pilih opsi :           \n";

        cout << endl;
        color(12); cout << setw(37) << warning << endl; color(7);
        cout << endl;

        color(opsi0); cout << "\t[0] Kembali ";
        color(opsi1); cout << "  [1] Log In ";
        color(opsi2); cout << "  [2] Sign Up\n"; color(7);

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
    color(14);
    cout << "\n\t#######################################\n" << endl; color(7);
    Penduduk pendudukBaru;

    cout << "\tNama Lengkap : "; getline(cin, pendudukBaru.namaLengkap); fflush(stdin);
    cout << "\tNIK          : "; cin >> pendudukBaru.nik;                fflush(stdin);
    cout << "\tPassword     : "; getline(cin, pendudukBaru.password);    fflush(stdin);
    
    // gagal sign up - nik sudah ada
    if (binarySearchNIK(pendudukBaru.nik) != -1) {

        color(12);
        cout << "\n\t         NIK telah terdaftar!  " << endl; color(7);
    
    // gagal sign up - nik salah
    } else if (!isNIK(pendudukBaru.nik)) {

        color(12);
        cout << "\n\t    NIK yang dimasukkan tidak valid!  " << endl; color(7);

    // berhasil sign up
    } else {

        appendToTxt(pendudukBaru);

        color(10);
        cout << "\n\t    Akun telah berhasil didaftarkan!  " << endl; color(7);
    }

    getch();

}

void logInPenduduk() {
    color(14);
    cout << "\n\t#######################################\n" << endl; color(7);
    string nik, password;

    cout << "\tNIK      : "; cin >> nik;             fflush(stdin);
    cout << "\tPassword : "; getline(cin, password); fflush(stdin);


    if (logInBerhasil(nik, password)){

        color(10);
        cout << "\n\t            Log in berhasil!  " << endl;
        color(7);

        getch();

        int index = binarySearchNIK(nik);
        menuPenduduk(dataPenduduk[index]);
    
    } else {
        color(12);
        cout << "\n\t              Log in gagal!  " << endl;
        color(7);

        getch();
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
        cout << endl << endl;

        cout << "\t     Selamat datang, " << penduduk.namaLengkap << "!" << endl;

        cout << endl;
        color(12); cout << setw(33) << warning << endl; color(7);
        cout << endl;

        color(opsi0); cout << "\t     [0] Keluar                \n\n";
        color(opsi1); cout << "\t     [1] Isi data diri         \n\n";
        color(opsi2); cout << "\t     [2] Tampilkan data diri   \n\n";
        color(opsi3); cout << "\t     [3] Ubah data diri        \n\n"; color(7);
        
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
    cout << endl << endl;
    
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

    updateToTxt(penduduk);

    color(10);
    cout << "\n\t    Formulir telah berhasil diisi!  " << endl; color(7);

    getch();
}

// pemerintah ::::::::::::::::::::
void logInPemerintah() {
    system("cls");
    cout << endl << endl << endl;

    cout << "\tLOGIN PEMERINTAH -*-\n" << endl;

    string username, password;
    cout << "\t    Username   : "; cin >> username; fflush(stdin);
    cout << "\t    Password   : "; cin >> password; fflush(stdin);

    if (username == "pemerintah" && password == "123") {
        color(10);
        cout << "\n\t    Log in berhasil!  " << endl;
        color(7);
        getch();

        menuPemerintah();
    } else {
        color(12);
        cout << "\n\t    Log in gagal!  " << endl;
        color(7);
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
        cout << endl << endl;

        cout << "\t     Selamat datang, Pmerintah!" << endl;

        cout << endl;
        color(12); cout << setw(33) << warning << endl; color(7);
        cout << endl;

        color(opsi0); cout << "\t     [0] Keluar                   \n\n";
        color(opsi1); cout << "\t     [1] Tampilkan data penduduk  \n\n";
        color(opsi2); cout << "\t     [2] Ubah data penduduk       \n\n";
        color(opsi3); cout << "\t     [3] Tampilkan hasil pendataan\n\n"; color(7);
        
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

int banyakDataTxt() {
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

void importFromTxt() {
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

void appendToTxt(Penduduk penduduk) {
    ofstream file;

    file.open("data.txt", ios::app);

    file << penduduk.namaLengkap << "|"
         << penduduk.nik << "|"
         << penduduk.password << "|"
         << penduduk.ttl << "|"
         << penduduk.usia << "|"
         << penduduk.gender << "|"
         << penduduk.agama << "|"
         << penduduk.golDar << "|"
         << penduduk.status << "\n";

    file.close();

    importFromTxt();
}

void updateToTxt(Penduduk penduduk) {
    deleteFromTxt(penduduk);
    appendToTxt(penduduk);
}

void deleteFromTxt(Penduduk penduduk) {
    fstream file;

    file.open("data.txt", ios::out | ios::in | ios::app);

    int length = banyakDataTxt(), 
        index = 0;

    string dataTersimpan[length], 
           baris;

    while (!file.eof()){
        getline(file, baris);
        dataTersimpan[index] = baris;
    }

    index = binarySearchNIK(penduduk.nik);

    for (int i=0; i<length; i++) {
        if (i == index) {
            continue;
        }

        file << dataTersimpan[i];
    }

    file.close();

    importFromTxt();
}

