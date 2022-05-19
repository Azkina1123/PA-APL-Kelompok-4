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
#define RESET 7
#define SIGNED 3
#define UNSIGNED 0
#define FAIL 12
#define SUCCESS 10

// penyimpanan data
#define STORAGE 1000

// pilihan utk isi formulir
const string GENDER[] = {"Laki-Laki", "Perempuan"};
const string AGAMA[] = {"Islam", "Kristen", "Katolik", "Hindu", "Buddha", "Konghuchu"};
const string GOLDAR[] = {"A", "B", "AB", "O"};
const string STATUSKAWIN[] = {"Belum kawin", "Kawin", "Cerai hidup", "Cerai mati"};
const string STATUSHIDUP[] = {"Wafat", "Hidup"};
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


struct Alamat {
    string jalan;
    short int kecamatan = -1;
    short int kelurahan = -1;
};

// struct penduduk
struct Penduduk{
    string tanggalPembaruan;
    string namaLengkap;
    char nik[17];
    string password;
    string ttl;
    Alamat alamat;
    string telepon;
    int usia = -1;
    short int gender      = -1;       // index GENDER
    short int agama       = -1;        // index AGAMA
    short int golDar      = -1;       // index GOLDAR
    short int statusKawin = -1;       // index STATUS
    short int statusHidup = -1;
};

// data tersimpan
Penduduk dataPenduduk[STORAGE];

// tampilan mode penduduk
void menuMasukPenduduk();                           // menu login atau signup
void logInPenduduk();                               // log in penduduk
void signUpPenduduk();                              // sign up penduduk
void menuPenduduk(Penduduk penduduk);               // menu di akun penduduk
Penduduk isiFormulirPenduduk(Penduduk penduduk);    // isi formulir penduduk
bool cancelForm();
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
void diagramStatusKawin();                               // diagram berdasarkna status

// write & read txt
void importFromTxt();                               // ambil semua data dari txt
void appendToTxt(Penduduk penduduk);                // tambahkan data baru ke txt
void deleteToTxt(Penduduk penduduk);                // hapus data tertentu dari txt
void updateToTxt(Penduduk penduduk);                // ubah data tertentu di txt

// sorting & searching
int indexNIK(string nik);                           // cari index NIK
void bubbleSortTanggal(const char* mode);           // sorting berdasarkan tanggal pembaruan

// tambahan
void color(unsigned short warna);                   // ganti warna
void gotoxy(int x, int y);                          // ganti posisi
tm *timeNow();                                      // waktu sekarang
string hariIni();                                   // tanggal hari ini
int random();                                       // angka random
void clearBuffer();                                 // bersihkan buffer
bool logInBerhasil(string nik, string password);    // memastikan nik dan pw benar
bool isAngka(string str);                           // memastikan string diisi angka saja
int banyakData();                                   // banyak data tersimpan
void karakter(int ascii, int jumlah, int warna=7);  // dekorasi tampilan
void diagram(int jumlah, unsigned int warna=7);     // batang diagram
string alamatKecamatan(string alamat);              // kecamatan pada alamat
bool formulirTerisi(Penduduk penduduk);             // cek apakah formulir sudah diisi
bool isSpace(string str);
void hapusTulisan();


/*----------------------------------- MAIN PROGRAM -----------------------------------*/

int main(){
    // default
    bool running = true;        // program berjalan
    int notif = SIGNED,
        opsi1 = SELECT,         // warna opsi 1
        opsi2 = UNSELECT,       // warna opsi 2
        opsi3 = UNSELECT,       // warna opsi 3
        sign1, sign2, sign3;    // tanda

    while (running) {
        // tampilan ----------------------------------------

        // warna tanda saat memilih opsi
        sign1 = (opsi1 == SELECT) ? 3 : 0;
        sign2 = (opsi2 == SELECT) ? 3 : 0;
        sign3 = (opsi3 == SELECT) ? 3 : 0;

        system("cls");
        gotoxy(0, 3);  cout << "\t"; karakter(177, 41, 9);  // taruh dekorasi
        gotoxy(0, 17); cout << "\t"; karakter(177, 41, 9);  
        gotoxy(0, 6);                                       // reset posisi
                                    
        importFromTxt();        // ambil data dari txt

        cout << "\t    PENDATAAN PENDUDUK KOTA SAMARINDA    \n\n";  // judul
        cout << "\t        Jalankan program sebagai :       \n\n";  
        
        color(notif); cout << "\t\t\t  ---     \n\n";              // notif peringatan
        color(sign1); cout << "\t    "   << char(16); color(opsi1); cout << " Pemerintah " ;              // opsi 1
        color(sign2); cout << "      "   << char(16); color(opsi2); cout << " Penduduk\n\n";              // opsi 2
        color(sign3); cout << "\t\t\t\b" << char(16); color(opsi3); cout << " Keluar  \n\n";              // opsi 3
        color(RESET);


        // navigasi ----------------------------------------

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
            
            // tekan UP || RIGHT || DOWN || LEFT 
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
                notif = FAIL;
                continue;   // lanjutkan looping

                break;
        }

        notif = SIGNED;
    }

    cout << "Program dihentikan" << endl;

    return 0;

}


/* ----------------------------------- TAMPILAN ----------------------------------- */

// penduduk :::::::::::::::::::::::::::::::::::::
void menuMasukPenduduk() {

    // default
    bool looping = true;   // selama halaman dibuka
    short int notif = SIGNED,
              opsi1 = SELECT,     // login
              opsi2 = UNSELECT,   // sign up
              opsi3 = UNSELECT,   // kembali
              sign1, sign2, sign3;

    while (looping) {

        // tampilan ----------------------------------------

        // warna tanda saat memilih opsi
        sign1 = (opsi1 == SELECT) ? 3 : 0;
        sign2 = (opsi2 == SELECT) ? 3 : 0;
        sign3 = (opsi3 == SELECT) ? 3 : 0;

        system("cls");
        gotoxy(0, 3);  cout << "\t"; karakter(177, 41, 9);  // taruh dekorasi
        gotoxy(0, 17); cout << "\t"; karakter(177, 41, 9);  
        gotoxy(0, 6);                                       // reset posisi

        cout << "\t                PENDUDUK               \n\n";    // judul halaman
        cout << "\t              Pilih opsi :             \n\n";

        color(notif); cout << "\t\t\t  ---     \n\n";              // notif peringatan
        color(sign1); cout << "\t\t" << char(16); color(opsi1); cout << " Log In   "  ;              // opsi 1
        color(sign2); cout << "    " << char(16); color(opsi2); cout << " Sign Up\n\n";              // opsi 2
        color(sign3); cout << "\t\t" << char(16); color(opsi3); cout << " Kembali\n\n";              // opsi 3
        

        // navigasi ----------------------------------------

        // pilih menu
        char menu, pilih;
        menu = getch();

        // opsi yg tersedia
        switch (menu) {

            // tekan ENTER
            case ENTER:

                // kembali
                if (opsi1 == SELECT) {
                    logInPenduduk();    
                    
                // log in
                } else if (opsi2 == SELECT) {
                    signUpPenduduk();   

                // sign up
                } else if (opsi3 == SELECT) {
                    looping = false;  
                }

                break;

            // tekan UP || RIGHT || DOWN || LEFT
            case -32:
                pilih = getch();

                // pilih opsi 1
                if (
                    pilih == UP && opsi3 == SELECT ||
                    pilih == LEFT && opsi2 == SELECT
                ) {
                    opsi1 = SELECT;
                    opsi2 = UNSELECT;
                    opsi3 = UNSELECT;
                } 
                
                // pilih opsi 2
                else if (
                    pilih == RIGHT && opsi1 == SELECT ||
                    pilih == RIGHT && opsi3 == SELECT
                ) {
                    opsi1 = UNSELECT;
                    opsi2 = SELECT;
                    opsi3 = UNSELECT;

                // pilih opsi 3
                } else if (
                    pilih == DOWN && opsi1 == SELECT ||
                    pilih == DOWN && opsi2 == SELECT
                ) {
                    opsi1 = UNSELECT;
                    opsi2 = UNSELECT;
                    opsi3 = SELECT;
                }
                
                break;

            default:
                notif = FAIL;
                continue;   // lanjutkan looping
                
                break;
        }

        notif = SIGNED;       // reset warning

    }
}

void logInPenduduk() {
    system("cls");
    gotoxy(0, 3);  cout << "\t"; karakter(177, 41, 9);  // taruh dekorasi
    gotoxy(0, 17); cout << "\t"; karakter(177, 41, 9);  
    gotoxy(0, 6);                                       // reset posisi

    string nik, password;

    cout << "\t                  -*- LOGIN PENDUDUK\n\n\n";
    cout << "\t   NIK      : "; color(SELECT); cin >> nik;             fflush(stdin); color(RESET);
    cout << "\t   Password : "; color(SELECT); getline(cin, password); fflush(stdin); color(RESET);
    cout << endl << endl;

    // login berhasil
    if ( logInBerhasil(nik, password) ) {

        color(SUCCESS); cout << "\t            Log in berhasil!" << endl << endl; color(RESET); 
        getch();

        int index = indexNIK(nik);          // index nik
        menuPenduduk(dataPenduduk[index]);  // masuk ke akun sesuai nik
    
    // login gagal
    } else {

        color(FAIL); cout << "\t              Log in gagal! " << endl << endl; color(RESET); 
        getch();
    }

}

void signUpPenduduk() {
    system("cls");
    gotoxy(0, 3);  cout << "\t"; karakter(177, 41, 9);  // taruh dekorasi
    gotoxy(0, 17); cout << "\t"; karakter(177, 41, 9);                         
    gotoxy(0, 6);   // reset posisi

    Penduduk pendudukBaru;

    cout << "\t                  -*- SIGN UP PENDUDUK   \n\n" << endl;
    cout << "\t   Nama Lengkap : "; color(SELECT); getline(cin, pendudukBaru.namaLengkap); fflush(stdin); color(RESET);
    cout << "\t   NIK          : "; color(SELECT); cin.get(pendudukBaru.nik, 17);          clearBuffer(); color(RESET);
    cout << "\t   Password     : "; color(SELECT); getline(cin, pendudukBaru.password);    fflush(stdin); color(RESET);
    cout << endl;

    // gagal sign up - nik sudah ada
    if (indexNIK(pendudukBaru.nik) != -1) {
        color(FAIL); cout << "\t         NIK telah terdaftar!        \n\n" << endl;
    
    // gagal sign up - nik salah
    } else if (!isAngka(pendudukBaru.nik)) {
        color(FAIL); cout << "\t    NIK yang dimasukkan tidak valid! \n\n" << endl;

    // gagal sign up - nama dikosongkan
    } else if (isSpace(pendudukBaru.namaLengkap)) {
        color(FAIL); cout << "\t        Nama tidak boleh kosong! \n\n" << endl;

    // gagal sign up - password dikosongkan
    } else if (!isAngka(pendudukBaru.password)) {
        color(FAIL); cout << "\t      Password tidak boleh kosong! \n\n" << endl;

    // berhasil sign up
    } else {
        pendudukBaru.tanggalPembaruan = hariIni();  // tgl data diri diubah
        pendudukBaru.statusHidup = 1;
        appendToTxt(pendudukBaru);

        color(SUCCESS); cout << "\t    Akun telah berhasil didaftarkan! \n\n" << endl;
    }

    color(RESET); cout << endl;
    getch();

}

void menuPenduduk(Penduduk penduduk) {
    
    // default
    bool looping = true;    // selama buka halaman
    int opsi1 = SELECT,     // pilih opsi 0
        opsi2 = UNSELECT,
        opsi3 = UNSELECT,
        opsi4 = UNSELECT,
        sign1, sign2, sign3, sign4;

    while(looping) {
        // tampilan ----------------------------------------
        
        // warna tanda saat memilih opsi
        sign1 = (opsi1 == SELECT) ? 3 : 0;
        sign2 = (opsi2 == SELECT) ? 3 : 0;
        sign3 = (opsi3 == SELECT) ? 3 : 0;
        sign4 = (opsi4 == SELECT) ? 3 : 0;

        system("cls");
        gotoxy(0, 3);  cout << "\t"; karakter(177, 12, 9); cout << "    PENDUDUK    "; karakter(177, 13, 9);   // taruh dekorasi
        gotoxy(0, 17); cout << "\t"; karakter(177, 41, 9);  
        gotoxy(0, 5);                        

        cout << "\n\t    Selamat datang, " << penduduk.namaLengkap << "! " << char(2)
             << endl << endl;

        color(sign1); cout << "\t\t" << char(16); color(opsi1); cout << " Keluar                \n\n";  // opsi 0
        color(sign2); cout << "\t\t" << char(16); color(opsi2); cout << " Isi data diri         \n\n";  // opsi 1
        color(sign3); cout << "\t\t" << char(16); color(opsi3); cout << " Tampilkan data diri   \n\n";  // opsi 2
        color(sign4); cout << "\t\t" << char(16); color(opsi4); cout << " Ubah data diri      \n\n\n";  // opsi 3
        color(RESET);


        // navigasi ----------------------------------------

        // pilih menu
        char menu, pilih;
        menu = getch();

        // menu tersedia
        switch (menu) {

            // tekan ENTER
            case ENTER:
                // kembali
                if (opsi1 == SELECT) {
                    looping = false;                       

                // isi formulir
                } else if (opsi2 == SELECT) {
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

                // pilih opsi 1
                if (pilih == UP && opsi2 == SELECT) {
                    opsi1 = SELECT; 
                    opsi2 = UNSELECT; 
                
                // pilih opsi 2
                } else if (
                    pilih == DOWN && opsi1 == SELECT
                    || pilih == UP && opsi3 == SELECT
                ) {
                    opsi2 = SELECT; 
                    opsi1 = UNSELECT; 
                    opsi3 = UNSELECT; 
                
                // pilih opsi 3
                } else if (
                    pilih == DOWN && opsi2 == SELECT
                    || pilih == UP && opsi4 == SELECT
                ) {
                    opsi3 = SELECT; 
                    opsi2 = UNSELECT; 
                    opsi4 = UNSELECT;
                
                // pilih opsi 4
                } else if (pilih == DOWN && opsi3 == SELECT) {
                    opsi4 = SELECT;
                    opsi3 = UNSELECT; 
                }

                break;
        }   // end switch

    } // end while

}

Penduduk isiFormulirPenduduk(Penduduk penduduk) {
    bool openPage = true;
    string warning = "";
    
    short int page = 1,
              isiTgl = SIGNED,
              isiBln = UNSIGNED,
              isiThn = UNSIGNED;

    while (openPage) {
        system("cls");
        cout << endl << endl << endl;

        gotoxy(0, 3);  
        cout << "\t"; karakter(177, 2, 9);
        cout << " Formulir Biodata Penduduk "; karakter(177, 17, 9); // judul halaman
        cout << endl << endl;           // notif peringatan
        
        if (formulirTerisi(penduduk)){
            page = 0;
            color(SUCCESS); cout << "\n\n\t    Anda telah mengisi formulir ini." << endl;
        }

        // halaman 1
        if ( page == 1 ) {

            // nama dan NIK
            cout << "\tNama Lengkap \t: " << penduduk.namaLengkap << endl;  // nama lengkap
            cout << "\tNIK \t\t: "        << penduduk.nik         << endl;  // NIK
            
            cout << "\n\tTempat/Tanggal Lahir" << endl;
            cout << "  \t   Tempat    : \n";
            color(8); cout << "\n\t   -- isi di bawah ini dengan angka   \n" << endl; color(7);
            cout << "  \t   Tanggal   : \n";
            cout << "  \t   Bulan     : \n";
            cout << "  \t   Tahun     : \n";
            cout << "\n\tNo. Telepon\t: \n";

            color(SELECT);
            
            string tempat;
            int tahunIni = timeNow()->tm_year + 1900;

            while (isSpace(tempat)) {
                gotoxy(23, 9); hapusTulisan();
                gotoxy(23, 9); color(SELECT); getline(cin, tempat); fflush(stdin);
                
            }

            cout << endl << endl << endl;

            short int jawaban[3], jarak = 0;
            
            for (int i=0; i<3; i++) {

                while (true) {
                    gotoxy(23, 13+jarak); hapusTulisan(); 
                    gotoxy(23, 13+jarak); color(SELECT); cin >> jawaban[i];

                    if (
                        !cin.fail() && 
                        jawaban[i] > 0 &&
                        (
                            i == 0 && jawaban[i] <= 31 ||
                            i == 1 && jawaban[i] <= 12 ||
                            i == 2 && jawaban[i] >= 1920 && jawaban[i] <= tahunIni
                        )
                    ) { clearBuffer(); break; }
                    clearBuffer();
                }

                jarak += 1;
            }

            penduduk.ttl = tempat + ", " + to_string(jawaban[0]) + "-" 
                           + to_string(jawaban[1]) + "-" + to_string(jawaban[2]);
            penduduk.usia = tahunIni - jawaban[2]; // usia

            string noTelp;
            while (isSpace(noTelp) || !isAngka(noTelp)) {
                gotoxy(26, 17); hapusTulisan(); 
                gotoxy(26, 17); color(SELECT); getline(cin, noTelp); fflush(stdin);
            }

            penduduk.telepon = noTelp;
            color(RESET); 

            cout << endl << endl << endl << endl << endl << endl;
                
        // halaman 2
        } else if ( page == 2 ) {   // halaman 2

            // alamat
            cout << "\tAlamat        " << endl;
            cout << "\t   Jalan    : " << endl; color(8); 

            cout << "\n\t-- isi dengan memilih angka pada opsi\n"; color(7);
            // kecamatan
            cout << "\n\t   Kecamatan                                    "
                 << "\n\t   [1] Palaran             [6] Sungai Kunjang   "
                 << "\n\t   [2] Samarinda Seberang  [7] Sambutan         "
                 << "\n\t   [3] Samarinda Ulu       [8] Sungai Pinang    "
                 << "\n\t   [4] Samarinda Ilir      [9] Samarinda Kota   "
                 << "\n\t   [5] Samarinda Utara     [10] Loa Janan Ilir  "
                 << "\n\t   : ";

            // var sementara
            string jalan;
            short int noKec, noKel;

            while (isSpace(jalan)) {
                gotoxy(22, 6); hapusTulisan(); 
                gotoxy(22, 6); color(SELECT); getline(cin, jalan); fflush(stdin);
            }

            while (true) {
                gotoxy(13, 16); hapusTulisan(); 
                gotoxy(13, 16); color(SELECT); cin >> noKec;
                if (!cin.fail() && noKec > 0 && noKec <= 10) { clearBuffer(); break; }
                hapusTulisan; clearBuffer();
            }

            color(RESET);

            // kelurahan
            if (noKec == 1) {           // palaran
                cout << "\n\t   Kelurahan                                   "
                     << "\n\t   [1] Rawa Makmur         [5] Bantuas         "
                     << "\n\t   [2] Handil Bakti                            "
                     << "\n\t   [3] Bukuan                                  "
                     << "\n\t   [4] Simpang Pasir                           "
                     << "\n\t   : ";

            } else if (noKec == 2) {    // samarinda seberang
                cout << "\n\t   Kelurahan                                   "
                     << "\n\t   [1] Sungai Keledang     [5] Gunung Panjang  "
                     << "\n\t   [2] Baqa                                    "
                     << "\n\t   [3] Mesjid                                  "
                     << "\n\t   [4] Mangkupalas                             "
                     << "\n\t   : ";

            } else if (noKec == 3) {    // samarinda ulu
                cout << "\n\t   Kelurahan                                   "
                     << "\n\t   [1] Teluk Lerong Ilir   [5] Air Hitam       "
                     << "\n\t   [2] Jawa                [6] Dadi Mulya      "
                     << "\n\t   [3] Air Putih           [7] Gunung Kelua    "
                     << "\n\t   [4] Sidodadi            [8] Bukit Pinang    "
                     << "\n\t   : ";


            } else if (noKec == 4) {    // samarinda ilir
                cout << "\n\t   Kelurahan                                   "
                     << "\n\t   [1] Selili              [5] Pelita          "
                     << "\n\t   [2] Sungai Dama                             "
                     << "\n\t   [3] Sidomulyo                               "
                     << "\n\t   [4] Sidodamai                               "
                     << "\n\t   : ";


            } else if (noKec == 5) {    // samarinda utara
                cout << "\n\t   Kelurahan                                   "
                     << "\n\t   [1] Sempaja Selatan     [5] Tanah Merah     "
                     << "\n\t   [2] Lempake             [6] Sempaja Barat   "   
                     << "\n\t   [3] Sungai Siring       [7] Sempaja Timur   "
                     << "\n\t   [4] Sempaja Utara       [8] Budaya Pampang  "
                     << "\n\t   : ";

            } else if (noKec == 6) {    // sungai kunjang
                cout << "\n\t   Kelurahan                                   "
                     << "\n\t   [1] Loa Bakung          [5] Teluk Lerong Ulu"
                     << "\n\t   [2] Loa Buah            [6] Karang Asam Ilir"   
                     << "\n\t   [3] Karang Asam Ulu     [7] Karang Anyar    "
                     << "\n\t   [4] Lok Bahu                                "
                     << "\n\t   : ";

            } else if (noKec == 7) {    // sambutan
                cout << "\n\t   Kelurahan                                   "
                     << "\n\t   [1] Sungai Kapih        [5] Pulau Atas      "
                     << "\n\t   [2] Sambutan                                "
                     << "\n\t   [3] Makroman                                "
                     << "\n\t   [4] Sindang Sari                            "
                     << "\n\t   : ";

            } else if (noKec == 8) {    // sungai pinang
                cout << "\n\t   Kelurahan                                   "
                     << "\n\t   [1] Temindung Permai    [5] Bandara         "
                     << "\n\t   [2] Sungai Pinang Dalam                     "
                     << "\n\t   [3] Gunung Lingai                           "
                     << "\n\t   [4] Mugirejo                                "
                     << "\n\t   : ";

            } else if (noKec == 9) {    // samarinda kota
                cout << "\n\t   Kelurahan                                   "
                     << "\n\t   [1] Karang Mumus        [5] Sungai Pinang   "
                     << "\n\t   [2] Pelabuhan               Luar            "
                     << "\n\t   [3] Pasar Pagi                              "
                     << "\n\t   [4] Bugis                                   "
                     << "\n\t   : ";

            } else if (noKec == 10) {   // loa janan ilir
                cout << "\n\t   Kelurahan                                   "
                     << "\n\t   [1] Simpang Tiga        [5] Rapak Dalam     "
                     << "\n\t   [2] Tani Aman                               "
                     << "\n\t   [3] Sengkotek                               "
                     << "\n\t   [4] Harapan Baru                            "
                     << "\n\t   : ";

            }
            
            while (true) {
                gotoxy(13, 23); hapusTulisan(); 
                gotoxy(13, 23); color(SELECT); cin >> noKel;

                if (
                    !cin.fail() && 
                    noKel >= 1  &&
                    (
                        noKec == 1 && noKel <= 5 ||
                        noKec == 2 && noKel <= 6 ||
                        noKec == 3 && noKel <= 8 ||
                        noKec == 4 && noKel <= 5 ||
                        noKec == 5 && noKel <= 8 ||
                        noKec == 6 && noKel <= 7 ||
                        noKec == 7 && noKel <= 5 ||
                        noKec == 8 && noKel <= 5 ||
                        noKec == 9 && noKel <= 5 ||
                        noKec == 10 && noKel <= 5
                    ) 
                ) { clearBuffer(); break; }

                hapusTulisan; clearBuffer();
            }

            penduduk.alamat.jalan = jalan;
            penduduk.alamat.kecamatan = noKec - 1;
            penduduk.alamat.kelurahan = noKel - 1;

        // halaman 3
        } else if ( page == 3 ) {   // halaman 3

            cout << "\tJenis Kelamin \n"       
                 << "\t     [1] Laki-laki     [2] Perempuan          \n"   
                 << "\t     : \n"; 

            cout << "\n\tAgama \n"
                << "\t     [1] Islam     [3] Katolik   [5] Buddha    \n"
                << "\t     [2] Kristen   [4] Hindu     [6] Konghuchu \n"
                << "\t     : \n";

            cout << "\n\tGolongan Darah                              \n"
                 << "\t     [1] A         [3] AB                     \n"
                 << "\t     [2] B         [4] O                      \n"
                 << "\t     : \n";

            cout << "\n\tStatus \n"
                << "\t     [1] Belum kawin    [3] Cerai hidup       \n"
                << "\t     [2] Kawin          [4] Cerai mati        \n"
                << "\t     : \n";

            color(SELECT);
            short int jawaban[4];

            int jarak = 0;
            for (int i=0; i<4; i++) {
                while (true) {
                    gotoxy(15, 7+jarak); hapusTulisan(); 
                    gotoxy(15, 7+jarak); color(SELECT); cin >> jawaban[i];

                    if (
                        !cin.fail() && 
                        jawaban[i] > 0 &&
                        (
                            i == 0 && jawaban[i] <= 2 ||
                            i == 1 && jawaban[i] <= 6 ||
                            i == 2 && jawaban[i] <= 4 ||
                            i == 3 && jawaban[i] <= 4
                        )
                    ) { clearBuffer(); break; }

                    clearBuffer();
                }

                jarak += 5;
            }

            penduduk.gender = jawaban[0]-1;
            penduduk.agama = jawaban[1]-1;
            penduduk.golDar = jawaban[2]-1;
            penduduk.statusKawin = jawaban[3]-1;

            penduduk.tanggalPembaruan = hariIni();  // tgl data pembaruan diubah
            updateToTxt(penduduk);

            color(SUCCESS); cout << "\n\t       Formulir telah berhasil diisi!    \n" << endl;

        }

        gotoxy(0, 27);
        color(SELECT); cout << "\t<= Keluar                       "; 
        if (page == 1 || page == 2) { cout << "Berikutnya =>"; }

        color(RESET); cout << endl << endl;
        
        char opsi, key;
        opsi = getch();

        if (opsi == -32) {
            key = getch();

            if (key == LEFT) {

                if (!formulirTerisi(penduduk) && cancelForm()) {
                    openPage = false;
                    break;

                }
                page += 1;

            } else if (key == RIGHT && page == 1) {
                page = 2;

            } else if (key == RIGHT && page == 2) {
                page = 3;

            }
        }   
        
        warning = "";

    }

    return penduduk;
}

bool cancelForm() {
    bool openNotif = true;
    short int ya1 = 3, ya2,
              tidak1, tidak2;

    while (openNotif) {
        ya2    = (ya1 == 3) ? SELECT : UNSELECT;
        tidak1 = (ya1 == 0) ? 3 : 0;
        tidak2 = (ya2 == UNSELECT) ? SELECT : UNSELECT;

        gotoxy(8, 10);
        for (int i=0; i<32; i++) {
            if (i%2 == 0) {
                karakter(177, 2, 9);
            } else {
                cout << " ";
            }
        }

        gotoxy(8, 18);
        for (int i=0; i<32; i++) {
            if (i%2 == 0) {
                karakter(177, 2, 9);
            } else {
                cout << " ";
            }
        }
        color(7);
        gotoxy(8, 9); cout << "-----------------------------------------------";
        gotoxy(8, 11); cout << "|                                             |";
        gotoxy(8, 12); cout << "|     Keluar saat ini tidak akan menyimpan    |";
        gotoxy(8, 13); cout << "|          data yang telah Anda isi.          |";
        gotoxy(8, 14); cout << "|                                             |";
        gotoxy(8, 15); cout << "|       Apakah Anda yakin ingin keluar?       |";
        gotoxy(8, 16); cout << "|                                             |";
        gotoxy(19, 16); color(ya1);    cout << char(16); color(ya2);    cout << " Ya";
        gotoxy(35, 16); color(tidak1); cout << char(16); color(tidak2); cout << " Tidak";
        gotoxy(8, 17); cout << "|                                             |";
        gotoxy(8, 19); cout << "-----------------------------------------------";

        gotoxy(0, 22);
        color(RESET); cout << endl << endl;

        // respon user
        char opsi, key;
        opsi = getch();

        switch (opsi) {
            // tekan enter
            case ENTER:

                // batal hapus
                if (tidak2 == SELECT) {
                    openNotif = false;
                    break;

                // benar hapus
                } else if (ya2 == SELECT) {
                    return true;
                }

                break;

            // tekan tombol panah
            case -32:
                key = getch();

                // tunjuk ya
                if (tidak1 == 3 && key == LEFT) {
                    ya1 = 3; 

                // tunjuk tidak
                } else if (ya1 == 3 && key == RIGHT) {
                    ya1 = 0;
                }

                break;
                    
        } // end swicth case

    }

    return false;

}


void tampilkanData(Penduduk penduduk) {
    system("cls");
    cout << "Gender " << GENDER[penduduk.gender] << endl; 
    cout << "Agama " << AGAMA[penduduk.agama] << endl; 
    cout << "GolDar " << GOLDAR[penduduk.golDar] << endl; 
    cout << "Status " << STATUSKAWIN[penduduk.statusKawin] << endl; 
    getch();   
}


// pemerintah :::::::::::::::::::::::::::::::::::::
void logInPemerintah() {
    system("cls");
    gotoxy(0, 3);  cout << "\t"; karakter(177, 41, 9);  // taruh dekorasi
    gotoxy(0, 17); cout << "\t"; karakter(177, 41, 9);  
    gotoxy(0, 6);                        

    cout << "\n\t  LOGIN PEMERINTAH -*-\n\n" << endl;   // judul

    // masukkan username dan password
    string username, password;
    cout << "\t      Username   : "; cin >> username; fflush(stdin);
    cout << "\t      Password   : "; cin >> password; fflush(stdin);
    cout << endl << endl;

    // berhasil masuk
    if (username == "p" && password == "p") {
        
        color(SUCCESS); cout << "\t            Log in berhasil!       \n\n\n" << endl; 
        color(RESET);   getch();

        menuPemerintah();

    // gagal masuk
    } else {

        color(FAIL);  cout << "\t              Log in gagal!        \n\n\n" << endl; 
        color(RESET); getch();
    }
    
}

void menuPemerintah() {

    // default
    bool looping = true;
    string warning = "";
    int opsi1 = SELECT,
        opsi2 = UNSELECT,
        opsi3 = UNSELECT,
        opsi4 = UNSELECT,
        opsi5 = UNSELECT,
        sign1, sign2, sign3, sign4, sign5;

    while(looping) {
        // tampilan ----------------------------------------
        
        // warna tanda saat memilih opsi
        sign1 = (opsi1 == SELECT) ? 3 : 0;
        sign2 = (opsi2 == SELECT) ? 3 : 0;
        sign3 = (opsi3 == SELECT) ? 3 : 0;
        sign4 = (opsi4 == SELECT) ? 3 : 0;
        sign5 = (opsi5 == SELECT) ? 3 : 0;

        system("cls");
        gotoxy(0, 3);  cout << "\t"; karakter(177, 12, 9); cout << "    PEMERINTAH    "; karakter(177, 13, 9);   // taruh dekorasi
        gotoxy(0, 17); cout << "\t"; karakter(177, 41, 9);  
        gotoxy(0, 5);                       

        cout << "\n\t   Selamat datang, Pemerintah! " << char(2)                                    // judul
             << "\n\t   Total penduduk : " << banyakData() << "."
             << endl << endl << endl;

        color(sign1); cout << "\t\t" << char(16); color(opsi1); cout << " Keluar                       \n";  // opsi 0
        color(sign2); cout << "\t\t" << char(16); color(opsi2); cout << " Tampilkan data penduduk      \n";  // opsi 1
        color(sign3); cout << "\t\t" << char(16); color(opsi3); cout << " Perbarui status penduduk     \n";  // opsi 2
        color(sign4); cout << "\t\t" << char(16); color(opsi4); cout << " Hapus data penduduk          \n";  // opsi 3
        color(sign5); cout << "\t\t" << char(16); color(opsi5); cout << " Tampilkan hasil pendataan\n  \n";  // opsi 3
        color(RESET);

        // pilih menu
        char menu, pilih;
        menu = getch();

        switch (menu) {
            // tekan ENTER
            case ENTER:

                // kembali
                if (opsi1 == SELECT) {
                    looping = false;           

                // tampilkan data penduduk
                } else if (opsi2 == SELECT) {
                    //         

                // perbarui status
                } else if (opsi3 == SELECT) {
                    //                          
                
                // hapus data penduduk
                } else if (opsi4 == SELECT) {
                    //

                // tampilkan diagram data
                } else if (opsi5 == SELECT) {
                    tampilkanDiagram();         

                }

                break;

            // tekan UP || DOWN
            case -32:
                pilih = getch();

                // pilih opsi 1
                if (
                    pilih == UP && opsi1 == SELECT ||
                    pilih == UP && opsi2 == SELECT
                ) {
                    opsi1 = SELECT; 
                    opsi2 = UNSELECT; 
                
                // pilih opsi 2
                } else if (
                    pilih == DOWN && opsi1 == SELECT ||
                    pilih == UP && opsi3 == SELECT
                ) {
                    opsi1 = UNSELECT; 
                    opsi2 = SELECT; 
                    opsi3 = UNSELECT; 
                
                // pilih opsi 3
                } else if (
                    pilih == DOWN && opsi2 == SELECT ||
                    pilih == UP && opsi4 == SELECT
                ) {
                    opsi3 = SELECT; 
                    opsi2 = UNSELECT;
                    opsi4 = UNSELECT;
                
                // pilih opsi 4
                } else if (
                    pilih == DOWN && opsi3 == SELECT ||
                    pilih == UP   && opsi5 == SELECT
                ) {
                    opsi4 = SELECT;
                    opsi3 = UNSELECT; 
                    opsi5 = UNSELECT;

                // pilih opsi 5
                } else if (
                    pilih == DOWN && opsi4 == SELECT
                ) {
                    opsi4 = UNSELECT;
                    opsi5 = SELECT;
                }

                break;

            // opsi tidak tersedia
            default:
            warning = "Menu tidak tersedia!";
            continue;
            
            break;
        }

        warning = "";   // reset warning
    }

}

void tampilkanDiagram() {

    // default
    bool looping = true;
    string kategori = "Jenis Kelamin";
    int page = 1;

    while (looping) {
        system("cls");
        cout << endl << endl << endl;

        cout << "\t         HASIL PENDATAAN PENDUDUK    \n\n";  // judul
        cout << "\t" << kategori << endl << endl;               // kategori diagram

        if (page == 1) {            // berdasarkan gender
            diagramGender();

        } else if (page == 2) {     // berdasarkan usia
            diagramUsia();

        } else if (page == 3) {     // berdasarkan agama
            diagramAgama();

        } else if (page == 4) {     // berdasarkan golongan darah
            diagramGolDar();

        } else if (page == 5) {     // berdasarkan status
            diagramStatusKawin();
        }
        
        // ganti halaman
        color(SELECT); 
        cout << "\n\t<= Kembali                     "; 
        if (page >= 1 && page < 5) { cout << "Berikutnya =>"; } color(7);

        cout << endl << endl << endl;

        // intruksi 
        char opsi, pilih;
        opsi = getch();

        if (opsi == -32) {
            pilih = getch();

            // kembali ke menu
            if (pilih == LEFT && page == 1) {
                looping = false;
                break;

            // ke diagram selanjutnya - jenis kelamin
            } else if (pilih == LEFT && page == 2) {
                page = 1; kategori = "Jenis Kelamin";

            // ke diagram selanjutnya - usia
            } else if (
                pilih == RIGHT && page == 1 || 
                pilih == LEFT && page == 3
            ) {
                page = 2; kategori = "Usia";

            // ke diagram selanjutnya - agama
            } else if (
                pilih == RIGHT && page == 2 || 
                pilih == LEFT && page == 4
            ) {
                page = 3; kategori = "Agama";

            // ke diagram selanjutnya - golongan darah
            } else if (
                pilih == RIGHT && page == 3 || 
                pilih == LEFT && page == 5
            ) {
                page = 4; kategori = "Golongan Darah";
        
            // ke diagram selanjutnya - status
            } else if (pilih == RIGHT && page == 4) {
                page = 5; kategori = "Status";

            } // end if 

        } // end if

    } // end while

}

// diagram
void diagramGender() {
    float totalL = 0,
              totalP = 0;

    // hitung jumlah data per gender
    for (int i=0; i<banyakData(); i++) {
        if (dataPenduduk[i].gender == 0) {
            totalL++;
        } else if (dataPenduduk[i].gender == 1) {
            totalP++;
        }
    }

    cout << setiosflags(ios::fixed) << setprecision(1);

    // diagram batang
    diagram(0); cout << endl; 
    diagram((totalL*35)/(totalL+totalP), 9); 
    cout << " " <<  (totalL*100)/(totalL+totalP) << "%" << endl;
    diagram(0); cout << endl;     
    diagram(0); cout << endl;              
    diagram(0); cout << endl;     
    diagram((totalP*35)/(totalL+totalP), 13); cout << " " << (totalP*100)/(totalL+totalP) << "%" << endl;
    diagram(0); cout << endl;     

    cout << endl;

    // keterangan
    color(9);  cout << "\t    " << char(254); color(7); cout << " Laki-laki\n";
    color(13); cout << "\t    " << char(254); color(7); cout << " Perempuan";

    cout << endl << endl << endl;

    // data tersimpan 
    cout << "\n\t    Terdapat " << int(totalL+totalP) << " data terverifikasi"
         << "\n\t    dari " << banyakData() << " penduduk terdaftar."
         << endl << endl;
}

void diagramUsia() {
    float total1 = 0,
          total2 = 0,
          total3 = 0,
          total4 = 0,
          total5 = 0,
          total6 = 0,
          total7 = 0,
          total;

    // hitung jumlah data per usia
    for (int i=0; i<banyakData(); i++) {
        if (dataPenduduk[i].usia >= 0 && dataPenduduk[i].usia <= 9) {
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

    cout << setiosflags(ios::fixed) << setprecision(1);

    // diagram batang
    diagram((total1*35)/total, 8); 
    cout << " " << (total1*100)/total << "%" << endl;

    diagram((total2*35)/total, 9); 
    cout << " " << (total2*100)/total << "%" << endl;
    
    diagram((total3*35)/total, 10); 
    cout << " " << (total3*100)/total << "%" << endl;
    
    diagram((total4*35)/total, 14); 
    cout << " " << (total4*100)/total << "%" << endl;
    
    diagram((total5*35)/total, 12); 
    cout << " " << (total5*100)/total << "%" << endl;
    
    diagram((total6*35)/total, 13); 
    cout << " " << (total6*100)/total << "%" << endl;
    
    diagram((total7*35)/total, 6); 
    cout << " " << (total7*100)/total << "%" << endl;
    
    cout << endl;

    // keterangan
    color(8);  cout << "\t    " << char(254); color(7); cout << " 0-9 tahun";
    color(12); cout << "\t    " << char(254); color(7); cout << " 40-49 tahun\n";
    color(9);  cout << "\t    " << char(254); color(7); cout << " 10-20 tahun";
    color(13); cout << "   "    << char(254); color(7); cout << " 50-59 tahun\n";
    color(10); cout << "\t    " << char(254); color(7); cout << " 20-29 tahun";
    color(6);  cout << "   "    << char(254); color(7); cout << " 60+ tahun\n";
    color(14); cout << "\t    " << char(254); color(7); cout << " 30-39 tahun";

    cout << endl;
    
    // data tersimpan
    cout << "\n\t    Terdapat " << int(total) << " data terverifikasi"
         << "\n\t    dari " << banyakData() << " penduduk terdaftar."
         << endl << endl;
}

void diagramAgama() {
    float total1 = 0,
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

    cout << setiosflags(ios::fixed) << setprecision(1);

    // diagram batang
    diagram((total1*35)/total, 10); 
    cout << " " << (total1*100)/total << "%" << endl;
    
    diagram((total2*35)/total, 13); 
    cout << " " << (total2*100)/total << "%" << endl;
    
    diagram((total3*35)/total, 8); 
    cout << " " << (total3*100)/total << "%" << endl;
    
    diagram((total4*35)/total, 14); 
    cout << " " << (total4*100)/total << "%" << endl;
    
    diagram((total5*35)/total, 9); 
    cout << " " << (total5*100)/total << "%" << endl;
    
    diagram((total6*35)/total, 12); 
    cout << " " << (total6*100)/total << "%" << endl;
    
    cout << endl << endl;

    // keterangan
    color(10); cout << "\t    " << char(254); color(7); cout << " Islam";
    color(14); cout << "\t    " << char(254); color(7); cout << " Hindu\n";
    color(13); cout << "\t    " << char(254); color(7); cout << " Kristen";
    color(9);  cout << "\t    " << char(254); color(7); cout << " Buddha\n";
    color(8);  cout << "\t    " << char(254); color(7); cout << " Katolik";
    color(12); cout << "\t    " << char(254); color(7); cout << " Konghuchu";

    cout << endl << endl;
    
    // data tersimpan
    cout << "\n\t    Terdapat " << int(total) << " data terverifikasi"
         << "\n\t    dari " << banyakData() << " penduduk terdaftar."
         << endl << endl;    
}

void diagramGolDar() {
    float total0 = 0,
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

    cout << setiosflags(ios::fixed) << setprecision(1);

    // diagram batang
    diagram((total0*35)/total, 12); cout << " " << (total0*100)/total << "%" << endl;
    diagram(0); cout << endl;
    diagram((total1*35)/total, 9);  cout << " " << (total1*100)/total << "%" << endl;
    diagram(0); cout << endl;
    diagram((total2*35)/total, 13); cout << " " << (total2*100)/total << "%" << endl;
    diagram(0); cout << endl;
    diagram((total3*35)/total, 8);  cout << " " << (total3*100)/total << "%" << endl;
    
    cout << endl;

    // keterangan
    color(12); cout << "\t    " << char(254); color(7); cout << " A";
    color(13); cout << "\t\t  " << char(254); color(7); cout << " AB\n";
    color(9);  cout << "\t    " << char(254); color(7); cout << " B";
    color(8);  cout << "\t\t  " << char(254); color(7); cout << " O\n";

    cout << endl << endl;
    
    // data tersimpan
    cout << "\n\t    Terdapat " << int(total) << " data terverifikasi"
         << "\n\t    dari " << banyakData() << " penduduk terdaftar."
         << endl << endl;    
}

void diagramStatusKawin() {
    float total0 = 0,
              total1 = 0,
              total2 = 0,
              total3 = 0,
              total;

    // hitung jumlah data per agama
    for (int i=0; i<banyakData(); i++) {
        if (dataPenduduk[i].statusKawin == 0) {
            total0++;
        } else if (dataPenduduk[i].statusKawin == 1) {
            total1++;
        } else if (dataPenduduk[i].statusKawin == 2) {
            total2++;
        } else if (dataPenduduk[i].statusKawin == 3) {
            total3++;
        }
    }

    total = total0 + total1 + total2 + total3;

    cout << setiosflags(ios::fixed) << setprecision(1);

    // diagram batang
    diagram((total0*35)/total, 3);  cout << " " << (total0*100)/total << "%" << endl;
    diagram(0); cout << endl;
    diagram((total1*35)/total, 10); cout << " " << (total1*100)/total << "%" << endl;
    diagram(0); cout << endl;
    diagram((total2*35)/total, 6);  cout << " " << (total2*100)/total << "%" << endl;
    diagram(0); cout << endl;
    diagram((total3*35)/total, 13); cout << " " << (total3*100)/total << "%" << endl;
    
    cout << endl;

    // keterangan
    color(3);  cout << "\t    " << char(254); color(7); cout << " Belum kawin";
    color(6);  cout << "   "    << char(254); color(7); cout << " Cerai hidup\n";
    color(10); cout << "\t    " << char(254); color(7); cout << " Kawin";
    color(13); cout << "\t    " << char(254); color(7); cout << " Cerai mati\n";

    cout << endl << endl;
    
    // data tersimpan
    cout << "\n\t    Terdapat " << int(total) << " data terverifikasi"
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
            strcpy(penduduk.nik, baris.c_str());

        // password
        } else if (kolom == 4) {
            penduduk.password = baris;

        // tempat tanggal lahir
        } else if (kolom == 5) {
            penduduk.ttl = baris;

        // alamat
        } else if (kolom == 6) {
            penduduk.alamat.jalan = baris;

        } else if (kolom == 7) {
            penduduk.alamat.kecamatan = stoi(baris);

        } else if (kolom == 8) {
            penduduk.alamat.kelurahan = stoi(baris);

        // telepon
        } else if (kolom == 9) {
            penduduk.telepon = baris;

        // usia
        } else if (kolom == 10) {
            penduduk.usia = stoi(baris); 

        // gender
        } else if (kolom == 11) {
            penduduk.gender = stoi(baris);

        // agama
        } else if (kolom == 12) {
            penduduk.agama = stoi(baris);

        // golongan darah
        } else if (kolom == 13) {
            penduduk.golDar = stoi(baris);

        // status kawin
        } else if (kolom == 14) {
            penduduk.statusKawin = stoi(baris);

        // status hidup
        } else if (kolom == 15) {
            penduduk.statusHidup = stoi(baris);

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
         << penduduk.alamat.jalan << "\n" 
         << penduduk.alamat.kecamatan << "\n" 
         << penduduk.alamat.kelurahan << "\n"
         << penduduk.telepon << "\n"
         << penduduk.usia << "\n"
         << penduduk.gender << "\n"
         << penduduk.agama << "\n"
         << penduduk.golDar << "\n"
         << penduduk.statusKawin << "\n"
         << penduduk.statusHidup << "\n";

    file.close();

    importFromTxt();
}

void deleteFromTxt(Penduduk penduduk) {
    int length = banyakData();
    int index = indexNIK(penduduk.nik);

    ofstream output;
    output.open("data.txt");

    for (int i=0; i<STORAGE; i++) {
        if (string(dataPenduduk[i].nik) == string(penduduk.nik)) {
            continue;
        } else if (string(dataPenduduk[i].nik) == "") {
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

void color(unsigned short warna) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, warna);
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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

bool isAngka(string str) {
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

    if (isInteger == length && !isSpace(str)) {
        return true;
    } else {
        return false;
    }

}

int banyakData(){
    for (int i=0; i<STORAGE; i++) {
        if (string(dataPenduduk[i].nik) == "") {
            return i;
        }
    }
    return STORAGE;
}

void karakter(int ascii, int jumlah, int warna) {
    color(warna);
    for (int i=0; i<jumlah; i++) {
        cout << char(ascii);
    }
    color(RESET);
}

void diagram(int jumlah, unsigned int warna) {
    cout << "\t    " << char(221); color(warna);

    for (int i=0; i<jumlah; i++) {
        cout << char(219);
    }

    color(7);
}

bool formulirTerisi(Penduduk penduduk) {

    if (
        penduduk.ttl              == "" ||
        penduduk.alamat.jalan     == "" ||
        penduduk.alamat.kecamatan == -1 ||
        penduduk.alamat.kelurahan == -1 ||
        penduduk.telepon          == "" ||
        penduduk.gender           == -1 ||
        penduduk.agama            == -1 ||
        penduduk.golDar           == -1 ||
        penduduk.statusKawin      == -1
    ) {
        return false;
    }

    return true;
}

string alamatKecamatan(string alamat) {
    int indexKec = alamat.find("Kec.");

    int length = alamat.length();
    char alamatChar[length];

    strcpy(alamatChar, alamat.c_str());

    string kecamatanDitemukan;
    int index = 0;

    for (int i=0; i<length; i++) {

        if (i >= indexKec+5) {
            kecamatanDitemukan += alamatChar[i];
        }
    }

    return kecamatanDitemukan;
}

bool isSpace(string str) {
    if (str == "\t" || str == "\n" || str == "") {
        return true;
    }

    int length = str.length(),
        isSpasi = 0;
    char strChar[length], 
         spasi = ' ';

    strcpy(strChar, str.c_str());

    for (int i=0; i<length; i++) {
        if (strChar[i] == spasi) {
            isSpasi++;
        }
    }

    if (length == isSpasi) {
        return true;
    }

    return false;
}

void hapusTulisan() {
    color(0);
    for (int i=0; i<50; i++) {
        cout << char(219);
    }
    color(RESET);
}


