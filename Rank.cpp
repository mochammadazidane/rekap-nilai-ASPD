#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

const int MAX_SISWA = 36;
const int JUMLAH_MAPEL = 3;
string mapel[JUMLAH_MAPEL] = {"Literasi Membaca", "Literasi Numerik", "Literasi Sains"};

// Prototipe fungsi
void inputData(string nama[], float nilai[][JUMLAH_MAPEL], int &n);
void hitungRataRata(float nilai[][JUMLAH_MAPEL], float rata[], int n);
void urutkanRanking(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n);
void tampilkanHasil(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n);
void tampilNilaiTertinggiTerendah(float nilai[][JUMLAH_MAPEL], int n);
void cariSiswa(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n);
int inputMenuUtama();
int inputJumlahSiswa();
float inputNilai(string namaMapel);

int main() {
    string nama[MAX_SISWA];
    float nilai[MAX_SISWA][JUMLAH_MAPEL];
    float rata[MAX_SISWA];
    int n = 0;
    int pilihan;
    bool dataExists = false;

    do {
        cout << "\n=== PROGRAM REKAP NILAI ASPD ===\n";
        cout << "1. Input Data Nilai\n";
        cout << "2. Tampilkan Rekap & Ranking\n";
        cout << "3. Tampilkan Nilai Tertinggi & Terendah\n";
        cout << "4. Cari Data Siswa\n";
        cout << "5. Keluar\n";
        
        pilihan = inputMenuUtama();

        switch (pilihan) {
            case 1:
                inputData(nama, nilai, n);
                hitungRataRata(nilai, rata, n);
                dataExists = true;
                break;
            case 2:
                if (!dataExists) {
                    cout << "\nBelum ada data! Silakan input data terlebih dahulu.\n";
                } else {
                    urutkanRanking(nama, nilai, rata, n);
                    tampilkanHasil(nama, nilai, rata, n);
                }
                break;
            case 3:
                if (!dataExists) {
                    cout << "\nBelum ada data! Silakan input data terlebih dahulu.\n";
                } else {
                    tampilNilaiTertinggiTerendah(nilai, n);
                }
                break;
            case 4:
                if (!dataExists) {
                    cout << "\nBelum ada data! Silakan input data terlebih dahulu.\n";
                } else {
                    cariSiswa(nama, nilai, rata, n);
                }
                break;
            case 5:
                cout << "\nTerima kasih telah menggunakan program ini!\n";
                break;
            default:
                cout << "\nPilihan tidak valid! Silakan pilih 1-5.\n";
        }
    } while (pilihan != 5);

    return 0;
}

// Fungsi untuk input menu utama dengan validasi
int inputMenuUtama() {
    int pilihan;
    while (true) {
        cout << "Pilih menu (1-5): ";
        cin >> pilihan;

        
        if (pilihan >= 1 && pilihan <= 5) {
            return pilihan;
        } else {
            cout << "Pilihan harus antara 1-5!\n\n";
        }
    }
}

// Fungsi untuk input jumlah siswa dengan validasi
int inputJumlahSiswa() {
    int jumlah;
    while (true) {
        cout << "Masukkan jumlah siswa (1-" << MAX_SISWA << "): ";
        cin >> jumlah;
        
        if (jumlah < 1 || jumlah > MAX_SISWA) {
            cout << "Jumlah siswa harus antara 1-" << MAX_SISWA << "!\n";
            continue;
        }
        
        return jumlah;
    }
}

// Fungsi untuk input nilai dengan validasi
float inputNilai(string namaMapel) {
    float nilaiInput;
    while (true) {
        cout << "Nilai " << namaMapel << " (0-100): ";
        cin >> nilaiInput;
        
        if (nilaiInput < 0 || nilaiInput > 100) {
            cout << "Nilai harus antara 0-100!\n";
            continue;
        }
        
        return nilaiInput;
    }
}

// Input data nilai
void inputData(string nama[], float nilai[][JUMLAH_MAPEL], int &n) {
    cout << "\n=== INPUT DATA NILAI ===\n";
    n = inputJumlahSiswa();

    for (int i = 0; i < n; i++) {
    cout << "\n--- Data Siswa ke-" << i + 1 << " ---\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
    
    cout << "\nSemua data berhasil diinput!\n";
}

// Hitung rata-rata tiap siswa
void hitungRataRata(float nilai[][JUMLAH_MAPEL], float rata[], int n) {
    for (int i = 0; i < n; i++) {
        float total = 0;
        for (int j = 0; j < JUMLAH_MAPEL; j++) {
            total += nilai[i][j];
        }
        rata[i] = total / JUMLAH_MAPEL;
    }
}

// Urutkan berdasarkan rata-rata (Bubble Sort)
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

// Tampilkan hasil rekap dan ranking
void tampilkanHasil(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n) {
    cout << "\n=== REKAP NILAI ASPD ===\n";
    cout << left << setw(5) << "Rank" << setw(20) << "Nama";
    for (int j = 0; j < JUMLAH_MAPEL; j++) {
        cout << setw(20) << mapel[j];
    }
    cout << setw(10) << "Rata-rata\n";
    cout << string(95, '=') << endl;

    for (int i = 0; i < n; i++) {
        cout << left << setw(5) << i + 1 
             << setw(20) << nama[i];
        for (int j = 0; j < JUMLAH_MAPEL; j++) {
            cout << setw(20) << fixed << setprecision(2) << nilai[i][j];
        }
        cout << setw(10) << fixed << setprecision(2) << rata[i] << endl;
    }
    cout << string(95, '=') << endl;
}

// Nilai tertinggi & terendah tiap mapel
void tampilNilaiTertinggiTerendah(float nilai[][JUMLAH_MAPEL], int n) {
    cout << "\n=== NILAI TERTINGGI & TERENDAH PER MAPEL ===\n";
    cout << string(60, '=') << endl;
    
    for (int j = 0; j < JUMLAH_MAPEL; j++) {
        float maks = nilai[0][j];
        float min = nilai[0][j];
        
        for (int i = 1; i < n; i++) {
            if (nilai[i][j] > maks) maks = nilai[i][j];
            if (nilai[i][j] < min) min = nilai[i][j];
        }
        
        cout << left << setw(25) << mapel[j] 
             << "| Tertinggi: " << fixed << setprecision(2) << setw(7) << maks 
             << "| Terendah: " << fixed << setprecision(2) << min << endl;
    }
    cout << string(60, '=') << endl;
}

// Pencarian data siswa
void cariSiswa(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n) {
    string cari;
    cout << "\n=== PENCARIAN DATA SISWA ===\n";
    cout << "Masukkan nama siswa yang ingin dicari: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, cari);
    
    // Hapus spasi di awal dan akhir
    size_t start = cari.find_first_not_of(" \t");
    size_t end = cari.find_last_not_of(" \t");
    
    if (start != string::npos) {
        cari = cari.substr(start, end - start + 1);
    }

    bool ditemukan = false;
    for (int i = 0; i < n; i++) {
        if (nama[i] == cari) {
            cout << "\n--- Data Nilai " << nama[i] << " ---\n";
            for (int j = 0; j < JUMLAH_MAPEL; j++) {
                cout << left << setw(25) << mapel[j] 
                     << ": " << fixed << setprecision(2) << nilai[i][j] << endl;
            }
            cout << string(40, '-') << endl;
            cout << left << setw(25) << "Rata-rata" 
                 << ": " << fixed << setprecision(2) << rata[i] << endl;
            ditemukan = true;
            break;
        }
    }
    
    if (!ditemukan) {
        cout << "\nSiswa dengan nama '" << cari << "' tidak ditemukan!\n";
    }
}