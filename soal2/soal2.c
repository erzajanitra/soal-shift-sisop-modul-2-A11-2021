#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include<dirent.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>

//fungsi untuk mempersingkat fork
void func1(char command[],char *arg[]){
  
  int status;
  pid_t pid;
  pid=fork();
  if(pid==0){
    printf("%s",command);
    execv(command,arg);
  }
  else{
     ((wait(&status))>0);
   }
}

//buat ngehapus string index-4
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

int main() {
  pid_t pid1;
  int status;

  pid1 = fork();
   
  if(pid1<0){
    exit(EXIT_FAILURE);
    //child ga berhasil dibuat
  }
  if(pid1==0){
    //child berhasil dibuat
    //2a
    //buat folder baru
    char *array[]={"mkdir","-p","/home/erzajanitra/modul2/petshop",NULL};
   func1("/bin/mkdir",array);

    //while((wait(NULL))>0);
    //unzip pets.zip lalu di extract ke folder petshop
    char *array2[]={"unzip","-q","pets.zip","-d","petshop",NULL};
    execv("/usr/bin/unzip",array2);
  }

    //remove file yg ga penting
    while((wait(NULL))>0);
    printf("coba\n");

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

       char *cutss=cut(dent->d_name); //menghilangkan.jpg
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
            //nama file setelah dipisah ke masing2 folder
              while((wait(NULL))>0);
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
            
            
          //keterangan.txt di masing2 folder pets
          char file[50];
          strcpy(file,"/home/erzajanitra/modul2/petshop/");
          strcat(file,pet);
          strcat(file,"/keterangan.txt");
          
           //isi file keterangan.txt
          char ch[50];
          strcat(ch,"nama : ");
          strcat(ch,pName);
          strcat(ch,"\numur: ");
          strcat(ch,pAge);
          strcat(ch,"tahun\n\n");
          
          //buat keterangan.txt
          FILE *fp;
          fp=fopen(file,"a");
          fputs(ch,fp);

          fclose(fp);
        }

        //remove setelah pindah ke folder masing2
        char hapus[60]="/home/erzajanitra/modul2/petshop/";
        strcat(hapus,dent->d_name);
        char *args[]={"rm",hapus,NULL};
        execv("/bin/rm",args);

                
      }
      closedir(dir);
    }
   
  return 0;
}

