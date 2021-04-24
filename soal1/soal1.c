#include <wait.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>


void move(char *oldfile, char *newfile){

	pid_t child_id;
	int status;
	child_id = fork();

	if(child_id < 0){
		exit(EXIT_FAILURE);
 	}

	if(child_id == 0){//ini child
		
		char *moves[] = {"mv",oldfile,newfile,NULL};
		execv("/usr/bin/mv",moves);

	}else{//ini parent
		while((wait(&status))>0);
	}
}

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

void downloadft(){

	pid_t child_id;
	int status;
	child_id = fork();

 	if(child_id < 0){
		exit(EXIT_FAILURE);
 	}

	if(child_id == 0){//ini child
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
		}else{//ini parent
			while((wait(&status1))>0);
			sleep(5);
			char *unzip[] = {"unzip","/home/tsania/Documents/sisopshift2/Foto_for_Stevany.zip",NULL};
			execv("/usr/bin/unzip",unzip);
		}
	}
	else{
		while((waitpid(child_id,&status,0))>0);
		re_move("FOTO","Pyoto");
	}

}

void downloadms(){

	pid_t child_id;
	int status;
	child_id = fork();
	//char links[100] = {"drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download"};

 	if(child_id < 0){
		exit(EXIT_FAILURE);
 	}

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
		}else{//ini parent
			while((wait(&status1))>0);
			sleep(5);
			char *unzip[] = {"unzip","/home/tsania/Documents/sisopshift2/Musik_for_Stevany.zip",NULL};
			execv("/usr/bin/unzip",unzip);
		}
	}
	else{
		while((waitpid(child_id,&status,0))>0);
		re_move("MUSIK","Musyik");
	}

}

void downloadfi(){

	pid_t child_id;
	int status;
	child_id = fork();
	//char link[100]={"drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};
 	if(child_id < 0){
		exit(EXIT_FAILURE);
 	}

	if(child_id == 0){//ini child
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
		}else{//ini parent
			while((wait(&status1))>0);
			sleep(5);
			char *unzip[] = {"unzip","/home/tsania/Documents/sisopshift2/Film_for_Stevany.zip",NULL};
			execv("/usr/bin/unzip",unzip);
		}
	}
	else{
		while((waitpid(child_id,&status,0))>0);
		re_move("FILM","Fylm");
	}

}

void do_something(){
	int i;
	pid_t child_id;
	int status;
	child_id = fork();

 	if(child_id < 0){
		exit(EXIT_FAILURE);
 	}

	if(child_id == 0){
		pid_t child1;
		int status1;
		child1=fork();

		if(child1 < 0){
			exit(EXIT_FAILURE);
 		}
		if(child1 == 0){
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
			else{
				while(wait((&status2))>0);
				downloadft();
				_exit(1);
			}
		}
		else{
			while(wait((&status1))>0);
			downloadfi();
			_exit(1);
		}
		
	}else{
		while(wait((&status))>0);
		downloadms();
		_exit(1);
	}
}


int main(){

	pid_t pid,sid;
	pid = fork();

	if (pid < 0){
		printf("PID Fail\n");
		exit(EXIT_FAILURE);
	}

	if (pid > 0){
		//printf("PID of Child Process %d\n", pid);
		exit(EXIT_SUCCESS);
	}


	umask(0);

	sid = setsid();

	if (sid < 0){
		//printf("SID Fail\n");
		exit(EXIT_FAILURE);
	}


	if((chdir("/home/tsania/Documents/sisopshift2/"))<0){
		exit(EXIT_FAILURE);
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

while(1){
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

	else if(strcmp(b_day,target2)==0){
	printf("Berhasil Target 2\n");
		char *zip[] = {"zip","-rmq","Lopyu_Stevany","Pyoto","Fylm","Musyik","FILM","FOTO","MUSIK",NULL};
		func1("/usr/bin/zip",zip);
	}

}
sleep(1);

return 0;
}
