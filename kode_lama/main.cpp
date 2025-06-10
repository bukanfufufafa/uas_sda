#include <iostream>
#include <string>
using namespace std;

const int MAKS_ANTRIAN = 10;

struct Character {
    string name;
    int hp;
    int atk;
    bool isPlayer;
};

struct Queue {
    Character data[MAKS_ANTRIAN];
    int front = -1;
    int rear = -1;

    bool isEmpty() { return front == -1; }
    bool isFull() { return rear == MAKS_ANTRIAN - 1; }

    void enqueue(Character c) {
        if (isFull()) return;
        if (isEmpty()) front = rear = 0;
        else rear++;
        data[rear] = c;
    }

    Character dequeue() {
        Character temp = data[front];
        if (front == rear) front = rear = -1;
        else front++;
        return temp;
    }

    Character& frontChar() {
        return data[front];
    }

    int size() {
        return isEmpty() ? 0 : rear - front + 1;
    }
};

struct treeRuangan {
    int data;
    string namaRuangan;
    bool adaMonster, adaHarta;
    Character musuh;
    treeRuangan *kiri, *kanan, *parent;
};

treeRuangan *pohonRuangan;

void deklarasi() {
    pohonRuangan = NULL;
}
void combat(Character player, Character musuh) {
    Queue giliran;
    giliran.enqueue(player);
    giliran.enqueue(musuh);

    while (giliran.size() > 1) {
        Character attacker = giliran.dequeue();
        Character& defender = giliran.frontChar();

        cout << "\n=== Giliran: " << attacker.name << " ===\n";
        if (attacker.isPlayer) {
            int pilihan;
            cout << "HP Kamu: " << attacker.hp << " | Musuh: " << defender.name << " (HP: " << defender.hp << ")\n";
            cout << "1. Serang\n2. Skip\nPilihan: ";
            cin >> pilihan;
            if (pilihan == 1) {
                defender.hp -= attacker.atk;
                cout << attacker.name << " menyerang! \n";
            } else {
                cout << attacker.name << " memilih bertahan.\n";
            }
        } else {
            defender.hp -= attacker.atk;
            cout << attacker.name << " menyerang kamu sebesar " << attacker.atk << "!\n";
        }

        if (defender.hp <= 0) {
            cout << defender.name << " telah dikalahkan!\n";
            giliran.dequeue();
        }

        if (attacker.hp > 0) giliran.enqueue(attacker);
    }
    cout << "\nPertarungan selesai!\n";
}

void eksplorasi(treeRuangan *rootRuangan) {
    if (rootRuangan == NULL) {
        cout << "Dungeon kosong" << endl;
        return;
    }

    treeRuangan *current = rootRuangan;
    int pilihan;
    Character player = {"Player", 100, 25, true};

    while (true) {
        cout << "\n==================================================" << endl;
        cout << current->namaRuangan << endl;
        cout << "==================================================" << endl;

        if (current->adaMonster) {
            cout << "Ada monster: " << current->musuh.name << "! Bersiap untuk bertarung!\n";
            combat(player, current->musuh);
            current->adaMonster = false;
        }

        cout << "Pilihan:\n1. Pintu kiri\n2. Pintu kanan\n3. Kembali\n4. Keluar\nPilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            if (current->kiri != NULL)
                current = current->kiri;
            else {
                cout << "Tidak ada ruangan di kiri.\n";
                cout << "Tekan enter untuk melanjutkan...";
                cin.ignore(); cin.get();
            }
            break;
        case 2:
            if (current->kanan != NULL)
                current = current->kanan;
            else {
                cout << "Tidak ada ruangan di kanan.\n";
                cout << "Tekan enter untuk melanjutkan...";
                cin.ignore(); cin.get();
            }
            break;
        case 3:
            if (current->parent != NULL)
                current = current->parent;
            else {
                cout << "Sudah di ruangan awal.\n";
                cout << "Tekan enter untuk melanjutkan...";
                cin.ignore(); cin.get();
            }
            break;
        case 4:
            return;
        default:
            cout << "Pilihan tidak valid.\n";
            cout << "Tekan enter untuk melanjutkan...";
            cin.ignore(); cin.get();
        }
    }
}
void insertTree(treeRuangan **rootRuangan, int nilai, string nama, bool adaMonster = false, Character musuh = {}, treeRuangan *parent = NULL) {
    if (*rootRuangan == NULL) {
        *rootRuangan = new treeRuangan;
        (*rootRuangan)->data = nilai;
        (*rootRuangan)->namaRuangan = nama;
        (*rootRuangan)->adaMonster = adaMonster;
        (*rootRuangan)->musuh = musuh;
        (*rootRuangan)->kiri = (*rootRuangan)->kanan = NULL;
        (*rootRuangan)->parent = parent;
    } else if (nilai < (*rootRuangan)->data) {
        insertTree(&(*rootRuangan)->kiri, nilai, nama, adaMonster, musuh, *rootRuangan);
    } else {
        insertTree(&(*rootRuangan)->kanan, nilai, nama, adaMonster, musuh, *rootRuangan);
    }
}

int main() {
    deklarasi();
    Character goblin = {"Goblin", 40, 10, false};
    Character orc = {"Orc", 60, 15, false};

    insertTree(&pohonRuangan, 10, "Ruangan awal dengan lentera menyala.");
    insertTree(&pohonRuangan, 5, "Ruangan lembab dan gelap.", true, goblin);
    insertTree(&pohonRuangan, 4, "Ruangan kecil dengan ukiran aneh.");
    insertTree(&pohonRuangan, 30, "Ruangan tinggi bergema.", true, orc);
    insertTree(&pohonRuangan, 7, "Ruangan dengan meja dan kursi rusak.");
    insertTree(&pohonRuangan, 90, "Ruangan terakhir dengan peti harta.");

    eksplorasi(pohonRuangan);
    return 0;
}