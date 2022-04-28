
void importFromTxt() {
    ifstream input;
    input.open("data.txt");

    Penduduk penduduk;
    string baris, 
           usia,
           gender,
           agama,
           golDar,
           status;
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
        // usia
        } else if (kolom == 6) {
            usia = baris; 
        // gender
        } else if (kolom == 7) {
            gender = baris;
        // agama
        } else if (kolom == 8) {
            agama = baris;
        // golongan darah
        } else if (kolom == 9) {
            golDar = baris;
        // status
        } else if (kolom == 10) {
            status = baris;
        }

        if (kolom == 10) {
            penduduk.usia   = atoi(usia.c_str());         // convert dari str ke int
            penduduk.gender = atoi(gender.c_str());
            penduduk.agama  = atoi(agama.c_str());
            penduduk.golDar = atoi(golDar.c_str());
            penduduk.status = atoi(status.c_str());

            dataPenduduk[index] = penduduk;

            index++;
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
         << penduduk.usia << "\n"
         << penduduk.gender << "\n"
         << penduduk.agama << "\n"
         << penduduk.golDar << "\n"
         << penduduk.status << "\n";

    file.close();
}

void updateToTxt(Penduduk penduduk) {
    deleteFromTxt(penduduk);
    // appendToTxt(penduduk);
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
