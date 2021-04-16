# soal-shift-sisop-modul-2-A11-2021

## Soal 1 

## Soal 2
[no 2](https://github.com/erzajanitra/soal-shift-sisop-modul-2-A11-2021/blob/main/soal2/soal2.c)
### 2a
**Soal** : Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop”. Karena bos Loba teledor, dalam zip tersebut bisa berisi folder-folder yang tidak penting, maka program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.
* Mengextract zip kemudian disimpan di folder ``petshop``
```
    
    char *array[]={"mkdir","-p","/home/erzajanitra/modul2/petshop",NULL};
    func1("/bin/mkdir",array);
    
    char *array2[]={"unzip","-q","pets.zip","-d","petshop",NULL};
    execv("/usr/bin/unzip",array2);
```
  Menggunakan *mkdir* untuk membuat folder petshop pada directory */home/erzajanitra/modul2/*. Untuk mengextract zip menggunakan *unzip* dengan syntax *unzip,file source,file    destination,NULL*. *-q* digunakan agar log ketika melakukan extract tidak ditampilkan pada terminal
* Menghapus folder yang tidak dibutuhkan
```
    DIR *dir=opendir("/home/erzajanitra/modul2/petshop");
    struct dirent *dent;
    if(dir!=NULL){
      while((dent=readdir(dir))!=NULL){
        
        //hidden file       
        if(strcmp(dent->d_name,".")==0 || strcmp(dent->d_name,"..")==0) continue; 
        if(fork()==0)  continue;  
        else if(dent->d_type==DT_DIR){
               char fileName[100]="/home/erzajanitra/modul2/petshop/";
               strcat(fileName,dent->d_name);
               char *argv[]={"rm","-rf",fileName,NULL};
               func1("/bin/rm",argv);
               exit(EXIT_SUCCESS); 
         }
```
  Menggunakan directory listing dengan library ``dirent.h`` untuk mengetahui isi folder yang telah di unzip. Karena file yang dibutuhkan hanya foto-foto dengan format *.jpg*, maka file yang berupa directory *DT_DIR* di remove.

### 2b
**Soal** : Foto peliharaan perlu dikategorikan sesuai jenis peliharaan, maka kamu harus membuat folder untuk setiap jenis peliharaan yang ada dalam zip. Karena kamu tidak mungkin
memeriksa satu-persatu, maka program harus membuatkan folder-folder yang dibutuhkan sesuai dengan isi zip. 
* Fungsi untuk menghilangkan 4 indeks terakhir dari sebuah string
```
  char* cut(char *arr){
    int n,i;
    char* cuts;

    for(i=0;arr[i]!='\0';i++);
      n=i-4+1;

    if(n<1) return NULL;

    cuts=(char*)malloc(n*sizeof(char));

    for(i=0;i<n-1;i++)
      cuts[i]=arr[i];
    cuts[i]='\0';
    return cuts;
  }
```
  Menggunakan fungsi *cut* untuk setiap file foto agar string nama file tersebut dapat digunakan untuk membuat folder untuk setiap jenis peliharaan dan nama file foto          peliharaan. 
```
  char *cutss=cut(dent->d_name); //menghilangkan.jpg
```
* Membuat folder sesuai kategori jenis peliharaan yang ada
```
        //string yg dipisahin _
        //untuk foto yg ada 2 pet(dipisahin _)
        char *photos;
        
        while(photos=strtok_r(cutss,"_",&cutss)){
            int i=0;
            char pet[30], pName[30], pAge[30];
            char *ph=photos;
            char *photo;
            while(photo=strtok_r(ph,";",&ph)){
                if(i==0){
                  //buat folder sesuai nama pets
                    char files[80]="/home/erzajanitra/modul2/petshop/";
                    strcat(files,photo);
                    char *argv[]={"mkdir","-p",files,NULL};
                    func1("/bin/mkdir",argv);
                    strcpy(pet,photo);
                }
```
  *strtok_r* digunakan untuk memotong kata dalam string. Pada *while loop* paling pertama, mengecek untuk foto yang terdiri dari dua hewan peliharaan sehingga dipisahkan dengan _ , kemudian memotong string. Setelah itu, membuat *char* untuk menyimpan kategori hewan peliharaan, nama hewan peliharaan, dan umur. Pada *while loop* kedua, memotong string nama file yang dipisahkan dengan ; . Ketika *i=0* , berarti sedang mengecek potongan pertama pada string sehingga mendapatkan kategori hewan peliharaan. Kemudian, menggunakan *mkdir* untuk membuat folder sesuai kategori peliharaan.
  
### 2c
**Soal** : Setelah folder kategori berhasil dibuat, programmu akan memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan.
* Memindahkan foto ke folder dengan kategori yang sesuai
```
              char fileku[80];
              strcpy(fileku,"/home/erzajanitra/modul2/petshop/");
              strcat(fileku,dent->d_name);
              
              //file destination
              char dest[80];
              strcpy(dest,"/home/erzajanitra/modul2/petshop/");
              strcat(dest,pet); 
              strcat(dest,"/"); 
              strcat(dest,pName); 
              strcat(dest,".jpg");
              char *argv[]={"cp",fileku,dest,NULL};
              func1("/bin/cp",argv);
```
  *char fileku* digunakan untuk menyimpan path file source, sedangkan *char dest* digunakan untuk menyimpan file tujuan. *strcat* untuk menambahkan string pada path */home/erzajanitra/modul2/petshop/* sehingga foto dapat dipindahkan ke folder kategori yang sesuai, dengan nama file foto yang sesuai. 
* Menghapus foto yang telah dipindahkan ke folder
```
    char hapus[60]="/home/erzajanitra/modul2/petshop/";
        strcat(hapus,dent->d_name);
        char *args[]={"rm",hapus,NULL};
        execv("/bin/rm",args);
```
   File foto yang sudah dipindahkan ke folder dengan kategori masing-masing di remove karena sudah tidak diperlukan.
   
### 2d
**Soal** : Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai
```
    while(photos=strtok_r(cutss,"_",&cutss)){
            int i=0;
            char pet[30], pName[30], pAge[30];
            char *ph=photos;
            char *photo;
            while(photo=strtok_r(ph,";",&ph)){
                if(i==0){
                  //buat folder sesuai nama pets
                    char files[80]="/home/erzajanitra/modul2/petshop/";
                    strcat(files,photo);
                    char *argv[]={"mkdir","-p",files,NULL};
                    func1("/bin/mkdir",argv);
                    strcpy(pet,photo);
                }
                 if(i==1){
                  //nama pets
                  strcpy(pName,photo);
                }
                if(i==2){
                  //umurnya pets
                  strcpy(pAge,photo);
                }

              i++;
            }
```
   Untuk satu foto yang terdiri dari 2 hewan peliharaan ditandai dengan _ yang memisahkan masing-masing kategori dan nama hewan peliharaan tersebut. Maka menggunakan *strtok_r* untuk memotong kedua kategori hewan peliharaan tersebut, kemudian kategori, nama, dan umur masing-masing disimpan pada sebuah *char*. Sehingga, foto yang terdiri dari 1 hewan peliharaan dapat berada di 2 folder kategori berbeda, dengan nama sesuai kategori hewan tersebut.
### 2e
**Soal** : Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut. 
* Membuat file ``keterangan.txt`` pada masing-masing folder kategori
```
     //keterangan.txt di masing2 folder pets
          char file[50];
          strcpy(file,"/home/erzajanitra/modul2/petshop/");
          strcat(file,pet);
          strcat(file,"/keterangan.txt");
```
   File ``keterangan.txt`` dibutuhkan untuk menampilkan informasi nama dan umur untuk masing-masing hewan peliharaan pada masing-masing kategori hewan peliharaan. Agar file tersebut disimpan pada folder kategori yang sesuai, kita harus memastikan bahwa path penyimpanannya sesuai. Oleh karena itu, menggunakan *strcat* untuk *"/home/erzajanitra/modul2/petshop/"* dengan *pet* sebagai kategori hewan peliharaan.
* Membuat isi file ``keterangan.txt``
```       
          char ch[50];
          strcat(ch,"nama : ");
          strcat(ch,pName);
          strcat(ch,"\numur: ");
          strcat(ch,pAge);
          strcat(ch,"tahun\n\n");
  ```
   Pada proses sebelumnya, nama dan umur masing-masing disimpan pada *pName* dan *pAge* sehingga untuk menampilkan isi file ``keterangan.txt`` dapat menggunakan *strcat*. *strcat* digunakan untuk menggabungkan string *pName* dan *pAge* sesuai format pada contoh soal.
* Membuat file ``keterangan.txt``
```
          //buat keterangan.txt
          FILE *fp;
          fp=fopen(file,"a");
          fputs(ch,fp);

          fclose(fp);
 ```
   Membuat file pada directory path yang sudah dibuat dengan mode *append* sehingga dapat menambahkan informasi baru tanpa menghapus isi file yang sudah ada. *fputs* digunakan untuk memasukkan isi file dari *char ch* yang telah dibuat pada file *fp*.
## Soal 3
