#include <iostream>
using namespace std;

struct Karakter
{
    string namaKarakter;
    int hp;
    int attack;
    int speed;
    bool isPlayer;

    bool isAlive()
    {
        if (hp > 0)
        {
            return true;
        }
        return false;
    }

    void takeDamage(int dmg)
    {
        hp -= dmg;
        if (hp < 0)
        {
            hp = 0;
        }
    }
};

const int maksAntrian=10;

struct antriGiliran
{
    Karakter* data[maksAntrian];
    int depan = 0;
    
    bool isEmpty()
    {
        if (depan == 0)
        {
            return true;
        }
        return false;
    }

    bool isFull()
    {
        if (depan == maksAntrian)
        {
            return true;
        }
        return false;
    }

    void masukAntrian(Karakter* karakter)
    {
        if (isFull())
        {
            cout << "Antrian Giliran sudah penuh!" << endl;
        }
        else
        {
            data[depan++] = karakter;
            cout << "Karakter " << karakter -> namaKarakter << " sudah masuk dalam antrian" << endl;
        }
    }


    Karakter* keluarAntrian()
    {
        if (isEmpty())
        {
            cout << "Antrian Giliran Kosong!" << endl;
            return NULL;
        }
        else
        {
            Karakter* barisanDepan = data[0];
            for (int i = 1; i < depan; i++)
            {
                data[i - 1] = data[i];
            }
            depan--;
            return barisanDepan;
        }
    }
};

void urutanGiliran(Karakter* arr[], int jumlah)
{
    for (int i = 0; i < jumlah - 1; i++)
    {
        for (int j = 0; j < jumlah - i - 1; j++)
        {
            if (arr[j] -> speed < arr[j + 1] -> speed)
            {
                Karakter* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void printStatus(Karakter* list[], int count)
{
    cout << "=== STATUS ===" << endl;
    for (int i = 0; i < count; i++)
    {
        cout << list[i] -> namaKarakter << " - HP: " << list[i] -> hp << endl;
    }
}

void giliranTim(Karakter* player, Karakter* musuh[], int jumlahMusuh)
{
    int pilihan;

    cout << "--- Giliran " << player -> namaKarakter << " ---" << endl;
    cout << "Pilih target musuh: "; cin >> pilihan;
    for (int i = 0; i < jumlahMusuh; i++)
    {
        if (musuh[i] -> isAlive())
        {
            cout << i + 1 << ". " << musuh[i] -> namaKarakter << " (HP: " << musuh[i] -> hp << endl;
        }
    }

    Karakter* target = musuh[pilihan - 1];

    if (target -> isAlive())
    {
        cout << player -> namaKarakter << " menyerang " << target -> namaKarakter << " sebesar " << player -> attack << endl;
    }
    else
    {
        cout << "Target sudah mati!" << endl;
    }
}

void giliranMusuh(Karakter* musuh, Karakter* players[], int jumlahPlayer)
{
    cout << "--- Giliran Musuh: " << musuh -> namaKarakter << " ---" << endl;
    Karakter* target = NULL;

    for (int i = 0; i < jumlahPlayer; i++)
    {
        if (players[i] -> isAlive())
        {
            target = players[i];
            break;
        }
    }

    if (target != NULL)
    {
        cout << musuh -> namaKarakter << " menyerang " << target -> namaKarakter << " sebesar " << musuh -> attack << endl;
        target -> takeDamage(musuh -> attack);
    }
    else
    {
        cout << musuh -> namaKarakter << " tidak punya target yang masih hidup" << endl;
    }
}

void mulaiTurnBase(Karakter* musuh, Karakter* players[], int jumlahPlayer)
{
    int maks = 10;
    Karakter* semua[maks];
    int total = 0;

    for (int i = 0; i < jumlahPlayer; i++)
    {
        if (players[i] -> isAlive())
        {
            semua[total++] = players[i];
        }
    }

    if (musuh -> isAlive())
    {
        semua[total++] = musuh;
    }

    urutanGiliran(semua, total);

    antriGiliran antriGiliran;
    for (int i = 0; i < total; i++)
    {
        antriGiliran.masukAntrian(semua[i]);
    }

    while (musuh->isAlive()) {
        bool masihAdaPlayerHidup = false;
        for (int i = 0; i < jumlahPlayer; i++) {
            if (players[i]->isAlive()) {
                masihAdaPlayerHidup = true;
                break;
            }
        }

        if (!masihAdaPlayerHidup) {
            break;
        }

        Karakter* sekarang = antriGiliran.keluarAntrian();

        if (!sekarang->isAlive()) {
            continue; // lewati karakter mati
        }

        if (sekarang->isPlayer) {
            cout << "--- Giliran " << sekarang->namaKarakter << " ---" << endl;

            cout << "Pilih target musuh (1 untuk " << musuh->namaKarakter << "): ";
            int pilihan;
            cin >> pilihan;

            if (pilihan == 1 && musuh->isAlive()) {
                cout << sekarang->namaKarakter << " menyerang " << musuh->namaKarakter
                     << " sebesar " << sekarang->attack << endl;
                musuh->takeDamage(sekarang->attack);
            } else {
                cout << "Target tidak valid atau sudah mati." << endl;
            }

        } else {
            cout << "--- Giliran Musuh: " << sekarang->namaKarakter << " ---" << endl;

            Karakter* target = nullptr;
            for (int i = 0; i < jumlahPlayer; i++) {
                if (players[i]->isAlive()) {
                    target = players[i];
                    break;
                }
            }

            if (target != nullptr) {
                cout << sekarang->namaKarakter << " menyerang " << target->namaKarakter
                     << " sebesar " << sekarang->attack << endl;
                target->takeDamage(sekarang->attack);
            } else {
                cout << sekarang->namaKarakter << " tidak punya target hidup." << endl;
            }
        }

        if (sekarang->isAlive()) {
            antriGiliran.masukAntrian(sekarang);
        }
    }

    if (musuh->isAlive()) {
        cout << "Semua player kalah! Musuh menang!" << endl;
    } else {
        cout << "Musuh berhasil dikalahkan!" << endl;
    }
}

struct treeRuangan
{
    int data;
    string deskripsi;
    bool adaMusuh;
    Karakter musuh;
    treeRuangan *kiri, *kanan, *parent;
};

treeRuangan *pohonRuangan, *rootRuangan;

void deklarasi()
{
    pohonRuangan = NULL;
}

void insertRuangan(treeRuangan **rootRuangan, int nilai, string desc, bool adaMusuh = false, Karakter musuh = {}, treeRuangan *parent = NULL)
{
    if (*rootRuangan == NULL)
    {
        *rootRuangan = new treeRuangan;
        (*rootRuangan) -> data = nilai;
        (*rootRuangan) -> deskripsi = desc;
        (*rootRuangan) -> adaMusuh = adaMusuh;
        (*rootRuangan) -> musuh = musuh;
        (*rootRuangan) -> kiri = (*rootRuangan) -> kanan = NULL;
        (*rootRuangan) -> parent = parent;
    }
    else if (nilai < (*rootRuangan) -> data)
    {
        insertRuangan(&(*rootRuangan) -> kiri, nilai, desc, adaMusuh, musuh, *rootRuangan);
    }
    else
    {
        insertRuangan(&(*rootRuangan) -> kanan, nilai, desc, adaMusuh, musuh, *rootRuangan);
    }
}
