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