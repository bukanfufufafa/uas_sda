#include <iostream>
#include <string>
using namespace std;

struct treeRuangan
{
    string namaRuangan;
    string deskripsi;
    bool adaMonster;
    bool adaHarta;
    treeRuangan *kiri, *kanan;
};

treeRuangan *pohonRuangan, *rootRuangan;

void deklarasi()
{
    pohonRuangan = NULL;
}

void insertTree(treeRuangan **rootRuangan, string nama, string deskripsi, bool monster, bool harta)
{
    if (*rootRuangan == NULL)
    {
        treeRuangan* nodeBaru = new treeRuangan;
        nodeBaru -> namaRuangan = nama;
        nodeBaru -> deskripsi   = deskripsi;
        nodeBaru -> adaMonster  = monster;
        nodeBaru -> adaHarta    = harta;
        nodeBaru -> kiri = nodeBaru -> kanan = NULL;
        *rootRuangan = nodeBaru;
        return;
    }

    if (nama.length() < (*rootRuangan) -> namaRuangan.length())
    {
        insertTree(&(*rootRuangan) -> kiri, nama, deskripsi, monster, harta);
    }
    else
    {
        insertTree(&(*rootRuangan) -> kanan, nama, deskripsi, monster, harta);
    }
}

int main()
{
    
}