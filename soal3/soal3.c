#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include<time.h>
#include<wait.h>

//ini buat 3b
void downloadft(char *fn){
  int status;
  pid_t pid;     
  pid = fork();   

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }
  if(pid==0){
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
  }
   else{
     while((wait(&status))>0);
     //sleep(5);
   }
}
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
     //return;
   }
}

//ini 3c
void txtFile(char *name){
    char file[50];
    strcpy(file,name);
    strcat(file,"/status.txt");
          
    //isi file status.txt
    char message[50],ch;
    strcat(message,"Download Success");
          
    //buat keterangan.txt
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
    }
    
    fclose(fp);
    //zip file
    char zips[50];
    strcpy(zips,name);
    strcat(zips,".zip");
    char *argv[]={"zip","-rmq",zips,name,NULL};
    execv("/usr/bin/zip",argv);
}

//ini 3d-e
void fileKl(char *argv[], int pid){
    //3d buat killer.sh
    FILE *kill=fopen("killer.sh","w");
    fprintf(kill,"#/bin/bash\n");

    //3e 
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

int main(int argc, char** argv) {
  pid_t pid,pid2, sid;        // Variabel untuk menyimpan PID
  pid = fork();     // Menyimpan PID dari Child Process
  if (pid < 0) {
      exit(EXIT_FAILURE);
    }
  if (pid > 0) {
      exit(EXIT_SUCCESS);
    }
  umask(0);
  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }
  if ((chdir("/home/erzajanitra/modul2/")) < 0) {
    exit(EXIT_FAILURE);
  }
  //untuk menjalankan argumen -z dan -x
  fileKl(argv,(int)getpid());

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  
  while (1) {
    // Tulis program kalian di sini
    time_t t=time(NULL);
    char fileName[100];
    struct tm *tmp=localtime(&t);
    strftime(fileName,sizeof(fileName),"%Y-%m-%d_%H:%M:%S", tmp);
    printf("coba");
    pid2=fork();
     if (pid2 < 0) {
      exit(EXIT_FAILURE);
    }

           
    if (pid2== 0) {
      //nama folder dengan format date-time
      char path[60]="/home/erzajanitra/modul2/";
      strcat(path,fileName);
      
      //3a direktori dengan nama file timestamp
      char *argv[] = {"mkdir", "-p", path, NULL};
      func1("/bin/mkdir", argv);

    
      for(int i=0;i<10;i++){
        //3b 
        downloadft(fileName);
          sleep(5);
      }
        //3c buat file status.txt -> caesar cipher shift 5
        // zip, abis itu dir dihapus
        //status.txt di masing2 folder pets
         txtFile(fileName);

      }
      
        sleep(40);    
    }
        
    
  }