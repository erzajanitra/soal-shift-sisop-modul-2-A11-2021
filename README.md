# soal-shift-sisop-modul-2-A11-2021

## Soal 1 

## Soal 2
[no 2](soal2.c)
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


### 2d
**Soal** : Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai

### 2e
**Soal** : Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut. 

## Soal 3
