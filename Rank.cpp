#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <algorithm> 
#include <cctype>   
using namespace std;

const int MAX_SISWA = 36;
const int JUMLAH_MAPEL = 3;
string mapel[JUMLAH_MAPEL] = {"Literasi Membaca", "Literasi Numerik", "Literasi Sains"};

void inputData(string nama[], float nilai[][JUMLAH_MAPEL], int &n);
void tambahData(string nama[], float nilai[][JUMLAH_MAPEL], int &n);
void hitungRataRata(float nilai[][JUMLAH_MAPEL], float rata[], int n);
void urutkanRanking(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n);
void tampilkanHasil(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n);
void tampilNilaiTertinggiTerendah(string nama[], float nilai[][JUMLAH_MAPEL], int n);
void cariSiswa(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n);
void editData(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n);
void hapusData(string nama[], float nilai[][JUMLAH_MAPEL], int &n);
int inputMenuUtama();
int inputJumlahSiswa(int limit);
float inputNilai(string namaMapel);
string toLowerStr(const string &s); // fungsi bantu case-insensitive

int main() {
    string nama[MAX_SISWA];
    float nilai[MAX_SISWA][JUMLAH_MAPEL];
    float rata[MAX_SISWA];
    int n = 0;
    int pilihan;
    bool dataExists = false;

    do {
        cout << "\n=== PROGRAM REKAP NILAI ASPD ===\n";
        cout << "1. Input Data Nilai (Data Baru)\n";
        cout << "2. Tampilkan Rekap & Ranking\n";
        cout << "3. Tampilkan Nilai Tertinggi & Terendah beserta Nama\n";
        cout << "4. Cari Data Siswa\n";
        cout << "5. Edit Data Siswa\n";
        cout << "6. Tambah Data Siswa Baru\n";
        cout << "7. Hapus Data Siswa\n";
        cout << "8. Keluar\n";

        pilihan = inputMenuUtama();
        switch (pilihan) {
            case 1:
                inputData(nama, nilai, n);
                hitungRataRata(nilai, rata, n);
                dataExists = true;
                break;
            case 2:
                if (!dataExists) cout << "Data belum ada!\n";
                else {
                    urutkanRanking(nama, nilai, rata, n);
                    tampilkanHasil(nama, nilai, rata, n);
                }
                break;
            case 3:
                if (!dataExists) cout << "Data belum ada!\n";
                else tampilNilaiTertinggiTerendah(nama, nilai, n);
                break;
            case 4:
                if (!dataExists) cout << "Data belum ada!\n";
                else cariSiswa(nama, nilai, rata, n);
                break;
            case 5:
                if (!dataExists) cout << "Data belum ada!\n";
                else editData(nama, nilai, rata, n);
                break;
            case 6:
                if (!dataExists) cout << "Data belum ada!\n";
                else tambahData(nama, nilai, n);
                hitungRataRata(nilai, rata, n);
                break;
            case 7:
                if (!dataExists) cout << "Data belum ada!\n";
                else hapusData(nama, nilai, n);
                hitungRataRata(nilai, rata, n);
                if (n == 0) dataExists = false;
                break;
            case 8:
                cout << "Terima kasih telah menggunakan program ini!\n";
                break;
            default:
                cout << "Pilihan salah!\n";
                break;
        }
    } while (pilihan != 8);

    return 0;
}

// Validasi menu
int inputMenuUtama() {
    int pilihan;
    while (true) {
        cout << "Pilih menu: ";
        cin >> pilihan;
        if (pilihan >= 1 && pilihan <= 8) return pilihan;
        cout << "Pilihan salah. Ulangi!\n";
    }
}

// Fungsi input jumlah siswa
int inputJumlahSiswa(int limit) {
    int jumlah;
    while (true) {
        cout << "Masukkan jumlah siswa (1-" << limit << "): ";
        cin >> jumlah;
        if (jumlah >= 1 && jumlah <= limit) return jumlah;
        cout << "Input tidak valid!\n";
    }
}

// Fungsi input nilai
float inputNilai(string namaMapel) {
    float nilaiInput;
    while (true) {
        cout << "Nilai " << namaMapel << " (0-100): ";
        cin >> nilaiInput;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input harus angka!\n";
            continue;
        }

        if (nilaiInput >= 0 && nilaiInput <= 100) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return nilaiInput;
        }

        cout << "Nilai harus 0-100!\n";
    }
}

// Fungsi bantu lowercase
string toLowerStr(const string &s) {
    string res = s;
    transform(res.begin(), res.end(), res.begin(),
              [](unsigned char c){ return tolower(c); });
    return res;
}

// Input Data Baru
void inputData(string nama[], float nilai[][JUMLAH_MAPEL], int &n) {
    cout << "\n=== INPUT DATA BARU ===\n";
    n = inputJumlahSiswa(MAX_SISWA);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < n; i++) {
        cout << "\n--- Data Siswa ke-" << i + 1 << " ---\n";

        while (true) {
            cout << "Nama siswa: ";
            getline(cin, nama[i]);

            size_t start = nama[i].find_first_not_of(" \t");
            size_t end = nama[i].find_last_not_of(" \t");

            if (start == string::npos) {
                cout << "Nama tidak boleh kosong!\n";
                continue;
            }

            nama[i] = nama[i].substr(start, end - start + 1);
            break;
        }

        for (int j = 0; j < JUMLAH_MAPEL; j++) {
            nilai[i][j] = inputNilai(mapel[j]);
        }

        cout << "Data siswa ke-" << i + 1 << " berhasil diinput!\n";
    }
}

// Tambah Data
void tambahData(string nama[], float nilai[][JUMLAH_MAPEL], int &n) {
    if (n >= MAX_SISWA) {
        cout << "Data sudah penuh!\n";
        return;
    }
    cout << "\n=== TAMBAH DATA SISWA ===\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nama siswa baru: ";
    getline(cin, nama[n]);
    for (int j = 0; j < JUMLAH_MAPEL; j++)
        nilai[n][j] = inputNilai(mapel[j]);
    n++;
    cout << "Data berhasil ditambahkan!\n";
}

// Hitung Rata-rata
void hitungRataRata(float nilai[][JUMLAH_MAPEL], float rata[], int n) {
    for (int i = 0; i < n; i++) {
        float total = 0;
        for (int j = 0; j < JUMLAH_MAPEL; j++)
            total += nilai[i][j];
        rata[i] = total / JUMLAH_MAPEL;
    }
}

// Bubble Sort Ranking
void urutkanRanking(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (rata[j] < rata[j + 1]) {
                swap(rata[j], rata[j + 1]);
                swap(nama[j], nama[j + 1]);
                for (int k = 0; k < JUMLAH_MAPEL; k++)
                    swap(nilai[j][k], nilai[j + 1][k]);
            }
        }
    }
}

// Tampilkan Rekap
void tampilkanHasil(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n) {
    cout << "\n=== REKAP NILAI DAN RANKING ===\n";
    cout << left << setw(5) << "Rank" << setw(20) << "Nama";
    for (auto &m : mapel) cout << setw(20) << m;
    cout << "Rata-rata\n";
    cout << string(95, '=') << endl;

    for (int i = 0; i < n; i++) {
        cout << left << setw(5) << i+1 << setw(20) << nama[i];
        for (int j = 0; j < JUMLAH_MAPEL; j++)
            cout << setw(20) << fixed << setprecision(2) << nilai[i][j];
        cout << rata[i] << endl;
    }
}

// Nilai Tertinggi & Terendah + Nama
void tampilNilaiTertinggiTerendah(string nama[], float nilai[][JUMLAH_MAPEL], int n) {
    cout << "\n=== NILAI TERTINGGI & TERENDAH ===\n";
    for (int j = 0; j < JUMLAH_MAPEL; j++) {
        float maks = nilai[0][j], min = nilai[0][j];
        string namaMaks = nama[0], namaMin = nama[0];
        for (int i = 1; i < n; i++) {
            if (nilai[i][j] > maks) {
                maks = nilai[i][j];
                namaMaks = nama[i];
            }
            if (nilai[i][j] < min) {
                min = nilai[i][j];
                namaMin = nama[i];
            }
        }
        cout << mapel[j] << " | Tertinggi: " << maks << " (" << namaMaks << ")"
             << " | Terendah: " << min << " (" << namaMin << ")\n";
    }
}

// Cari Siswa (case-insensitive)
void cariSiswa(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string cari;
    cout << "Nama siswa: ";
    getline(cin, cari);

    string cariLower = toLowerStr(cari);

    for (int i = 0; i < n; i++) {
        if (toLowerStr(nama[i]) == cariLower) {
            cout << "\nData ditemukan!\n";
            for (int j = 0; j < JUMLAH_MAPEL; j++)
                cout << mapel[j] << ": " << nilai[i][j] << endl;
            cout << "Rata-rata: " << rata[i] << endl;
            return;
        }
    }
    cout << "Tidak ditemukan!\n";
}

// Edit Data Siswa
void editData(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string cari;
    cout << "Masukkan nama siswa yang ingin diedit: ";
    getline(cin, cari);

    string cariLower = toLowerStr(cari);

    for (int i = 0; i < n; i++) {
        if (toLowerStr(nama[i]) == cariLower) {
            cout << "Edit nama (lama: " << nama[i] << "): ";
            getline(cin, nama[i]);

            for (int j = 0; j < JUMLAH_MAPEL; j++)
                nilai[i][j] = inputNilai(mapel[j]);

            cout << "Data berhasil diperbarui!\n";
            return;
        }
    }
    cout << "Siswa tidak ditemukan!\n";
}

// Hapus Data Siswa
void hapusData(string nama[], float nilai[][JUMLAH_MAPEL], int &n) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string cari;
    cout << "Masukkan nama siswa yang ingin dihapus: ";
    getline(cin, cari);

    string cariLower = toLowerStr(cari);

    for (int i = 0; i < n; i++) {
        if (toLowerStr(nama[i]) == cariLower) {
            for (int j = i; j < n - 1; j++) {
                nama[j] = nama[j + 1];
                for (int k = 0; k < JUMLAH_MAPEL; k++)
                    nilai[j][k] = nilai[j + 1][k];
            }
            n--;
            cout << "Data siswa " << cari << " berhasil dihapus!\n";
            return;
        }
    }
    cout << "Siswa tidak ditemukan!\n";
}
