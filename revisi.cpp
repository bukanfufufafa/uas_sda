#include <iostream>
#include <windows.h>
using namespace std;

struct Karakter;

struct Skill
{
    string nama;
    int damage;
    string deskripsi;

    void gunakan (Karakter *target);
};

struct Karakter
{
    string namaKarakter;
    int hp;
    int attack;
    int speed;
    bool isPlayer;
    Skill skills[2];
    int jumlahSkill = 0;

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

void Skill::gunakan (Karakter *target)
{
    cout << "Menggunakan skill: " << nama << "!" << endl;
    target -> takeDamage(damage);
}

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

string healthBar(int hp, int maxHp, int barLength = 20)
{
    int filled = (hp * barLength) / maxHp;
    string bar = "[";

    for (int i = 0; i < barLength; i++)
    {
        if (i < filled) 
        {
            bar += "#";
        }
        else
        {
            bar += "-";
        }
    }
    bar += "]";
    return bar;
}

void printStatus(Karakter* list[], int count)
{
    cout << "======== STATUS PARTY ========" << endl;
    for (int i = 0; i < count; i++)
    {
        int maxHp = 100;
        if (list[i] -> namaKarakter == "Paladin")
        {
            maxHp = 120;
        }
        if (list[i] -> namaKarakter == "Archer")
        {
            maxHp = 90;
        }
        if (list[i] -> namaKarakter == "Mage")
        {
            maxHp = 80;
        }
        cout << list[i] -> namaKarakter << " - HP: " << list[i] -> hp << " " << healthBar(list[i] -> hp, maxHp) << endl;
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
            int maxHpMusuh = 100;
            if (musuh -> namaKarakter == "Naga Merah")
            {
                maxHpMusuh = 200;
            }

            cout << musuh -> namaKarakter << " - HP: " << musuh -> hp << " " << healthBar(musuh -> hp, maxHpMusuh) << endl;
            cout << "==============================" << endl;
            cout << "--- Giliran " << sekarang -> namaKarakter << " ---" << endl;

            cout << "Pilih aksi:" << endl;
            cout << "1. Basic Attack" << endl;
            for (int i = 0; i < sekarang -> jumlahSkill; i++)
            {
                cout << i + 2 << ". " << sekarang -> skills[i].nama << " (" << sekarang -> skills[i].deskripsi << ")" << endl;
            }
            int pilihan; 
            cin >> pilihan;

            if (pilihan == 1)
            {
                cout << "==============================" << endl;
                cout << sekarang -> namaKarakter << " menyerang " << musuh -> namaKarakter << " sebesar " << sekarang -> attack << endl;
                cout << "==============================" << endl;
                musuh -> takeDamage(sekarang -> attack);
            }
            else if (pilihan > 1 && pilihan <= 1 + sekarang -> jumlahSkill)
            {
                sekarang -> skills[pilihan - 2].gunakan(musuh);
                cout << "==============================" << endl;
                cout << sekarang -> namaKarakter << " menyerang " << musuh -> namaKarakter << " sebesar " << sekarang -> attack << endl;
                cout << "==============================" << endl;
            }
            else
            {
                cout << "Aksi tidak valid." << endl;
            }

            Sleep(3000);
            system("cls");
        } 
        else 
        {
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
            Sleep(3000);
            system("cls");
        }

        if (sekarang -> isAlive()) {
            antriGiliran.masukAntrian(sekarang);
        }
    }

    if (musuh -> isAlive()) {
        cout << "Semua player kalah! Musuh menang!" << endl;
        Sleep(3000);
    } else {
        cout << "Musuh berhasil dikalahkan!" << endl;
        Sleep(3000);
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
            Sleep(3000);
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
    Karakter archer = {"Archer", 100, 15, 20, true};
    Karakter mage = {"Mage", 100, 20, 10, true};

    Karakter jamur = {"Jamur Punya Kaki", 100, 10, 8, false};

    Karakter tengkorak1 = {"Tengkorak", 80, 18, 12, false};

    Karakter laba2 = {"Laba-Laba", 80, 12, 14, false};

    Karakter redDragon = {"Naga Merah", 200, 40, 30, false};

    Karakter semuaHero[5] = {
    {"Knight", 100, 25, 15, true},
    {"Paladin", 120, 35, 10, true},
    {"Healer", 100, 10, 12, true},
    {"Archer", 90, 20, 18, true},
    {"Mage", 80, 30, 14, true}
};

semuaHero[0].skills[0] = {"Slash", 30, "Serangan pedang kuat"};
semuaHero[0].jumlahSkill = 1;

semuaHero[1].skills[0] = {"Holy Strike", 40, "Serangan suci ke musuh"};
semuaHero[1].jumlahSkill = 1;

semuaHero[2].skills[0] = {"Heal", -30, "Sihir Penyembuhan"};
semuaHero[2].jumlahSkill = 1;

semuaHero[3].skills[0] = {"Poison Arrow", 25, "Menembakkan panah beracun"};
semuaHero[3].jumlahSkill = 1;

semuaHero[4].skills[0] = {"Fireball", 30, "Serangan bola api"};
semuaHero[4].skills[1] = {"Ice Blast", 25, "Serangan es"};
semuaHero[4].jumlahSkill = 2;

int terpilih[3] = {-1, -1, -1}; // Untuk menyimpan indeks hero yang dipilih
int jumlahDipilih = 0;

while (jumlahDipilih < 3) {
    cout << "Pilih Hero ke-" << jumlahDipilih + 1 << ":" << endl;
    for (int i = 0; i < 5; i++) {
        // Tampilkan hanya yang belum dipilih
        bool sudah = false;
        for (int j = 0; j < jumlahDipilih; j++) {
            if (terpilih[j] == i) {
                sudah = true;
                break;
            }
        }
        if (!sudah) {
            cout << i + 1 << ". " << semuaHero[i].namaKarakter << " (HP: " << semuaHero[i].hp << ", ATK: " << semuaHero[i].attack << ", SPD: " << semuaHero[i].speed << ")" << endl;
        }
    }

    cout << "Masukkan nomor hero: ";
    int pilihan;
    cin >> pilihan;

    if (pilihan < 1 || pilihan > 5) {
        cout << "Pilihan tidak valid. Coba lagi." << endl;
        continue;
    }

    bool sudahDipilih = false;
    for (int j = 0; j < jumlahDipilih; j++) {
        if (terpilih[j] == pilihan - 1) {
            sudahDipilih = true;
            break;
        }
    }

    if (sudahDipilih) {
        cout << "Hero sudah dipilih sebelumnya." << endl;
    } else {
        terpilih[jumlahDipilih++] = pilihan - 1;
        cout << "Hero berhasil dipilih!" << endl;
    }
    Sleep(1000);
    system("cls");
}

Karakter* players[3] = {
        &semuaHero[terpilih[0]],
        &semuaHero[terpilih[1]],
        &semuaHero[terpilih[2]]
    };

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