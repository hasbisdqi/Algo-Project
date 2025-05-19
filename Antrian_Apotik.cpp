#include <iostream>
#include <string>
#include <fstream>
#include <stack>
using namespace std;

// ========================== STRUCT & GLOBAL ==========================
struct Pasien {
    string nama;
    Pasien* next;
};

struct Obat {
    string nama;
    int stok;
    Obat* prev;
    Obat* next;
};

struct Node {
    string nama;
    Node* kiri;
    Node* kanan;
};

Pasien* front = NULL;
Pasien* rear = NULL;
Obat* headObat = NULL;
stack<string> riwayat;

// ========================== ANTRIAN (QUEUE) ==========================
void tambahPasien(string nama) {
    Pasien* baru = new Pasien{nama, NULL};
    if (!rear) front = rear = baru;
    else {
        rear->next = baru;
        rear = baru;
    }
    cout << "Pasien " << nama << " ditambahkan ke antrian.\n";
}

void layaniPasien() {
    if (!front) {
        cout << "Antrian kosong.\n";
        return;
    }
    Pasien* hapus = front;
    cout << "Melayani pasien: " << hapus->nama << endl;
    riwayat.push(hapus->nama);
    front = front->next;
    if (!front) rear = NULL;
    delete hapus;
}

void tampilAntrian() {
    if (!front) {
        cout << "Antrian kosong.\n";
        return;
    }
    Pasien* curr = front;
    cout << "Antrian saat ini:\n";
    while (curr) {
        cout << "- " << curr->nama << endl;
        curr = curr->next;
    }
}

// ========================== OBAT (LINKED LIST GANDA) ==========================
void tambahObat() {
    string nama;
    int stok;
    cout << "Nama Obat: "; getline(cin, nama);
    cout << "Stok: "; cin >> stok; cin.ignore();

    Obat* baru = new Obat{nama, stok, NULL, NULL};
    if (!headObat) headObat = baru;
    else {
        Obat* temp = headObat;
        while (temp->next) temp = temp->next;
        temp->next = baru;
        baru->prev = temp;
    }
    cout << "Obat ditambahkan.\n";
}

void tampilObat() {
    Obat* temp = headObat;
    if (!temp) {
        cout << "Belum ada obat.\n";
        return;
    }
    cout << "Daftar Obat:\n";
    while (temp) {
        cout << "- " << temp->nama << " (Stok: " << temp->stok << ")\n";
        temp = temp->next;
    }
}

void cariObat(string nama) {
    Obat* temp = headObat;
    while (temp) {
        if (temp->nama == nama) {
            cout << "Obat ditemukan: " << temp->nama << ", Stok: " << temp->stok << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Obat tidak ditemukan.\n";
}

void urutkanObat() {
    if (!headObat) return;
    for (Obat* i = headObat; i->next; i = i->next) {
        for (Obat* j = i->next; j; j = j->next) {
            if (i->nama > j->nama) {
                swap(i->nama, j->nama);
                swap(i->stok, j->stok);
            }
        }
    }
    cout << "Obat diurutkan berdasarkan nama.\n";
}

// ========================== FILE ==========================
void simpanData() {
    ofstream file("obat.txt");
    Obat* temp = headObat;
    while (temp) {
        file << temp->nama << "," << temp->stok << endl;
        temp = temp->next;
    }
    file.close();
    cout << "Data obat disimpan ke 'obat.txt'\n";
}

// ========================== STACK RIWAYAT ==========================
void tampilRiwayat() {
    if (riwayat.empty()) {
        cout << "Belum ada riwayat transaksi.\n";
        return;
    }
    stack<string> temp = riwayat;
    cout << "Riwayat transaksi:\n";
    while (!temp.empty()) {
        cout << "- " << temp.top() << endl;
        temp.pop();
    }
}

// ========================== BINARY TREE ==========================
Node* buatNode(string nama) {
    return new Node{nama, NULL, NULL};
}

Node* tambahNode(Node* akar, string nama) {
    if (!akar) return buatNode(nama);
    if (nama < akar->nama) akar->kiri = tambahNode(akar->kiri, nama);
    else akar->kanan = tambahNode(akar->kanan, nama);
    return akar;
}

void inorder(Node* akar) {
    if (akar) {
        inorder(akar->kiri);
        cout << akar->nama << " ";
        inorder(akar->kanan);
    }
}

// ========================== MAIN ==========================
int main() {
    int pilihan;
    string nama;
    Node* pohon = NULL;

    do {
        cout << "\n=== MENU ANTRIAN APOTIK ===\n";
        cout << "1. Tambah Pasien\n";
        cout << "2. Layani Pasien\n";
        cout << "3. Tampilkan Antrian\n";
        cout << "4. Tambah Obat\n";
        cout << "5. Tampilkan Obat\n";
        cout << "6. Cari Obat\n";
        cout << "7. Urutkan Obat\n";
        cout << "8. Tampilkan Riwayat Transaksi\n";
        cout << "9. Simpan Data Obat\n";
        cout << "10. Masukkan ke Pohon & Tampilkan (Inorder)\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch(pilihan) {
            case 1:
                cout << "Nama Pasien: ";
                getline(cin, nama);
                tambahPasien(nama);
                break;
            case 2:
                layaniPasien();
                break;
            case 3:
                tampilAntrian();
                break;
            case 4:
                tambahObat();
                break;
            case 5:
                tampilObat();
                break;
            case 6:
                cout << "Cari nama obat: ";
                getline(cin, nama);
                cariObat(nama);
                break;
            case 7:
                urutkanObat();
                break;
            case 8:
                tampilRiwayat();
                break;
            case 9:
                simpanData();
                break;
            case 10:
                pohon = NULL;
                for (Obat* temp = headObat; temp; temp = temp->next)
                    pohon = tambahNode(pohon, temp->nama);
                cout << "Pohon Inorder: ";
                inorder(pohon);
                cout << endl;
                break;
            case 0:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    return 0;
}
