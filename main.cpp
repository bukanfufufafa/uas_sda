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
    cout << "\nPertarungan selesai!\n";
}