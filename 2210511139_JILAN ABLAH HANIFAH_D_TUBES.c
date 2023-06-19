#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char isiDosa[50];
} Dosa;

typedef struct elmt *alamatelmt;
typedef struct elmt
{
    Dosa kontainer;
    alamatelmt prev;
    alamatelmt next;
} elemen;

typedef struct
{
    elemen *first;
    elemen *tail;
} list;
//fungsi untuk membuat createList ganda
void createList(list *L)
{
    L->first = NULL;
    L->tail = NULL;
}

int countElement(list L)
{
    int hasil = 0;
    if (L.first != NULL)
    {
        elemen *bantu;
        bantu = L.first;
        while (bantu != NULL)
        {
            hasil = hasil + 1;
            bantu = bantu->next;
        }
    }
    return hasil;
}
//menambah list ke paling awal
void addFirst(char isiDosa[], list *L)
{
    elemen *baru;
    baru = (elemen *)malloc(sizeof(elemen));
    strcpy(baru->kontainer.isiDosa, isiDosa);

    if (L->first == NULL)
    {
        baru->next = NULL;
        L->tail = baru;
    }
    else
    {
        baru->next = L->first;
        L->first->prev = baru;
    }

    baru->prev = NULL;
    L->first = baru;
    baru = NULL;
}
//menambah list ke setelahnya
void addAfter(elemen *before, char isiDosa[], list *L)
{
    if (before != NULL)
    {
        elemen *baru;
        baru = (elemen *)malloc(sizeof(elemen));

        strcpy(baru->kontainer.isiDosa, isiDosa);

        if (before->next == NULL)
        {
            baru->next = NULL;
            L->tail = baru;
        }
        else
        {
            baru->next = before->next;
            baru->next->prev = baru;
        }
        baru->prev = before;
        before->next = baru;
        baru = NULL;
    }
}
//menambah list ke paling akhir
void addLast(char isiDosa[], list *L)
{
    if (L->first == NULL)
    {
        addFirst(isiDosa, L);
    }
    else
    {
        addAfter(L->tail, isiDosa, L);
    }
}

void delFirst(list *L)
{
    if (L->first != NULL)
    {
        elemen *hapus = L->first;

        if (countElement(*L) == 1)
        {
            L->first = NULL;
            L->tail = NULL;
        }
        else
        {
            L->first = L->first->next;
            L->first->prev = NULL;
        }
        hapus->next = NULL;
        free(hapus);
    }
    else
    {
        printf("list kosong");
    }
}

void delAfter(elemen *before, list *L)
{
    if (before != NULL)
    {
        elemen *hapus = before->next;

        if (hapus != NULL)
        {
            if (hapus->next == NULL)
            {
                before->next = NULL;
                L->tail = before;
            }
            else
            {
                before->next = hapus->next;
                hapus->next->prev = before;
            }
            hapus->prev = NULL;
            hapus->next = NULL;
            free(hapus);
        }
    }
}

void delLast(list *L)
{
    if (L->first != NULL)
    {
        if (countElement(*L) == 1)
        {
            delFirst(L);
        }
        else
        {
            delAfter(L->tail->prev, L);
        }
    }
}
void delAll(list *L){
    if(countElement(*L) != 0){
        int i;
        
        for(i=countElement(*L); i>=1; i++){
            delLast(L);
        }
    }
}

typedef struct smp *alamatsimpul;

typedef struct smp
{
    char kontainer[20]; 
    list kumpulanDosa;
    alamatsimpul sibling;
    alamatsimpul child;
} simpul;

typedef struct
{
    simpul *root;
} tree;
//membuat tree
void makeTree(char nama[], tree *T)
{
    simpul *baru;
    baru = (simpul *)malloc(sizeof(simpul));
    strcpy(baru->kontainer, nama); 
    baru->sibling = NULL;
    baru->child = NULL;
    T->root = baru;
}
//menambah anak 
void addChild(char nama[], simpul *root)
{
    if (root != NULL)
    {
        simpul *baru;
        baru = (simpul *)malloc(sizeof(simpul));
        strcpy(baru->kontainer, nama);
        baru->child = NULL;

        if (root->child == NULL)
        {
            baru->sibling = NULL;
            root->child = baru;
        }
        else
        {
            if (root->child->sibling == NULL)
            {
                baru->sibling = root->child;
                root->child->sibling = baru;
            }
            else
            {
                simpul *last = root->child;

                while (last->sibling != root->child)
                {
                    last = last->sibling;
                }

                baru->sibling = root->child;
                last->sibling = baru;
            }
        }
    }
}

//menemukan simpul yang dicari
simpul *findSimpul(char nama[], simpul *root)
{
    simpul *hasil = NULL;

    if (root != NULL)
    {
        if (strcmp(root->kontainer, nama) == 0)
        {
            hasil = root;
        }
        else
        {
            simpul *bantu = root->child;

            while (bantu != NULL && hasil == NULL)
            {
                hasil = findSimpul(nama, bantu);
                bantu = bantu->sibling;
            }
        }
    }

    return hasil;
}


simpul* cariBapak(char nama[], simpul* root) {
    simpul* hasil = NULL;

    if (root != NULL) {
        simpul* bantu = root->child; 

        if (bantu != NULL) {
            if (strcmp(bantu->kontainer, nama) == 0) { 
                hasil = root; 
            } else {
                if (bantu->sibling == NULL) {
                    hasil = cariBapak(nama, bantu); 
                } else {
                    while (bantu->sibling != root->child && hasil == NULL) {
                        hasil = cariBapak(nama, bantu); 
                        bantu = bantu->sibling;
                        if (strcmp(bantu->kontainer, nama)==0)
                        {
                            hasil = root;
                        }
                        
                    }
                    if (hasil == NULL) {
                        hasil = cariBapak(nama, bantu); 
                    }
                }
            }
        }
    }

    return hasil;
}


void printElement(list L)
{
    if (L.first != NULL)
    {
        elemen *bantu = L.first;
        int i = 1;
        while (bantu != NULL)
        {
            printf("	%s\n", bantu->kontainer.isiDosa);
            bantu = bantu->next;
            i = 1 + 1;
        }
    }
}
//mengprint simpulnya lalu dosanya

void printSemuaDosa(simpul *root)
{
    if (root != NULL)
    {
        printf("%s\n", root->kontainer); // Menampilkan nama simpul (root)
        printElement(root->kumpulanDosa); // Menampilkan list dosa dari simpul tersebut
        simpul *bantu = root->child; // Menginisialisasi variabel bantu dengan child pertama dari simpul root

        if (bantu != NULL)
        {
            if (bantu->sibling == NULL) {
                printSemuaDosa(bantu); // Jika simpul hanya memiliki satu anak, rekursif panggil fungsi untuk anak tersebut
            }
            else
            {
                while (bantu->sibling != root->child) // Loop melalui semua simpul anak (child) selain yang terakhir
                {
                    printSemuaDosa(bantu); // Rekursif panggil fungsi untuk simpul anak tersebut
                    bantu = bantu->sibling; // Pindah ke simpul saudara selanjutnya (sibling)
                }
                printSemuaDosa(bantu); // Rekursif panggil fungsi untuk simpul anak terakhir
            }
        }
    }
}
void telusurSilsilahPendosa(char nama[], char dosa[], simpul *root) {
    if (root != NULL) {
        char silsilah[20];
        printf("%s \n", dosa);//print dosa
        simpul *bantu = cariBapak(nama, root); //mencari bapak dari parameter
        addFirst(nama, &root->kumpulanDosa); //menambah naama parameter para addfirst
        while (bantu != NULL) {
            elemen *ptr = bantu->kumpulanDosa.first;
            while (ptr != NULL) {
                if (strcmp(ptr->kontainer.isiDosa, dosa) == 0) {
                    strcpy(silsilah, bantu->kontainer);
                    addFirst(silsilah, &(root->kumpulanDosa));
                }
                ptr = ptr->next;
            }
            bantu = cariBapak(bantu->kontainer, root);
        }
    }
    printElement(root->kumpulanDosa);
    delAll(&root->kumpulanDosa);
}

void hapusDosa(char nama[], char dosa[], simpul *root)
{
    if (root != NULL)
    {
        simpul *bantu = findSimpul(nama, root); // Mencari simpul dengan nama yang sesuai
        if (bantu != NULL)
        {
            elemen *ptr = bantu->kumpulanDosa.first; // Inisialisasi pointer ptr ke elemen pertama dalam list dosa
            elemen *prev = NULL; // Inisialisasi pointer prev sebagai penunjuk ke elemen sebelum ptr

            while (ptr != NULL)
            {
                if (strcmp(ptr->kontainer.isiDosa, dosa) == 0) // Jika dosa pada elemen saat ini sama dengan dosa yang ingin dihapus
                {
                    if (prev == NULL) //jika sebelumnya adalah NULL
                    {
                        delFirst(&bantu->kumpulanDosa); // Hapus elemen pertama dari list dosa
                        ptr = bantu->kumpulanDosa.first; // Update ptr ke elemen pertama setelah penghapusan
                    }
                    else
                    {
                        delAfter(prev, &bantu->kumpulanDosa); // Hapus elemen setelah elemen prev dari list dosa
                        ptr = prev->next; // Update ptr ke elemen setelah penghapusan
                    }
                }
                else
                {
                    prev = ptr; // Pindah ke elemen berikutnya
                    ptr = ptr->next; // Pindah ke elemen berikutnya
                }
            }
        }
    }
}

int main()
{
    tree T;
    char nama1[20];
    char dosa1[20];
    int banyak, banyakDosa, banyakdosa2;
    char nama[20];
    char bapak[20];
    char anak[20];
    char dosanya[50];
    simpul *bantu;
    printf("Banyak Data:\n");
    scanf("%d", &banyak);
    printf("Masukan Data:\n");
    int i, j, k;
    for (i = 0; i < banyak; i++)
    {
        scanf(" %[^#]#%[^#]#%d", &bapak, &anak, &banyakDosa);
        if (banyakDosa == 0) //jika dosanya noll maka maketree dan creatlist 
        {
            makeTree(anak, &T);
            createList(&findSimpul(anak, T.root)->kumpulanDosa);
        }
        else
        {
            bantu = findSimpul(bapak, T.root); //cari bapaknya
            if (bantu != NULL)
            {
                addChild(anak, bantu); //tambahin anaknya di simpul bapaknya 
            }
            fflush(stdin);
            createList(&findSimpul(anak, T.root)->kumpulanDosa); //membuat list
            for (j = 0; j < banyakDosa; j++)
            {
                scanf("%s", dosanya); //masukkan dosanya 
                addLast(dosanya, &findSimpul(anak, T.root)->kumpulanDosa); //tampahkan dosa ke paling terakhir 
            }
        }
    }
    printSemuaDosa(T.root); //menampilkan dosa dan orangnya
    printf("cari sepuh pendosa: \n");
    scanf(" %[^#]#%[^\n]", &nama1, &dosa1);
    telusurSilsilahPendosa(nama1, dosa1, T.root); //mencari bapaknya pendosa
    printf("Berapa banyak mau hapus dosa? \n");
    scanf("%d", &banyakdosa2); 
    for (k = 0; k < banyakdosa2; k++) //looping untuk hapus dosa 
    {
        scanf(" %[^#]#%[^\n]", &nama, &dosanya);
        hapusDosa(nama, dosanya, T.root);
    }
    printSemuaDosa(T.root);//menampilkan dosa dan nama orangnya
    return 0;
}
