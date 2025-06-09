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
