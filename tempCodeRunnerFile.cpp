#include <iostream>
#include <iomanip>
#include <string>
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

int main() {
    string nama[MAX_SISWA];
    float nilai[MAX_SISWA][JUMLAH_MAPEL];
    float rata[MAX_SISWA];
    int n;
    int pilihan;

    do {
        cout << "\n=== PROGRAM REKAP NILAI ASPD ===\n";
        cout << "1. Input Data Nilai\n";
        cout << "2. Tampilkan Rekap & Ranking\n";
        cout << "3. Tampilkan Nilai Tertinggi & Terendah\n";
        cout << "4. Cari Data Siswa\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                inputData(nama, nilai, n);
                hitungRataRata(nilai, rata, n);
                break;
            case 2:
                urutkanRanking(nama, nilai, rata, n);
                tampilkanHasil(nama, nilai, rata, n);
                break;
            case 3:
                tampilNilaiTertinggiTerendah(nilai, n);
                break;
            case 4:
                cariSiswa(nama, nilai, rata, n);
                break;
            case 5:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 5);

    return 0;
}

// Input data nilai
void inputData(string nama[], float nilai[][JUMLAH_MAPEL], int &n) {
    cout << "Masukkan jumlah siswa: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        cout << "\nNama siswa ke-" << i + 1 << ": ";
        getline(cin, nama[i]);

        for (int j = 0; j < JUMLAH_MAPEL; j++) {
            while (true) {
                cout << "Nilai " << mapel[j] << ": ";
                cin >> nilai[i][j];

                if (cin.fail()) {
                    cin.clear();                      // reset error state
                    cin.ignore(10000, '\n');          // buang input yang salah
                    cout << "Input tidak valid! Masukkan angka.\n";
                    continue;                         // ulangi input
                }

                if (nilai[i][j] < 0 || nilai[i][j] > 100) {
                    cout << "Nilai harus antara 0 - 100!\n";
                    continue;                         // ulangi input
                }

                cin.ignore(10000, '\n');              // bersihkan newline
                break;                                // keluar dari loop valid
            }
        }
        cin.ignore();
    }
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
    cout << left << setw(15) << "Nama";
    for (int j = 0; j < JUMLAH_MAPEL; j++) cout << setw(8) << mapel[j];
    cout << setw(10) << "Rata2" << setw(10) << "Ranking\n";
    cout << "--------------------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << left << setw(15) << nama[i];
        for (int j = 0; j < JUMLAH_MAPEL; j++) cout << setw(8) << nilai[i][j];
        cout << setw(10) << rata[i] << setw(10) << i + 1 << endl;
    }
}

// Nilai tertinggi & terendah tiap mapel
void tampilNilaiTertinggiTerendah(float nilai[][JUMLAH_MAPEL], int n) {
    cout << "\n=== NILAI TERTINGGI & TERENDAH PER MAPEL ===\n";
    for (int j = 0; j < JUMLAH_MAPEL; j++) {
        float maks = nilai[0][j];
        float min = nilai[0][j];
        for (int i = 1; i < n; i++) {
            if (nilai[i][j] > maks) maks = nilai[i][j];
            if (nilai[i][j] < min) min = nilai[i][j];
        }
        cout << mapel[j] << " -> Tertinggi: " << maks << " | Terendah: " << min << endl;
    }
}

// Pencarian data siswa
void cariSiswa(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n) {
    string cari;
    cin.ignore();
    cout << "Masukkan nama siswa yang ingin dicari: ";
    getline(cin, cari);

    bool ditemukan = false;
    for (int i = 0; i < n; i++) {
        if (nama[i] == cari) {
            cout << "\nData nilai " << nama[i] << ":\n";
            for (int j = 0; j < JUMLAH_MAPEL; j++)
                cout << mapel[j] << ": " << nilai[i][j] << endl;
            cout << "Rata-rata: " << rata[i] << endl;
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan)
        cout << "Siswa tidak ditemukan!\n";
}
