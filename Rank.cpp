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

// Prototipe fungsi
void inputData(string nama[], float nilai[][JUMLAH_MAPEL], int &n);
void hitungRataRata(float nilai[][JUMLAH_MAPEL], float rata[], int n);
void urutkanRanking(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n);
void tampilkanHasil(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n);
void tampilNilaiTertinggiTerendah(float nilai[][JUMLAH_MAPEL], string nama[], int n);
void cariSiswa(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n);
int inputMenuUtama();
int inputMenuKelola();
int inputJumlahSiswaMax(int maxAllowed);
float inputNilai(const string &namaMapel);
int inputIntInRange(const string &prompt, int minVal, int maxVal);
bool konfirmasiYN(const string &prompt);
string toLowerStr(const string &s);

void editSiswa(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int &n);
void hapusSiswa(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int &n);
void tambahSiswa(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int &n);

int main() {
    string nama[MAX_SISWA];
    float nilai[MAX_SISWA][JUMLAH_MAPEL];
    float rata[MAX_SISWA];
    int n = 0;
    int pilihan;
    bool dataExists = false;

    do {
        cout << "\n=== PROGRAM REKAP NILAI ASPD ===\n";
        cout << "1. Input Data Nilai \n";
        cout << "2. Tampilkan Rekap & Ranking\n";
        cout << "3. Tampilkan Nilai Tertinggi & Terendah\n";
        cout << "4. Cari Data Siswa\n";
        cout << "5. Kelola Data Siswa\n";
        cout << "6. Keluar\n";
        
        pilihan = inputMenuUtama();

        switch (pilihan) {
            case 1:
                inputData(nama, nilai, n);
                hitungRataRata(nilai, rata, n);
                urutkanRanking(nama, nilai, rata, n);
                dataExists = (n > 0);
                break;
            case 2:
                if (!dataExists) {
                    cout << "\nBelum ada data! Silakan input data terlebih dahulu.\n";
                } else {
                    // assume always sorted (we ensure sorting after any add/edit/delete)
                    tampilkanHasil(nama, nilai, rata, n);
                }
                break;
            case 3:
                if (!dataExists) {
                    cout << "\nBelum ada data! Silakan input data terlebih dahulu.\n";
                } else {
                    tampilNilaiTertinggiTerendah(nilai, nama, n);
                }
                break;
            case 4:
                if (!dataExists) {
                    cout << "\nBelum ada data! Silakan input data terlebih dahulu.\n";
                } else {
                    cariSiswa(nama, nilai, rata, n);
                }
                break;
            case 5: {
                if (!dataExists) {
                    cout << "\nBelum ada data! Silakan input data terlebih dahulu.\n";
                    break;
                }
                int sub;
                do {
                    cout << "\n=== KELOLA DATA SISWA ===\n";
                    cout << "1. Edit Data Siswa\n";
                    cout << "2. Hapus Data Siswa\n";
                    cout << "3. Tambah Siswa Baru\n";
                    cout << "4. Kembali\n";
                    sub = inputMenuKelola();
                    switch (sub) {
                        case 1:
                            editSiswa(nama, nilai, rata, n);
                            break;
                        case 2:
                            hapusSiswa(nama, nilai, rata, n);
                            break;
                        case 3:
                            tambahSiswa(nama, nilai, rata, n);
                            break;
                        case 4:
                            break;
                        default:
                            cout << "Pilihan tidak valid!\n";
                    }
                } while (sub != 4);
                dataExists = (n > 0);
                break;
            }
            case 6:
                cout << "\nTerima kasih telah menggunakan program ini!\n";
                break;
            default:
                cout << "\nPilihan tidak valid! Silakan pilih 1-6.\n";
        }
    } while (pilihan != 6);

    return 0;
}

// ----------------------- Helper Input & Util -----------------------
int inputMenuUtama() {
    return inputIntInRange("Pilih menu (1-6): ", 1, 6);
}

int inputMenuKelola() {
    return inputIntInRange("Pilih submenu (1-4): ", 1, 4);
}

int inputJumlahSiswaMax(int maxAllowed) {
    return inputIntInRange(("Masukkan jumlah siswa (1-" + to_string(maxAllowed) + "): ").c_str(), 1, maxAllowed);
}

int inputIntInRange(const string &prompt, int minVal, int maxVal) {
    int val;
    while (true) {
        cout << prompt;
        if (!(cin >> val)) {
            cout << "Input harus berupa angka!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear rest of line
        if (val < minVal || val > maxVal) {
            cout << "Nilai harus antara " << minVal << "-" << maxVal << "!\n";
            continue;
        }
        return val;
    }
}

float inputNilai(const string &namaMapel) {
    float nilaiInput;
    while (true) {
        cout << "Nilai " << namaMapel << " (0-100): ";
        if (!(cin >> nilaiInput)) {
            cout << "Input harus berupa angka!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (nilaiInput < 0 || nilaiInput > 100) {
            cout << "Nilai harus antara 0-100!\n";
            continue;
        }
        return nilaiInput;
    }
}

bool konfirmasiYN(const string &prompt) {
    string s;
    while (true) {
        cout << prompt << " (Y/N): ";
        getline(cin, s);
        if (s.size() == 0) continue;
        char c = tolower(s[0]);
        if (c == 'y') return true;
        if (c == 'n') return false;
        cout << "Masukkan Y atau N saja.\n";
    }
}

string toLowerStr(const string &s) {
    string t = s;
    transform(t.begin(), t.end(), t.begin(), [](unsigned char c){ return tolower(c); });
    return t;
}

// ----------------------- Core Functions -----------------------
void inputData(string nama[], float nilai[][JUMLAH_MAPEL], int &n) {
    cout << "\n=== INPUT DATA NILAI (Reset semua data) ===\n";
    int jumlah = inputJumlahSiswaMax(MAX_SISWA);

    for (int i = 0; i < jumlah; i++) {
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
    n = jumlah;
    cout << "\nSemua data berhasil diinput!\n";
}

void hitungRataRata(float nilai[][JUMLAH_MAPEL], float rata[], int n) {
    for (int i = 0; i < n; i++) {
        float total = 0;
        for (int j = 0; j < JUMLAH_MAPEL; j++) {
            total += nilai[i][j];
        }
        rata[i] = total / JUMLAH_MAPEL;
    }
}

void urutkanRanking(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n) {
    // Bubble sort descending berdasarkan rata
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

void tampilNilaiTertinggiTerendah(float nilai[][JUMLAH_MAPEL], string nama[], int n) {
    cout << "\n=== NILAI TERTINGGI & TERENDAH PER MAPEL ===\n";
    cout << string(80, '=') << endl;
    
    for (int j = 0; j < JUMLAH_MAPEL; j++) {
        float maks = nilai[0][j];
        float min = nilai[0][j];
        
        // temukan nilai max & min
        for (int i = 1; i < n; i++) {
            if (nilai[i][j] > maks) maks = nilai[i][j];
            if (nilai[i][j] < min) min = nilai[i][j];
        }

        // kumpulkan nama yang memiliki nilai max & min
        string namaMaks = "";
        string namaMin = "";
        bool firstMaks = true, firstMin = true;
        for (int i = 0; i < n; i++) {
            if (abs(nilai[i][j] - maks) < 1e-6) {
                if (!firstMaks) namaMaks += ", ";
                namaMaks += nama[i];
                firstMaks = false;
            }
            if (abs(nilai[i][j] - min) < 1e-6) {
                if (!firstMin) namaMin += ", ";
                namaMin += nama[i];
                firstMin = false;
            }
        }
        
        cout << left << setw(25) << mapel[j] 
             << "| Tertinggi: " << fixed << setprecision(2) << setw(7) << maks 
             << "(" << namaMaks << ") "
             << "| Terendah: " << fixed << setprecision(2) << min << " (" << namaMin << ")" << endl;
    }
    cout << string(80, '=') << endl;
}

void cariSiswa(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int n) {
    string cari;
    cout << "\n=== PENCARIAN DATA SISWA ===\n";
    cout << "Masukkan nama siswa yang ingin dicari: ";
    getline(cin, cari);
    
    // Trim
    size_t start = cari.find_first_not_of(" \t");
    size_t end = cari.find_last_not_of(" \t");
    if (start == string::npos) {
        cout << "Input kosong.\n";
        return;
    }
    cari = cari.substr(start, end - start + 1);

    string cariLower = toLowerStr(cari);
    bool ditemukan = false;
    for (int i = 0; i < n; i++) {
        if (toLowerStr(nama[i]) == cariLower) {
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

// ----------------------- Kelola: Edit / Hapus / Tambah -----------------------
void editSiswa(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int &n) {
    cout << "\n=== EDIT DATA SISWA ===\n";
    cout << "Masukkan nama siswa yang ingin diedit (case-insensitive): ";
    string cari;
    getline(cin, cari);

    // Trim
    size_t start = cari.find_first_not_of(" \t");
    size_t end = cari.find_last_not_of(" \t");
    if (start == string::npos) {
        cout << "Input kosong.\n";
        return;
    }
    cari = cari.substr(start, end - start + 1);
    string cariLower = toLowerStr(cari);

    // Cari semua kecocokan (case-insensitive exact)
    int foundCount = 0;
    int indices[MAX_SISWA];
    for (int i = 0; i < n; i++) {
        if (toLowerStr(nama[i]) == cariLower) {
            indices[foundCount++] = i;
        }
    }

    if (foundCount == 0) {
        cout << "Siswa '" << cari << "' tidak ditemukan.\n";
        return;
    }

    int idx = -1;
    if (foundCount == 1) {
        idx = indices[0];
    } else {
        cout << "Ditemukan " << foundCount << " siswa dengan nama tersebut:\n";
        for (int k = 0; k < foundCount; k++) {
            cout << k+1 << ". " << nama[indices[k]] << endl;
        }
        int pilih = inputIntInRange("Pilih nomor siswa yang ingin diedit: ", 1, foundCount);
        idx = indices[pilih-1];
    }

    cout << "\n-- Data saat ini --\n";
    cout << "Nama: " << nama[idx] << endl;
    for (int j = 0; j < JUMLAH_MAPEL; j++)
        cout << mapel[j] << ": " << fixed << setprecision(2) << nilai[idx][j] << endl;

    if (konfirmasiYN("Apakah ingin mengubah nama juga?")) {
        while (true) {
            cout << "Nama baru: ";
            string namaBaru;
            getline(cin, namaBaru);
            size_t s = namaBaru.find_first_not_of(" \t");
            size_t e = namaBaru.find_last_not_of(" \t");
            if (s == string::npos) {
                cout << "Nama tidak boleh kosong!\n";
                continue;
            }
            namaBaru = namaBaru.substr(s, e - s + 1);
            nama[idx] = namaBaru;
            break;
        }
    }

    if (konfirmasiYN("Apakah ingin mengubah nilai?")) {
        for (int j = 0; j < JUMLAH_MAPEL; j++) {
            cout << "Nilai lama " << mapel[j] << ": " << fixed << setprecision(2) << nilai[idx][j] << endl;
            if (konfirmasiYN("Ubah nilai " + mapel[j] + "?")) {
                nilai[idx][j] = inputNilai(mapel[j]);
            }
        }
    }

    // setelah edit, rekalkulasi dan urutkan
    hitungRataRata(nilai, rata, n);
    urutkanRanking(nama, nilai, rata, n);
    cout << "Data siswa berhasil diperbarui dan ranking diperbarui.\n";
}

void hapusSiswa(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int &n) {
    cout << "\n=== HAPUS DATA SISWA ===\n";
    cout << "Masukkan nama siswa yang ingin dihapus (case-insensitive): ";
    string cari;
    getline(cin, cari);

    // Trim
    size_t start = cari.find_first_not_of(" \t");
    size_t end = cari.find_last_not_of(" \t");
    if (start == string::npos) {
        cout << "Input kosong.\n";
        return;
    }
    cari = cari.substr(start, end - start + 1);
    string cariLower = toLowerStr(cari);

    // Cari semua kecocokan
    int foundCount = 0;
    int indices[MAX_SISWA];
    for (int i = 0; i < n; i++) {
        if (toLowerStr(nama[i]) == cariLower) {
            indices[foundCount++] = i;
        }
    }

    if (foundCount == 0) {
        cout << "Siswa '" << cari << "' tidak ditemukan.\n";
        return;
    }

    int idx = -1;
    if (foundCount == 1) {
        idx = indices[0];
    } else {
        cout << "Ditemukan " << foundCount << " siswa dengan nama tersebut:\n";
        for (int k = 0; k < foundCount; k++) {
            cout << k+1 << ". " << nama[indices[k]] << endl;
        }
        int pilih = inputIntInRange("Pilih nomor siswa yang ingin dihapus: ", 1, foundCount);
        idx = indices[pilih-1];
    }

    cout << "\n-- Data yang akan dihapus --\n";
    cout << "Nama: " << nama[idx] << endl;
    for (int j = 0; j < JUMLAH_MAPEL; j++)
        cout << mapel[j] << ": " << fixed << setprecision(2) << nilai[idx][j] << endl;

    if (!konfirmasiYN("Yakin ingin menghapus siswa ini?")) {
        cout << "Penghapusan dibatalkan.\n";
        return;
    }

    // hapus dengan menggeser data
    for (int i = idx; i < n - 1; i++) {
        nama[i] = nama[i + 1];
        for (int j = 0; j < JUMLAH_MAPEL; j++)
            nilai[i][j] = nilai[i + 1][j];
    }
    n--;
    // rekalkulasi dan urutkan jika masih ada data
    if (n > 0) {
        hitungRataRata(nilai, rata, n);
        urutkanRanking(nama, nilai, rata, n);
    }
    cout << "Data siswa berhasil dihapus dan ranking diperbarui.\n";
}

void tambahSiswa(string nama[], float nilai[][JUMLAH_MAPEL], float rata[], int &n) {
    cout << "\n=== TAMBAH SISWA BARU ===\n";
    int spaceLeft = MAX_SISWA - n;
    if (spaceLeft <= 0) {
        cout << "Kapasitas maksimum siswa (" << MAX_SISWA << ") telah tercapai. Hapus beberapa data dulu.\n";
        return;
    }
    int qty = inputIntInRange(("Berapa siswa yang ingin ditambah? (1-" + to_string(spaceLeft) + "): ").c_str(), 1, spaceLeft);

    for (int i = 0; i < qty; i++) {
        cout << "\n--- Data Siswa Tambahan ke-" << i + 1 << " ---\n";
        while (true) {
            cout << "Nama siswa: ";
            string tmp;
            getline(cin, tmp);
            size_t s = tmp.find_first_not_of(" \t");
            size_t e = tmp.find_last_not_of(" \t");
            if (s == string::npos) {
                cout << "Nama tidak boleh kosong!\n";
                continue;
            }
            nama[n] = tmp.substr(s, e - s + 1);
            break;
        }
        for (int j = 0; j < JUMLAH_MAPEL; j++) {
            nilai[n][j] = inputNilai(mapel[j]);
        }
        cout << "Data siswa '" << nama[n] << "' berhasil ditambahkan.\n";
        n++;
    }

    // rekalkulasi dan urutkan
    hitungRataRata(nilai, rata, n);
    urutkanRanking(nama, nilai, rata, n);
    cout << "Semua siswa baru ditambahkan dan ranking diperbarui.\n";
}
