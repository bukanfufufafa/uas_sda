#include <iostream>
#include <windows.h>
#include <vector>
#include <algorithm>
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
    cout << "======== STATUS PARTY ========" << endl;
    for (int i = 0; i < count; i++)
    {
        cout << list[i] -> namaKarakter << " - HP: " << list[i] -> hp << endl;
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

    while (musuh -> isAlive()) {
        bool masihAdaPlayerHidup = false;
        for (int i = 0; i < jumlahPlayer; i++) 
        {
            if (players[i] -> isAlive()) {
                masihAdaPlayerHidup = true;
                break;
            }
        }

        if (!masihAdaPlayerHidup) 
        {
            break;
        }

        Karakter* sekarang = antriGiliran.keluarAntrian();

        if (!sekarang -> isAlive()) 
        {
            continue;
        }

        if (sekarang -> isPlayer) 
        {
            printStatus(players, jumlahPlayer);
            cout << "======== STATUS MUSUH ========" << endl;
            cout << musuh -> namaKarakter << " - HP: " << musuh -> hp << endl;
            cout << "==============================" << endl;
            cout << "--- Giliran " << sekarang->namaKarakter << " ---" << endl;

            cout << "Pilih target musuh (1 untuk " << musuh->namaKarakter << "): ";
            int pilihan;
            cin >> pilihan;

            if (pilihan == 1 && musuh -> isAlive()) {
                cout << sekarang -> namaKarakter << " menyerang " << musuh->namaKarakter << " sebesar " << sekarang->attack << endl;
                musuh -> takeDamage(sekarang -> attack);
            } else {
                cout << "Target tidak valid atau sudah mati." << endl;
            }
            Sleep(2000);
            system("cls");

        } else {
            printStatus(players, jumlahPlayer);
            cout << "======== STATUS MUSUH ========" << endl;
            cout << musuh -> namaKarakter << " - HP: " << musuh -> hp << endl;
            cout << "==============================" << endl;
            cout << "--- Giliran Musuh: " << sekarang->namaKarakter << " ---" << endl;

            Karakter* target = nullptr;
            for (int i = 0; i < jumlahPlayer; i++) {
                if (players[i] -> isAlive()) {
                    target = players[i];
                    break;
                }
            }

            if (target != nullptr) {
                cout << sekarang -> namaKarakter << " menyerang " << target->namaKarakter << " sebesar " << sekarang->attack << endl;
                target -> takeDamage(sekarang->attack);
            } else {
                cout << sekarang -> namaKarakter << " tidak punya target hidup." << endl;
            }
            Sleep(2000);
            system("cls");
        }

        if (sekarang -> isAlive()) {
            antriGiliran.masukAntrian(sekarang);
        }
    }

    if (musuh -> isAlive()) {
        cout << "Semua player kalah! Musuh menang!" << endl;
        Sleep(2000);
    } else {
        cout << "Musuh berhasil dikalahkan!" << endl;
        Sleep(2000);
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
    system("cls");
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

void eksplorasi(treeRuangan *rootRuangan, Karakter* players[], int jumlahPlayer)
{
    system("cls");
    if (rootRuangan == NULL)
    {
        cout << "Dungeon kosong" << endl;
        return;
    }

    treeRuangan *current = rootRuangan;
    int pilihan;

    while (true)
    {
        system("cls");
        cout << "\n==================================================" << endl;
        cout << current -> deskripsi << endl;

        if (current -> adaMusuh)
        {
            cout << "Ada musuh: " << current -> musuh.namaKarakter << "! Bersiap untuk bertarung!" << endl;
            cout << "==================================================" << endl;
            Sleep(2000);
            system("cls");

            mulaiTurnBase(&(current -> musuh), players, jumlahPlayer);

            current -> adaMusuh = false;
        }

        if (current -> data == 90)
        {
            cout << "==================================================" << endl;
            cout << "  Selamat, kamu telah mencapai ruangan terakhir!" << endl;
            cout << "         KAMU MENANG! PERMAINAN BERAKHIR" << endl;
            cout << "==================================================" << endl;
            Sleep(3000);
            break;
        }

        cout << "==================================================" << endl;
        cout << "Pilihan: " << endl;
        cout << "1. Pintu Kiri" << endl;
        cout << "2. Pintu Kanan" << endl;
        cout << "3. Kembali ke Ruangan Sebelumnya" << endl;
        cout << "4. Keluar dari Game" << endl;
        cout << "==================================================" << endl;
        cout << "Masukkan pilihan anda: "; cin >> pilihan;

        switch (pilihan)
        {
            case 1:
                if (current -> kiri != NULL)
                {
                    current = current -> kiri;
                }
                else
                {
                    cout << "Tidak ada ruangan di sebelah kiri" << endl;
                    cout << "Tekan enter untuk melanjutkan..." << endl;
                    cin.ignore();
                    cin.get();
                    system("cls");
                }
                break;
            case 2:
                if (current -> kanan != NULL)
                {
                    current = current -> kanan;
                }
                else
                {
                    cout << "Tidak ada ruangan di sebelah kanan" << endl;
                    cout << "Tekan enter untuk melanjutkan..." << endl;
                    cin.ignore();
                    cin.get();
                    system("cls");
                }
                break;
            case 3:
                if (current -> parent != NULL)
                {
                    current = current -> parent;
                }
                else
                {
                    cout << "Sudah berada di pintu awal." << endl;
                    cout << "Tekan enter untuk melanjutkan..." << endl;
                    cin.ignore();
                    cin.get();
                    system("cls");
                }
                break;
            case 4:
                return;
            default:
                cout << "Pilihan tidak tersedia. Silakan input ulang" << endl;
                cout << "Tekan enter untuk melanjutkan..." << endl;
                cin.ignore();
                cin.get();
                system("cls");
        }
    }
}

void mulaiGame()
{
    deklarasi();
    // nama, hp, att, speed, isplayer
    Karakter knight = {"Knight", 100, 25, 15, true};
    Karakter paladin = {"Paladin", 120, 35, 10, true};
    Karakter healer = {"Healer", 100, 10, 12, true};
    Karakter jamur = {"Jamur Punya Kaki", 100, 10, 8, false};
    Karakter tengkorak1 = {"Tengkorak", 80, 18, 12, false};
    Karakter laba2 = {"Laba-Laba", 80, 12, 14, false};
    Karakter redDragon = {"Naga Merah", 200, 40, 30, false};

    vector<Karakter> semuaHero = {
    {"Knight", 100, 25, 15, true},
    {"Paladin", 120, 35, 10, true},
    {"Healer", 100, 10, 12, true},
    {"Rogue", 90, 20, 18, true},
    {"Archer", 95, 22, 17, true}
};

Karakter* players[3];

cout << "=== PILIH 3 HERO UNTUK PETUALANGANMU ===" << endl;
for (int i = 0; i < semuaHero.size(); i++) {
    cout << i + 1 << ". " << semuaHero[i].namaKarakter
         << " (HP: " << semuaHero[i].hp
         << ", ATK: " << semuaHero[i].attack
         << ", SPD: " << semuaHero[i].speed << ")" << endl;
}

int pilihan;
vector<int> terpilih;
for (int i = 0; i < 3; i++) {
    while (true) {
        cout << "Pilih hero ke-" << i + 1 << " (1-" << semuaHero.size() << "): ";
        cin >> pilihan;
        if (pilihan >= 1 && pilihan <= semuaHero.size() &&
            find(terpilih.begin(), terpilih.end(), pilihan) == terpilih.end()) {
            players[i] = &semuaHero[pilihan - 1];
            terpilih.push_back(pilihan);
            break;
        } else {
            cout << "Pilihan tidak valid atau sudah dipilih sebelumnya. Coba lagi." << endl;
        }
    }
}

    insertRuangan(&pohonRuangan, 10, "Ruangan awal dengan lentera menyala.");
    insertRuangan(&pohonRuangan, 9, "Ruangan lembab dan gelap.");
    insertRuangan(&pohonRuangan, 12, "Ruangan kecil dengan ukiran aneh.");
    insertRuangan(&pohonRuangan, 2, "Ruangan sempit penuh sarang laba-laba.", true, laba2);
    insertRuangan(&pohonRuangan, 11, "Ruangan gelap dengan suara aneh.", true, jamur);
    insertRuangan(&pohonRuangan, 100, "Ruangan penuh tulang belulang.", true, tengkorak1);
    insertRuangan(&pohonRuangan, 95, "Ruangan yang panas", true, redDragon);
    insertRuangan(&pohonRuangan, 1, "Ruangan dengan meja dan kursi rusak.");
    insertRuangan(&pohonRuangan, 7, "Ruangan dengan dinding berlumut.");
    insertRuangan(&pohonRuangan, 120, "Ruangan dengan patung misterius.");
    insertRuangan(&pohonRuangan, 90, "Ruangan terakhir dengan peti harta.");

    system("cls");

    eksplorasi(pohonRuangan, players, 3);
}

int main()
{
    system("cls");

    cout << "==================================================" << endl;
    cout << "Selamat datang di Dungeon!" << endl;
    cout << "Objektif: Mencari ruangan harta" << endl;
    cout << "==================================================" << endl;
    cout << "Tekan enter untuk memulai permainan..." << endl;
    cin.ignore(); 

    system("cls");

    mulaiGame();
}