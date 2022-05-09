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
const string KECAMATAN[] = {
    "Palaran", "Samarinda Seberang", "Samarinda Ulu", "Samarinda Ulu", 
    "Samarinda Ilir", "Samarinda Utara", "Sungai Kunjang", "Sambutan", 
    "Sungai Pinang", "Samarinda Kota", "Loa Janan Ilir"
};
const string KELURAHAN[10][8] = {
    {"Rawa Makmur", "Handil Bakti", "Bukuan", "Simpang Pasir", "Bantuas"}, 
    {"Sungai Keledang", "Baqa", "Mesjid", "Mangkupalas", "Tenun", "Gunung Panjang"},
    {"Teluk Lerong Ilir", "Jawa", "Air Putih", "Sidodadi", "Air Hitam", "Dadi Mulya", "Gunung Kelua", "Bukit Pinang"},
    {"Selili", "Sungai Dama", "Sidomulyo", "Sidodamai", "Pelita"},
    {"Sempaja Selatan", "Lempake", "Sungai Siring", "Sempaja Utara", "Tanah Merah", "Sempaja Barat", "Sempaja Timur", "Budaya Pampang"},
    {"Loa Bakung", "Loa Buah", "Karang Asam Ulu", "Lok Bahu", "Teluk Lerong Ulu", "Karang Asam Ilir", "Karang Anyar"},
    {"Sungai Kapih", "Sambutan", "Makroman", "Sindang Sari", "Pulau Atas"},
    {"Temindung Permai", "Sungai Pinang Dalam", "Gunung Lingai", "Mugirejo", "Bandara"},
    {"Karang Mumus", "Pelabuhan", "Pasar Pagi", "Bugis", "Sungai Pinang Luar"},
    {"Simpang Tiga", "Tani Aman", "Sengkotek", "Harapan Baru", "Rapak Dalam"}
};

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

// tampilan mode penduduk
void menuMasukPenduduk();                           // menu login atau signup
void logInPenduduk();                               // log in penduduk
void signUpPenduduk();                              // sign up penduduk
void menuPenduduk(Penduduk penduduk);               // menu di akun penduduk
Penduduk isiFormulirPenduduk(Penduduk penduduk);    // isi formulir penduduk
void tampilkanData(Penduduk penduduk);              // tampilkan data

// tampilan mode pemerintah
void logInPemerintah();                             // log in pemerintah
void menuPemerintah();                              // menu di akun pemerintah
void tampilkanDiagram();                            // tampilkan diagram data penduduk

// diagram
void diagramGender();                               // diagram berdasarkan gender
void diagramUsia();                                 // diagram berdasarkan usia
void diagramAgama();                                // diagram berdasarkan agama
void diagramGolDar();                               // diagram berdasarkan golongan darah
void diagramStatus();                               // diagram berdasarkna status

// write & read txt
void importFromTxt();                               // ambil semua data dari txt
void appendToTxt(Penduduk penduduk);                // tambahkan data baru ke txt
void deleteToTxt(Penduduk penduduk);                // hapus data tertentu dari txt
void updateToTxt(Penduduk penduduk);                // ubah data tertentu di txt

// sorting & searching
void insertionSort(string array[], string mode= "ASC");    // sorting berdasarkan NIK          
int indexElemen(string array[], string cari);
int indexNIK(string nik);                                       // cari index NIK
void bubbleSortTanggal(const char* mode);                       // sorting berdasarkan tanggal pembaruan

// tambahan
void color(unsigned short kodeWarna);               // ganti warna
tm *timeNow();                                      // waktu sekarang
string hariIni();                                   // tanggal hari ini
int random();                                       // angka random
void clearBuffer();                                 // bersihkan buffer
bool logInBerhasil(string nik, string password);    // memastikan nik dan pw benar
bool isDigit(string str);                           // memastikan string diisi angka saja
int banyakData();                                   // banyak data tersimpan
void dekorasi(int ascii, int jumlah);               // dekorasi tampilan
void diagram(int jumlah, unsigned int kodeWarna=7); // batang diagram


/*----------------------------------- MAIN PROGRAM -----------------------------------*/

int main(){
    // default
    bool running = true;        // program berjalan
    string warning = "";        // peringatan
    int opsi1 = SELECT,         // warna opsi 1
        opsi2 = UNSELECT,       // warna opsi 2
        opsi3 = UNSELECT;       // warna opsi 3

    while (running) {
        system("cls");  
        cout << endl << endl << endl;

        importFromTxt();        // ambil data dari txt

        dekorasi(177, 41);
        cout << "\n\t    PENDATAAN PENDUDUK KOTA SAMARINDA  \n\n";  // judul

        color(12); cout << setw(38) << warning << endl;  color(7);  // notif peringatan
        
        // tampilan menu
        cout << "\n\t       Jalankan program sebagai :      \n\n";  
        color(opsi1); cout << "\t   [1] Pemerintah  ";              // opsi 1
        color(opsi2); cout << "     [2] Penduduk\n\n";              // opsi 2
        color(opsi3); cout << "\t\t\t[KELUAR]   \n\n";              // opsi 3
        
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
                    logInPemerintah();      // buka login pemerintah
                    
                // mode penduduk
                } else if (opsi2 == SELECT) {
                    menuMasukPenduduk();    // buka menu masuk penduduk
                    
                // keluar
                } else if (opsi3 == SELECT) {
                    running = false;        // hentikan program

                }

                break;
            
            // tekan UP|| RIGHT || DOWN || LEFT 
            case -32:
                pilih = getch();

                // pilih opsi 1
                if (pilih == LEFT || pilih == UP && opsi3 == SELECT) {
                    opsi1 = SELECT;
                    opsi2 = UNSELECT;
                    opsi3 = UNSELECT;

                // pilih opsi 2  
                } else if (pilih == RIGHT) {
                    opsi1 = UNSELECT;
                    opsi2 = SELECT;
                    opsi3 = UNSELECT;
                    
                // pilih opsi 3  
                } else if (pilih == DOWN) {
                    opsi1 = UNSELECT;
                    opsi2 = UNSELECT;
                    opsi3 = SELECT;
                }

                break;

            // opsi tidak ada
            default:
                warning = "Opsi tidak tersedia!";
                continue;   // lanjutkan looping

                break;
        }

        warning = "";
    }

    cout << "Program dihentikan" << endl;

    return 0;

}


/* ----------------------------------- TAMPILAN ----------------------------------- */

// penduduk :::::::::::::::::::::::::::::::::::::
void menuMasukPenduduk() {

    // default
    bool openPage = true;   // selama halaman dibuka
    string warning = "";    // notif peringatan
    int opsi0 = SELECT,     // pilih opsi 1
        opsi1 = UNSELECT,
        opsi2 = UNSELECT;

    while (openPage) {
        system("cls");
        cout << endl << endl << endl;
        dekorasi(177, 41);

        cout << "\n\t                PENDUDUK                 ";    // judul halaman
        cout << "\n\t              Pilih opsi :           \n\n";

        color(12); cout << setw(38) << warning << endl; color(7);   // notif peringatan
        cout << endl;

        color(opsi0); cout << "\t     [0] Kembali";     // opsi 0
        color(opsi2); cout << "\t[2] Sign Up   \n";     // opsi 1
        color(opsi1); cout << "\t     [1] Log In\n\n";  // opsi 2
        
        color(7); cout << endl; 
        dekorasi(177, 41);

        // pilih menu
        char menu, pilih;
        menu = getch();

        // opsi yg tersedia
        switch (menu) {

            // tekan ENTER
            case ENTER:

                // kembali
                if (opsi0 == SELECT) {
                    openPage = false;   // berhenti buka halaman

                // log in
                } else if (opsi1 == SELECT) {
                    logInPenduduk();    // buka log in penduduk

                // sign up
                } else if (opsi2 == SELECT) {
                    signUpPenduduk();   // buka sign up penduduk
                }

                break;

            // tekan UP || RIGHT || DOWN || LEFT
            case -32:
                pilih = getch();

                // pilih opsi 0
                if (
                    pilih == LEFT && opsi2 == SELECT
                    || pilih == UP && opsi1 == SELECT
                ) {
                    opsi0 = SELECT;
                    opsi1 = UNSELECT;
                    opsi2 = UNSELECT;
                } 
                
                // pilih opsi 1
                else if (
                    pilih == DOWN && opsi0 == SELECT
                    || pilih == DOWN && opsi2 == SELECT
                ) {
                    opsi0 = UNSELECT;
                    opsi1 = SELECT;
                    opsi2 = UNSELECT;

                // pilih opsi 2
                } else if (
                    pilih == RIGHT && opsi0 == SELECT 
                    || pilih == RIGHT && opsi1 == SELECT
                ) {
                    opsi0 = UNSELECT;
                    opsi1 = UNSELECT;
                    opsi2 = SELECT;
                }
                
                break;

            default:
                warning = "Opsi tidak tersedia!";
                continue;   // lanjutkan looping
                
                break;
        }

        warning = "";

    }
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

    // login berhasil
    if ( logInBerhasil(nik, password) ) {

        color(10);
        cout << "\t            Log in berhasil!      \n\n" << endl; color(7); 

        dekorasi(177, 41); getch();

        int index = indexNIK(nik);          // index nik
        menuPenduduk(dataPenduduk[index]);  // masuk ke akun sesuai nik
    
    // login gagal
    } else {
        color(12);
        cout << "\t              Log in gagal!       \n\n" << endl; color(7); 

        dekorasi(177, 41); getch();
    }

}

void signUpPenduduk() {
    system("cls");
    cout << endl << endl << endl;
    dekorasi(177, 41);

    Penduduk pendudukBaru;

    cout << "\n\t                  -*- SIGN UP PENDUDUK   \n" << endl;

    cout << "\t   Nama Lengkap : "; getline(cin, pendudukBaru.namaLengkap); fflush(stdin);
    cout << "\t   NIK          : "; cin >> pendudukBaru.nik;                fflush(stdin);
    cout << "\t   Password     : "; getline(cin, pendudukBaru.password);    fflush(stdin);
    
    // gagal sign up - nik sudah ada
    if (indexNIK(pendudukBaru.nik) != -1) {
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

    dekorasi(177, 41); getch();

}

void menuPenduduk(Penduduk penduduk){
    
    // default
    bool openPage = true;   // selama buka halaman
    string warning = "";    // notif peringatan
    int opsi0 = SELECT,     // pilih opsi 0
        opsi1 = UNSELECT,
        opsi2 = UNSELECT,
        opsi3 = UNSELECT;

    while(openPage) {
        system("cls");
        cout << endl << endl << endl;

        dekorasi(240, 41);

        cout << "\t   Selamat datang, " << penduduk.namaLengkap << "! " << char(2)
             << endl << endl;

        color(12); cout << setw(33) << warning << endl << endl; 

        color(opsi0); cout << "\t       [0] Keluar                \n";  // opsi 0
        color(opsi1); cout << "\t       [1] Isi data diri         \n";  // opsi 1
        color(opsi2); cout << "\t       [2] Tampilkan data diri   \n";  // opsi 2
        color(opsi3); cout << "\t       [3] Ubah data diri    \n\n\n";  // opsi 3
        
        color(7); dekorasi(240, 41);

        // pilih menu
        char menu, pilih;
        menu = getch();

        // menu tersedia
        switch (menu) {

            // tekan ENTER
            case ENTER:
                // kembali
                if (opsi0 == SELECT) {
                    openPage = false;                       // berhenti buka halaman

                // isi formulir
                } else if (opsi1 == SELECT) {
                    penduduk = isiFormulirPenduduk(penduduk);    // buka halaman isi formulir

                // tampilkan data diri
                } else if (opsi2 == SELECT) {   
                    tampilkanData(penduduk);                // buka halaman tampilkan data diri

                // ubah data diri
                } else if (opsi3 == SELECT) {
                                                            // buka halaman ubah data diri
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

        warning = "";   // reset warning
    }

}

Penduduk isiFormulirPenduduk(Penduduk penduduk){
    bool openPage = true;
    int page = 1;
    string warning = "";

    while (openPage) {
        system("cls");
        cout << endl << endl << endl;

        cout << "\t         FORMULIR BIODATA PENDUDUK         \n" << endl;
        color(12); cout << setw(38) << warning << endl; color(7);   // notif peringatan
        
        // halaman 1
        if ( page == 1 ) {

            cout << "\tNama Lengkap \t: " << penduduk.namaLengkap << endl;  // nama lengkap
            cout << "\tNIK \t\t: "        << penduduk.nik         << endl;  // NIK

            if (penduduk.ttl == "") {   // ttl belum diisi
                // TTL
                string tempat;
                int tanggal, bulan, tahun, 
                    thnNow = timeNow()->tm_year + 1900;

                cout << "\n\tTempat/Tanggal Lahir" << endl;
                cout << "  \t   Tempat    : "; 
                color(11); getline(cin, tempat); fflush(stdin); color(8); 
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
                    warning = "Isian Anda salah!";
                    continue;
                } 

                penduduk.ttl = tempat + ", " + to_string(tanggal) + "/" + to_string(bulan) + "/" + to_string(tahun);
                penduduk.usia = timeNow()->tm_year + 1900 - tahun; // usia

            } else {    // ttl sudah diisi

                cout << "\n\tTempat/Tanggal Lahir" << endl;
                cout << "  \t   Tempat    : "; color(14); cout << "sudah diisi." << endl; color(7);

                color(8); cout << "\n\t   -- isi di bawah ini dengan angka   \n" << endl; color(7);

                cout << "  \t   Tanggal   : "; color(14); cout << "sudah diisi." << endl; color(7);
                cout << "  \t   Bulan     : "; color(14); cout << "sudah diisi." << endl; color(7);
                cout << "  \t   Tahun     : "; color(14); cout << "sudah diisi." << endl; color(7);
            }

                cout << "\n\tNo. Telepon\t: ";
                if (penduduk.telepon == "") { 
                    color(11); getline(cin, penduduk.telepon); color(7); fflush(stdin); 
                } else { 
                    color(14); cout << "sudah diisi" << endl;; color(7); 
                }

        cout << endl << endl << endl << endl << endl << endl;
                
        // halaman 2
        } else if ( page == 2 ) {

            string jalan;
            short int kecamatan, kelurahan;

            cout << "\tAlamat" << endl;
            cout << "\t   Jalan    : ";
            if (penduduk.alamat == "") { 
                color(11); getline(cin, jalan); fflush(stdin); color(7);

                if (jalan == "") {
                    warning = "Isian Anda salah";
                    continue;
                }

            } else { 
                color(14); cout << "sudah diisi" << endl; color(7);
            }

            color(8); 
            cout << "\n\t-- isi dengan memilih angka pada opsi\n"; color(7);

            cout << "\n\t   Kecamatan                                          "
                 << "\n\t   [1] Palaran             [6] Sungai Kunjang   "
                 << "\n\t   [2] Samarinda Seberang  [7] Sambutan         "
                 << "\n\t   [3] Samarinda Ulu       [8] Sungai Pinang    "
                 << "\n\t   [4] Samarinda Ilir      [9] Samarinda Kota   "
                 << "\n\t   [5] Samarinda Utara     [10] Loa Janan Ilir  "
                 << "\n\t   : ";

            if (penduduk.alamat == "") {
                color(11); cin >> kecamatan; clearBuffer(); color(7);

                if (kecamatan < 1 || kecamatan > 10) {
                    warning = "Isian Anda salah!";
                    continue;
                }

            } else {
                for (int i=0; i<10; i++) {
                    kecamatan = penduduk.alamat.find(KECAMATAN[i]);

                    if (kecamatan != -1) {
                        string kecamatanPenduduk = KECAMATAN[i];

                        for (int i=0; i<10; i++) {
                            if (KECAMATAN[i] == kecamatanPenduduk) {
                                kecamatan = i;
                                break;
                            }
                        }
                        break; 
                    }
                }

                color(14); cout << "sudah diisi" << endl; color(7); 
            }

            if ( kecamatan == 1) {
                cout << "\n\t   Kelurahan                                     "
                     << "\n\t   [1] Rawa Makmur         [5] Bantuas         "
                     << "\n\t   [2] Handil Bakti                            "
                     << "\n\t   [3] Bukuan                                  "
                     << "\n\t   [4] Simpang Pasir                           "
                     << "\n\t   : ";

            } else if (kecamatan == 2) {
                cout << "\n\t   Kelurahan                                     "
                     << "\n\t   [1] Sungai Keledang     [5] Gunung Panjang  "
                     << "\n\t   [2] Baqa                                    "
                     << "\n\t   [3] Mesjid                                  "
                     << "\n\t   [4] Mangkupalas                             "
                     << "\n\t   : ";

            } else if (kecamatan == 3) {
                cout << "\n\t   Kelurahan                                     "
                     << "\n\t   [1] Teluk Lerong Ilir   [5] Air Hitam       "
                     << "\n\t   [2] Jawa                [6] Dadi Mulya      "
                     << "\n\t   [3] Air Putih           [7] Gunung Kelua    "
                     << "\n\t   [4] Sidodadi            [8] Bukit Pinang    "
                     << "\n\t   : ";


            } else if (kecamatan == 4) {
                cout << "\n\t   Kelurahan                                     "
                     << "\n\t   [1] Selili              [5] Pelita          "
                     << "\n\t   [2] Sungai Dama                             "
                     << "\n\t   [3] Sidomulyo                               "
                     << "\n\t   [4] Sidodamai                               "
                     << "\n\t   : ";


            } else if (kecamatan == 5) {
                cout << "\n\t   Kelurahan                                     "
                     << "\n\t   [1] Sempaja Selatan     [5] Tanah Merah     "
                     << "\n\t   [2] Lempake             [6] Sempaja Barat   "   
                     << "\n\t   [3] Sungai Siring       [7] Sempaja Timur   "
                     << "\n\t   [4] Sempaja Utara       [8] Budaya Pampang  "
                     << "\n\t   : ";

            } else if (kecamatan == 6) {
                cout << "\n\t   Kelurahan                                     "
                     << "\n\t   [1] Loa Bakung          [5] Teluk Lerong Ulu"
                     << "\n\t   [2] Loa Buah            [6] Karang Asam Ilir"   
                     << "\n\t   [3] Karang Asam Ulu     [7] Karang Anyar    "
                     << "\n\t   [4] Lok Bahu                                "
                     << "\n\t   : ";

            } else if (kecamatan == 7) {
                cout << "\n\t   Kelurahan                                     "
                     << "\n\t   [1] Sungai Kapih        [5] Pulau Atas      "
                     << "\n\t   [2] Sambutan                                "
                     << "\n\t   [3] Makroman                                "
                     << "\n\t   [4] Sindang Sari                            "
                     << "\n\t   : ";

            } else if (kecamatan == 8) {
                cout << "\n\t   Kelurahan                                     "
                     << "\n\t   [1] Temindung Permai    [5] Bandara         "
                     << "\n\t   [2] Sungai Pinang Dalam                     "
                     << "\n\t   [3] Gunung Lingai                           "
                     << "\n\t   [4] Mugirejo                                "
                     << "\n\t   : ";

            } else if (kecamatan == 9) {
                cout << "\n\t   Kelurahan                                     "
                     << "\n\t   [1] Karang Mumus        [5] Sungai Pinang   "
                     << "\n\t   [2] Pelabuhan               Luar            "
                     << "\n\t   [3] Pasar Pagi                              "
                     << "\n\t   [4] Bugis                                   "
                     << "\n\t   : ";

            } else if (kecamatan == 10) {
                cout << "\n\t   Kelurahan                                     "
                     << "\n\t   [1] Simpang Tiga        [5] Rapak Dalam     "
                     << "\n\t   [2] Tani Aman                               "
                     << "\n\t   [3] Sengkotek                               "
                     << "\n\t   [4] Harapan Baru                            "
                     << "\n\t   : ";

            }
            
            if (penduduk.alamat != "") {
                color(14); cout << "sudah diisi" << endl; color(7); 
                
            } else {
                color(11); cin >> kelurahan; clearBuffer(); color(7);
                
                if (
                    kelurahan < 1 
                    || kecamatan == 1 && kelurahan > 5
                    || kecamatan == 2 && kelurahan > 6 
                    || kecamatan == 3 && kelurahan > 8
                    || kecamatan == 4 && kelurahan > 5
                    || kecamatan == 5 && kelurahan > 8
                    || kecamatan == 6 && kelurahan > 7
                    || kecamatan == 7 && kelurahan > 5
                    || kecamatan == 8 && kelurahan > 5
                    || kecamatan == 9 && kelurahan > 5
                    || kecamatan == 10 && kelurahan > 5
                ) {
                    warning = "Isian Anda salah!";
                    continue;
                }

                penduduk.alamat = jalan + "Kel. " + KELURAHAN[kecamatan-1][kelurahan-1] + "Kec. " + KECAMATAN[kecamatan-1];

            }

        // halaman 3
        } else if ( page == 3 ) {
            short int gender, agama, golDar, status;

            // gender
            cout << "\n\tJenis Kelamin \n"       
                 << "\t     [1] Laki-laki     [2] Perempuan           \n"   
                 << "\t     : "; 

            if (penduduk.gender == -1) { 

                color(11); cin >> gender; color(7);
                
                if (gender < 1 || gender > 2) {
                    warning = "Isian Anda salah!"; 
                    continue;
                }

                penduduk.gender = gender;

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

                color(11); cin >> agama; color(7);

                if (agama < 1 || agama > 4) {
                    warning = "Isian Anda salah!";
                    continue;
                }

                penduduk.agama = agama;

            } else { 
                color(14); cout << "sudah diisi"; color(7); 
            }

            // golongan darah
            cout << "\n\tGolongan Darah                                \n"
                 << "\t     [1] A         [3] AB                     \n"
                 << "\t     [2] B         [4] O                      \n"
                 << "\t     : ";

            if (penduduk.golDar == -1) { 
                color(11); cin >> golDar; color(7);

                if (golDar < 1 || golDar > 4) {
                    warning = "Isian Anda salah!";
                    continue;
                }

                penduduk.golDar = golDar;

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
                color(11); cin >> status; color(7);

                if (status < 1 || status > 4) {
                    warning = "Isian Anda salah!";
                    continue;
                } 

                penduduk.status = status;

            } else { 
                color(14); cout << "sudah diisi"; color(7); 
            }

            cout << endl << endl;

        }

        penduduk.tanggalPembaruan = hariIni();  // tgl data pembaruan diubah

        updateToTxt(penduduk);

        color(10); cout << "\n\t       Formulir telah berhasil diisi!    \n"; color(7);
        color(11); cout << "\n\t<= Kembali                     "; 
        
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
        
        warning = "";

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

// pemerintah :::::::::::::::::::::::::::::::::::::
void logInPemerintah() {
    system("cls");
    cout << endl << endl << endl;
    dekorasi(177, 41);

    cout << "\n\t  LOGIN PEMERINTAH -*-\n" << endl;

    string username, password;
    cout << "\t      Username   : "; cin >> username; fflush(stdin);
    cout << "\t      Password   : "; cin >> password; fflush(stdin);

    cout << endl << endl;

    // berhasil masuk
    if (username == "p" && password == "p") {
        
        color(10);
        cout << "\t            Log in berhasil!       \n\n" << endl; color(7);
        
        dekorasi(177, 41); getch();

        menuPemerintah();

    // gagal masuk
    } else {

        color(12);
        cout << "\t              Log in gagal!        \n\n" << endl; color(7);

        dekorasi(177, 41); getch();
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
                    openPage = false;           // berhenti buka halaman

                // tampilkan data penduduk
                } else if (opsi1 == SELECT) {
                                                // buka tampilkan data penduduk

                // ubah data penduduk
                } else if (opsi2 == SELECT) {
                                                // buka ubah data penduduk
                
                // tampilkan diagram
                } else if (opsi3 == SELECT) {
                    tampilkanDiagram();         // buka tampilkan diagram

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

        cout << "\t         HASIL PENDATAAN PENDUDUK    \n\n";
        cout << "\t" << kategori << endl << endl;

        if (page == 1) {
            diagramGender();

        } else if (page == 2) {
            diagramUsia();

        } else if (page == 3) {
            diagramAgama();

        } else if (page == 4) {
            diagramGolDar();

        } else if (page == 5) {
            diagramStatus();
        }
        
        color(SELECT); 
        cout << "\n\t<= Kembali                     "; 
        if (page >= 1 && page < 5) { 
            cout << "Berikutnya =>"; 
        } color(7);

        cout << endl << endl << endl;

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

            } else if (pilih == RIGHT && page == 2 || pilih == LEFT && page == 4) {
                page = 3; kategori = "Agama";

            } else if (pilih == RIGHT && page == 3 || pilih == LEFT && page == 5) {
                page = 4; kategori = "Golongan Darah";
        
            } else if (pilih == RIGHT && page == 4) {
                page = 5; kategori = "Status";

            } // end if 

        } // end if

    } // end while

}

// diagram
void diagramGender() {
    short int totalL = 0,
              totalP = 0;

    // hitung jumlah data per gender
    for (int i=0; i<banyakData(); i++) {
        if (dataPenduduk[i].gender == 0) {
            totalL++;
        } else if (dataPenduduk[i].gender == 1) {
            totalP++;
        }
    }

    diagram(0); cout << endl; 
    diagram((totalL*45)/(totalL+totalP), 9); cout << " " << (totalL*100)/(totalL+totalP) << "%" << endl;
    diagram(0); cout << endl;     
    diagram(0); cout << endl;              
    diagram(0); cout << endl;     
    diagram((totalP*45)/(totalL+totalP), 13); cout << " " << (totalP*100)/(totalL+totalP) << "%" << endl;
    diagram(0); cout << endl;     

    cout << endl;

    color(9);  cout << "\t    " << char(254); color(7); cout << " Laki-laki\n";
    color(13); cout << "\t    " << char(254); color(7); cout << " Perempuan";

    cout << endl << endl << endl;

    cout << "\n\t    Terdapat " << totalL+totalP << " data terverifikasi"
         << "\n\t    dari " << banyakData() << " penduduk terdaftar."
         << endl << endl;
}

void diagramUsia() {
    short int total1 = 0,
              total2 = 0,
              total3 = 0,
              total4 = 0,
              total5 = 0,
              total6 = 0,
              total7 = 0,
              total;

    // hitung jumlah data per usia
    for (int i=0; i<banyakData(); i++) {
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
        } else if (dataPenduduk[i].usia >= 50 && dataPenduduk[i].usia <= 59) {
            total6++;
        } else if (dataPenduduk[i].usia >= 60) {
            total7++;
        }
    }

    total = total1 + total2 + total3 + total4 + total5 + total6 + total7;

    diagram((total1*45)/total, 8); 
    cout << " " << (total1*100)/total << "%" << endl;

    diagram((total2*45)/total, 9); 
    cout << " " << (total2*100)/total << "%" << endl;
    
    diagram((total3*45)/total, 10); 
    cout << " " << (total3*100)/total << "%" << endl;
    
    diagram((total4*45)/total, 14); 
    cout << " " << (total4*100)/total << "%" << endl;
    
    diagram((total5*45)/total, 12); 
    cout << " " << (total5*100)/total << "%" << endl;
    
    diagram((total6*45)/total, 13); 
    cout << " " << (total6*100)/total << "%" << endl;
    
    diagram((total7*45)/total, 6); 
    cout << " " << (total7*100)/total << "%" << endl;
    
    cout << endl;

    color(8);  cout << "\t    " << char(254); color(7); cout << " 0-9 tahun";
    color(12); cout << "\t    "    << char(254); color(7); cout << " 40-49 tahun\n";
    color(9);  cout << "\t    " << char(254); color(7); cout << " 10-20 tahun";
    color(13); cout << "   "    << char(254); color(7); cout << " 50-59 tahun\n";
    color(10); cout << "\t    " << char(254); color(7); cout << " 20-29 tahun";
    color(6);  cout << "   "    << char(254); color(7); cout << " 60+ tahun\n";
    color(14); cout << "\t    " << char(254); color(7); cout << " 30-39 tahun";

    cout << endl;
    
    cout << "\n\t    Terdapat " << total << " data terverifikasi"
         << "\n\t    dari " << banyakData() << " penduduk terdaftar."
         << endl << endl;
}

void diagramAgama() {
    short int total1 = 0,
              total2 = 0,
              total3 = 0,
              total4 = 0,
              total5 = 0,
              total6 = 0,
              total;

    // hitung jumlah data per agama
    for (int i=0; i<banyakData(); i++) {
        if (dataPenduduk[i].agama == 0) {
            total1++;
        } else if (dataPenduduk[i].agama == 1) {
            total2++;
        } else if (dataPenduduk[i].agama == 2) {
            total3++;
        } else if (dataPenduduk[i].agama == 3) {
            total4++;
        } else if (dataPenduduk[i].agama == 4) {
            total5++;
        } else if (dataPenduduk[i].agama == 5) {
            total6++;
        }
    }

    total = total1 + total2 + total3 + total4 + total5 + total6;

    diagram((total1*45)/total, 10); 
    cout << " " << (total1*100)/total << "%" << endl;
    
    diagram((total2*45)/total, 13); 
    cout << " " << (total2*100)/total << "%" << endl;
    
    diagram((total3*45)/total, 8); 
    cout << " " << (total3*100)/total << "%" << endl;
    
    diagram((total4*45)/total, 14); 
    cout << " " << (total4*100)/total << "%" << endl;
    
    diagram((total5*45)/total, 9); 
    cout << " " << (total5*100)/total << "%" << endl;
    
    diagram((total6*45)/total, 12); 
    cout << " " << (total6*100)/total << "%" << endl;
    
    cout << endl << endl;

    color(10); cout << "\t    " << char(254); color(7); cout << " Islam";
    color(14); cout << "\t    " << char(254); color(7); cout << " Hindu\n";
    color(13); cout << "\t    " << char(254); color(7); cout << " Kristen";
    color(9);  cout << "\t    " << char(254); color(7); cout << " Buddha\n";
    color(8);  cout << "\t    " << char(254); color(7); cout << " Katolik";
    color(12); cout << "\t    " << char(254); color(7); cout << " Konghuchu";

    cout << endl << endl;
    
    cout << "\n\t    Terdapat " << total << " data terverifikasi"
         << "\n\t    dari " << banyakData() << " penduduk terdaftar."
         << endl << endl;    
}

void diagramGolDar() {
    short int total0 = 0,
              total1 = 0,
              total2 = 0,
              total3 = 0,
              total;

    // hitung jumlah data per agama
    for (int i=0; i<banyakData(); i++) {
        if (dataPenduduk[i].golDar == 0) {
            total0++;
        } else if (dataPenduduk[i].golDar == 1) {
            total1++;
        } else if (dataPenduduk[i].golDar == 2) {
            total2++;
        } else if (dataPenduduk[i].golDar == 3) {
            total3++;
        }
    }

    total = total0 + total1 + total2 + total3;


    diagram((total0*45)/total, 12); cout << " " << (total0*100)/total << "%" << endl;
    diagram(0); cout << endl;
    diagram((total1*45)/total, 9);  cout << " " << (total1*100)/total << "%" << endl;
    diagram(0); cout << endl;
    diagram((total2*45)/total, 13); cout << " " << (total2*100)/total << "%" << endl;
    diagram(0); cout << endl;
    diagram((total3*45)/total, 8);  cout << " " << (total3*100)/total << "%" << endl;
    
    cout << endl;

    color(12); cout << "\t    "   << char(254); color(7); cout << " A";
    color(13); cout << "\t\t  " << char(254); color(7); cout << " AB\n";
    color(9);  cout << "\t    "   << char(254); color(7); cout << " B";
    color(8);  cout << "\t\t  " << char(254); color(7); cout << " O\n";

    cout << endl << endl;
    
    cout << "\n\t    Terdapat " << total << " data terverifikasi"
         << "\n\t    dari " << banyakData() << " penduduk terdaftar."
         << endl << endl;    
}

void diagramStatus() {
    short int total0 = 0,
              total1 = 0,
              total2 = 0,
              total3 = 0,
              total;

    // hitung jumlah data per agama
    for (int i=0; i<banyakData(); i++) {
        if (dataPenduduk[i].status == 0) {
            total0++;
        } else if (dataPenduduk[i].status == 1) {
            total1++;
        } else if (dataPenduduk[i].status == 2) {
            total2++;
        } else if (dataPenduduk[i].status == 3) {
            total3++;
        }
    }

    total = total0 + total1 + total2 + total3;


    diagram((total0*45)/total, 3); cout << " " << (total0*100)/total << "%" << endl;
    diagram(0); cout << endl;
    diagram((total1*45)/total, 10);  cout << " " << (total1*100)/total << "%" << endl;
    diagram(0); cout << endl;
    diagram((total2*45)/total, 6); cout << " " << (total2*100)/total << "%" << endl;
    diagram(0); cout << endl;
    diagram((total3*45)/total, 13);  cout << " " << (total3*100)/total << "%" << endl;
    
    cout << endl;

    color(3);  cout << "\t    " << char(254); color(7); cout << " Belum kawin";
    color(6);  cout << "   "    << char(254); color(7); cout << " Cerai hidup\n";
    color(10); cout << "\t    " << char(254); color(7); cout << " Kawin";
    color(13); cout << "\t    " << char(254); color(7); cout << " Cerai mati\n";

    cout << endl << endl;
    
    cout << "\n\t    Terdapat " << total << " data terverifikasi"
         << "\n\t    dari " << banyakData() << " penduduk terdaftar."
         << endl << endl;    
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
    int index = indexNIK(penduduk.nik);

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


/* ----------------------------------- SORT & SEARCH ----------------------------------- */

// cari index NIK
int indexNIK(string nik) {
    for (int i=0; i<banyakData(); i++) {
        if (dataPenduduk[i].nik == nik) {
            return i;
        }
    }

    return -1;
}

// urutkan array tipe string
void insertionSort(string array[], string mode) {
    string key;
    int i, j,
        length = banyakData();

    for (i = 1; i < length; i++) {

        key = array[i];
        j = i-1;

        // ascending
        if (mode == "ASC") {
            while (j >= 0 && array[j].compare(key) > 0){
                array[j+1] = array[j];
                j = j-1;
            }

        // descending
        } else if (mode == "DESC"){
            while (j >= 0 && array[j].compare(key) < 0){
                array[j+1] = array[j];
                j = j-1;
            }
        }

        array[j+1] = key;
    }
}

// cari index array tipe string
int indexElemen(string array[], string cari) {  // binary search
    int length = sizeof(array)/sizeof(array[0]);

    for (int i=0; i<length; i++) {
        if (array[i] == cari) {
            return i;
        }
    }

    return -1;
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


/* ----------------------------------- TAMBAHAN ----------------------------------- */

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
    cout << "\t    " << char(221);
    color(kodeWarna);
    for (int i=0; i<jumlah; i++) {
        cout << char(219);
    }
    color(7);
}



