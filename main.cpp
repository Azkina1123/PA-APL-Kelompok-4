#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <iomanip>
#include <fstream>

using namespace std;

const int UP = 72;
const int DOWN = 80;
const int LEFT = 75;
const int RIGHT = 77;
const int SELECT = 11;
const int UNSELECT = 7;
const int ENTER = 13;

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

void logInPemerintah();
void menuPemerintah();

void saveToTxt(Penduduk penduduk);
int savedDataTxt();
void konfigurasiData();

void buatDataPenduduk();

int main(){
    bool running = true;
    string warning = "";

    int opsi1 = SELECT, 
        opsi2 = UNSELECT;

    while (true) {
        system("cls");
        konfigurasiData();

        cout << endl << endl;

        cout << "\t            Selamat Datang!            \n";
        
        cout << endl;
        color(12); cout << setw(37) << warning << endl; color(7);
        cout << endl;
        
        cout << "\t       Jalankan program sebagai :      \n\n";
        color(opsi1); cout << "\t   [1] Pemerintah  ";
        color(opsi2); cout << "     [2] Penduduk\n\n"; color(7);

        char mode, pilih;
        mode = getch();

        if (mode == ENTER && opsi1 == SELECT) {
            logInPemerintah();
            goto skip;
        
        } else if (mode == ENTER && opsi2 == SELECT) {
            menuMasukPenduduk();
            goto skip;
        }

        switch (mode) {
            case -32:
                pilih = getch();
                if (pilih == RIGHT){
                    opsi1 = UNSELECT;
                    opsi2 = SELECT;
                    
                } else if (pilih == LEFT){
                    opsi1 = SELECT;
                    opsi2 = UNSELECT;
                }
                break;

            default:
                warning = "Opsi tidak tersedia!";
                continue;
                break;
        }

        skip:
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

        if (menu == ENTER && opsi0 == SELECT) {
            openPage = false;
            break;

        } else if (menu == ENTER && opsi1 == SELECT) {
            logInPenduduk();
            goto skip;

        } else if (menu == ENTER && opsi2 == SELECT) {
            signUpPenduduk();
            goto skip;
        }

        switch (menu) {
            case -32:
                pilih = getch();
                if (
                    pilih == LEFT && opsi0 == UNSELECT && opsi1 == SELECT
                    || pilih == LEFT && opsi0 == SELECT
                ) {
                    opsi0 = SELECT;
                    opsi1 = UNSELECT;
                    opsi2 = UNSELECT;
                } 
                else if (
                    pilih == RIGHT && opsi1 == UNSELECT && opsi2 == UNSELECT 
                    || pilih == LEFT && opsi1 == UNSELECT && opsi2 == SELECT
                ) {
                    opsi0 = UNSELECT;
                    opsi1 = SELECT;
                    opsi2 = UNSELECT;

                } else if (
                    pilih == RIGHT && opsi2 == UNSELECT 
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

        skip:
        warning = "";

    }
}

void signUpPenduduk() {
    cout << "\n\t#######################################\n" << endl;
    Penduduk pendudukBaru;

    cout << "\tNama Lengkap : "; getline(cin, pendudukBaru.namaLengkap); fflush(stdin);
    cout << "\tNIK          : "; cin >> pendudukBaru.nik;                fflush(stdin);
    cout << "\tPassword     : "; getline(cin, pendudukBaru.password);    fflush(stdin);
    
    saveToTxt(pendudukBaru);

    color(10);
    cout << "\n\t   Akun telah berhasil didaftarkan!  " << endl;
    color(7);

    getch();

}

void logInPenduduk() {
    cout << "\n\t#######################################\n" << endl;

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

        if (menu == ENTER && opsi0 == SELECT) {
            openPage = false;
            break;

        } else if (menu == ENTER && opsi1 == SELECT) {
            isiFormulirData(penduduk);
            goto skip;

        } else if (menu == ENTER && opsi2 == SELECT) {
            // tampilkan data diri
            goto skip;
        
        } else if (menu == ENTER && opsi3 == SELECT) {
            // ubah data diri
            goto skip;
        }

        switch (menu) {
            case -32:
                pilih = getch();
                if (
                    pilih == UP && opsi0 == SELECT
                    || pilih == UP && opsi1 == SELECT
                ) {
                    opsi0 = SELECT; 
                    opsi1 = UNSELECT; 
                    opsi2 = UNSELECT; 
                    opsi3 = UNSELECT;
                
                } else if (
                    pilih == DOWN && opsi0 == SELECT
                    || pilih == UP && opsi2 == SELECT
                ) {
                    opsi0 = UNSELECT; 
                    opsi1 = SELECT; 
                    opsi2 = UNSELECT; 
                    opsi3 = UNSELECT;
                
                } else if (
                    pilih == DOWN && opsi1 == SELECT
                    || pilih == UP && opsi3 == SELECT
                ) {
                    opsi0 = UNSELECT; 
                    opsi1 = UNSELECT; 
                    opsi2 = SELECT; 
                    opsi3 = UNSELECT;
                
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

        skip:
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

        if (menu == ENTER && opsi0 == SELECT) {
            openPage = false;
            break;

        } else if (menu == ENTER && opsi1 == SELECT) {
            // tampilkan data penduduk
            goto skip;

        } else if (menu == ENTER && opsi2 == SELECT) {
            // ubah data penduduk
            goto skip;
        
        } else if (menu == ENTER && opsi3 == SELECT) {
            // tampilkan diagram
            goto skip;
        }

        switch (menu) {
            case -32:
                pilih = getch();
                if (
                    pilih == UP && opsi0 == SELECT
                    || pilih == UP && opsi1 == SELECT
                ) {
                    opsi0 = SELECT; 
                    opsi1 = UNSELECT; 
                    opsi2 = UNSELECT; 
                    opsi3 = UNSELECT;
                
                } else if (
                    pilih == DOWN && opsi0 == SELECT
                    || pilih == UP && opsi2 == SELECT
                ) {
                    opsi0 = UNSELECT; 
                    opsi1 = SELECT; 
                    opsi2 = UNSELECT; 
                    opsi3 = UNSELECT;
                
                } else if (
                    pilih == DOWN && opsi1 == SELECT
                    || pilih == UP && opsi3 == SELECT
                ) {
                    opsi0 = UNSELECT; 
                    opsi1 = UNSELECT; 
                    opsi2 = SELECT; 
                    opsi3 = UNSELECT;
                
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

        skip:
        warning = "";
    }

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

