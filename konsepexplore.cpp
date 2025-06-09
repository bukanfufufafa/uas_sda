#include <iostream>
using namespace std;

struct tree
{
    int data;
    tree *left, *right, *parent;
};

tree *pohon, *root;

void deklarasi()
{
    pohon = NULL;
}

void deleteTree()
{
    pohon = NULL;
    cout << "Seluruh data pada tree sudah terhapus." << endl;
}

void eksplorasi(tree *root) {
    if (root == NULL) {
        cout << "Tree kosong.\n";
        return;
    }

    tree *current = root;
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
            if (current->left != NULL)
                current = current->left;
            else
                cout << "Tidak ada node di kiri.\n";
            break;

        case 2:
            if (current->right != NULL)
                current = current->right;
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

void insertTree(tree **root, int nilai, tree *parent = NULL)
{
    if (*root == NULL)
    {
        *root = new tree;
        (*root)->data = nilai;
        (*root)->left = (*root)->right = NULL;
        (*root)->parent = parent; // simpan parent saat buat node
        cout << "Data " << nilai << " berhasil ditambahkan ke dalam tree." << endl;
    }
    else if (nilai < (*root)->data)
    {
        insertTree(&(*root)->left, nilai, *root);
    }
    else
    {
        insertTree(&(*root)->right, nilai, *root);
    }
}

void preOrder(tree *root)
{
    if (root != NULL)
    {
        // root ada isinya
        cout << root -> data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(tree *root)
{
    if (root != NULL)
    {
        // root ada isinya
        inOrder(root -> left);
        cout << root -> data << " ";
        inOrder(root->right);
    }
}

void postOrder(tree *root)
{
    if (root != NULL)
    {
        postOrder(root -> left);
        postOrder(root -> right);
        cout << root -> data << " ";   
    }
}

void findTree(tree *root, int cari)
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
            root = root -> left;
        }
        else
        {
            root = root -> right;
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