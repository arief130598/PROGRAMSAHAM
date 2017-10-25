#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Daftar Variabel
char nama[50], sandi[50], username[100],password[50],temp[10][50],namaperusahaan[50];
char milih, hapus[50],sementara[50], belisahamnama[50], b[200];
int pilihan, belilembarsaham, deposit, jumlahsaham, hargasaham, juallembarsaham[50], lembarsahamsementara, a[50], t[50];
int saldo;
FILE *user, *pass, *perusahaan, *sahamperusahaan, *tempperusahaan, *lembarsaham, *templembar, *tempharga, *filedeposit;
FILE *tempdeposit, *lembardimiliki, *templembardimiliki, *templembarbaru, *tempjual, *tempbeli;

int registermenu() // Fungsi Register
{
    printf("\t\t\t\t\t\t=====REGISTER AKUN====\n\n");
    fflush(stdin);
    printf("\t\t\t\t\t\tMasukkan Username : "); gets(username); // Input Username untuk di register
    imp(password);
    printf("\t\t\t\t\t\tMasukkan Deposit : "); scanf("%d", &deposit);   // INput Deposit / Saldo untuk di register

    strcpy(temp[0],username); // Menyalin username ke temp
    strcat(temp[0],"\n"); // Menggabungkan temp dengan fungsi enter (\n)

    //Membuka file user, pass dan filedeposit
    user=fopen("username.txt","a+");
    pass=fopen("password.txt","a+");
    filedeposit=fopen("deposit.txt","a+");

    while(fgets(temp[1],50,user)!=NULL) //Membaca file pada user
    {
        if(strcmp(temp[1],temp[0])==0) // Jika ada user sama maka tidak ditulis
        {
            printf("Username sudah ada\n");
            return main();
        }
    }

    //Membuka file user
    user=fopen("username.txt","a+");
    // Menulis username, password dan deposit pada file
    fputs(strcat(username,"\n"),user);
    fputs(strcat(password,"\n"),pass);
    fprintf(filedeposit,"%d\n", deposit);
    //Menutup file user, pass dan filedeposit
    fclose(user);
    fclose(pass);
    fclose(filedeposit);

    printf("\n\t\t\t\t    ===Akun Berhasil Registrasi, Silahkan Login===\n\n");
    system("pause");
    system("cls");
    return main(); // kembali ke menu utama
}

int menulogin() // fungsi menu login
{
    printf("\t\t\t\t\t\t========LOGIN========\n");
    printf("\t\t\t\t\t\t1. Admin\n");
    printf("\t\t\t\t\t\t2. User\n");
    printf("\t\t\t\t\t\t3. Kembali\n");
    fflush(stdin);
    printf("\t\t\t\t\t\tMasukkan pilihan : "); scanf("%d", &pilihan); //Input Pilihan
    switch(pilihan)
    {
        case 1 :
        {
            fflush(stdin);
            // Membaca username dan password
            printf("\n\t\t\t\t\t\tMasukkan username : "); gets(nama);
            imp(sandi);
            loginadmin(); //Memanggil fungsi login admin
        } break;
            case 2 :
        {
            fflush(stdin);
            // Membaca username dan password
            printf("\n\t\t\t\t\t\tMasukkan username : "); gets(nama);
            imp(sandi);
            loginuser(); //Memanggil fungsi login user
        } break;
            case 3 :
        {
            system("cls");
            return main(); //Kembali ke fungsi utama
        } break;
    }
}

int imp(char sandi[30])
{
    char pass;
    int i=0,p=2;
    printf("\t\t\t\t\t\tMasukkan password : ");
    while(p)
    {
        pass=getch();
        if(pass==13)
        break;
        if(pass==10)
        {
            putch('\b');
            putch(EOF);
            putch('\b');
            i--;
            continue;
        }
        sandi[i++]=pass;
        pass='*';
        putch(pass);
    }

    char *pch = strstr(sandi, "\n");
        if(pch != NULL)
        {
            strncpy(pch, "\0", 1);
        }
    sandi[i]='\0';
}

int loginadmin() //Fungsi LoginAdmin
{
    system("cls"); // Membersihkan Layar
    //Menyalin nama dan sandi ke temp[0]
    strcpy(temp[0],nama);
    strcat(temp[0],"\n");
    strcpy(temp[1],sandi);
    strcat(temp[1],"\n");
    //Membuka file user dan pass
    user=fopen("username.txt","r+");
    pass=fopen("password.txt","r+");

    //Membaca file pada user dan pass
    while((fgets(temp[2],50,user)!=NULL) && (fgets(temp[3],50,pass)!=NULL))
    {
        if((strcmp("Arief\n",temp[0])==0) && (strcmp("Maulana\n",temp[1])==0))
        // jika file sama dengan yang diinput maka :
        {
            menuadmin(); // Memanggil fungsi menuadmin

            return menulogin(); // kembali ke fungsi menulogin
        }
        else
        {
            printf("\t\t\t\t\t\t=====LOGIN GAGAL====\n");
            system("pause");
            system("cls"); //membersihkan layar
            return menulogin(); //Memanggil fungsi menulogin
        }
    }
    system("cls"); //Membersihkan layar
}

int menuadmin() //Fungsi Admin
{
    printf("\t\t\t\t\t\t===LOGIN SEBAGAI ADMIN===\n\n");
    printf("\t\t\t\t\t\t1. Tambah Perusahaan\n");
    printf("\t\t\t\t\t\t2. Hapus Perusahaan\n");
    printf("\t\t\t\t\t\t3. Tambah Deposit User\n");
    printf("\t\t\t\t\t\t4. Ubah Harga Saham Perusahaan\n");
    printf("\t\t\t\t\t\t5. Tambah Lembar Saham Perusahaan\n");
    printf("\t\t\t\t\t\t6. Logout\n");
    printf("\t\t\t\t\t\t7. Kembali Ke Menu Awal\n\n");

    fflush(stdin);
    printf("\t\t\t\t\t\tMasukkan pilihan : "); scanf("%d", &pilihan); //Membaca pilihan
    switch(pilihan)
    {
        case 1 :
        {
            system("cls"); // Membersihkan layar
            tambahperusahaan(); // Memanggil fungsi tambah perusahaan
        } break;
        case 2 :
        {
            system("cls"); // Membersihkan layar
            hapusperusahaan(); //Memanggil fungsi hapus perusahaan
        } break;
            case 3 :
        {
            system("cls"); // Membersihkan layar
            tambahsaldo(); // Memanggil fungsi tambah saldo
        } break;
        case 4 :
        {
            system("cls"); // Membersihkan layar
            ubahhargasaham(); // Memanggil fungsi ubah saham
        } break;
        case 5 :
        {
            system("cls"); // Membersihkan layar
            tambahlembarsaham(); // Memanggil fungsi tambah lembar saham
        } break;
        case 6 :
        {
            system("cls"); // Membersihkan layar
            return menulogin(); // Kembali ke fungsi menulogin
        } break;
        case 7 :
        {
            system("cls");
            return main(); // Kembali ke fungsi utama
        } break;
    }
}

int tambahlembarsaham() //fungsi tambalembarsaham
{
    printf("\t\t\t\t\t\t======MENAMBAH JUMLAH SAHAM======\n\n");

    printf("\t\t\t\t\tDaftar Jumlah Saham : \n\n");
    perusahaan = fopen("perusahaan.txt", "r+");
    lembarsaham = fopen("lembarsaham.txt", "r+");

    int z=1;
    //Membaca pada file
    //Menampilkan jumlah saham yang dimiliki
    while(fgets(namaperusahaan,50,perusahaan)!=NULL && fscanf(lembarsaham,"%d\n",&jumlahsaham)!=EOF)
    {
        printf("\t\t\t\t\t%d. %s", z,namaperusahaan);
        printf("\t\t\t\t\tJumlah Saham = %d Lembar\n\n",jumlahsaham);
        z++;
    }
    //Menutup file
    fclose(perusahaan);
    fclose(lembarsaham);

    int lembarsahambaru;
    //Menginput nama perusahaan yang ingin dihapus dan jumlah saham yang ingin ditambah
    printf("\t\t\t\t\tMasukkan nama perusahaan yang ingin ditambah sahamnya  : "); fflush(stdin); gets(nama);
    printf("\t\t\t\t\tMasukkan jumlah saham yang ingin ditambah : "); scanf("%d", &lembarsahambaru);
    strcat(nama,"\n");
    //Membuka file
    perusahaan = fopen("perusahaan.txt", "r+");
    lembarsaham = fopen("lembarsaham.txt", "r+");
    templembar = fopen("templembar.txt", "w+");

    //Membaca pada file sekaligus memindahkan ke file temporary
    while(fgets(namaperusahaan,50,perusahaan)!=NULL && fscanf(lembarsaham,"%d\n",&jumlahsaham)!=EOF)
    {
        if(strcmp(namaperusahaan,nama)==0)
        {
            jumlahsaham=jumlahsaham+lembarsahambaru; //Mengubah saham
        }

        fprintf(templembar,"%d\n",jumlahsaham);
    }
    //Menutup file
    fclose(perusahaan);
    fclose(lembarsaham);
    fclose(templembar);
    //Membuka file
    lembarsaham = fopen("lembarsaham.txt", "w+");
    templembar = fopen("templembar.txt", "r+");
    //Membaca sekaligus menyalin file temporary ke file utama
    while(fscanf(templembar,"%d\n",&jumlahsaham)!=EOF)
    {
        fprintf(lembarsaham,"%d\n",jumlahsaham);
    }
    //Menutup file
    fclose(lembarsaham);
    fclose(templembar);

    printf("\n\t\t\t\t\t===TAMBAH SAHAM SUKSES===\n");

    system("pause");
    system("cls");
    return menuadmin();
}

int ubahhargasaham() //fungsi ubah harga saham
{
    printf("\t\t\t\t\t\t======MERUBAH HARGA SAHAM======\n\n");

    printf("\t\t\t\t\tDaftar Harga Saham : \n\n");
    perusahaan = fopen("perusahaan.txt", "r+");
    sahamperusahaan = fopen("sahamperusahaan.txt", "r+");

    int z=1;
    //Membaca pada file dan menampilkan data yang ada
    while(fgets(namaperusahaan,50,perusahaan)!=NULL && fscanf(sahamperusahaan,"%d\n",&hargasaham)!=EOF)
    {
        printf("\t\t\t\t\t%d. %s", z,namaperusahaan);
        printf("\t\t\t\t\tHarga Saham = %d\n\n",hargasaham);
        z++;
    }
    //Menutup file
    fclose(perusahaan);
    fclose(sahamperusahaan);

    int hargasahambaru;
    //Input data yang ingin diubah dan harga yang ingin diubah
    printf("\t\t\t\t\tMasukkan nama perusahaan yang ingin diubah harganya  : "); fflush(stdin); gets(nama);
    printf("\t\t\t\t\tMasukkan harga saham yang ingin diubah : "); scanf("%d", &hargasahambaru);
    strcat(nama,"\n");
    //Membuka file
    perusahaan = fopen("perusahaan.txt", "r+");
    sahamperusahaan = fopen("sahamperusahaan.txt", "r+");
    tempharga = fopen("tempharga.txt", "w+");

    //Membaca pada file sekaligus memindahkan ke file temporary
    while(fgets(namaperusahaan,50,perusahaan)!=NULL && fscanf(sahamperusahaan,"%d\n",&hargasaham)!=EOF)
    {
        if(strcmp(namaperusahaan,nama)==0)
        {
            hargasaham=hargasahambaru; //Mengubah saham
        }

        fprintf(tempharga,"%d\n",hargasaham);
    }
    //Menutup file
    fclose(perusahaan);
    fclose(sahamperusahaan);
    fclose(tempharga);
    //Membuka file
    sahamperusahaan = fopen("sahamperusahaan.txt", "w+");
    tempharga = fopen("tempharga.txt", "r+");
    //Membaca sekaligus menyalin file temporary ke file utama
    while(fscanf(tempharga,"%d\n",&hargasaham)!=EOF)
    {
        fprintf(sahamperusahaan,"%d\n",hargasaham);
    }
    //Menutup file
    fclose(perusahaan);
    fclose(sahamperusahaan);

    printf("\n\t\t\t\t\t===SAHAM SUKSES DIUBAH===\n");

    system("pause");
    system("cls");
    return menuadmin();
}

int tambahsaldo() //fungsi tambah saldo
{
    printf("\t\t\t\t\t\t======TAMBAH DEPOSIT======\n\n");

    printf("\t\t\t\t\tDaftar User : \n\n");
    user = fopen("username.txt", "r+");
    filedeposit = fopen("deposit.txt", "r+");

    int z=1;
    //Membaca pada file dan menampilkan daftar perusahaan dan depositnya
    while(fgets(username,50,user)!=NULL && fscanf(filedeposit,"%d\n",&deposit)!=EOF)
    {
        printf("\t\t\t\t\t%d. User %s", z,username);
        printf("\t\t\t\t\tJumlah Deposit = %d\n\n",deposit);
        z++;
    }
    //Menutup file
    fclose(filedeposit);
    fclose(user);
    //Input nama user yang ingin ditambah dan saldo yang ingin ditambah
    printf("\t\t\t\t\tMasukkan nama user yang ingin ditambah saldonya  : "); fflush(stdin); gets(nama);
    printf("\t\t\t\t\tMasukkan jumlah saldo yang ingin ditambah : "); scanf("%d", &saldo);
    strcat(nama,"\n");
    //Membuka file
    user = fopen("username.txt", "r+");
    filedeposit = fopen("deposit.txt", "r+");
    tempdeposit = fopen("tempdeposit.txt", "w+");

    //Membaca pada file sekaligus memindahkan ke file temporary
    while(fgets(username,50,user)!=NULL && fscanf(filedeposit,"%d\n",&deposit)!=EOF)
    {
        if(strcmp(username,nama)==0) //untuk mencari tahu deposit pada suatu user mana
        {
            deposit=deposit+saldo; //Menghitung sisa deposit
        }

        fprintf(tempdeposit,"%d\n",deposit); //Menulis deposit ke file temporary
    }
    //Menutup file
    fclose(filedeposit);
    fclose(user);
    fclose(tempdeposit);
    //Membuka file
    filedeposit = fopen("deposit.txt", "w+");
    tempdeposit = fopen("tempdeposit.txt", "r+");
    //Membaca sekaligus menyalin file temporary ke file deposit utama
    while(fscanf(tempdeposit,"%d\n",&deposit)!=EOF)
    {
        fprintf(filedeposit,"%d\n",deposit);
    }
    //Menutup file
    fclose(filedeposit);
    fclose(tempdeposit);

    printf("\n\t\t\t\t\t===SALDO SUKSES DITAMBAH===\n");

    system("pause");
    system("cls");
    return menuadmin();
}

int tambahperusahaan() //Fungsi tambah perusahaan
{
    printf("\t\t\t\t\t\t======TAMBAH PERUSAHAAN======\n\n");
    //Membaca nama perusahaan, harga saham dan jumlah saham
    printf("\t\t\t\t\t\tMasukkan Nama Perusahaan : "); fflush(stdin); gets(namaperusahaan);
    printf("\t\t\t\t\t\tMasukkan Harga Saham/Lembar : "); scanf("%d", &hargasaham);
    printf("\t\t\t\t\t\tMasukkan Total Lembar Saham : "); scanf("%d", &jumlahsaham);
    // Membuka file perusahaan, saham perusahaan dan lembarsaham
    perusahaan=fopen("perusahaan.txt","a+");
    sahamperusahaan=fopen("sahamperusahaan.txt","a+");
    lembarsaham=fopen("lembarsaham.txt","a+");
    //Menulis ke file perusahaan, harga saham dan jumlahsaham
    fputs(strcat(namaperusahaan,"\n"),perusahaan);
    fprintf(sahamperusahaan,"%d\n",hargasaham);
    fprintf(lembarsaham,"%d\n",jumlahsaham);
    //Menutup file
    fclose(perusahaan);
    fclose(sahamperusahaan);
    fclose(lembarsaham);
    printf("\t\t\t\t\t\tPerusahaan sudah ditambahkan\n");
    printf("\t\t\t\t\t\tIngin menambahkan lagi? (Y/N) : "); scanf("%*c"); scanf("%c", &milih);
    if(milih=='Y') // Pilihan jika ingin menambah data perusahaan
    {
        printf("\n");
        return tambahperusahaan();
    }
    else
    {
        system("cls"); // Membersihkan layar
        return menuadmin(); // kembali ke menu admin
    }
}

int hapusperusahaan() // Fungsi hapus perusahaan
{
    printf("\t\t\t\t\t\t======HAPUS PERUSAHAAN======\n\n");
    perusahaan = fopen("perusahaan.txt", "r+"); //Membuka file
    int i=1;
    while(fgets(namaperusahaan,50,perusahaan)!=NULL) //Membaca nama perusahaan
    {
        printf("\t\t\t\t%d. %s", i, namaperusahaan); // Menampilkan nama perusahaab
        i++;
    }
    fclose(perusahaan); //Menutup file

    //Membaca nama perusahaan yang ingin dihapus
    printf("\n\t\t\t\tMasukkan nama perusahaan yang ingin dihapus : "); fflush(stdin); gets(hapus);
    strcat(hapus,"\n");

    user=fopen("username.txt","r+");

    while(fgets(username,100,user)!=NULL)
    {

        //Menghapus enter pada username
        char *pch = strstr(username, "\n");
        if(pch != NULL)
        {
            strncpy(pch, "\0", 1);
        }
        strcpy(b,username); //Mengopy file
        strcat(b,"'s Saham.txt"); //Menggabungkan file

        lembardimiliki=fopen(b,"r+");
        templembardimiliki=fopen("templembardimiliki.txt", "w+");
        perusahaan = fopen("perusahaan.txt", "r+");
        sahamperusahaan = fopen("sahamperusahaan.txt", "r+");
        lembarsaham = fopen("lembarsaham.txt", "r+");
        templembar = fopen("templembar.txt", "w+");
        while(fscanf(lembardimiliki,"%d\n",&belilembarsaham)!=EOF && fgets(namaperusahaan,50,perusahaan)!=NULL && fscanf(sahamperusahaan,"%d\n",&hargasaham)!=EOF && fscanf(lembarsaham,"%d\n",&jumlahsaham)!=EOF)
        {
            if(strcmp(namaperusahaan,hapus)!=0)
            {
                fprintf(templembardimiliki,"%d\n",belilembarsaham);
            }
        }
        fclose(lembardimiliki);
        fclose(perusahaan);
        fclose(templembardimiliki);
        fclose(templembar);
        fclose(sahamperusahaan);
        fclose(lembarsaham);

        lembardimiliki=fopen(b,"w+");
        templembardimiliki=fopen("templembardimiliki.txt", "r+");
        while(fscanf(templembardimiliki,"%d\n",&belilembarsaham)!=EOF)
        {
            fprintf(lembardimiliki,"%d\n",belilembarsaham);
        }
        fclose(lembardimiliki);
        fclose(templembardimiliki);
        strcpy(b,"");
    }
    fclose(user);
    //Membuka file
    perusahaan = fopen("perusahaan.txt", "r+");
    tempperusahaan = fopen("tempperusahaan.txt", "w+");
    tempharga = fopen("tempharga.txt", "w+");
    templembar = fopen("templembar.txt", "w+");
    sahamperusahaan = fopen("sahamperusahaan.txt", "r+");
    lembarsaham = fopen("lembarsaham.txt", "r+");

    // Membaca nama, harga saham dan lembar saham pada perusahaan
    while(fgets(namaperusahaan,50,perusahaan)!=NULL && fscanf(sahamperusahaan,"%d\n",&hargasaham)!=EOF && fscanf(lembarsaham,"%d\n",&jumlahsaham)!=EOF)
    {
        if(strcmp(hapus,namaperusahaan)!=0) //Jika tidak sama dengan 0 tulis ke file temporary
        {
            fputs(namaperusahaan,tempperusahaan);
            fprintf(tempharga,"%d\n",hargasaham);
            fprintf(templembar,"%d\n",jumlahsaham);
        }
    }
    //Menutup file
    fclose(sahamperusahaan);
    fclose(perusahaan);
    fclose(lembarsaham);
    fclose(tempperusahaan);
    fclose(tempharga);
    fclose(templembar);
    //Membuka file
    perusahaan = fopen("perusahaan.txt", "w+");
    tempperusahaan = fopen("tempperusahaan.txt", "r+");
    tempharga = fopen("tempharga.txt", "r+");
    templembar = fopen("templembar.txt", "r+");
    sahamperusahaan = fopen("sahamperusahaan.txt", "w+");
    lembarsaham = fopen("lembarsaham.txt", "w+");
    // Membaca file temporary sebelumnya
    while(fgets(namaperusahaan,50,tempperusahaan)!=NULL && fscanf(tempharga,"%d\n",&hargasaham)!=EOF && fscanf(templembar,"%d\n",&jumlahsaham)!=EOF)
    {
        //Menulis kembali ke file utama
        fputs(namaperusahaan,perusahaan);
        fprintf(sahamperusahaan,"%d\n",hargasaham);
        fprintf(lembarsaham,"%d\n",jumlahsaham);
    }
    //Menutup file
    fclose(sahamperusahaan);
    fclose(perusahaan);
    fclose(lembarsaham);
    fclose(tempperusahaan);
    fclose(tempharga);
    fclose(templembar);

    printf("\t\t\t\t\t=======Perusahaan sudah terhapus=======\n");

    system("pause"); // Mempause layar
    system("cls");
    return menuadmin();
}

int loginuser() //Fungsi loginuser
{
    system("cls"); // Membersihkan layar
    //Menggabungkan nama dan sandi dengan enter

    strcpy(b, nama);
    strcat(b, "'s Saham.txt");
    lembardimiliki=fopen(b,"a+");
    fclose(lembardimiliki);
    strcat(nama,"\n");
    strcat(sandi,"\n");
    //Membuka file
    user=fopen("username.txt","r+");
    pass=fopen("password.txt","r+");

    //Membaca username dan password pada file
    while(fgets(username,100,user)!=NULL && fgets(password,50,pass)!=NULL)
    {
        if(strcmp(username,nama)==0 && strcmp(password,sandi)==0) //Jika username dan nama begitu juga password sama maka :
        {
            menuuser(); // Memanggil fungsi menusuer
            system("pause"); // Mempause layar
        }
    }

    printf("\t\t\t\t\t\t====LOGIN GAGAL====\n\n");
    system("pause"); // Mempause layar
    system("cls"); // Membersihkan layar
    return menulogin(); //Kembali ke menu login
}

int menuuser() //Fungsi menuuser
{
    printf("\t\t\t\t\t\t===LOGIN SEBAGAI USER===\n\n");
    printf("\t\t\t\t\t1. Lihat Daftar Perusahaan\n");
    printf("\t\t\t\t\t2. Beli Saham\n");
    printf("\t\t\t\t\t3. Jual Saham\n");
    printf("\t\t\t\t\t4. Lihat Akun\n");
    printf("\t\t\t\t\t5. Logout\n");
    printf("\t\t\t\t\t6. Kembali Ke Menu Awal\n");

    fflush(stdin);
    printf("\n\t\t\t\t\tMasukkan pilihan : "); scanf("%d", &pilihan);
    switch(pilihan)
    {
        case 1 :
        {
            system("cls");
            daftarperusahaan(); //Memanggil fungsi daftarperusahaan
        } break;
            case 2 :
        {
            system("cls");
            belisaham(); //Memanggil fungsi belisaham
        } break;
            case 3 :
        {
            system("cls");
            jualsaham(); //Memanggil fungsi jualsaham
        } break;
        case 4 :
        {
            system("cls");
            menuakun(); //Memanggil fungsi menuakun
        }
        case 5 :
        {
            system("cls");
            return menulogin(); //kembali ke menulogin
            break;
        }
        case 6 :
        {
            system("cls");
            return main(); //kembali ke menuutama
            break;
        }
    }
}

int daftarperusahaan() //fungsi daftarperusahaan
{
    printf("\t\t\t\t\t\t===DAFTAR PERUSAHAAN===\n\n");
    //Membuka file
    perusahaan = fopen("perusahaan.txt", "r+");
    sahamperusahaan = fopen("sahamperusahaan.txt", "r+");
    lembarsaham = fopen("lembarsaham.txt", "r+");

    int i=1;
    //Membaca file
    while(fgets(namaperusahaan,50,perusahaan)!=NULL && fscanf(sahamperusahaan,"%d\n",&hargasaham)!=EOF && fscanf(lembarsaham,"%d\n",&jumlahsaham)!=EOF)
    {
        // Menampilkan nama, harga, dan sisa lembar saham
        printf("\t\t\t\t\t%d. Nama Perusahaan = %s\t\t\t\t\tHarga Saham/Lembar = %d\n\t\t\t\t\tSisa Lembar = %d\n\n",i, namaperusahaan, hargasaham, jumlahsaham);
        i++;
    }
    //Menutup file
    fclose(perusahaan);
    fclose(sahamperusahaan);
    fclose(lembarsaham);

    system("pause");
    system("cls");
    return menuuser(); //Kembali ke fungsi menuuser
}

int belisaham() //Fungsi belisaham
{
    printf("\t\t\t\t\t\t===BELI SAHAM===\n\n");
    //Membuka file
    lembardimiliki=fopen(b,"r+");
    int z=1;
    while(fscanf(lembardimiliki, "%d\n", &belilembarsaham)!=EOF)
    {
        a[z]=belilembarsaham;
        z++;
    }
    fclose(lembardimiliki);
    if(a[1]==0){
        perusahaan = fopen("perusahaan.txt", "r+");
        sahamperusahaan = fopen("sahamperusahaan.txt", "r+");
        lembarsaham = fopen("lembarsaham.txt", "r+");
        templembar = fopen("templembar.txt", "w+");
        lembardimiliki=fopen(b,"w+");

        int totalbelisaham=0;
        while(fgets(namaperusahaan,50,perusahaan)!=NULL && fscanf(sahamperusahaan,"%d\n",&hargasaham)!=EOF && fscanf(lembarsaham,"%d\n",&jumlahsaham)!=EOF)
        {
            printf("\t\t\t\tBerapa lembar yang akan dibeli untuk perusahaan %s \t\t\t\t(Isi 0 jika tidak membeli) : ", namaperusahaan); scanf("%d", &belilembarsaham);
            printf("\n");
            printf("\t\t\t\tSaham yang dimiliki = %d\n", belilembarsaham);
            fprintf(lembardimiliki, "%d\n", belilembarsaham); //Menulis file ke lembardimiliki sebagai saham yang dimiliki
            totalbelisaham += belilembarsaham*hargasaham; //Menjumlah total harga saham yang ingin dibeli
            printf("\t\t\t\tTotal harga beli saham = %d\n", totalbelisaham);
            jumlahsaham = jumlahsaham-belilembarsaham; //Mengurangi jumlah lembar saham perusahaan dengan yang dibeli
            fprintf(templembar,"%d\n",jumlahsaham); //Menulis sisa lembar saham ke file temporary
            printf("\t\t\t\tJumlah saham perusahaan tersisa = %d\n\n", jumlahsaham);
        }
        //Menutup File
        fclose(lembardimiliki);
        fclose(templembar);
        fclose(perusahaan);
        fclose(sahamperusahaan);
        fclose(lembarsaham);
        //Membuka file
        lembarsaham = fopen("lembarsaham.txt", "w+");
        templembar = fopen("templembar.txt", "r+");
        //Membaca file
        while(fscanf(templembar,"%d\n",&jumlahsaham)!=EOF)
        {
            fprintf(lembarsaham,"%d\n",jumlahsaham); //Menyalin kembali ke file utama yaitu lembarsaham
        }

        //Menutup file
        fclose(templembar);
        fclose(lembarsaham);

        //Membuka file
        user = fopen("username.txt", "r+");
        filedeposit = fopen("deposit.txt", "r+");
        tempdeposit = fopen("tempdeposit.txt", "w+");

        //Membaca pada file
        while(fgets(username,50,user)!=NULL && fscanf(filedeposit,"%d\n",&deposit)!=EOF)
        {
            if(strcmp(username,nama)==0) //untuk mencari tahu deposit pada suatu user mana
            {
                deposit=deposit-totalbelisaham; //Menghitung sisa deposit
            }

            fprintf(tempdeposit,"%d\n",deposit); //Menulis deposit ke file temporary
        }
        //Menutup file
        fclose(filedeposit);
        fclose(user);
        fclose(tempdeposit);
        //Membuka file
        filedeposit = fopen("deposit.txt", "w+");
        tempdeposit = fopen("tempdeposit.txt", "r+");
        //Membaca sekaligus menyalin file temporary ke file deposit utama
        while(fscanf(tempdeposit,"%d\n",&deposit)!=EOF)
        {
            fprintf(filedeposit,"%d\n",deposit);
        }
        //Menutup file
        fclose(filedeposit);
        fclose(tempdeposit);

        printf("\t\t\t\t\t===PEMBELIAN SAHAM SUKSES===\n");
        }
    else
    {
        perusahaan = fopen("perusahaan.txt", "r+");
        sahamperusahaan = fopen("sahamperusahaan.txt", "r+");
        lembarsaham = fopen("lembarsaham.txt", "r+");
        lembardimiliki = fopen(b,"r+");
        templembar = fopen("templembar.txt", "w+");
        templembardimiliki = fopen("templembardimiliki.txt", "w+");

        int z=0;
        int totalbelisaham=0;
        while(fgets(namaperusahaan,50,perusahaan)!=NULL && fscanf(sahamperusahaan,"%d\n",&hargasaham)!=EOF && fscanf(lembarsaham,"%d\n",&jumlahsaham)!=EOF)
        {
            printf("\t\t\t\tBerapa lembar yang akan dibeli untuk perusahaan %s \t\t\t\t(Isi 0 jika tidak membeli) : ", namaperusahaan); scanf("%d", &a[z]);
            fscanf(lembardimiliki,"%d\n", &belilembarsaham);
            belilembarsaham=belilembarsaham+a[z];
            printf("\t\t\t\tSaham yang dimiliki = %d\n", belilembarsaham);
            fprintf(templembardimiliki, "%d\n", belilembarsaham); //Menulis file ke lembardimiliki sebagai saham yang dimiliki
            totalbelisaham += a[z]*hargasaham; //Menjumlah total harga saham yang ingin dibeli
            printf("\t\t\t\tTotal harga beli saham = %d\n", totalbelisaham);
            jumlahsaham = jumlahsaham-a[z]; //Mengurangi jumlah lembar saham perusahaan dengan yang dibeli
            printf("\t\t\t\tJumlah saham perusahaan tersisa = %d\n\n", jumlahsaham);
            fprintf(templembar,"%d\n",jumlahsaham); //Menulis sisa lembar saham ke file temporary
            z++;
        }
        //Menutup File
        fclose(templembar);
        fclose(perusahaan);
        fclose(sahamperusahaan);
        fclose(lembarsaham);
        fclose(templembardimiliki);
        fclose(lembardimiliki);

        templembardimiliki=fopen("templembardimiliki.txt", "r+");
        lembardimiliki=fopen(b,"w+");
        while(fscanf(templembardimiliki, "%d\n", &belilembarsaham)!=EOF)
        {
            fprintf(lembardimiliki,"%d\n", belilembarsaham);
        }
        fclose(templembardimiliki);
        fclose(lembardimiliki);

        //Membuka file
        lembarsaham = fopen("lembarsaham.txt", "w+");
        templembar = fopen("templembar.txt", "r+");
        //Membaca file
        while(fscanf(templembar,"%d\n",&jumlahsaham)!=EOF)
        {
            fprintf(lembarsaham,"%d\n",jumlahsaham); //Menyalin kembali ke file utama yaitu lembarsaham
        }
        //Menutup file
        fclose(templembar);
        fclose(lembarsaham);

        //Membuka file
        user = fopen("username.txt", "r+");
        filedeposit = fopen("deposit.txt", "r+");
        tempdeposit = fopen("tempdeposit.txt", "w+");

        //Membaca pada file
        while(fgets(username,50,user)!=NULL && fscanf(filedeposit,"%d\n",&deposit)!=EOF)
        {
            if(strcmp(username,nama)==0) //untuk mencari tahu deposit pada suatu user mana
            {
                deposit=deposit-totalbelisaham; //Menghitung sisa deposit
            }

            fprintf(tempdeposit,"%d\n",deposit); //Menulis deposit ke file temporary
        }
        //Menutup file
        fclose(filedeposit);
        fclose(user);
        fclose(tempdeposit);
        //Membuka file
        filedeposit = fopen("deposit.txt", "w+");
        tempdeposit = fopen("tempdeposit.txt", "r+");
        //Membaca sekaligus menyalin file temporary ke file deposit utama
        while(fscanf(tempdeposit,"%d\n",&deposit)!=EOF)
        {
            fprintf(filedeposit,"%d\n",deposit);
        }
        //Menutup file
        fclose(filedeposit);
        fclose(tempdeposit);

        printf("\t\t\t\t\t===PEMBELIAN SAHAM SUKSES===\n");
    }

    system("pause");
    system("cls");
    return menuuser();
}

int jualsaham() //fungsi jualsaham
{
    printf("\t\t\t\t\t\t===JUAL SAHAM===\n\n");

    printf("\t\t\t\t\tDaftar Saham Yang Dimiliki : \n");
    lembardimiliki = fopen(b, "r+");
    perusahaan = fopen("perusahaan.txt","r+");
    int z=1;
    while(fscanf(lembardimiliki, "%d\n", &belilembarsaham)!=EOF && fgets(namaperusahaan,50,perusahaan)!=NULL)
    {

        printf("\t\t\t\t\t%d. Perusahaan %s",z,namaperusahaan);
        printf("\t\t\t\t\tJumlah lembar saham = %d Lembar\n\n",belilembarsaham);
        z++;
    }

    fclose(lembardimiliki);
    fclose(perusahaan);

    //Membuka file
    perusahaan = fopen("perusahaan.txt", "r+");
    sahamperusahaan = fopen("sahamperusahaan.txt", "r+");
    lembarsaham = fopen("lembarsaham.txt", "r+");
    templembar = fopen("templembar.txt", "w+");
    lembardimiliki=fopen(b,"r+");
    templembardimiliki=fopen("templembardimiliki.txt", "w+");

    //Membaca file
    z=1;
    int totalbelisaham=0;
    while(fgets(namaperusahaan,50,perusahaan)!=NULL && fscanf(sahamperusahaan,"%d\n",&hargasaham)!=EOF && fscanf(lembarsaham,"%d\n",&jumlahsaham)!=EOF && fscanf(lembardimiliki,"%d\n",&belilembarsaham)!=EOF)
    {
        printf("\t\t\t\tBerapa lembar yang akan dijual untuk perusahaan %s \t\t\t\t(Isi 0 jika tidak menjual) : ", namaperusahaan); scanf("%d", &a[z]);
        belilembarsaham = belilembarsaham-a[z];
        fprintf(templembardimiliki, "%d\n", belilembarsaham); //Menulis file ke lembardimiliki sebagai saham yang dimiliki
        printf("\t\t\t\tJumlah saham yang dimiliki = %d\n", belilembarsaham);
        totalbelisaham += a[z]*hargasaham; //Menjumlah total harga saham yang ingin dibeli
        printf("\t\t\t\tTotal harga saham yang dijual = %d\n", totalbelisaham);
        jumlahsaham = jumlahsaham+a[z]; //Mengurangi jumlah lembar saham perusahaan dengan yang dibeli
        printf("\t\t\t\tJumlah perusahaan yang tersisa = %d\n\n", jumlahsaham);
        fprintf(templembar,"%d\n",jumlahsaham); //Menulis sisa lembar saham ke file temporary
        z++;
    }
    //Menutup File
    fclose(lembardimiliki);
    fclose(templembardimiliki);
    fclose(templembar);
    fclose(perusahaan);
    fclose(sahamperusahaan);
    fclose(lembarsaham);

    lembardimiliki = fopen(b, "w+");
    templembardimiliki = fopen("templembardimiliki.txt", "r+");
    while(fscanf(templembardimiliki, "%d\n", &belilembarsaham)!=EOF)
    {
        fprintf(lembardimiliki,"%d\n",belilembarsaham);
    }
    fclose(lembardimiliki);
    fclose(templembardimiliki);

    //Membuka file
    lembarsaham = fopen("lembarsaham.txt", "w+");
    templembar = fopen("templembar.txt", "r+");
    //Membaca file
    while(fscanf(templembar,"%d\n",&jumlahsaham)!=EOF)
    {
        fprintf(lembarsaham,"%d\n",jumlahsaham); //Menyalin kembali ke file utama yaitu lembarsaham
    }

    //Menutup file
    fclose(templembar);
    fclose(lembarsaham);

    //Membuka file
    user = fopen("username.txt", "r+");
    filedeposit = fopen("deposit.txt", "r+");
    tempdeposit = fopen("tempdeposit.txt", "w+");

    //Membaca pada file
    while(fgets(username,50,user)!=NULL && fscanf(filedeposit,"%d\n",&deposit)!=EOF)
    {
        if(strcmp(username,nama)==0) //untuk mencari tahu deposit pada suatu user mana
        {
            deposit=deposit+totalbelisaham; //Menghitung sisa deposit
        }

        fprintf(tempdeposit,"%d\n",deposit); //Menulis deposit ke file temporary
    }
    //Menutup file
    fclose(filedeposit);
    fclose(user);
    fclose(tempdeposit);
    //Membuka file
    filedeposit = fopen("deposit.txt", "w+");
    tempdeposit = fopen("tempdeposit.txt", "r+");
    //Membaca sekaligus menyalin file temporary ke file deposit utama
    while(fscanf(tempdeposit,"%d\n",&deposit)!=EOF)
    {
        fprintf(filedeposit,"%d\n",deposit);
    }
    //Menutup file
    fclose(filedeposit);
    fclose(tempdeposit);

    printf("\t\t\t\t\t===SAHAM SUKSES TERJUAL===\n");
    system("pause");
    system("cls");
    system("cls");
    return menuuser();//Kembali ke fungsu menuuser
}

int menuakun() //fungsi menuakun
{
    printf("\t\t\t\t\t\t===AKUN===\n\n");
    //Membuka file
    user = fopen("username.txt", "r+");
    filedeposit = fopen("deposit.txt", "r+");
    //Menampilkan sisa deposit
    while(fgets(username,50,user)!=NULL && fscanf(filedeposit,"%d\n",&deposit)!=EOF)
    {
        if(strcmp(username,nama)==0)
        {
            printf("\t\t\t\t\tSisa uang anda = %d Rupiah\n",deposit);
        }
    }
    //Menutup file
    fclose(filedeposit);
    fclose(user);

    printf("\n\n");

    //Membuka file
    lembardimiliki = fopen(b, "r+");
    perusahaan = fopen("perusahaan.txt","r+");
    int z=1;
    while(fscanf(lembardimiliki, "%d\n", &belilembarsaham)!=EOF && fgets(namaperusahaan,50,perusahaan)!=NULL)
    {
        printf("\t\t\t\t\t%d. Perusahaan %s",z,namaperusahaan);
        printf("\t\t\t\t\tJumlah lembar saham = %d Lembar\n\n",belilembarsaham);
        z++;
    }

    fclose(lembardimiliki);
    fclose(perusahaan);
    system("pause");
    system("cls");
    return menuuser(); //Kembali ke fungsi menuuser
}

int main()
{
    printf("\t\t\t\t\t\t========PROGRAM SAHAM========\n");
    printf("\t\t\t\t\t\t1. Register\n");
    printf("\t\t\t\t\t\t2. Login\n");
    printf("\t\t\t\t\t\t3. Exit\n\n");

    printf("\t\t\t\t\t\tMasukkan pilihan : "); scanf("%d", &pilihan);
    system("cls");
    switch(pilihan)
    {
    case 1 :
        {
            registermenu(); //Memanggil fungsi registermenu
            system("cls");
        } break;
    case 2 :
        {
            menulogin(); //Memanggil fungsi menulogin
        } break;
    case 3 :
        {
            exit(0); //Exit
        }
    }
}
