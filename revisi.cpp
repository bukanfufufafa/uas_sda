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