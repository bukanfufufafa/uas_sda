#include <iostream>
#include <string>
using namespace std;

struct treeRuangan
{
    int data;
    string namaRuangan;
    bool adaMonster, adaHarta;
    treeRuangan *kiri, *kanan, *parent;
};

treeRuangan *pohon, *root;

void deklarasi()
{
    pohon = NULL;
}

void eksplorasi(treeRuangan *root) {
    if (root == NULL) {
        cout << "Tree kosong.\n";
        return;
    }

    treeRuangan *current = root;
    int pilihan;

    while (true) {
        cout << "\nAnda berada di node: " << current->data << endl;
        cout << "Pilihan:\n";
        cout << "1. Ke kiri\n";
        cout << "2. Ke kanan\n";
        cout << "3. Kembali ke node sebelumnya (parent)\n";
        cout << "4. Keluar eksplorasi\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            if (current->kiri != NULL)
                current = current->kiri;
            else
                cout << "Tidak ada node di kiri.\n";
            break;

        case 2:
            if (current->kanan != NULL)
                current = current->kanan;
            else
                cout << "Tidak ada node di kanan.\n";
            break;

        case 3:
            if (current->parent != NULL)
                current = current->parent;
            else
                cout << "Sudah di root, tidak bisa kembali lagi.\n";
            break;

        case 4:
            return;

        default:
            cout << "Pilihan tidak valid.\n";
        }
    }
}

void insertTree(treeRuangan **root, int nilai, treeRuangan *parent = NULL)
{
    if (*root == NULL)
    {
        *root = new treeRuangan;
        (*root)->data = nilai;
        (*root)->kiri = (*root)->kanan = NULL;
        (*root)->parent = parent; // simpan parent saat buat node
        cout << "Data " << nilai << " berhasil ditambahkan ke dalam treeRuangan." << endl;
    }
    else if (nilai < (*root)->data)
    {
        insertTree(&(*root)->kiri, nilai, *root);
    }
    else
    {
        insertTree(&(*root)->kanan, nilai, *root);
    }
}

void preOrder(treeRuangan *root)
{
    if (root != NULL)
    {
        // root ada isinya
        cout << root -> data << " ";
        preOrder(root->kiri);
        preOrder(root->kanan);
    }
}

void inOrder(treeRuangan *root)
{
    if (root != NULL)
    {
        // root ada isinya
        inOrder(root -> kiri);
        cout << root -> data << " ";
        inOrder(root->kanan);
    }
}

void postOrder(treeRuangan *root)
{
    if (root != NULL)
    {
        postOrder(root -> kiri);
        postOrder(root -> kanan);
        cout << root -> data << " ";   
    }
}

void findTree(treeRuangan *root, int cari)
{
    int level = 0;
    while (root != NULL)
    {
        if (root -> data == cari)
        {
            cout << "Data " << cari << " ditemukan pada level " << level << endl;
            return;
        }
        else if (cari < root -> data)
        {
            root = root -> kiri;
        }
        else
        {
            root = root -> kanan;
        }
        level++;
    }
    cout << "Data " << cari << " tidak ditemukan" << endl;
}

int main()
{
    deklarasi();
    insertTree(&pohon, 10);
    insertTree(&pohon, 5);
    insertTree(&pohon, 4);
    insertTree(&pohon, 30);
    insertTree(&pohon, 7);
    insertTree(&pohon, 90);
    eksplorasi(pohon);
}