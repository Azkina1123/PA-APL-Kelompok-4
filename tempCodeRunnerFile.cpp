struct Alamat {
    string jalan;
    short int kecamatan = -1;
    short int kelurahan = -1;
};

struct Kelahiran {
    string tempat;
    short int tanggal = -1;
    short int bulan = -1;
    int tahun = -1;
};

// struct penduduk
struct Penduduk{
    string tanggalPembaruan;
    string namaLengkap;
    char nik[17];                // 16 digit + \0
    string password;
    Kelahiran ttl;
    Alamat alamat;
    string telepon;            // 12 digit + \0
    int usia = -1;
    short int gender = -1;       // index GENDER
    short int agama = -1;        // index AGAMA
    short int golDar = -1;       // index GOLDAR
    short int statusKawin = -1;  // index STATUS
    short int statusHidup = -1;
};
