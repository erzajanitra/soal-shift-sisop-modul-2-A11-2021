# soal-shift-sisop-modul-2-A11-2021

## Soal 1 
[no 1](https://github.com/erzajanitra/soal-shift-sisop-modul-2-A11-2021/blob/main/soal1/soal1.c)

### 1a
**Soal** : (a) Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg.
```
            pid_t child2;
			int status2;
			child2=fork();
			if(child2 < 0){
				exit(EXIT_FAILURE);
 			}
			if(child2 == 0){
				char *mkdir[] = {"mkdir","Musyik","Pyoto","Fylm",NULL};
				execv("/bin/mkdir",mkdir);
 			}
```
Pembuatan folder baru diletakkan pada child process terdalam pada fungsi ``do_something()`` agar proses ini dieksekusi paling awal oleh program berurutan sebagaimana output yang diminta. Menggunakan *mkdir* untuk membuat 3 directory, yaitu "Musyik","Pyoto", dan "Fylm".

### 1b
**Soal** : (b) untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga :).
* Download film pada ``downloadfi()``
```
        pid_t child1;
		int status1;
		child1 = fork();
		char link[100]={"drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};
		if(child1< 0){
			exit(EXIT_FAILURE);
 		}
		 if(child1==0){
		char *download[] = {"wget","-b","--no-check-certificate",link,"-O","Film_for_Stevany.zip",NULL};
		execv("/usr/bin/wget",download);
		}
```
Source code di atas berfungsi untuk mendownload zipfile 'Film_for_Stevany.zip' dari link film yang sudah disediakan. Link download di simpan pada sebuah char bernama *link* yang akan digunakan pada *wget*. Lalu, proses ini diletakkan di dalam fungsi ``downloadfi()``
* Download musik pada ``downloadms()``
```
        if(child_id == 0){//ini child
		pid_t child1;
		int status1;
		child1 = fork();
		char link[100]={"drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download"};
		if(child1< 0){
			exit(EXIT_FAILURE);
 		}
		 if(child1==0){
		char *download[] = {"wget","-b","--no-check-certificate",link,"-O","Musik_for_Stevany.zip",NULL};
		execv("/usr/bin/wget",download);
		}
```
Source code di atas berfungsi untuk mendownload zipfile 'Musik_for_Stevany.zip' dari link film yang sudah disediakan. Link download di simpan pada sebuah char bernama *link* yang akan digunakan pada *wget*. Lalu, proses ini diletakkan di dalam fungsi ``downloadms()``
* Download foto pada ``downloadft()``
```
        pid_t child1;
		int status1;
		child1 = fork();
		char link[100]={"drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download"};
		if(child1< 0){
			exit(EXIT_FAILURE);
 		}
		if(child1==0){
		char *download[] = {"wget","-b","--no-check-certificate",link,"-O","Foto_for_Stevany.zip",NULL};
		execv("/usr/bin/wget",download);
		}
```
Source code di atas berfungsi untuk mendownload zipfile 'Foto_for_Stevany.zip' dari link film yang sudah disediakan. Link download di simpan pada sebuah char bernama *link* yang akan digunakan pada *wget*. Lalu, proses ini diletakkan di dalam fungsi ``downloadft()``

### 1c
**Soal** : (c) Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu meng-extract-nya setelah didownload.
* Unzip *Foto_for_Stevany.zip*
```
        else{//ini parent
			while((wait(&status1))>0);
			sleep(5);
			char *unzip[] = {"unzip","/home/tsania/Documents/sisopshift2/Foto_for_Stevany.zip",NULL};
			execv("/usr/bin/unzip",unzip);
		}
```
source code di atas berfungsi untuk meng-unzip zipfile 'Foto_for_Stevany.zip' yang sudah terdownload, prosesnya bersambung dengan download dimana proses unzip ini berposisi sebagai parent process sehingga prosesnya dijalankan setelah child processnya yaitu download sudah dikerjakan.
* Unzip *Film_for_Stevany.zip*
```
        else{//ini parent
			while((wait(&status1))>0);
			sleep(5);
			char *unzip[] = {"unzip","/home/tsania/Documents/sisopshift2/Film_for_Stevany.zip",NULL};
			execv("/usr/bin/unzip",unzip);
		}
```
source code di atas berfungsi untuk meng-unzip zipfile 'Film_for_Stevany.zip' yang sudah terdownload, prosesnya bersambung dengan download dimana proses unzip ini berposisi sebagai parent process sehingga prosesnya dijalankan setelah child processnya yaitu download sudah dikerjakan.
* Unzip *Musik_for_Stevany.zip*
```
        else{//ini parent
			while((wait(&status1))>0);
			sleep(5);
			char *unzip[] = {"unzip","/home/tsania/Documents/sisopshift2/Musik_for_Stevany.zip",NULL};
			execv("/usr/bin/unzip",unzip);
		}
```
source code di atas berfungsi untuk meng-unzip zipfile 'Musik_for_Stevany.zip' yang sudah terdownload, prosesnya bersambung dengan download dimana proses unzip ini berposisi sebagai parent process sehingga prosesnya dijalankan setelah child processnya yaitu download sudah dikerjakan.


### 1d
**Soal** : (d) serta memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan).
* Fungsi yang menjalankan proses pemindahan file dalam direktori hasil unzip berlaku untuk semua pemanggilannya di fungsi lain yaitu pada fungsi ``re_move(file1,file2);``
```
void re_move(char *oldfile, char *newfile){

	char current[1000];
	struct dirent *dent;
	DIR *dir=opendir(oldfile);

 	if(dir!=NULL){
        while((dent=readdir(dir))!=NULL){
                    //hidden file       
            if(strcmp(dent->d_name,".")!=0 || strcmp(dent->d_name,"..")!=0){
                strcpy(current,oldfile);
                strcat(current,"/");
                strcat(current,dent->d_name);
                move(current,newfile);
            }
        }
 	}

	(void) closedir(dir);
}
```
* Memindahkan isi FOTO ke folder baru "Pyoto"
```   else{
		while((waitpid(child_id,&status,0))>0);
		re_move("FOTO","Pyoto");
	}
```
di atas adalah source code pemanggilan fungsi ``re_move()`` oleh proses pemindahan isi folder FOTO ke folder baru "Pyoto". prosesnya dieksekusi setelah unzipping zipfile yang terdownload dan terletak di setiap fungsi ``downloadms()``,``downloadft()``, dan ``downloadfi()``. Jadi pada setiap fungsi yang sebelumnya disebutkan terdapat nested fork agar proses dapat dijalankan berurutan tidak terbatas 1 pasang child-parent terlebih multiple child-parent process.
* Memindahkan isi MUSIK ke folder baru "Musyik"
```   else{
		while((waitpid(child_id,&status,0))>0);
		re_move("MUSIK","Musyik");
	}
```
di atas adalah source code pemanggilan fungsi ``re_move()`` oleh proses pemindahan isi folder MUSIK ke folder baru "Musyik". prosesnya dieksekusi setelah unzipping zipfile yang terdownload dan terletak di setiap fungsi ``downloadms()``,``downloadft()``, dan ``downloadfi()``. Jadi pada setiap fungsi yang sebelumnya disebutkan terdapat nested fork agar proses dapat dijalankan berurutan tidak terbatas 1 pasang child-parent terlebih multiple child-parent process.
* Memindahkan isi FILM ke folder baru "Fylm"
```   else{
		while((waitpid(child_id,&status,0))>0);
		re_move("FILM","Fylm");
	}
```
di atas adalah source code pemanggilan fungsi ``re_move()`` oleh proses pemindahan isi folder FILM ke folder baru "Fylm". prosesnya dieksekusi setelah unzipping zipfile yang terdownload dan terletak di setiap fungsi ``downloadms()``,``downloadft()``, dan ``downloadfi()``. Jadi pada setiap fungsi yang sebelumnya disebutkan terdapat nested fork agar proses dapat dijalankan berurutan tidak terbatas 1 pasang child-parent terlebih multiple child-parent process.

### 1e
**Soal** : (e) Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany).
* Menjalankan program 6 jam sebelum waktu ulang tahun
```
time_t t = time(NULL);
	char b_day[100];
	struct tm tmp = *localtime(&t);
	strftime(b_day,sizeof(b_day),"%Y-%m-%d %H:%M:%S",&tmp);
	char target1[]="2021-04-09 16:22:00";
	char target2[]="2021-04-09 22:22:00";

	if(strcmp(b_day,target1)==0){
		printf("Berhasil Target 1\n");
		do_something();
		
	}

```
source code di atas berfungsi untuk mendeklarasikan jam untuk proses pertama dan kedua. dimana proses pertama akan dilakukan perbandingan string localtime yang disimpan pada array of string bervariabel b_day. kemudian jika perbandingan kedua string ``b_day`` dan ``target1`` sama maka proses pertama yang terdiri dari download, unzip, dan pemindahan isi file lama ke folder baru akan tereksekusi secara otomatis.

### 1f
**Soal** : (f) Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip).
* Menjalankan program ketika waktu ulang tahun
```
	else if(strcmp(b_day,target2)==0){
	printf("Berhasil Target 2\n");
		char *zip[] = {"zip","-rmq","Lopyu_Stevany","Pyoto","Fylm","Musyik","FILM","FOTO","MUSIK",NULL};
		func1("/usr/bin/zip",zip);
	}
```
merujuk pada source code nomor sebelumnya proses kedua yaitu proses zipping folder-folder baru sekaligus pembersihan folder-folder lama beserta isinya dieksekusi oleh pembandingan string ``b_day`` yang bervalue localtime dengan string target2 yaitu 6 jam setelah target1 seperti yang diminta pada soal. dengan cara yang sama dengan nomor sebelumnya, jika pembandingan kedua string valid bernilai sama maka proses zipping dan folder removal akan dieksekusi.

## Hasil Program
- pada 9 April 16:22 <br/>
![capt](https://user-images.githubusercontent.com/69724694/115961347-388a2680-a540-11eb-9a41-05489ca618a2.PNG)

- pada 9 April 22:22<br/>
![capt2](https://user-images.githubusercontent.com/69724694/115961369-535c9b00-a540-11eb-8eb8-f97df47825f4.PNG)


### Kendala yang dialami
- Program sebelum revisi menggunakan loop dan fungsi sleep() yang banyak pada awalnya berjalan normal kemudian dicoba beberapa kali justru mengakibatkan VM crash. masih belum tau penyebabnya.
- Belum terlalu paham cara kerja nested-fork dan bagaimana urutan spawningnya dengan kompleksitas prosesnya.
- Dengan command yang sesuai masih saja ikut mendownload logfile yang tidak diminta untuk ikut muncul pada proses download zipfile.
### Screenshot Error
* Eror ketika mengganti waktu menjadi 22.22 WIB saat proses untuk 16.22 WIB belum selesai <br/>
![err2](https://user-images.githubusercontent.com/75319371/115982286-15a15600-a5c4-11eb-8586-8f5da509ad2a.JPG)


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
  Menggunakan *mkdir* untuk membuat folder petshop pada directory */home/erzajanitra/modul2/*. Untuk mengextract zip menggunakan *unzip* dengan syntax *unzip,file source,file   destination,NULL*. *-q* digunakan agar log ketika melakukan extract tidak ditampilkan pada terminal. Untuk mengekseksui *mkdir* menggunakan ``func1`` yang merupakan fungsi    untuk mempersingkat fork. Fungsi tersebut akan mengeksekusi command apabila child process berhasil dibuat dan melakukan wait apabila merupakan parent process.
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
  Menggunakan directory listing dengan library ``dirent.h`` untuk mengetahui isi folder yang telah di unzip. Karena file yang dibutuhkan hanya foto-foto dengan format *.jpg*,   maka file yang berupa directory *DT_DIR* di remove. Kemudian, menggunakan ``func1`` untuk mempersingkat fork dan melakukan *exit* ketika selesai menghapus directory           tersebut.

### 2b
**Soal** : Foto peliharaan perlu dikategorikan sesuai jenis peliharaan, maka kamu harus membuat folder untuk setiap jenis peliharaan yang ada dalam zip. Karena kamu tidak mungkin memeriksa satu-persatu, maka program harus membuatkan folder-folder yang dibutuhkan sesuai dengan isi zip. 
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
* Menggunakan fungsi *cut* pada setiap file foto agar string nama file tersebut dapat digunakan untuk membuat folder untuk setiap jenis peliharaan dan nama file foto          peliharaan. Fungsi ini akan menghilangkan string *.jpg* pada nama file sehingga ketika memotong string menggunakan *strtok_r*, string *.jpg* itu tidak diikutkan. 
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

### Kendala yang dialami
1. **No 2a**
   - Tidak bisa mengunzip pets.zip. Solusinya, kami harus menggunakan *usr* pada *execv(/usr/bin/unzip*) ketika mengunzip pets.zip.
   - Ketika menghilangkan file yang tidak penting, terjadi eror untuk file *"."* dan *".."* karena kedua file tersebut merupakan hidden file. Solusinya, kami menggunakan *if-      else condition*  apabila memenuhi kondisi tersebut akan di continue
2. Kami menggunakan strtok_r untuk memotong file name foto agar masing-masing potongan tersebut dapat disimpan di sebuah char dan digunakan untuk membuat folder dan isi file    keterangan.txt. Kendalanya yaitu tidak bisa membuat folder kategori, disebabkan file name yang dipotong tersebut memiliki .jpg pada akhir nama file. Oleh karena itu, kami    menggunakan fungsi ``cut`` untuk menghapus 4 indeks terakhir dari nama file.
3. Pada saat memindahkan foto ke masing-masing folder kategori, ada beberapa file foto yang tidak berhasil dipindahkan. Hal itu disebabkan kami menggunakan ``func`` ketika      mengunzip. Dimana fungsi tersebut digunakan untuk mempersingkat fork sehingga akan melakukan wait apabila bukan proses child. Solusinya, kami menggunakan ``execv`` dan        proses setelah unzip diletakkan pada parent process.

### Screenshot Error
1. Kendala no 1
![image](https://user-images.githubusercontent.com/75319371/115656412-65331800-a35f-11eb-8ebc-76fdc43104ac.png)
2. Kendala no 2
![image](https://user-images.githubusercontent.com/75319371/115656289-2e5d0200-a35f-11eb-976a-33db40a1824a.png)

### Hasil ketika berhasil melakukan semua proses
* Folder kategori hewan peliharaan
![image](https://user-images.githubusercontent.com/75319371/115656963-4ed98c00-a360-11eb-8d5e-a8a10c365310.png)
* Isi Folder (menggunakan contoh folder dog)
![er2](https://user-images.githubusercontent.com/75319371/115656904-35d0db00-a360-11eb-9507-69e801d6aa6c.JPG)


## Soal 3
[no 3](https://github.com/erzajanitra/soal-shift-sisop-modul-2-A11-2021/blob/main/soal3/soal3.c)
### 3a
**Soal** : Membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp **YYYY-mm-dd_HH:ii:ss**
* Menggunakan timestamp untuk nama directory
```
     time_t t=time(NULL);
    char fileName[100];
    struct tm *tmp=localtime(&t);
    strftime(fileName,sizeof(fileName),"%Y-%m-%d_%H:%M:%S", tmp);
```
   Timestamp didapatkan dari *localtome* saat ini yang kemudian disimpan pada sebuah char *fileName* dengan format *YYYY-mm-dd_HH:ii:ss*.    
* Membuat directory
```
      char path[60]="/home/erzajanitra/modul2/";
      strcat(path,fileName);
      
      char *argv[] = {"mkdir", "-p", path, NULL};
      func1("/bin/mkdir", argv);
```
   Membuat directory dengan *mkdir* dan nama file yang digunakan adalah *fileName*, sesuai path dimana directory tersebut diletakkan.
 
 ### 3b
 **Soal** : Setiap direktori yang sudah dibuat diisi dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap
gambar yang didownload akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.
* Fungsi void ``downloadft``
```
     time_t t=time(NULL);
      char fileName2[100];
      struct tm *tmp=localtime(&t);
      strftime(fileName2,sizeof(fileName2),"%Y-%m-%d_%H:%M:%S", tmp);
      
      //long long ts=time(NULL);
      long int size=(t%1000)+50;
      
      char d[50];
      strcpy(d,fn);
      strcat(d,"/");
      strcat(d,fileName2);

      char link[50]={"https://picsum.photos/"};
      char ps[50];
      sprintf(ps,"%ld",size);
      strcat(link,ps);
      
      //ILE *dst=fopen("get.txt","a");
      //fprintf(dst,"halo");
      //fclose(dst);

      char *foto[] = {"wget","-bq",link,"-O",d,NULL};
      execv("/usr/bin/wget",foto);
```
   Untuk mendownload 10 foto menggunakan *for loop* yang didalamnya memanggil fungsi ``downloadft`` dan menjalankan fungsi tersebut tiap 5 detik dengan *sleep(5)*. File nama foto menggunakan *timestamp* dengan cara seperti no **3a**. Detik Epoch Unix didapatkan dengan *time_t*. Destination path untuk foto disimpan pada *char d* dan link download foto disimpan pada *char link* yang di strcat dengan size foto tersebut.
   
 ### 3c
  **Soal** : Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang
terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan
shift/key yang kita tentukan. Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Karena Ranora orangnya perfeksionis dan rapi, dia ingin setelah file
tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.
* Penyelesaian no 3c menggunakan fungsi ``txtFile`` untuk membuat file *status.txt* dan mengenkripsi pesan didalamnya dengan Algoritma Caesar Cipher. Kemudian, membuat zip 10 file foto + *status.txt*
* Membuat file *status.txt*
```
    char file[50];
    strcpy(file,name);
    strcat(file,"/status.txt");
          
    //isi file status.txt
    char message[50],ch;
    strcat(message,"Download Success");
```
   File *status.txt* dibuat pada masing-masing folder foto, maka dari itu menggunakan *strcat* untuk menggabungkan *status.txt* pada path masing-masing directory. Kemudian, file txt tersebut berisi pesan *Download Success*.
* Enkripsi isi *status.txt* dengan Caesar Cipher
```
    FILE *fp;
    fp=fopen(file,"w");

    //caesar cipher
    for(int i=0;message[i]!='\0';++i){
      ch=message[i];
      if(ch>='a' && ch<='z'){
         ch=ch+5;
        if(ch>'z'){
           ch=ch-'z'+'a'-1;
        }
        message[i]=ch;
      }
      else if(ch>='A' && ch<='Z'){
         ch=ch+5;
         if(ch>'Z'){
            ch=ch-'Z'+'A'-1;
         }
         message[i]=ch;
        }
      fputc(ch,fp);
    }fclose(fp);
 ```
   File *status.txt* tersebut menggunakan mode write agar isi file tersebut bisa digantikan dengan hasil enkripsi pesan tersebut. Pesan yang telah dienkripsi disimpan pada file *status.txt* dengan nama file *fp*.
  * Zip file
  ```
    
    //zip file
    char zips[50];
    strcpy(zips,name);
    strcat(zips,".zip");
    char *argv[]={"zip","-rmq",zips,name,NULL};
    execv("/usr/bin/zip",argv);
```
   Setelah file *status.txt* selesai dienkripsi, 10 foto yang telah didownload dan file *status.txt* dijadikan satu dalam sebuah file zip. Nama file zip tersebut adalah nama directory.   

### 3d
**Soal** : Untuk mempermudah pengendalian program, pembimbing magang Ranora ingin program tersebut akan men-generate sebuah program “Killer” yang executable, dimana
program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankan. Karena Ranora menyukai
sesuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat nantinya harus merupakan program bash.
* Penyelesaian no 3d menggunakan fungsi ``fileKl`` untuk membuat script *killer.sh* 
* Membuat file *killer.sh* 
```
    void fileKl(char *argv[], int pid){
        //3d buat killer.sh
        FILE *kill=fopen("killer.sh","w");
        fprintf(kill,"#/bin/bash\n");
```
   Karena tidak diperbolehkan menggunakan system(), membuat file *killer.sh* dengan ``FILE *kill``. Kemudian file tersebut diisi dengan ``#/bin/bash`` karena merupakan sebuah shell script.
 
### 3e
**Soal** : Untuk mengaktifkan mode pertama, program harus dijalankan dengan argumen -z, dan Ketika dijalankan dalam mode pertama, program
utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan
argumen -x, dan Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai
(Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).
* Penyelesaian no 3e juga menggunakan fungsi ``fileKl`` setelah membuat script *killer.sh*
* Dua mode dengan argumen -z dan -x
``` 
         // arg -z menghentikan semua operasi
         if(strcmp(argv[1],"-z")==0){
          fprintf(kill,"killall -9 soal3\n");
          }
         //arg -x kill proses utama-->pid
         else if(strcmp(argv[1], "-x")==0){
          fprintf(kill,"kill -9 %d\n", pid);
        }

        //delete dir setelah selesai di zip
         fprintf(kill,"rm killer.sh\n");
         fclose(kill);
 }
```
   Menggunakan *if-else condition* dan *strcmp* untuk pilihan mode yang diinginkan. Apabila **-z** akan memasukkan string ``killall -9 soal3`` untuk mematikan seluruh proses. Sementara itu, untuk **-x** akan memasukkan string ``kill -9 %d`` dimana *%d* adalah pid untuk mematikan proses utama. Sehingga apabila **-x** dijalankan, program akan menyelesaikan proses terakhir, baru kemudian berhenti.
   
### Kendala yang dialami
1. Pada saat mengerjakan no 3b, kami tidak bisa mendownload foto dari link tersebut. Solusinya, kami harus menggunakan *usr* pada *execv(/usr/bin/wget*) ketika mendownload foto.
2. Pada saat mengerjakan no 3e, kami tidak bisa menjalankan argumen **-x**. Seharusnya program akan menyelesaikan proses terakhir, baru kemudian berhenti. Tetapi, proses tetap berjalan. Permasalahan tersebut disebabkan kami menggunakan ``func1`` untuk mengezip file. Karena pada ``func1`` akan melakukan fork lagi, sehingga proses akan terus berjalan. Solusinya, kami menggunakan ``execv`` untuk mengezip file.

### Screenshot Error
* Error penulisan syntax *fputs* yang seharusnya *fput*
![image](https://user-images.githubusercontent.com/75319371/115953599-4626b880-a50e-11eb-91a9-380057c62854.png)

### Hasil ketika berhasil menjalankan semua proses
* File zip yang berisi 10 foto dan status.txt <br />
![image](https://user-images.githubusercontent.com/75319371/115657308-d921f000-a360-11eb-9615-d0fb3cd4040d.png)
* Isi *status.txt*, berisi pesan *Download Success* yang telah dienkripsi <br />
![image](https://user-images.githubusercontent.com/75319371/115657386-f5be2800-a360-11eb-8559-7f9dffadfc7c.png)


