#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>
using namespace std;

const int MAKS = 100;

struct Daging {
    int id;
    string nama;
    int stok;
    double harga;
};

struct Penjualan {
    string namaDaging;
    int jumlah;
    double total;
};

struct User {
    string username;
    string password;
};

Daging daftarDaging[MAKS];
Penjualan riwayat[MAKS];
User users[MAKS] = { {"admin", "123"} };
int jumlahUser = 1;
int jumlahDaging = 0;
int jumlahRiwayat = 0;
bool isAdmin = false;

void clearScreen() {
    system("cls");
}

int inputAngka() {
    int nilai;
    cin >> nilai;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Input harus berupa angka!");
    }
    return nilai;
}

double inputDouble() {
    double nilai;
    cin >> nilai;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Input harus berupa angka desimal!");
    }
    return nilai;
}

void inputPassword(string* password) {
    cout << "Masukkan password: ";
    cin >> *password;
}

void loginUser();
void registerUser();
void menuAdmin();
void menuUser();
void tambahDagingPtr(Daging *arr, int *pCount);
void tampilDagingPtr(Daging *arr, int count);
void sortingDaging(Daging *arr, int count, int mode);
void updateDagingPtr(Daging *arr, int count);
void hapusDagingPtr(Daging *arr, int *pCount);
void searchDagingById(Daging *arr, int count);
void searchDagingByNama(Daging *arr, int count);
void beliDaging();
void tampilRiwayat();

int main() {
    daftarDaging[0] = {1, "Sapi", 5, 120000};
    daftarDaging[1] = {2, "Ayam", 6, 45000};
    daftarDaging[2] = {3, "B2", 10, 50000};
    jumlahDaging = 3;

    int pilihan;
    do {
        try {
            clearScreen();
            cout << "\n=== MeatSOP ===\n";
            cout << "1. Login\n2. Register\n3. Keluar\n";
            cout << "Pilihan: ";
            pilihan = inputAngka();
            switch (pilihan) {
                case 1: loginUser(); break;
                case 2: registerUser(); break;
                case 3: cout << "Keluar dari program.\n"; break;
                default: cout << "Pilihan tidak valid.\n"; break;
            }
            cout << "Tekan enter untuk lanjut...";
            cin.ignore();
            cin.get();
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
            cout << "Tekan enter untuk coba lagi...";
            cin.ignore();
            cin.get();
        }
    } while (pilihan != 3);
    return 0;
}

void loginUser() {
    string user, pass;
    cout << "Username: "; cin >> user;
    inputPassword(&pass);
    for (int i = 0; i < jumlahUser; i++) {
        if (users[i].username == user && users[i].password == pass) {
            cout << "Login berhasil sebagai " << user << endl;
            isAdmin = (user == "admin");
            if (isAdmin) menuAdmin();
            else menuUser();
            return;
        }
    }
    cout << "Login gagal!\n";
}

void registerUser() {
    string user, pass;
    cout << "Masukkan username baru: "; cin >> user;
    for (int i = 0; i < jumlahUser; i++) {
        if (users[i].username == user) {
            cout << "Username sudah digunakan.\n";
            return;
        }
    }
    inputPassword(&pass);
    users[jumlahUser++] = {user, pass};
    cout << "Registrasi berhasil!\n";
}

// ================= MENU ADMIN =================
void menuAdmin() {
    int pilihan;
    do {
        try {
            cout << "\n--- Menu Admin ---\n";
            cout << "1. Tambah Daging\n2. Tampil Daging\n3. Update Daging\n4. Hapus Daging\n5. Riwayat Penjualan\n6. Cari Daging (ID)\n7. Cari Daging (Nama)\n8. Logout\n";
            cout << "Pilihan: ";
            pilihan = inputAngka();
            switch (pilihan) {
                case 1: tambahDagingPtr(daftarDaging, &jumlahDaging); break;
                case 2: tampilDagingPtr(daftarDaging, jumlahDaging); break;
                case 3: updateDagingPtr(daftarDaging, jumlahDaging); break;
                case 4: hapusDagingPtr(daftarDaging, &jumlahDaging); break;
                case 5: tampilRiwayat(); break;
                case 6: searchDagingById(daftarDaging, jumlahDaging); break;
                case 7: searchDagingByNama(daftarDaging, jumlahDaging); break;
                case 8: cout << "Logout.\n"; break;
                default: cout << "Pilihan tidak valid!\n"; break;
            }
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
            cout << "Tekan enter untuk coba lagi...";
            cin.ignore();
            cin.get();
        }
    } while (pilihan != 8);
}

// ================= MENU USER =================
void menuUser() {
    int pilihan;
    do {
        try {
            cout << "\n--- Menu User ---\n";
            cout << "1. Tampilkan Daging\n2. Pesan Daging\n3. Cari Daging (Nama)\n4. Logout\n";
            cout << "Pilihan: ";
            pilihan = inputAngka();
            switch (pilihan) {
                case 1: tampilDagingPtr(daftarDaging, jumlahDaging); break;
                case 2: beliDaging(); break;
                case 3: searchDagingByNama(daftarDaging, jumlahDaging); break;
                case 4: cout << "Logout.\n"; break;
                default: cout << "Pilihan tidak valid!\n"; break;
            }
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
            cout << "Tekan enter untuk coba lagi...";
            cin.ignore();
            cin.get();
        }
    } while (pilihan != 4);
}

void tambahDagingPtr(Daging *arr, int *pCount) {
    if (*pCount >= MAKS) {
        cout << "Data penuh!\n";
        return;
    }

    try {
        Daging d;
        cout << "ID Daging: ";
        d.id = inputAngka();

        for (int i = 0; i < *pCount; i++) {
            if (arr[i].id == d.id) {
                cout << "Error: ID sudah digunakan.\n";
                return;
            }
        }

        cout << "Nama Daging: "; cin.ignore(); getline(cin, d.nama);

        for (int i = 0; i < *pCount; i++) {
            if (arr[i].nama == d.nama) {
                cout << "Error: Nama daging sudah ada.\n";
                return;
            }
        }

        cout << "Stok: ";
        d.stok = inputAngka();
        if (d.stok < 0) throw runtime_error("Stok tidak boleh minus!");

        cout << "Harga: ";
        d.harga = inputDouble();
        if (d.harga < 0) throw runtime_error("Harga tidak boleh minus!");

        arr[(*pCount)++] = d;
        cout << "Daging ditambahkan.\n";
    } catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
    }
}

void tampilDagingPtr(Daging *arr, int count) {
    if (count == 0) {
        cout << "Tidak ada data daging.\n";
        return;
    }
    try {
        clearScreen();
        int pilihanSort;
        cout << "\n--- Opsi Sorting ---\n";
        cout << "1. Harga Termurah\n";
        cout << "2. Harga Termahal\n";
        cout << "3. Stok Terendah\n";
        cout << "4. Stok Tertinggi\n";
        cout << "5. Tanpa Sorting\n";
        cout << "Pilihan: ";
        pilihanSort = inputAngka();

        switch (pilihanSort) {
            case 1:
            case 2:
            case 3:
            case 4:
                sortingDaging(arr, count, pilihanSort);
                break;
            case 5:
                cout << "\nMenampilkan tanpa sorting...\n";
                break;
            default:
                cout << "\nPilihan tidak valid.\n";
                return;
        }

        cout << "\n--- Daftar Daging ---\n";
        cout << "ID\tNama\tStok\tHarga\n";
        for (int i = 0; i < count; i++) {
            cout << arr[i].id << "\t" << arr[i].nama << "\t" << arr[i].stok << "\tRp" << arr[i].harga << endl;
        }

        cout << "Tekan enter untuk kembali...";
        cin.ignore();
        cin.get();

    } catch (...) {
        cout << "Terjadi kesalahan saat menampilkan daging.\n";
    }
}


void tampilDagingPtrupdate(Daging *arr, int count) {
    if ((!daftarDaging)) {
        cout << "Tidak ada data daging.\n";
        return;
    }

    try {
        clearScreen();
        cout << "\n--- Daftar Daging ---\n";
        cout << "ID\tNama\tStok\tHarga\n";
        for (int i = 0; i < count; i++) {
            cout << arr[i].id << "\t" << arr[i].nama << "\t" << arr[i].stok << "\tRp" << arr[i].harga << endl;
        }
    } catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
    }
}
void sortingDaging(Daging *arr, int count, int mode) {
    clearScreen();
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            bool tukar = false;
            switch (mode) {
                case 1: tukar = arr[i].harga > arr[j].harga; break;
                case 2: tukar = arr[i].harga < arr[j].harga; break;
                case 3: tukar = arr[i].stok > arr[j].stok; break;
                case 4: tukar = arr[i].stok < arr[j].stok; break;
            }
            if (tukar) {
                Daging temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void updateDagingPtr(Daging *arr, int count) {
    try {
        clearScreen();
        tampilDagingPtrupdate(daftarDaging, jumlahDaging);
        cout << "Masukkan ID daging yang ingin diupdate: ";
        int id = inputAngka();
        for (int i = 0; i < count; i++) {
            if (arr[i].id == id) {
                cout << "Nama baru: "; cin.ignore(); getline(cin, arr[i].nama);
                cout << "Stok baru: ";
                arr[i].stok = inputAngka();
                if (arr[i].stok < 0) throw runtime_error("Stok tidak boleh minus!");
                cout << "Harga baru: ";
                arr[i].harga = inputDouble();
                if (arr[i].harga < 0) throw runtime_error("Harga tidak boleh minus!");
                cout << "Data diperbarui.\n";
                return;
            }
        }
        cout << "ID tidak ditemukan.\n";
    } catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
    }
}

void hapusDagingPtr(Daging *arr, int *pCount) {
    try {
        clearScreen();
        tampilDagingPtrupdate(daftarDaging, jumlahDaging);
        cout << "Masukkan ID daging yang ingin dihapus: ";
        int id = inputAngka();
        for (int i = 0; i < *pCount; i++) {
            if (arr[i].id == id) {
                for (int j = i; j < *pCount - 1; j++) {
                    arr[j] = arr[j + 1];
                }
                (*pCount)--;
                cout << "Daging dihapus.\n";
                return;
            }
        }
        cout << "ID tidak ditemukan.\n";
    } catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
    }
}

void searchDagingById(Daging *arr, int count) {
    try {
        clearScreen();
        cout << "Masukkan ID yang dicari: ";
        int id = inputAngka();
        for (int i = 0; i < count; i++) {
            if (arr[i].id == id) {
                cout << "\nData ditemukan:\n";
                cout << "ID: " << arr[i].id << ", Nama: " << arr[i].nama << ", Stok: " << arr[i].stok << ", Harga: Rp" << arr[i].harga << endl;
                return;
            }
        }
        cout << "Data tidak ditemukan.\n";
    } catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
    }
}

void searchDagingByNama(Daging *arr, int count) {
    string keyword;
    cout << "Masukkan nama yang dicari: "; cin.ignore(); getline(cin, keyword);
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

    bool found = false;
    cout << "\nHasil pencarian:\n";
    for (int i = 0; i < count; i++) {
        string namaLower = arr[i].nama;
        transform(namaLower.begin(), namaLower.end(), namaLower.begin(), ::tolower);
        if (namaLower.find(keyword) != string::npos) {
            cout << "ID: " << arr[i].id << ", Nama: " << arr[i].nama << ", Stok: " << arr[i].stok << ", Harga: Rp" << arr[i].harga << endl;
            found = true;
        }
    }
    if (!found) cout << "Tidak ditemukan.\n";
}

void beliDaging() {
    int id, jumlah;
    double totalHarga = 0;
    bool lanjut = true;

    struct Pembelian {
        string nama;
        int jumlah;
        double hargaTotal;
    };
    Pembelian daftarPembelian[MAKS];
    int pembelianCount = 0;

    while (lanjut) {
        clearScreen();
        try {
            tampilDagingPtrupdate(daftarDaging, jumlahDaging);
            cout << "Masukkan ID daging yang ingin dibeli: ";
            id = inputAngka();

            int index = -1;
            for (int i = 0; i < jumlahDaging; i++) {
                if (daftarDaging[i].id == id) {
                    index = i;
                    break;
                }
            }

            if (index == -1) {
                cout << "ID tidak ditemukan.\n";
            } else {
                cout << "Jumlah yang ingin dibeli: ";
                jumlah = inputAngka();

                if (jumlah <= 0) {
                    throw runtime_error("Jumlah harus lebih dari 0.");
                }
                if (jumlah > daftarDaging[index].stok) {
                    throw runtime_error("Stok tidak mencukupi.");
                }

                double subtotal = jumlah * daftarDaging[index].harga;
                daftarPembelian[pembelianCount++] = {
                    daftarDaging[index].nama, jumlah, subtotal
                };
                daftarDaging[index].stok -= jumlah;
                totalHarga += subtotal;

                cout << "Berhasil ditambahkan ke keranjang.\n";
            }

            char jawaban;
            cout << "Ingin beli lagi? (y/n): ";
            cin >> jawaban;
            lanjut = (jawaban == 'y' || jawaban == 'Y');

        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    if (pembelianCount > 0) {
        cout << fixed << setprecision(2);  
        cout << "\n=== Ringkasan Pembelian ===\n";
        for (int i = 0; i < pembelianCount; i++) {
            cout << daftarPembelian[i].nama
                << " x" << daftarPembelian[i].jumlah
                << " = Rp" << daftarPembelian[i].hargaTotal << endl;

            if (jumlahRiwayat < MAKS) {
                riwayat[jumlahRiwayat++] = {
                    daftarPembelian[i].nama,
                    daftarPembelian[i].jumlah,
                    daftarPembelian[i].hargaTotal
                };
            }
        }
        cout << "Total Pembayaran: Rp" << totalHarga << endl;
        cout << "Terima kasih sudah berbelanja!\n";
    } else {
        cout << "Tidak ada pembelian.\n";
    }

    cout << "Tekan enter untuk kembali...";
    cin.ignore();
    cin.get();
}

void tampilRiwayat() {
    clearScreen();
    if (jumlahRiwayat == 0) {
        cout << "Riwayat kosong.\n";
        return;
    }

    double totalHargaKeseluruhan = 0;
    int totalJumlahDaging = 0;

    cout << "\n--- Riwayat Penjualan ---\n";
    cout << "Nama\tJumlah\tTotal Harga\n";

    for (int i = 0; i < jumlahRiwayat; i++) {
        cout << riwayat[i].namaDaging << "\t" 
             << riwayat[i].jumlah << "\tRp" 
             << fixed << setprecision(0) << riwayat[i].total << endl;

        totalJumlahDaging += riwayat[i].jumlah;
        totalHargaKeseluruhan += riwayat[i].total;
    }

    cout << "\nTotal jumlah daging terjual: " << totalJumlahDaging << endl;
    cout << "Total pendapatan: Rp" << fixed << setprecision(0) << totalHargaKeseluruhan << endl;
}