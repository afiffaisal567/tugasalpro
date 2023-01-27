#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct inventory
{
    char nama_lab[100];
    char nama_barang[100];
    int jumlah;
};

void lihatData();
void tambahData();
void editData();
void cariData();
void urutData();
void hapusData();

int main()
{
    int pilihan;
    while (1)
    {
        printf("Menu:\n");
        printf("1. Lihat data\n");
        printf("2. Tambah data\n");
        printf("3. Edit data\n");
        printf("4. Pencarian data\n");
        printf("5. Pengurutan data\n");
        printf("6. Hapus data\n");
        printf("7. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            lihatData();
            break;
        case 2:
            tambahData();
            break;
        case 3:
            editData();
            break;
        case 4:
            cariData();
            break;
        case 5:
            urutData();
            break;
        case 6:
            hapusData();
            break;
        case 7:
            return 0;
        default:
            printf("Pilihan tidak valid\n");
            break;
        }
    }
}

void lihatData()
{
    FILE *fp;
    struct inventory item;
    fp = fopen("inventory.txt", "r");
    printf("Nama Lab\tNama Barang\tJumlah\n");
    while (fscanf(fp, "%s %s %d", item.nama_lab, item.nama_barang, &item.jumlah) != EOF)
    {
        printf("%s\t\t%s\t\t%d\n", item.nama_lab, item.nama_barang, item.jumlah);
    }
    fclose(fp);
    printf("\nTekan enter untuk kembali ke menu\n");
    getchar();
    getchar();
}

void tambahData()
{
    FILE *fp;
    struct inventory item;
    fp = fopen("inventory.txt", "a");
    printf("Masukkan nama lab: ");
    scanf("%s", item.nama_lab);
    printf("Masukkan nama barang: ");
    scanf("%s", item.nama_barang);
    printf("Masukkan jumlah barang: ");
    scanf("%d", &item.jumlah);
    fprintf(fp, "%s %s %d\n", item.nama_lab, item.nama_barang, item.jumlah);
    fclose(fp);
    printf("\nData berhasil ditambahkan\n");
    printf("Tekan enter untuk kembali ke menu\n");
    getchar();
    getchar();
}

void editData()
{
    FILE *fp;
    struct inventory item;
    char lab_cari[100];
    printf("Masukkan nama lab yang ingin diedit: ");
    scanf("%s", lab_cari);
    fp = fopen("inventory.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    while (fscanf(fp, "%s %s %d", item.nama_lab, item.nama_barang, &item.jumlah) != EOF)
    {
        if (strcmp(item.nama_lab, lab_cari) == 0)
        {
            printf("Masukkan nama lab baru: ");
            scanf("%s", item.nama_lab);
            printf("Masukkan nama barang baru: ");
            scanf("%s", item.nama_barang);
            printf("Masukkan jumlah barang baru: ");
            scanf("%d", &item.jumlah);
        }
        fprintf(temp, "%s %s %d\n", item.nama_lab, item.nama_barang, item.jumlah);
    }
    fclose(fp);
    fclose(temp);
    remove("inventory.txt");
    rename("temp.txt", "inventory.txt");
    printf("\nData berhasil diubah\n");
    printf("Tekan enter untuk kembali ke menu\n");
    getchar();
    getchar();
}

int compare(const void *a, const void *b)
{
    struct inventory *ia = (struct inventory *)a;
    struct inventory *ib = (struct inventory *)b;
    return strcmp(ia->nama_lab, ib->nama_lab);
}

void cariData()
{
    FILE *fp;
    struct inventory item[100];
    char lab_cari[100];
    int i = 0, low, high, mid, flag = 0;
    fp = fopen("inventory.txt", "r");
    while (fscanf(fp, "%s %s %d", item[i].nama_lab, item[i].nama_barang, &item[i].jumlah) != EOF)
    {
        i++;
    }
    fclose(fp);
    int n = i;
    qsort(item, n, sizeof(struct inventory), compare); // sort the data using qsort and compare function
    printf("Masukkan nama lab yang ingin dicari: ");
    scanf("%s", lab_cari);
    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (strcmp(item[mid].nama_lab, lab_cari) == 0)
        {
            printf("Data ditemukan\n");
            printf("Nama Lab: %s\nNama Barang: %s\nJumlah: %d\n", item[mid].nama_lab, item[mid].nama_barang, item[mid].jumlah);
            flag = 1;
            break;
        }
        else if (strcmp(item[mid].nama_lab, lab_cari) > 0)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    if (flag == 0)
    {
        printf("Data tidak ditemukan\n");
    }
    printf("Tekan enter untuk kembali ke menu\n");
    getchar();
    getchar();
}

void urutData()
{
    FILE *fp;
    struct inventory item[100];
    int i = 0, j, min_idx;
    fp = fopen("inventory.txt", "r");
    while (fscanf(fp, "%s %s %d", item[i].nama_lab, item[i].nama_barang, &item[i].jumlah) != EOF)
    {
        i++;
    }
    fclose(fp);
    int n = i;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (strcmp(item[j].nama_lab, item[min_idx].nama_lab) < 0)
            {
                min_idx = j;
            }
        }
        struct inventory temp = item[min_idx];
        item[min_idx] = item[i];
        item[i] = temp;
    }
    fp = fopen("inventory.txt", "w");
    for (i = 0; i < n; i++)
    {
        fprintf(fp, "%s %s %d\n", item[i].nama_lab, item[i].nama_barang, item[i].jumlah);
    }
    fclose(fp);
    printf("Data berhasil diurutkan\n");
    printf("Tekan enter untuk kembali ke menu\n");
    getchar();
    getchar();
}

void hapusData()
{
    FILE *fp;
    struct inventory item;
    char lab_hapus[100];
    int flag = 0;
    printf("Masukkan nama lab yang ingin dihapus: ");
    scanf("%s", lab_hapus);
    fp = fopen("inventory.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    while (fscanf(fp, "%s %s %d", item.nama_lab, item.nama_barang, &item.jumlah) != EOF)
    {
        if (strcmp(item.nama_lab, lab_hapus) != 0)
        {
            fprintf(temp, "%s %s %d\n", item.nama_lab, item.nama_barang, item.jumlah);
        }
        else
        {
            flag = 1;
        }
    }
    if (flag == 1)
    {
        printf("Data berhasil dihapus\n");
    }
    else
    {
        printf("Data tidak ditemukan\n");
    }
    fclose(fp);
    fclose(temp);
    remove("inventory.txt");
    rename("temp.txt", "inventory.txt");
    printf("Tekan enter untuk kembali ke menu\n");
    getchar();
    getchar();
}
