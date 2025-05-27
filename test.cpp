#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
using namespace std;

// Struktur Data Obat dan Node
struct Obat
{
    char kode[10];
    char nama[50];
    int stok;
    float harga;
    char kadaluarsa[11];
};

struct Node
{
    Obat data;
    Node *next;
};

// Tambah Obat ke Linked List
void tambahObat(Node **head, Obat obatBaru)
{
    Node *baru = new Node;
    baru->data = obatBaru;
    baru->next = nullptr;

    if (*head == nullptr)
    {
        *head = baru;
    }
    else
    {
        Node *temp = *head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = baru;
    }
}

void printHeader() {
    cout << left << setw(10) << "Kode" << setw(20) << "Nama" << setw(6) << "Stok" << setw(10) << "Harga" << setw(12) << "Kadaluarsa" << endl;
}

void printObat(Node *head)
{
    cout << left << setw(10) << head->data.kode
         << setw(20) << head->data.nama
         << setw(6) << head->data.stok
         << setw(10) << head->data.harga
         << setw(12) << head->data.kadaluarsa << endl;
}

// Tampilkan Semua Obat
void tampilkanObat(Node *head)
{
    cout << "\nDaftar Obat:\n";
    printHeader();
    while (head != nullptr)
    {
        printObat(head);
        head = head->next;
    }
}

// Cari Obat Berdasarkan Kode
Node *cariObat(Node *head, const char *kode)
{
    while (head != nullptr)
    {
        if (strcmp(head->data.kode, kode) == 0)
            return head;
        head = head->next;
    }
    return nullptr;
}

// Hapus Obat Berdasarkan Kode
void hapusObat(Node **head, const char *kode)
{
    Node *temp = *head, *prev = nullptr;

    while (temp != nullptr && strcmp(temp->data.kode, kode) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr)
    {
        cout << "Obat dengan kode " << kode << " tidak ditemukan.\n";
        return;
    }

    if (prev == nullptr)
        *head = temp->next;
    else
        prev->next = temp->next;

    delete temp;
    cout << "Obat dengan kode " << kode << " berhasil dihapus.\n";
}

// Simpan Data ke File Biner
void simpanKeFile(Node *head, const char *namaFile)
{
    FILE *f = fopen(namaFile, "wb");
    if (!f)
    {
        cout << "Gagal membuka file!\n";
        return;
    }
    while (head != nullptr)
    {
        fwrite(&head->data, sizeof(Obat), 1, f);
        head = head->next;
    }
    fclose(f);
}

// Load Data dari File Biner
void loadDariFile(Node **head, const char *namaFile)
{
    FILE *f = fopen(namaFile, "rb");
    if (!f)
    {
        cout << "File " << namaFile << " tidak ditemukan.\n";
        return;
    }

    Obat obat;
    while (fread(&obat, sizeof(Obat), 1, f))
    {
        tambahObat(head, obat);
    }

    fclose(f);
    cout << "Data berhasil dimuat dari " << namaFile << endl;
}

// Sorting Berdasarkan Nama Obat
void sortNamaObat(Node **head)
{
    if (*head == nullptr || (*head)->next == nullptr)
        return;

    int swapped;
    Node *ptr1, *lptr = nullptr;

    do
    {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr)
        {
            if (strcmp(ptr1->data.nama, ptr1->next->data.nama) > 0)
            {
                Obat temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    cout << "Data berhasil diurutkan berdasarkan nama.\n";
}
void checkoutTransaksi(Node *head)
{
    char kode[10];
    int jumlah;
    float total = 0;

    cout << "\n=== CHECKOUT TRANSAKSI ===\n";
    while (true)
    {
        cout << "Masukkan kode obat (atau 0 untuk selesai): ";
        cin.getline(kode, 10);
        if (strcmp(kode, "0") == 0)
            break;

        Node *item = cariObat(head, kode);
        if (!item)
        {
            cout << "Obat tidak ditemukan.\n";
            continue;
        }
        printHeader();
        printObat(item);

        cout << "Jumlah yang dibeli: ";
        cin >> jumlah;
        cin.ignore();
        if (jumlah > item->data.stok)
        {
            cout << "Stok tidak mencukupi.\n";
            continue;
        }

        item->data.stok -= jumlah;
        float subtotal = jumlah * item->data.harga;
        total += subtotal;
        cout << "Subtotal: Rp " << subtotal << endl;
    }

    cout << "Total belanja: Rp " << total << endl;
}
// Fungsi Utama
int main()
{
    Node *daftarObat = nullptr;
    int choice;
    bool running = true;
    loadDariFile(&daftarObat, "data_obat.dat");

    while (running)
    {
        cout << "\n=== MENU MANAJEMEN OBAT ===" << endl;
        cout << "1. Tambah Obat" << endl;
        cout << "2. Tampilkan Obat" << endl;
        cout << "3. Hapus Obat" << endl;
        cout << "4. Cari Obat" << endl;
        cout << "5. Urutkan Nama" << endl;
        cout << "6. Checkout Transaksi" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            Obat o;
            cout << "Masukkan kode: ";
            cin.getline(o.kode, 10);
            cout << "Masukkan nama: ";
            cin.getline(o.nama, 50);
            cout << "Masukkan stok: ";
            cin >> o.stok;
            cin.ignore();
            cout << "Masukkan harga: ";
            cin >> o.harga;
            cin.ignore();
            cout << "Masukkan tanggal kadaluarsa (YYYY-MM-DD): ";
            cin.getline(o.kadaluarsa, 11);
            tambahObat(&daftarObat, o);
        }
        else if (choice == 2)
        {
            tampilkanObat(daftarObat);
        }
        else if (choice == 3)
        {
            char kode[10];
            cout << "Masukkan kode obat yang akan dihapus: ";
            cin.getline(kode, 10);
            hapusObat(&daftarObat, kode);
        }
        else if (choice == 4)
        {
            char kode[10];
            cout << "Masukkan kode obat yang dicari: ";
            cin.getline(kode, 10);
            Node *hasil = cariObat(daftarObat, kode);
            if (hasil)
            {
                cout << "Ditemukan: " << hasil->data.nama << ", Stok: " << hasil->data.stok << endl;
            }
            else
            {
                cout << "Obat tidak ditemukan." << endl;
            }
        }
        else if (choice == 5)
        {
            sortNamaObat(&daftarObat);
            tampilkanObat(daftarObat);
        }
        else if (choice == 6)
        {
            checkoutTransaksi(daftarObat);
        }
        else if (choice == 0)
        {
            running = false;
        }
        else
        {
            cout << "Pilihan tidak valid." << endl;
        }

        simpanKeFile(daftarObat, "data_obat.dat");
        if (running)
        {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
        }
    }

    return 0;
}
