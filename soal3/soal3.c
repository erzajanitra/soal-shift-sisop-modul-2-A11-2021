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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  ;
  while (1) {
    // Tulis program kalian di sini
    
    pid2=fork();
     if (pid2 < 0) {
      exit(EXIT_FAILURE);
    }

      time_t t=time(NULL);
      char fileName[100];
      struct tm *tmp=localtime(&t);
      strftime(fileName,sizeof(fileName),"%Y-%m-%d_%H:%M:%S", tmp);
      
    if (pid2== 0) {
      //nama folder dengan format date-time
      char path[60]="/home/erzajanitra/modul2/";
      strcat(path,fileName);
      //3a direktori dengan nama file timestamp
      char *argv[] = {"mkdir", "-p", path, NULL};
      func1("/bin/mkdir", argv);

      sleep(10);
    }
    
    while((wait(NULL))>0);
    //3b download 10 foto(/5 s)-> save di directory
    //nama file foto sesuai timestamp
    //ukuran (n%1000)+50 px 
    char dir[60]="/home/erzajanitra/modul2/";
    strcat(dir,fileName);
    for(int i=0;i<10;i++){
      int size=(t%1000)+50;
      
      //char link[50]="https://picsum.photos/";
      char d[50];
      sprintf(d,"https://picsum.photos/%d",size);

      char *foto[] = {"wget","-bq",d,"-O",dir,NULL};
      func1("/bin/wget",foto);
      sleep(5);
    }
    
  }
}