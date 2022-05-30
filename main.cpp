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
#define MARKED 8

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
const string HARI[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

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

/*----------------------------------- PROTOTYPE -----------------------------------*/

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
Penduduk ubahDataDiri(Penduduk penduduk);

// tampilan mode pemerintah
void logInPemerintah();                             // log in pemerintah
void menuPemerintah();                              // menu di akun pemerintah
void tampilkanDiagram();                            // tampilkan diagram data penduduk
void tampilkanDataPenduduk();

// diagram
void diagramKecamatan();
void diagramGender();                               // diagram berdasarkan gender
void diagramStatusHidup();
void diagramUsia();                                 // diagram berdasarkan usia
void diagramAgama();                                // diagram berdasarkan agama
void diagramGolDar();                               // diagram berdasarkan golongan darah
void diagramStatusKawin();                          // diagram berdasarkna status

// tampilan opsi
void tampilkanOpsi(string opsi);

// tabel
void tabel();

// write & read txt
void importFromTxt();                               // ambil semua data dari txt
void appendToTxt(Penduduk penduduk);                // tambahkan data baru ke txt
void deleteFromTxt(Penduduk penduduk);                // hapus data tertentu dari txt
void updateToTxt(Penduduk penduduk);                // ubah data tertentu di txt

// sorting & searching
int indexNIK(string nik);                           // cari index NIK
void bubbleSortTanggal(const char* mode);           // sorting berdasarkan tanggal pembaruan
int indexElemen(short int array[], int cari, int length);   // cari index elemen

// tambahan
void color(unsigned short warna);                   // ganti warna
void gotoxy(int x, int y);                          // ganti posisi
tm *timeNow();                                      // waktu sekarang
string hariIni();                                   // tanggal hari ini
int random();                                       // angka random
void clearCin();                                    // bersihkan buffer
bool logInBerhasil(string nik, string password);    // memastikan nik dan pw benar
int banyakData();                                   // banyak data tersimpan
void karakter(int ascii, int jumlah, int warna=7);  // dekorasi tampilan
void diagram(int jumlah, unsigned int warna=7);     // batang diagram
bool formulirTerisi(Penduduk penduduk);             // cek apakah formulir sudah diisi
void hapusTulisan(int panjang=50);
int banyakDataTerisi();                             // banyak data yg sudah diisi

// cek pengisian formulir
bool isAngka(string str);                           // memastikan string diisi angka saja
bool isSpace(string str);                           // memastikan string diisi spasi saja
bool isTanggal(int tanggal);                        // memastikan sesuai ketentuan tanggal
bool isBulan(int bulan);                            // memastikan sesuai ketentuan bulan
bool isTahun(int tahun);                            // memastikan sesuai ketentuan tahun
bool isNIK(char nik[]);                             // memastikan sesuai ketentuan nik
bool isTelp(string telp);                           // memastikan sesuai ketentuan telepon

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
        importFromTxt(); // ambil data dari txt

        // tampilan ----------------------------------------

        // warna tanda saat memilih opsi
        sign1 = (opsi1 == SELECT) ? 3 : 0;
        sign2 = (opsi2 == SELECT) ? 3 : 0;
        sign3 = (opsi3 == SELECT) ? 3 : 0;

        system("cls"); cout << endl << endl;
        cout << "\t"; karakter(177, 67, 9); cout << endl << endl << endl;

        cout << "\t\t\t PENDATAAN PENDUDUK KOTA SAMARINDA \n\n";  // judul
        cout << "\t\t\t     Jalankan program sebagai :  \n\n\n";  
        
        color(notif); cout << "\t\t\t\t       ---     \n\n\n";    // notif peringatan
        color(sign1); cout << "\t\t    "     << char(16); color(opsi1); cout << " Pemerintah" ;              // opsi 1
        color(sign2); cout << "\t\t  "       << char(16); color(opsi2); cout << " Penduduk\n\n";              // opsi 2
        color(sign3); cout << "\t\t\t\t    " << char(16); color(opsi3); cout << " Keluar  \n\n";              // opsi 3
        
        color(RESET); cout << endl;

        cout << "\t"; karakter(177, 67, 9);

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

    cout << ""
         << "Program dihentikan" << endl;

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

        system("cls"); cout << endl << endl;
        cout << "\t"; karakter(177, 67, 9); gotoxy(0, 18); 
        cout << "\t"; karakter(177, 67, 9); gotoxy(0, 5);   // reset posisi

        cout << "\t\t\t            PENDUDUK            \n\n";    // judul halaman
        cout << "\t\t\t          Pilih opsi :        \n\n\n";

        color(notif); cout << "\t\t\t\t       ---     \n\n\n";              // notif peringatan
        color(sign1); cout << "\t\t\t" << char(16); color(opsi1); cout << " Log In   "  ;              // opsi 1
        color(sign2); cout << "\t\t  " << char(16); color(opsi2); cout << " Sign Up\n\n";              // opsi 2
        color(sign3); cout << "\t\t\t" << char(16); color(opsi3); cout << " Kembali\n\n";              // opsi 3
        

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
    system("cls"); cout << endl << endl;
    cout << "\t"; karakter(177, 67, 9); gotoxy(0, 18); 
    cout << "\t"; karakter(177, 67, 9);  
    gotoxy(0, 5);                                      // reset posisi

    string nik, password;

    cout << "\t\t\t                      -*- LOGIN PENDUDUK\n\n\n" << endl;
    cout << "\t\t   NIK      : "; color(SELECT); cin >> nik;             fflush(stdin); color(RESET);
    cout << "\t\t   Password : "; color(SELECT); getline(cin, password); fflush(stdin); color(RESET);
    cout << endl << endl << endl;

    // login berhasil
    if ( logInBerhasil(nik, password) ) {

        color(SUCCESS); cout << "\t\t\t\t   Log in berhasil!" << endl << endl; color(RESET); 
        getch();

        int index = indexNIK(nik);          // index nik
        menuPenduduk(dataPenduduk[index]);  // masuk ke akun sesuai nik
    
    // login gagal
    } else {

        color(FAIL);    cout << "\t\t\t\t     Log in gagal! " << endl << endl; color(RESET); 
        getch();
    }

}

void signUpPenduduk() {
    system("cls"); cout << endl << endl;
    cout << "\t"; karakter(177, 67, 9); gotoxy(0, 18); 
    cout << "\t"; karakter(177, 67, 9);  
    gotoxy(0, 5); 

    Penduduk pendudukBaru;

    cout << "\t\t\t                      -*- SIGN UP PENDUDUK        \n\n\n" << endl;
    cout << "\t\t   Nama Lengkap : "; color(SELECT); getline(cin, pendudukBaru.namaLengkap); fflush(stdin); color(RESET);
    cout << "\t\t   NIK          : "; color(SELECT); cin.get(pendudukBaru.nik, 17);          clearCin();    color(RESET);
    cout << "\t\t   Password     : "; color(SELECT); getline(cin, pendudukBaru.password);    fflush(stdin); color(RESET);
    cout << endl << endl;

    // gagal sign up - nik sudah ada
    if (indexNIK(pendudukBaru.nik) != -1) {
        color(FAIL); cout << "\t\t\t       NIK telah terdaftar!        \n\n" << endl;
    
    // gagal sign up - nik salah
    } else if (!isNIK(pendudukBaru.nik)) {
        color(FAIL); cout << "\t\t\t NIK yang dimasukkan tidak valid! \n\n" << endl;

    // gagal sign up - nama dikosongkan
    } else if (isSpace(pendudukBaru.namaLengkap)) {
        color(FAIL); cout << "\t\t\t     Nama tidak boleh kosong!     \n\n" << endl;

    // gagal sign up - password dikosongkan
    } else if (isSpace(pendudukBaru.password)) {
        color(FAIL); cout << "\t\t\t   Password tidak boleh kosong!    \n\n" << endl;

    // berhasil sign up
    } else {
        pendudukBaru.tanggalPembaruan = hariIni();  // tgl data diri diubah
        pendudukBaru.statusHidup = 1;
        appendToTxt(pendudukBaru);

        color(SUCCESS); cout << "\t\t\t Akun telah berhasil didaftarkan! \n\n" << endl;
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

        system("cls"); cout << endl << endl;
        cout << "\t"; karakter(177, 25, 9); 
        cout << "    PENDUDUK    "; karakter(177, 26, 9); gotoxy(0, 18);    // taruh dekorasi
        cout << "\t"; karakter(177, 67, 9);  
        gotoxy(0, 4);                        

        cout << "\n\t     Selamat datang, " << penduduk.namaLengkap << "! " << char(2)
             << endl << endl << endl << endl;

        color(sign1); cout << "\t\t" << char(16); color(opsi1); cout << " Keluar                \n\n";  // opsi 0
        color(sign2); cout << "\t\t" << char(16); color(opsi2); cout << " Isi data diri         \n\n";  // opsi 1
        color(sign3); cout << "\t\t" << char(16); color(opsi3); cout << " Tampilkan data diri   \n\n";  // opsi 2
        color(sign4); cout << "\t\t" << char(16); color(opsi4); cout << " Ubah data diri      \n\n\n";  // opsi 3
        color(RESET);


        // navigasi ----------------------------------------

        // pilih menu
        char menu, key;
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
                } else if (opsi3 == SELECT) {   
                    tampilkanData(penduduk);                // buka halaman tampilkan data diri

                // ubah data diri
                } else if (opsi4 == SELECT) {
                    penduduk = ubahDataDiri(penduduk);      // buka halaman ubah data diri
                }

                break;

            // tekan UP || DOWN
            case -32:
                key = getch();

                if (key == UP && opsi2 == SELECT) {
                    opsi1 = SELECT; 
                    opsi2 = UNSELECT; 
                
                } else if (
                    key == DOWN && opsi1 == SELECT ||
                    key == UP && opsi3 == SELECT
                ) {
                    opsi2 = SELECT; 
                    opsi1 = UNSELECT; 
                    opsi3 = UNSELECT; 
                
                } else if (
                    key == DOWN && opsi2 == SELECT ||
                    key == UP && opsi4 == SELECT
                ) {
                    opsi3 = SELECT; 
                    opsi2 = UNSELECT; 
                    opsi4 = UNSELECT;
                
                } else if (key == DOWN && opsi3 == SELECT) {
                    opsi4 = SELECT;
                    opsi3 = UNSELECT; 
                }

                break;
        }   // end switch

    } // end while

}

Penduduk isiFormulirPenduduk(Penduduk penduduk) {
    bool openPage = true;
    short int page = 1;

    while (openPage) {
        system("cls");
        cout << endl << endl;

        // judul halaman
        cout << "\t"; karakter(177, 5, 9);
        cout << "  Formulir Biodata Penduduk  "; karakter(177, 35, 9); 
        cout << endl;
        
        if (formulirTerisi(penduduk)){
            page = 0;
            color(SUCCESS); cout << "\n\n\t\t\bAnda telah mengisi formulir ini." << endl;
        }

        // halaman 1
        if ( page == 1 ) {
            cout << endl;

            // nama dan NIK
            cout << "\tNama Lengkap \t: " << penduduk.namaLengkap << endl;  // nama lengkap
            cout << "\tNIK \t\t: "        << penduduk.nik         << endl;  // NIK
            
            // tempat tanggal lahir
            cout << "\n\tTempat/Tanggal Lahir" << endl;
            cout << "  \t   Tempat    :   \n";
            color(8); cout << "\n\t   -- isi di bawah ini dengan angka   \n" << endl; color(7);
            cout << "  \t   Tanggal   : \n\n";
            cout << "  \t   Bulan     : \n\n";
            cout << "  \t   Tahun     :   \n";
            cout << "\n\tNo. Telepon\t: \n";

            color(SELECT);
            
            // isi tempat
            string tempat;
            int tahunIni = timeNow()->tm_year + 1900;

            while (isSpace(tempat)) {
                gotoxy(23, 8); hapusTulisan();
                gotoxy(23, 8); color(SELECT); getline(cin, tempat); fflush(stdin);
                
            }

            cout << endl << endl << endl;

            // isi tanggal, bulan, tahun
            short int jawaban[3], jarak = 0;
            for (int i=0; i<3; i++) {

                // selama pengisian sesuai syarat
                while (true) {
                    gotoxy(23, 12+jarak); hapusTulisan(); 
                    gotoxy(23, 12+jarak); color(SELECT); cin >> jawaban[i];

                    if (
                        !cin.fail() &&
                        (
                            i == 0 && isTanggal(jawaban[i]) ||
                            i == 1 && isBulan(jawaban[i])   ||
                            i == 2 && isTahun(jawaban[i])
                        )
                    ) { clearCin(); break; }
                    clearCin();
                }

                jarak += 2;
            }

            // simpan ttl
            penduduk.ttl = tempat + ", " + to_string(jawaban[0]) + "-" 
                           + to_string(jawaban[1]) + "-" + to_string(jawaban[2]);
            // simpan usia
            penduduk.usia = tahunIni - jawaban[2]; // usia

            // isi nomor telepon
            string noTelp;
            while (!isTelp(noTelp)) {
                gotoxy(26, 18); hapusTulisan(); 
                gotoxy(26, 18); color(SELECT); getline(cin, noTelp); fflush(stdin);
            }

            // simpan nomor telepon
            penduduk.telepon = noTelp;
            color(RESET); 
                

        } else if ( page == 2 ) {   // halaman 2
            cout << endl;

            // alamat
            cout << "\tAlamat        " << endl;
            cout << "\t   Jalan    : " << endl; color(8); 

            cout << "\n\t-- isi dengan memilih angka pada opsi\n"; color(7);
            
            // kecamatan
            tampilkanOpsi("Kecamatan");

            // var sementara
            string jalan;
            short int noKec, noKel;

            while (isSpace(jalan)) {
                gotoxy(22, 5); hapusTulisan(); 
                gotoxy(22, 5); color(SELECT); getline(cin, jalan); fflush(stdin);
            }

            while (true) {
                gotoxy(13, 14); hapusTulisan(); 
                gotoxy(13, 14); color(SELECT); cin >> noKec;
                if (!cin.fail() && noKec > 0 && noKec <= 10) { clearCin(); break; }
                hapusTulisan; clearCin();
            }

            color(RESET);

            // kelurahan
            tampilkanOpsi(KECAMATAN[noKec]);
            
            while (true) {
                gotoxy(13, 20); hapusTulisan(); 
                gotoxy(13, 20); color(SELECT); cin >> noKel;

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
                ) { clearCin(); break; }

                clearCin();
            }

            penduduk.alamat.jalan = jalan;
            penduduk.alamat.kecamatan = noKec - 1;
            penduduk.alamat.kelurahan = noKel - 1;

        // halaman 3
        } else if ( page == 3 ) {   // halaman 3
            tampilkanOpsi("Jenis Kelamin");
            tampilkanOpsi("Agama");
            tampilkanOpsi("Golongan Darah");
            tampilkanOpsi("Status Perkawinan");

            color(SELECT);
            short int jawaban[4];

            int jarak = 0;
            for (int i=0; i<4; i++) {
                while (true) {
                    gotoxy(15, 6+jarak); hapusTulisan(); 
                    gotoxy(15, 6+jarak); color(SELECT); cin >> jawaban[i];

                    if (
                        !cin.fail() && 
                        jawaban[i] > 0 &&
                        (
                            i == 0 && jawaban[i] <= 2 ||
                            i == 1 && jawaban[i] <= 6 ||
                            i == 2 && jawaban[i] <= 4 ||
                            i == 3 && jawaban[i] <= 4
                        )
                    ) { clearCin(); break; }

                    clearCin();
                }

                if (i == 0) { jarak += 5; }
                else { jarak += 4; }
            }

            penduduk.gender = jawaban[0]-1;
            penduduk.agama = jawaban[1]-1;
            penduduk.golDar = jawaban[2]-1;
            penduduk.statusKawin = jawaban[3]-1;

            penduduk.tanggalPembaruan = hariIni();  // tgl data pembaruan diubah
            updateToTxt(penduduk);

            color(SUCCESS); cout << "\n\t       Formulir telah berhasil diisi!    \n" << endl;

        }

        gotoxy(0, 23);
        color(SELECT); cout << "\t<= Keluar                       "; 
        if (page == 1 || page == 2) { cout << "  Lanjutkan =>     "; }

        color(RESET); cout << endl << endl;


        // navigasi ----------------------------------------
        
        char opsi, key;
        opsi = getch();

        if (opsi == -32) {
            key = getch();

            if (key == LEFT) {

                
                if (
                    !formulirTerisi(penduduk) && cancelForm() || // keluar saat belum selesai isi
                    formulirTerisi(penduduk)                     // keluar saat sudah selesai isi
                ) {
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

        // batas atas
        gotoxy(15, 8);
        for (int i=0; i<32; i++) {
            if (i%2 == 0) { karakter(177, 2, 9); } 
            else          { cout << " "; }
        }

        // batas bawah
        gotoxy(15, 16);
        for (int i=0; i<32; i++) {
            if (i%2 == 0) { karakter(177, 2, 9); } 
            else          { cout << " "; }
        }

        color(RESET); gotoxy(15, 7);  
        cout << "-----------------------------------------------\n\t\t";
        cout << "|                                             |\n\t\t";
        cout << "|     Keluar saat ini tidak akan menyimpan    |\n\t\t";
        cout << "|          data yang telah Anda isi.          |\n\t\t";
        cout << "|                                             |\n\t\t";
        cout << "|       Apakah Anda yakin ingin keluar?       |\n\t\t";
        cout << "|                                             |\n\t\t";
        cout << "|                                             |\n\t\t";
        cout << "-----------------------------------------------\n\t\t";

        gotoxy(28, 14); color(ya1);    cout << char(16); color(ya2);    cout << " Ya";
        gotoxy(40, 14); color(tidak1); cout << char(16); color(tidak2); cout << " Tidak";

        gotoxy(0, 22);
        color(RESET); cout << endl << endl;

        // respon user
        char opsi, key;
        opsi = getch();

        switch (opsi) {
            // tekan enter
            case ENTER:

                // tidak
                if (tidak2 == SELECT) {
                    openNotif = false;
                    break;

                // ya
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
    cout << "Kec " << KECAMATAN[penduduk.alamat.kecamatan] << penduduk.alamat.kecamatan << endl; 
    
    getch();   
}

Penduduk ubahDataDiri(Penduduk penduduk) {
    bool openPage = true,
         editing = false;
    short int index,
              warna[11] = {
                  SELECT, UNSELECT, UNSELECT, UNSELECT, UNSELECT,
                  UNSELECT, UNSELECT, UNSELECT, UNSELECT, UNSELECT,
                  UNSELECT
              },
              sign[11] = {
                  SIGNED, UNSIGNED, UNSIGNED, UNSIGNED, UNSIGNED,
                  UNSIGNED, UNSIGNED, UNSIGNED, UNSIGNED, UNSIGNED,
                  UNSIGNED
              };

    string opsi[11] = {
        "Nama Lengkap", "NIK",    "Password", "Tempat, Tanggal Lahir", "Jenis Kelamin", 
        "Telepon",      "Alamat", "Agama",    "Golongan Darah",        "Status Perkawinan",
        "Kembali"
    };

    while (openPage) {
        string dataStr[] = {
            penduduk.namaLengkap,                                               // 0
            penduduk.nik,                                                       // 1
            penduduk.password,                                                  // 2
            penduduk.ttl,                                                       // 3
            GENDER[penduduk.gender],                                            // 4
            penduduk.telepon,                                                   // 5
            penduduk.alamat.jalan,                                              // 6
            KELURAHAN[penduduk.alamat.kecamatan][penduduk.alamat.kelurahan],    // 7
            KECAMATAN[penduduk.alamat.kecamatan],                               // 8
            AGAMA[penduduk.agama],                                              // 9 
            GOLDAR[penduduk.golDar],                                            // 10
            STATUSKAWIN[penduduk.statusKawin]                                   // 11
        };

        system("cls");
        cout << endl << endl;

        // judul halaman
        cout << "\t"; karakter(177, 5, 9);
        cout << "  Mengubah Biodata Diri  "; karakter(177, 40, 9); 

        // jika belum isi formulir
        if (!formulirTerisi(penduduk)) {
            color(14); cout << "\n\n\t\t\bHarap isi formulir terlebih dahulu." << endl;
            goto kembali;
        }

        // tampilkan opsi data yg ingin diubah
        for (int i=0; i<10; i++) {

            if (i == 0 || i == 5) { gotoxy(0, 3); }

            if (i < 5) { cout << "\n\n\t\t"; }
            else       { cout << "\n\n\t\t\t\t\t\t"; }

            color(sign[i]);  cout << char(16) << " "; 
            color(warna[i]); cout << opsi[i];

        }
        
        color(8);
        cout << "\n\n\n\t\t\t"
             << "[Tekan ENTER untuk mengubah data]" 
             << endl; color(RESET);

        // jika sedang tidak mengedit
        if (!editing) {

            // tampilkan isian data yg ingin diubah
            for (int i=0; i<10; i++) {
                
                // jika ditunjuk
                if (warna[i] == SELECT || sign[i] == MARKED) {

                    // alamat
                    if (i == 6) {
                        cout << "\n\t\t Jalan       \t: " << dataStr[6]
                             << "\n\t\t Kelurahan   \t: " << dataStr[7]
                             << "\n\t\t Kecamatan   \t: " << dataStr[8];

                    // 
                    } else if (i > 6) {
                        cout << "\n\t\t " << opsi[i] << " \t: " << dataStr[i+2];

                    } else {
                        cout << "\n\t\t " << opsi[i] << " \t: " << dataStr[i];

                    } // end if
                    
                } // end if

            }

        } else {

            // ganti tempat tanggal lahir
            if (index == 3) {

                // var untuk pengisian formulir
                string tempat,
                       keterangan[3] = {"Tanggal", "Bulan", "Tahun"};
                int jawaban[3];

                // tempat
                cout << "\n\t\t Tempat   \t: ";

                // isi tempat
                while (isSpace(tempat)) {
                    gotoxy(34, 18); hapusTulisan();
                    gotoxy(34, 18); getline(cin, tempat); fflush(stdin);
                }

                // tanggal, bulan, tahun
                for (int i=0; i<3; i++) {
                    cout << "\t\t " << keterangan[i] << "   \t: ";

                    // isi tanggal / bulan / tahun
                    while (true) {
                        gotoxy(34, 19+i); hapusTulisan();
                        gotoxy(34, 19+i); cin >> jawaban[i]; 

                        // jika isian telah benar, berhenti isi
                        if (
                            !cin.fail() && 
                            jawaban[i] > 0 &&
                            (
                                i == 0 && isTanggal(jawaban[i]) ||
                                i == 1 && isBulan(jawaban[i])   ||
                                i == 2 && isTahun(jawaban[i])
                            )
                        ) { clearCin(); break; }
                        clearCin();

                    }
                }

                // simpan ttl
                penduduk.ttl = tempat + ", "                    // tempat
                                + to_string(jawaban[0]) + "-"   // tanggal
                                + to_string(jawaban[1]) + "-"   // bulan
                                + to_string(jawaban[2]);        // tahun

                // ubah usia
                int tahunIni = timeNow()->tm_year + 1900;
                penduduk.usia = tahunIni - jawaban[2];

            // ganti alamat
            } else if (index == 6) {

                // var untuk pengisian
                string jalan;
                int noKec, noKel;
                
                // jalan
                cout << "\n\t\t Jalan   \t: ";
                while (isSpace(jalan)) {
                    gotoxy(34, 18); hapusTulisan();
                    gotoxy(34, 18); getline(cin, jalan); fflush(stdin);
                }

                // kecamatan
                gotoxy(0, 17);
                tampilkanOpsi("Kecamatan");

                // isi kecamatan
                while (true) {
                    gotoxy(15, 23); hapusTulisan();
                    gotoxy(15, 23); cin >> noKec; 

                    // jika isian sudah benar, berhenti isi;
                    if (!cin.fail() && noKec >= 1 && noKec <= 10) { clearCin; break; }
                    clearCin();

                }

                // kelurahan
                gotoxy(10, 22); hapusTulisan(100);
                gotoxy(0, 17);  tampilkanOpsi(KECAMATAN[noKec]);

                // isi kelurahan
                while (true) {
                    gotoxy(15, 22); hapusTulisan();
                    gotoxy(15, 22); cin >> noKel; 

                    // jika isian sudah benar, berhenti isi
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
                    ) { clearCin(); break; }   

                    clearCin();
                }

                // ubah alamat
                penduduk.alamat.jalan = jalan;
                penduduk.alamat.kecamatan = noKec-1;
                penduduk.alamat.kelurahan = noKel-1;

            // gender, agama, golongan darah, status perkawinan
            } else if (index == 4 || index == 7 || index == 8 || index == 9){
                
                int isiInt;
                cout << endl; tampilkanOpsi(opsi[index]);

                while (true) {
                    
                    // letak isian agama
                    if (index == 7) {
                        gotoxy(15, 22); hapusTulisan();
                        gotoxy(15, 22); cin >> isiInt; 

                    // letak isian gender, golongan darah, status perkawinan
                    } else {
                        gotoxy(15, 21); hapusTulisan();
                        gotoxy(15, 21); cin >> isiInt; 

                    }

                    // jika isian sudah benar, berhenti isi;
                    if (
                        !cin.fail() && 
                        isiInt >= 1 && 
                        (
                            index == 4 && isiInt <= 2 ||    // syarat jenis kelamin
                            index == 7 && isiInt <= 6 ||    // syarat agama
                            index == 8 && isiInt <= 4 ||    // syarat golongan darah
                            index == 9 && isiInt <= 4       // syarat status perkawinan
                        )   
                    ) { clearCin; break; }
                    clearCin();

                }

                if      (index == 4) { penduduk.gender      = isiInt-1; }
                else if (index == 7) { penduduk.agama       = isiInt-1; }
                else if (index == 8) { penduduk.golDar      = isiInt-1; }
                else if (index == 9) { penduduk.statusKawin = isiInt-1; }
            
            // nama, password, telepon, nik
            } else {
                cout << "\n\t\t " << opsi[index] << " \t: ";
                
                // nama, password, telepon
                if (index == 0 || index == 2 || index == 5) {
                    string isiStr;

                    while (isSpace(isiStr) || index == 5 && !isTelp(isiStr)) {
                        gotoxy(34, 18); hapusTulisan();
                        gotoxy(34, 18); getline(cin, isiStr); fflush(stdin);
                    }

                    if      (index == 0) { penduduk.namaLengkap = isiStr; }
                    else if (index == 2) { penduduk.password    = isiStr; }
                    else if (index == 5) { penduduk.telepon     = isiStr; }
                
                // nik
                } else {
                    char nik[17];
                    
                    while (!isNIK(nik)) {
                        gotoxy(27, 18); hapusTulisan();
                        gotoxy(27, 18); cin.get(nik, 17); clearCin();
                    }

                    strcpy(penduduk.nik, nik);
                
                } // end if

            } // end if
            
            editing = false; 
            warna[index] = SELECT; 
            sign[index]  = SIGNED;
            penduduk.tanggalPembaruan = hariIni();
            updateToTxt(penduduk);
            continue;
        }

        kembali:
        gotoxy(0, 23);

        color(warna[10]); cout << "\tKembali" << endl;
        color(sign[10]);  cout << "\t  <=   " << endl;

        cout << endl << endl; color(RESET);
        
        // navigasi ----------------------------------------------------------
        char opsi, key;
        opsi = getch();

        switch (opsi) {

            case ENTER:

                index = indexElemen(warna, SELECT, 11);
                warna[index] = UNSELECT;
                sign[index] = MARKED;
                editing = true;

                break;

            case -32:
            key = getch();

            index = indexElemen(warna, SELECT, 11);


            if (key == DOWN && index+1 <= 10) {
                warna[index] = UNSELECT;
                sign[index]  = UNSIGNED;

                if (index == 4) { index += 6; }
                else            { index += 1; }

            } else if (key == RIGHT && index+5 < 10) {
                warna[index] = UNSELECT;
                sign[index]  = UNSIGNED;

                index += 5;
            
            } else if (key == UP && index-1 >= 0) {
                warna[index] = UNSELECT;
                sign[index]  = UNSIGNED;

                if (index == 10) { index -= 6; }
                else             { index -= 1; }

            } else if (key == LEFT && index-5 >= 0) {
                if (index == 10) { openPage = false; break; }

                warna[index] = UNSELECT;
                sign[index]  = UNSIGNED;

                index -= 5;
            }
            
            warna[index] = SELECT;
            sign[index] = SIGNED;
        
        } // end switch

    }

    return penduduk;
}



// pemerintah :::::::::::::::::::::::::::::::::::::
void logInPemerintah() {
    system("cls"); cout << endl << endl;
    cout << "\t"; karakter(177, 67, 9); gotoxy(0, 18); 
    cout << "\t"; karakter(177, 67, 9);  
    gotoxy(0, 5);                                      // reset posisi
                        
 
    cout << "\t\tLOGIN PEMERINTAH -*-  \n\n\n" << endl;   // judul

    // masukkan username dan password
    string username, password;
    cout << "\t\t    Username   : "; cin >> username; fflush(stdin);
    cout << "\t\t    Password   : "; cin >> password; fflush(stdin);
    cout << endl << endl << endl;

    // berhasil masuk
    if (username == "p" && password == "p") {
        
        color(SUCCESS); cout << "\t\t\t         Log in berhasil!       \n\n\n" << endl; 
        color(RESET);   getch();

        menuPemerintah();

    // gagal masuk
    } else {

        color(FAIL);    cout << "\t\t\t           Log in gagal!        \n\n\n" << endl; 
        color(RESET); getch();
    }
    
}

void menuPemerintah() {

    // var yg digunakan
    bool looping = true;
    short int opsi[5] = {SELECT, UNSELECT, UNSELECT, UNSELECT, UNSELECT},   // warna tulisan menu
              index;                                                        // index warna yg di-SELECT

    while(looping) {
        // tampilan ---------------------------------------------------------------------------

        // warna tanda
        int sign[5] = {
            (opsi[0] == SELECT) ? SIGNED : UNSIGNED,    // tampilkan data penduduk
            (opsi[1] == SELECT) ? SIGNED : UNSIGNED,    // tampilkan diagram
            (opsi[2] == SELECT) ? SIGNED : UNSIGNED,    // perbarui status hidup
            (opsi[3] == SELECT) ? SIGNED : UNSIGNED,    // hapus data penduduk
            (opsi[4] == SELECT) ? SIGNED : UNSIGNED     // keluar
        };

        system("cls");

        // judul dan dekorasi
        gotoxy(0, 2);  cout << "\t"; karakter(177, 24, 9); cout << "    PEMERINTAH    "; karakter(177, 25, 9);   // taruh dekorasi
        gotoxy(0, 18); cout << "\t"; karakter(177, 67, 9);  
        
        gotoxy(0, 4);   // reset posisi                  

        // judul
        cout << "\n\t    Selamat datang, Pemerintah! " << char(2)                                   
             << "\n\t    Total penduduk : " << banyakData() << "."
             << endl << endl << endl;

        // tampilkan opsi
        color(sign[0]); cout << "\t\t" << char(16); 
        color(opsi[0]); cout << " Tampilkan data" << "\n\t\t "
                             << " penduduk      " << "\n\n";  // opsi 1

        color(sign[1]); cout << "\t\t" << char(16); 
        color(opsi[1]); cout << " Tampilkan hasil" << "\n\t\t "
                             << " pendataan      " << "\n\n";  // opsi 3

        gotoxy(0, 9);
        color(sign[2]); cout << "\t\t\t\t\t\t"     << char(16); 
        color(opsi[2]); cout << " Perbarui status" << "\n\t\t\t\t\t\t "
                             << " penduduk       " << "\n\n";  // opsi 2

        color(sign[3]); cout << "\t\t\t\t\t\t" << char(16); 
        color(opsi[3]); cout << " Hapus data " << "\n\t\t\t\t\t\t "
                             << " penduduk   " << "\n\n";  // opsi 3

        color(sign[4]); cout << "\t\t\t\t    " << char(16); 
        color(opsi[4]); cout << " Keluar     " << "\n\n\n";  // opsi 0
        color(RESET);

        // navigasi ---------------------------------------------------------------------
        char menu, key;
        menu = getch();

        switch (menu) {
            // tekan ENTER
            case ENTER:

                // tampilkan data penduduk
                if (opsi[0] == SELECT) {
                    tampilkanDataPenduduk();

                // tampilkan diagram data
                } else if (opsi[1] == SELECT) {
                    tampilkanDiagram();         
                    //         

                // perbarui status
                } else if (opsi[2] == SELECT) {
                    //                          
                
                // hapus data penduduk
                } else if (opsi[3] == SELECT) {
                    //

                // kembali
                } else if (opsi[4] == SELECT) {
                    looping = false;           

                }

                break;

            // tekan UP || DOWN
            case -32:

                // key yg ditekan
                key = getch();

                // opsi yang di-SELECT
                index = indexElemen(opsi, SELECT, 5);

                // pilih opsi[0] - tampilkan data penduduk
                if (
                    key == UP   && opsi[1] == SELECT ||
                    key == LEFT && opsi[2] == SELECT
                ) {
                    opsi[0] = SELECT; 
                
                // pilih opsi[1] - tampilkan diagram
                } else if (
                    key == DOWN && opsi[0] == SELECT ||
                    key == LEFT && opsi[3] == SELECT ||
                    key == UP   && opsi[4] == SELECT ||
                    key == LEFT && opsi[4] == SELECT
                ) {
                    opsi[1] = SELECT; 

                // pilih opsi[2] - perbarui status penduduk
                } else if (
                    key == RIGHT && opsi[0] == SELECT ||
                    key == UP    && opsi[3] == SELECT
                ) {
                    opsi[2] = SELECT; 
                
                // pilih opsi[3] - hapus data penduduk
                } else if (
                    key == DOWN  && opsi[2] == SELECT ||
                    key == RIGHT && opsi[1] == SELECT ||
                    key == RIGHT && opsi[4] == SELECT
                ) {
                    opsi[3] = SELECT;

                // pilih opsi[4] - keluar
                } else if (
                    key == DOWN && (opsi[1] == SELECT || opsi[3] == SELECT)
                ) {
                    opsi[4] = SELECT;
                }

                opsi[index] = UNSELECT;
                if (indexElemen(opsi, SELECT, 5) == -1) {
                    opsi[index] = SELECT;
                }

                break;

        }   // end switch

    }   // end while

}

void tampilkanDiagram() {

    // default
    bool openPage = true;
    string kategori = "Jenis Kelamin";
    short int kec1    = SELECT,   kec2    = SIGNED,  // kecamatan
              hidup1  = UNSELECT, hidup2  = UNSIGNED,  
              gender1 = UNSELECT, gender2 = UNSIGNED,  
              usia1   = UNSELECT, usia2   = UNSIGNED,  
              agama1  = UNSELECT, agama2  = UNSIGNED, 
              golDar1 = UNSELECT, golDar2 = UNSIGNED,  
              kawin1  = UNSELECT, kawin2  = UNSIGNED,  
              nav1    = UNSELECT, nav2    = UNSIGNED;

    while (openPage) {
        system("cls");
        cout << endl << endl;

        // judul halaman
        cout << "\t"; karakter(177, 5, 9);
        cout << "  Diagram Data Penduduk  "; karakter(177, 40, 9); 
        cout << endl << endl;

        // kategori diagram  
        cout << "\t"   ; color(kec2);    cout << char(16); color(kec1);    cout << " Kecamatan";        
        cout << "     "; color(hidup2);  cout << char(16); color(hidup1);  cout << " Status Hidup ";        
        cout << "     "; color(gender2); cout << char(16); color(gender1); cout << " Jenis Kelamin";    
        cout << "\t   "; color(usia2);   cout << char(16); color(usia1);   cout << " Usia";             
        cout << "\n\t" ; color(agama2);  cout << char(16); color(agama1);  cout << " Agama";            
        cout << "\t\t" ; color(golDar2); cout << char(16); color(golDar1); cout << " Golongan Darah";   
        cout << "    " ; color(kawin2);  cout << char(16); color(kawin1);  cout << " Status Perkawinan";
        
        color(RESET); cout << endl << endl; 

        // jika belum ada yg mengisi formulir
        if (banyakDataTerisi() == 0) {
            color(14); 
            cout << endl << endl
                 << "\t\t\tBelum ada data penduduk yang tersimpan" << endl;
        
        // jika sudah ada yg mengisi formulir
        } else {

            // tampilkan diagram
            if      (kec1    == SELECT || kec2    == MARKED) { diagramKecamatan();   } 
            else if (hidup1  == SELECT || hidup2  == MARKED) { diagramStatusHidup(); } 
            else if (gender1 == SELECT || gender2 == MARKED) { diagramGender();      } 
            else if (usia1   == SELECT || usia2   == MARKED) { diagramUsia();        } 
            else if (agama1  == SELECT || agama2  == MARKED) { diagramAgama();       } 
            else if (golDar1 == SELECT || golDar2 == MARKED) { diagramGolDar();      } 
            else if (kawin1  == SELECT || kawin2  == MARKED) { diagramStatusKawin(); }

        }

        gotoxy(0, 18); color(RESET);    // reset posisi dan warna

        // banyak data tersimpan 
        cout << "\tPenduduk terdaftar     : " << banyakData()       << endl
             << "\tPenduduk terverifikasi : " << banyakDataTerisi() << endl << endl << endl;
        
        // ganti halaman
        color(nav1); cout << "\tKembali\n";
        color(nav2); cout << "\t  <=   ";
        color(RESET); cout << endl << endl << endl;

        // navigasi ----------------------------------------
 
        char opsi, key;
        opsi = getch();

        if (opsi == -32) {
            key = getch();

            // kembali ke menu
            if (
                key == LEFT && hidup1 == SELECT ||
                key == UP   && agama1 == SELECT
            ) {
                kec1   = SELECT;   kec2   = SIGNED;
                hidup1 = UNSELECT; hidup2 = UNSIGNED;
                agama1 = UNSELECT; agama2 = UNSIGNED;

            // status hidup
            } else if (
                key == RIGHT && kec1    == SELECT || 
                key == LEFT  && gender1 == SELECT ||
                key == UP    && golDar1 == SELECT
            ) {
                hidup1  = SELECT;   hidup2  = SIGNED;
                kec1    = UNSELECT; kec2    = UNSIGNED;
                gender1 = UNSELECT; gender2 = UNSIGNED;
                golDar1 = UNSELECT; golDar2 = UNSIGNED;

            // jenis kelamin
            } else if (
                key == RIGHT && hidup1 == SELECT || 
                key == LEFT  && usia1  == SELECT ||
                key == UP    && kawin1 == SELECT
            ) {
                gender1 = SELECT;   gender2 = SIGNED;
                hidup1  = UNSELECT; hidup2  = UNSIGNED;
                usia1   = UNSELECT; usia2   = UNSIGNED;
                kawin1  = UNSELECT; kawin2  = UNSIGNED;

            // usia
            } else if (
                key == RIGHT && gender1 == SELECT || 
                key == RIGHT && kawin1  == SELECT
            ) {
                usia1 = SELECT;     usia2   = SIGNED;
                gender1 = UNSELECT; gender2 = UNSIGNED;
                kawin1 = UNSELECT;  kawin2  = UNSIGNED;
        
            // agama
            } else if (
                key == DOWN && kec1    == SELECT ||
                key == LEFT && golDar1 == SELECT ||
                key == UP   && nav1    == SELECT && agama2 == MARKED
            ) {
                agama1  = SELECT;   agama2  = SIGNED;
                kec1    = UNSELECT; kec2    = UNSIGNED;
                golDar1 = UNSELECT; golDar2 = UNSIGNED;
                nav1    = UNSELECT; nav2    = UNSIGNED;

            // golongan darah
            } else if (
                key == DOWN  && hidup1 == SELECT ||
                key == LEFT  && kawin1 == SELECT ||
                key == RIGHT && agama1 == SELECT ||
                key == UP    && nav1   == SELECT && golDar2 == MARKED
            ) {
                golDar1 = SELECT;   golDar2 = SIGNED;
                hidup1  = UNSELECT; hidup2  = UNSIGNED;
                kawin1  = UNSELECT; kawin2  = UNSIGNED;
                agama1  = UNSELECT; agama2  = UNSIGNED;
                nav1    = UNSELECT; nav2    = UNSIGNED;

            // status kawin
            } else if (
                key == DOWN  && gender1 == SELECT ||
                key == DOWN  && usia1   == SELECT ||
                key == RIGHT && golDar1 == SELECT ||
                key == UP    && nav1    == SELECT && kawin2 == MARKED 
            ) {
                kawin1  = SELECT;   kawin2  = SIGNED;
                gender1 = UNSELECT; gender2 = UNSIGNED;
                usia1   = UNSELECT; usia2   = UNSIGNED;
                golDar1 = UNSELECT; golDar2 = UNSIGNED;
                nav1    = UNSELECT; nav2    = UNSIGNED;

            // navigasi
            } else if (
                key == DOWN && agama1  == SELECT ||
                key == DOWN && golDar1 == SELECT ||
                key == DOWN && kawin1  == SELECT 
            ) {
                if      (agama1  == SELECT) { agama2  = MARKED; }
                else if (golDar1 == SELECT) { golDar2 = MARKED; }
                else if (kawin1  == SELECT) { kawin2  = MARKED; }
                
                nav1    = SELECT; nav2 = SIGNED;
                agama1  = UNSELECT; 
                golDar1 = UNSELECT; 
                kawin1  = UNSELECT;

            } else if (
                key == LEFT && nav1 == SELECT
            ) {
                openPage = false;
                break;

            } // end if 

        } // end if

    } // end while

}

void tampilkanDataPenduduk() {
    bool openPage = true;
    short int nav1, nav2;

    while (openPage) {
        system("cls");
        cout << endl << endl;

        // judul halaman
        cout << "\t"; karakter(177, 5, 9);
        cout << "  Data Penduduk  "; karakter(177, 50, 9); 
        cout << endl << endl;

        for (int i=0; i<15; i++) {
            gotoxy(10, 7+i); cout << i;
            gotoxy(19, 7+i); cout << dataPenduduk[i].tanggalPembaruan;
            gotoxy(39, 7+i); cout << dataPenduduk[i].nik;
            gotoxy(58, 7+i); cout << dataPenduduk[i].namaLengkap;

        }
        
        tabel();

        // ganti halaman
        color(nav1); cout << "\tKembali\n";
        color(nav2); cout << "\t  <=   ";
        color(RESET); cout << endl << endl << endl;

        char opsi, key;
        opsi = getch();

        switch (opsi) {
            case ENTER:

                break;

            case -32:
                key = getch();
                break;

        }

    }
    
    


}

// diagram
void diagramKecamatan() {

    float total[10]     = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          totalData     = banyakDataTerisi();
    short int warna[10] = {1, 2, 15, 5, 12, 6, 3, 8, 13, 14};

    // atur angka belakang koma
    cout << setiosflags(ios::fixed) << setprecision(1);

    for (int i=0; i<10; i++) {

        // hitung jumlah data per gender
        for (int j=0; j<totalData; j++) {
            if (dataPenduduk[j].alamat.kecamatan == i) {
                 total[i]++;
            } 
        }

        // tampilkan diagram
        diagram((total[i]*30)/(totalData), warna[i]); 
        cout << " " <<  (total[i]*100)/(totalData) << "%" << endl;

    }

    // keterangan warna
    for (int i=0; i<10; i++) {
        gotoxy(55, 7+i); 
        color(warna[i]); cout << char(254) << " "; 
        color(RESET); cout << KECAMATAN[i]; 
    }

    cout << endl << endl;
}

void diagramStatusHidup() {
    float total[2]  = {0, 0},
          totalData = banyakDataTerisi();
    short int warna[2] = {8, 14};

    // atur angka belakang koma
    cout << setiosflags(ios::fixed) << setprecision(1);

    // hitung jumlah data per status 
    for (int i=0; i<totalData; i++) {
        if      (dataPenduduk[i].statusHidup == 0) { total[0]++; }
        else if (dataPenduduk[i].statusHidup == 1) { total[1]++; }
    }

    // tampilkan diagram
    for (int i=0; i<10; i++) {

        if (i == 2) {           // hidup
            diagram((total[1]*30)/(totalData), warna[1]); 
            cout << " " << (total[1]*100)/(totalData) << "%" << endl;

        } else if (i == 7) {    // wafat
            diagram((total[0]*30)/(totalData), warna[0]); 
            cout << " " <<  (total[0]*100)/(totalData) << "%" << endl;

        } else {
            diagram(0); cout << endl;
        }

    }

    // keterangan warna
    gotoxy(55, 9);  color(warna[1]); cout << char(254) << " "; color(RESET); cout << STATUSHIDUP[1]; 
    gotoxy(55, 14); color(warna[0]); cout << char(254) << " "; color(RESET); cout << STATUSHIDUP[0]; 

    cout << endl << endl << endl;


}

void diagramGender() {
    float total[2] = {0, 0},
          totalData = banyakDataTerisi();
    short int warna[2] = {9, 13};

    // atur angka belakang koma
    cout << setiosflags(ios::fixed) << setprecision(1);

    // hitung jumlah data per gender
    for (int j=0; j<totalData; j++) {
        if      (dataPenduduk[j].gender == 0) { total[0] += 1; }    // laki-laki
        else if (dataPenduduk[j].gender == 1) { total[1] += 1; }    // perempuan
    }

    // tampilkan diagram
    for (int i=0; i<10; i++) {
        if (i == 2) {           // laki-laki
            diagram((total[0]*30)/(totalData), warna[0]); 
            cout << " " << (total[0]*100)/(totalData) << "%" << endl;

        } else if (i == 7) {    // perempuan
            diagram((total[1]*30)/(totalData), warna[1]); 
            cout << " " <<  (total[1]*100)/(totalData) << "%" << endl;

        } else {
            diagram(0); cout << endl;
        }

    }

    // keterangan warna
    gotoxy(55, 9);  color(warna[0]); cout << char(254) << " "; color(RESET); cout << GENDER[0]; 
    gotoxy(55, 14); color(warna[1]); cout << char(254) << " "; color(RESET); cout << GENDER[1]; 

}

void diagramUsia() {
    float total[7] = {0, 0, 0 , 0 , 0 , 0, 0},
          totalData = banyakDataTerisi();
    short int warna[7] = {8, 9, 10, 14, 12, 13, 6};

    cout << setiosflags(ios::fixed) << setprecision(1);

    // hitung jumlah data per usia
    for (int j=0; j<totalData; j++) {
        if      (dataPenduduk[j].usia >= 0  && dataPenduduk[j].usia <= 9)  { total[0]++; } 
        else if (dataPenduduk[j].usia >= 10 && dataPenduduk[j].usia <= 19) { total[1]++; } 
        else if (dataPenduduk[j].usia >= 20 && dataPenduduk[j].usia <= 29) { total[2]++; } 
        else if (dataPenduduk[j].usia >= 30 && dataPenduduk[j].usia <= 39) { total[3]++; } 
        else if (dataPenduduk[j].usia >= 40 && dataPenduduk[j].usia <= 49) { total[4]++; } 
        else if (dataPenduduk[j].usia >= 50 && dataPenduduk[j].usia <= 59) { total[5]++; } 
        else if (dataPenduduk[j].usia >= 60)                               { total[6]++; }
    }

    // tampilkan diagram
    for (int i=0; i<9; i++) {

        if (i == 0 || i == 8) {
            diagram(0); cout << endl;

        } else {
            diagram(total[i-1]*30/totalData, warna[i-1]); 
            cout << " " <<  total[i-1]*100/totalData << "%" << endl;

        }
        
    }

    // keterangan 
    gotoxy(55, 8);  color(warna[0]); cout << char(254) << " "; color(RESET); cout << "0-9 tahun"; 
    gotoxy(55, 9);  color(warna[1]); cout << char(254) << " "; color(RESET); cout << "10-19 tahun"; 
    gotoxy(55, 10); color(warna[2]); cout << char(254) << " "; color(RESET); cout << "20-29 tahun"; 
    gotoxy(55, 11); color(warna[3]); cout << char(254) << " "; color(RESET); cout << "30-39 tahun"; 
    gotoxy(55, 12); color(warna[4]); cout << char(254) << " "; color(RESET); cout << "40-49 tahun"; 
    gotoxy(55, 13); color(warna[5]); cout << char(254) << " "; color(RESET); cout << "50-59 tahun"; 
    gotoxy(55, 14); color(warna[6]); cout << char(254) << " "; color(RESET); cout << "60+ tahun"; 

    cout << endl;

}

void diagramAgama() {
    float total[6]  = {0, 0, 0, 0, 0, 0},
          totalData = banyakDataTerisi();

    short int warna[6] = {10, 13, 8, 14, 9, 12};

    cout << setiosflags(ios::fixed) << setprecision(1);

    // hitung jumlah data per agama
    for (int i=0; i<totalData; i++) {
        if      (dataPenduduk[i].agama == 0) { total[0]++; } 
        else if (dataPenduduk[i].agama == 1) { total[1]++; } 
        else if (dataPenduduk[i].agama == 2) { total[2]++; } 
        else if (dataPenduduk[i].agama == 3) { total[3]++; } 
        else if (dataPenduduk[i].agama == 4) { total[4]++; } 
        else if (dataPenduduk[i].agama == 5) { total[5]++; }
    }

    // tampilkan diagram
    for (int i=0; i<10; i++) {
        if (i < 2 || i > 7) {
            diagram(0); cout << endl;
        } else {
            diagram((total[i-2]*30)/totalData, warna[i-2]); 
            cout << " " << (total[i-2]*100)/totalData << "%" << endl;
        }
    }

    // keterangan warna
    for (int i=0; i<6; i++) {
        gotoxy(55, 9+i); 
        color(warna[i]); cout << char(254) << " "; 
        color(RESET); cout << AGAMA[i]; 
    }
    
}

void diagramGolDar() {
    float total[4]  = {0, 0, 0, 0},
          totalData = banyakDataTerisi();

    short int warna[4] = {12, 3, 8, 15};

    cout << setiosflags(ios::fixed) << setprecision(1);

    // hitung jumlah data per agama
    for (int i=0; i<totalData; i++) {
        if      (dataPenduduk[i].golDar == 0) { total[0]++; } 
        else if (dataPenduduk[i].golDar == 1) { total[1]++; } 
        else if (dataPenduduk[i].golDar == 2) { total[2]++; } 
        else if (dataPenduduk[i].golDar == 3) { total[3]++; } 
    }

    // tampilkan diagram
    for (int i=0; i<9; i++) {

        if (i%2 == 0) {
            diagram(0); cout << endl;

        } else {
            diagram((total[i/2]*30)/totalData, warna[i/2]); 
            cout << " " << (total[i/2]*100)/totalData << "%" << endl;
        }
    }

    // keterangan warna
    int jarak = 0;
    for (int i=0; i<4; i++) {

        gotoxy(55, 8+jarak); 
        color(warna[i]); cout << char(254) << " "; 
        color(RESET); cout << GOLDAR[i]; 

        jarak += 2;
    }
    
}

void diagramStatusKawin() {
    float total[4]  = {0, 0, 0, 0},
          totalData = banyakDataTerisi();

    short int warna[4] = {3, 10, 6, 13};

    cout << setiosflags(ios::fixed) << setprecision(1);

    // hitung jumlah data per status kawin
    for (int i=0; i<totalData; i++) {
        if      (dataPenduduk[i].statusKawin == 0) { total[0]++; } 
        else if (dataPenduduk[i].statusKawin == 1) { total[1]++; } 
        else if (dataPenduduk[i].statusKawin == 2) { total[2]++; } 
        else if (dataPenduduk[i].statusKawin == 3) { total[3]++; } 
    }

    // tampilkan diagram
    for (int i=0; i<9; i++) {

        if (i%2 == 0) {
            diagram(0); cout << endl;

        } else {
            diagram((total[i/2]*30)/totalData, warna[i/2]); 
            cout << " " << (total[i/2]*100)/totalData << "%" << endl;
        }
    }

    // keterangan warna
    int jarak = 0;
    for (int i=0; i<4; i++) {

        gotoxy(55, 8+jarak); 
        color(warna[i]); cout << char(254) << " "; 
        color(RESET); cout << STATUSKAWIN[i]; 

        jarak += 2;
    }
    
}


// pengisian formulir
void tampilkanOpsi(string opsi) {
    if (opsi == "Kecamatan") {
        cout << "\n\t   Kecamatan                                   "
             << "\n\t   [1] Palaran             [5] Samarinda Utara    [9]  Samarinda Kota"
             << "\n\t   [2] Samarinda Seberang  [6] Sungai Kunjang     [10] Loa Janan Ilir"
             << "\n\t   [3] Samarinda Ulu       [7] Sambutan        "
             << "\n\t   [4] Samarinda Ilir      [8] Sungai Pinang   "
             << "\n\t   : ";
    
    } else if (opsi == "Palaran") {
        cout << "\n\t   Kelurahan                                   "
             << "\n\t   [1] Rawa Makmur         [4] Simpang Pasir   "
             << "\n\t   [2] Handil Bakti        [5] Bantuas         "
             << "\n\t   [3] Bukuan                                  "
             << "\n\t   : ";
    } else if (opsi == "Samarinda Seberang") {
        cout << "\n\t   Kelurahan                                   "
             << "\n\t   [1] Sungai Keledang     [4] Mangkupalas     "
             << "\n\t   [2] Baqa                [5] Gunung Panjang  "
             << "\n\t   [3] Mesjid                                  "
             << "\n\t   : ";
    } else if (opsi == "Samarinda Ulu") {
        cout << "\n\t   Kelurahan                                   "
             << "\n\t   [1] Teluk Lerong Ilir    [4] Sidodadi          [7] Gunung Kelua "
             << "\n\t   [2] Jawa                 [5] Air Hitam         [8] Bukit Pinang "
             << "\n\t   [3] Air Putih            [6] Dadi Mulya       "
             << "\n\t   : ";
    } else if (opsi == "Samarinda Ilir") {
        cout << "\n\t   Kelurahan                                   "
             << "\n\t   [1] Selili              [4] Sidodamai       "
             << "\n\t   [2] Sungai Dama         [5] Pelita          "
             << "\n\t   [3] Sidomulyo                               "
             << "\n\t   : ";
    } else if (opsi == "Samarinda Utara") {
        cout << "\n\t   Kelurahan                                   "
             << "\n\t   [1] Sempaja Selatan     [4] Sempaja Utara     [7] Sempaja Timur"
             << "\n\t   [2] Lempake             [5] Tanah Merah       [8] Budaya Pampang"   
             << "\n\t   [3] Sungai Siring       [6] Sempaja Barat   "
             << "\n\t   : "; 
    } else if (opsi == "Sungai Kunjang") {
        cout << "\n\t   Kelurahan                                   "
             << "\n\t   [1] Loa Bakung          [4] Lok Bahu          [6] Karang Asam "
             << "\n\t   [2] Loa Buah            [5] Telok Lerong          Ilir        "   
             << "\n\t   [3] Karang Asam Ulu         Ulu               [7] Karang Anyar"
             << "\n\t   : "; 
    } else if (opsi == "Sambutan") {
        cout << "\n\t   Kelurahan                                   "
             << "\n\t   [1] Sungai Kapih        [4] Sindang Sari    "
             << "\n\t   [2] Sambutan            [5] Pulau Atas      "
             << "\n\t   [3] Makroman                                "
             << "\n\t   : ";
    } else if (opsi == "Sungai Pinang") {
        cout << "\n\t   Kelurahan                                   "
             << "\n\t   [1] Temindung Permai    [3] Gunung Lingai   "
             << "\n\t   [2] Sungai Pinang       [4] Mugirejo        "
             << "\n\t       Dalam               [5] Bandara         "
             << "\n\t   : ";
    } else if (opsi == "Samarinda Kota") {
        cout << "\n\t   Kelurahan                                   "
             << "\n\t   [1] Karang Mumus        [4] Bugis           "
             << "\n\t   [2] Pelabuhan           [5] Sungai Pinang   "
             << "\n\t   [3] Pasar Pagi              Luar            "
             << "\n\t   : ";
    } else if (opsi == "Loa Janan Ilir") {
        cout << "\n\t   Kelurahan                                   "
             << "\n\t   [1] Simpang Tiga        [4] Harapan Baru    "
             << "\n\t   [2] Tani Aman           [5] Rapak Dalam     "
             << "\n\t   [3] Sengkotek                               "
             << "\n\t   : ";
    } else if (opsi == "Jenis Kelamin") {
        cout << "\n\tJenis Kelamin \n"       
             << "\t     [1] Laki-laki          [2] Perempuan          \n"   
             << "\t     : \n";
    } else if (opsi == "Agama") {
        cout << "\n\tAgama \n"
             << "\t     [1] Islam        [3] Katolik     [5] Buddha    \n"
             << "\t     [2] Kristen      [4] Hindu       [6] Konghuchu \n"
             << "\t     : \n";
    } else if (opsi == "Golongan Darah") {
        cout << "\n\tGolongan Darah                                   \n"
             << "\t     [1] A        [2] B        [3] AB        [4] O \n"
             << "\t     : \n";

    } else if (opsi == "Status Perkawinan") {
        cout << "\n\tStatus \n"
             << "\t     [1] Belum kawin   [2] Kawin   [3] Cerai hidup   [4] Cerai mati     \n"
             << "\t     : \n";
    } else if (opsi == "Status Hidup") {
    }
}

// tabel
void tabel(short int opsi1) {
    gotoxy(0, 5);
    cout << "\t+--------+-------------------+------------------+----------------------+" << endl;

    cout << "\t|   No   "; color(opsi1); cout << char(31);
    cout << "| Tanggal Pembaruan |        NIK       |     Nama Lengkap     |" << endl;
    
    cout << "\t+--------+-------------------+------------------+----------------------+" << endl;

    for (int i=0; i<15; i++) {
        gotoxy(8, 8+i);  cout << "|"; 
        gotoxy(17, 8+i); cout << "|"; 
        gotoxy(37, 8+i); cout << "|";
        gotoxy(56, 8+i); cout << "|";
        gotoxy(79, 8+i); cout << "|";
    }
    cout << "\n\t+--------+-------------------+------------------+----------------------+" << endl;
}

/* ----------------------------------- FILE TXT ----------------------------------- */

void importFromTxt() {
    ifstream input;
    input.open("data.txt");

    Penduduk penduduk;
    string temp;
    int index = 0;

    while (!input.eof()) {
        getline(input, temp, '|');

        if (temp == "") {
            break;
        } else {
            penduduk.tanggalPembaruan = temp;
        }       

        getline(input, penduduk.namaLengkap, '|');
        
        getline(input, temp, '|');
        strcpy(penduduk.nik, temp.c_str());

        getline(input, penduduk.password, '|');

        getline(input, penduduk.ttl, '|');

        getline(input, penduduk.alamat.jalan, '|');

        getline(input, temp, '|');
        penduduk.alamat.kecamatan = stoi(temp);

        getline(input, temp, '|');
        penduduk.alamat.kelurahan = stoi(temp);

        getline(input, penduduk.telepon, '|');

        getline(input, temp, '|');
        penduduk.usia = stoi(temp);

        getline(input, temp, '|');
        penduduk.gender = stoi(temp);

        getline(input, temp, '|');
        penduduk.agama = stoi(temp);

        getline(input, temp, '|');
        penduduk.golDar = stoi(temp);

        getline(input, temp, '|');
        penduduk.statusKawin = stoi(temp);

        getline(input, temp, '\n');
        penduduk.statusHidup = stoi(temp);

        dataPenduduk[index] = penduduk;

        index++;

    }

    input.close();
}

void appendToTxt(Penduduk penduduk) {
    ofstream file;

    file.open("data.txt", ios::app);

    penduduk.tanggalPembaruan = hariIni();  // tgl data diri diubah

    file << penduduk.tanggalPembaruan << "|"
         << penduduk.namaLengkap << "|"
         << penduduk.nik << "|"
         << penduduk.password << "|"
         << penduduk.ttl << "|"
         << penduduk.alamat.jalan << "|" 
         << penduduk.alamat.kecamatan << "|" 
         << penduduk.alamat.kelurahan << "|"
         << penduduk.telepon << "|"
         << penduduk.usia << "|"
         << penduduk.gender << "|"
         << penduduk.agama << "|"
         << penduduk.golDar << "|"
         << penduduk.statusKawin << "|"
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

int indexElemen(short int array[], int cari, int length) {
    for (int i=0; i<length; i++) {
        if (array[i] == cari) {
            return i;
        }
    }

    return -1;
}

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
    int hari = timeNow()->tm_wday;
    string tgl  = to_string(timeNow()->tm_mday);
    string bulan = to_string(timeNow()->tm_mon);
    string tahun = to_string(timeNow()->tm_year + 1900);

    return HARI[hari] + ", " + tgl + "/" + bulan + "/" + tahun;
}

int random() {
    return rand()%9;
}

void clearCin() {
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
    cout << "\t      " << char(221); color(warna);

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

void hapusTulisan(int panjang) {
    color(0);
    for (int i=0; i<panjang; i++) {
        cout << char(219);
    }
    color(RESET);
}

int banyakDataTerisi() {
    // hitung data terverifikasi
    int total = 0;
    for (int i=0; i<banyakData(); i++) {
        if (formulirTerisi(dataPenduduk[i])) {
            total += 1;
        }
    }

    return total;
}


/* ----------------------------------- CEK ISIAN ----------------------------------- */

bool isAngka(string str) {
    int length = str.length();

    int isInteger = 0;
    for (int i=0; i<length; i++) {
        int cek = (int)str[i] - 48;

        if (0 <= cek && cek <= 9) {
            isInteger += 1;
        }
    }

    if (isInteger == length && !isSpace(str)) {
        return true;
    } 

    return false;
}

bool isSpace(string str) {
    if (str == "\t" || str == "\n" || str == "") {
        return true;
    }

    int length = str.length(),
        banyakSpasi = 0;

    for (int i=0; i<length; i++) {
        if (str[i] == ' ') {
            banyakSpasi++;
        }
    }

    if (length == banyakSpasi) {
        return true;
    }

    return false;
}

bool isTahun(int tahun) {
    int tahunIni = timeNow()->tm_year + 1900;
    
    if (tahun >= 1920 && tahun <= tahunIni) {
        return true;
    }

    return false;
}

bool isTanggal(int tanggal) {
    if (tanggal >= 1 && tanggal <= 31) {
        return true;
    }

    return false;
}

bool isBulan(int bulan) {
    if (bulan >= 1 && bulan <= 12) {
        return true;
    }

    return false;
}

bool isNIK(char nik[]) {
    string nikStr = string(nik);
    int length = nikStr.length();

    if (!isSpace(nikStr) && isAngka(nikStr) && length == 16) {
        return true;
    }

    return false;
}

bool isTelp(string telp) {
    int length = telp.length();

    if (!isSpace(telp) && isAngka(telp) && (length >= 10 && length <= 12)) {
        return true;
    }

    return false;
}



