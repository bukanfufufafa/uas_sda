#include <iostream>
#include <string>
using namespace std;

struct treeRuangan
{
    int data;
    string namaRuangan;
    bool adaMonster, adaHarta;
    treeRuangan *kiri, *kanan, *parent;
};

treeRuangan *pohonRuangan, *rootRuangan;

void deklarasi()
{
    pohonRuangan = NULL;
}

void eksplorasi(treeRuangan *rootRuangan) {
    if (rootRuangan == NULL) {
        system("CLS");
        cout << "Dungeon kosong" << endl;
        return;
    }

    treeRuangan *current = rootRuangan;
    int pilihan;

    while (true) {
        system("CLS");
        cout << "==================================================" << endl;
        cout << current->namaRuangan << endl;
        cout << "==================================================" << endl;
        cout << "Pilihan:" << endl;
        cout << "1. Pintu kiri" << endl;
        cout << "2. Pintu kanan" << endl;
        cout << "3. Kembali ke ruangan sebelumnya" << endl;
        cout << "4. Keluar dari dungeon" << endl;
        cout << "==================================================" << endl;
        cout << "Pilihan Anda: " << endl;
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            if (current -> kiri != NULL)
                current = current -> kiri;
            else
                cout << "Tidak ada node di kiri.\n";
            break;

        case 2:
            if (current -> kanan != NULL)
                current = current -> kanan;
            else
                cout << "Tidak ada node di kanan.\n";
            break;

        case 3:
            if (current -> parent != NULL)
                current = current -> parent;
            else
                cout << "Sudah di pintu awal, tidak bisa kembali lagi.\n";
            break;

        case 4:
            return;

        default:
            cout << "Pilihan tidak valid.\n";
        }
    }
}

void insertTree(treeRuangan **rootRuangan, int nilai, string nama, treeRuangan *parent = NULL)
{
    system("CLS");
    if (*rootRuangan == NULL)
    {
        *rootRuangan = new treeRuangan;
        (*rootRuangan) -> data = nilai;
        (*rootRuangan) -> namaRuangan = nama;
        (*rootRuangan) -> kiri = (*rootRuangan) -> kanan = NULL;
        (*rootRuangan) -> parent = parent;
        cout << "Data " << nilai << " berhasil ditambahkan ke dalam treeRuangan." << endl;
    }
    else if (nilai < (*rootRuangan) -> data)
    {
        insertTree(&(*rootRuangan) -> kiri, nilai, nama, *rootRuangan);
    }
    else
    {
        insertTree(&(*rootRuangan) -> kanan, nilai, nama, *rootRuangan);
    }
}

int main() {
    deklarasi();

    insertTree(&pohonRuangan, 10, "Ruangan awal, ada lentera yang menyala.");
    insertTree(&pohonRuangan, 5, "Ruangan gelap dengan bau lembab.");
    insertTree(&pohonRuangan, 4, "Ruangan kecil, terdapat tulisan di dinding.");
    insertTree(&pohonRuangan, 30, "Ruangan besar dengan langit-langit tinggi.");
    insertTree(&pohonRuangan, 7, "Ruangan dengan meja kayu dan beberapa kursi.");
    insertTree(&pohonRuangan, 90, "Ruangan terakhir, terlihat ada peti harta karun.");

    eksplorasi(pohonRuangan);

    return 0;
}