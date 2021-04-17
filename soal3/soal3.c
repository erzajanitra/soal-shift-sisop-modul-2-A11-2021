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
      
      FILE *dst=fopen("get.txt","a");
      fprintf(dst,"halo");
      fclose(dst);

      char *foto[] = {"wget","-b",link,"-O",d,NULL};
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

int main() {
  pid_t pid,pid2, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
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

     //while((wait(NULL))>0);
    //3b download 10 foto(/5 s)-> save di directory
    //nama file foto sesuai timestamp
    //ukuran (n%1000)+50 px 
      pid_t pid3;
      int status3;
      if((pid3=fork())==0){
        for(int i=0;i<10;i++){
          
          downloadft(fileName);
          sleep(5);
        }
      }
      else{
        while((wait(&status3))>0);
        
      }
      
    }
        
    sleep(40);
  }
}