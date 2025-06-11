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
    system("cls");
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
    system("cls");
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
            cout << "--- Giliran " << sekarang->namaKarakter << " ---" << endl;

            cout << "Pilih target musuh (1 untuk " << musuh->namaKarakter << "): ";
            int pilihan;
            cin >> pilihan;

            if (pilihan == 1 && musuh -> isAlive()) {
                cout << sekarang->namaKarakter << " menyerang " << musuh->namaKarakter << " sebesar " << sekarang->attack << endl;
                musuh -> takeDamage(sekarang->attack);
            } else {
                cout << "Target tidak valid atau sudah mati." << endl;
            }

        } else {
            cout << "--- Giliran Musuh: " << sekarang->namaKarakter << " ---" << endl;

            Karakter* target = nullptr;
            for (int i = 0; i < jumlahPlayer; i++) {
                if (players[i] -> isAlive()) {
                    target = players[i];
                    break;
                }
            }

            if (target != nullptr) {
                cout << sekarang -> namaKarakter << " menyerang " << target->namaKarakter
                     << " sebesar " << sekarang->attack << endl;
                target -> takeDamage(sekarang->attack);
            } else {
                cout << sekarang -> namaKarakter << " tidak punya target hidup." << endl;
            }
        }

        if (sekarang -> isAlive()) {
            antriGiliran.masukAntrian(sekarang);
        }
    }

    if (musuh -> isAlive()) {
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
            cout << "\n==================================================" << endl;

            mulaiTurnBase(&(current -> musuh), players, jumlahPlayer);

            current -> adaMusuh = false;
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

int main()
{
    deklarasi();
    Karakter karakter1 = {"karakter1", 100, 25, 15, true};
    Karakter karakter2 = {"karakter2", 90, 20, 10, true};
    Karakter karakter3 = {"karakter3", 80, 30, 12, true};
    Karakter musuh1 = {"musuh1", 100, 15, 8, false};
    Karakter musuh2 = {"musuh2", 100, 18, 5, false};

    Karakter* players[] = {&karakter1, &karakter2, &karakter2};

    insertRuangan(&pohonRuangan, 10, "Ruangan awal dengan lentera menyala.", false);
    insertRuangan(&pohonRuangan, 5, "Ruangan lembab dan gelap.", true, musuh1);
    insertRuangan(&pohonRuangan, 4, "Ruangan kecil dengan ukiran aneh.");
    insertRuangan(&pohonRuangan, 30, "Ruangan tinggi bergema.", true, musuh2);
    insertRuangan(&pohonRuangan, 7, "Ruangan dengan meja dan kursi rusak.");
    insertRuangan(&pohonRuangan, 90, "Ruangan terakhir dengan peti harta.");

    system("cls");

    eksplorasi(pohonRuangan, players, 3);
    return 0;
}