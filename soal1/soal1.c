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

 char *files[] = {"Musyik","Pyoto","Fylm"};
 char *oldfiles[] = {"Musik_for_Stevany","Foto_for_Stevany","Film_for_Stevany"};
 char *folders[] = {"MUSIK","FOTO","FILM"};
 char *links[] = {"drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download",
"drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
"drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};


void download(char *link, char *filename){

	pid_t child_id;
	int status;
	child_id = fork();

 	if(child_id < 0){
		exit(EXIT_FAILURE);
 	}

	if(child_id == 0){//ini child
		char *download[] = {"wget","-q",link,"-O",filename,NULL};
		execv("/bin/wget",download);
	}else{//ini parent
		wait(&status); return;
	}

}

void unzip(char *filename){

	pid_t child_id;
	int status;
	child_id = fork();

 	if(child_id < 0){
		exit(EXIT_FAILURE);
 	}

	if(child_id == 0){//ini child
		char *unzip[] = {"unzip","-q",filename,NULL};
		execv("/bin/unzip",unzip);
	}else{//ini parent
		wait(&status); return;
	}

}


void makedir(char *newfile){

	pid_t child_id;
	int status;
	child_id = fork();

 	if(child_id < 0){
		exit(EXIT_FAILURE);
 	}

	if(child_id == 0){//ini child
		char *mkdir[] = {"mkdir",newfile,NULL};
		execv("/bin/mkdir",mkdir);
	}else{//ini parent
		wait(&status);return;
		//wait(&status);
	}
}

void move(char *oldfile, char *newfile){

	pid_t child_id;
	int status;
	child_id = fork();

	char current[1000] = "/home/tsania/Documents/sisopshift2/";
	strcat(current,oldfile);

 	if(child_id < 0){
		exit(EXIT_FAILURE);
 	}

	if(child_id == 0){//ini child
		strcat(current,"/.");
		char *move[] = {"cp","-R",current,newfile,NULL};
		execv("/bin/cp",move);

	}else{//ini parent
		wait(&status);return;
	}
}


void re_move(char *oldfile, char *newfile){

	pid_t child_id;
	int status;
	child_id = fork();

	char current[1000] = "/home/tsania/Documents/sisopshift2/";
	strcat(current,oldfile);

 	if(child_id < 0){
		exit(EXIT_FAILURE);
 	}

	if(child_id == 0){//ini child
		strcat(current,"/");
		char *remove[] = {"rm","-rf",current,NULL};
		execv("/bin/rm",remove);
	}else{//ini parent
		wait(&status);return;
		//while((wait(&status))>0);
	}
}

void zipfile(char file1[], char file2[], char file3[]){

	pid_t child_id;
	int status;
	child_id = fork();

 	if(child_id < 0){
		exit(EXIT_FAILURE);
 	}

	if(child_id == 0){//ini child
		char *zip[] = {"zip","-rm","Lopyu_Stevany",file1,file2,file3,NULL};
		execv("/bin/zip",zip);
	}else{//ini parent
		wait(&status);return;
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
		
		for(i=0;i<3;i++){
			makedir(files[i]);
		}
		for(i=0;i<3;i++){
			download(links[i],oldfiles[i]);
		}
		for(i=0;i<3;i++){
			unzip(oldfiles[i]);
		}
		for(i=0;i<3;i++){
			move(folders[i],files[i]);
		}
			
	}else{
		wait(&status); return;
	}
}


void zipfolders(){
	int i;
	pid_t child_id;
	int status;
	child_id = fork();

 	if(child_id < 0){
		exit(EXIT_FAILURE);
 	}

	if(child_id == 0){
		zipfile("Musyik","Pyoto","Fylm");
		sleep(10);

		for(i=0;i<3;i++){
			re_move(folders[i],files[i]);
		}
	}else{
		wait(&status);return;
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
	printf("PID of Child Process %d\n", pid);
	exit(EXIT_SUCCESS);
}


umask(0);

sid = setsid();

if (sid < 0){
	printf("SID Fail\n");
	exit(EXIT_FAILURE);
}

char address[1000];
getcwd(address,sizeof(address));
strcat(address,"/");

if((chdir(address))<0){
	exit(EXIT_FAILURE);
}

close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);

while(1){
 time_t t = time(NULL);
 char b_day[100];
 struct tm *tmp = localtime(&t);
 strftime(b_day,sizeof(b_day),"%Y-%m-%d %H:%M:%S",tmp);
 char target1[]="2021-04-09 16:21:59";
 char target2[]="20210-04-09 22:21:59";


	pid_t child, child2;
	child = fork();

if (child < 0){
	printf("PID Fail\n");
	exit(EXIT_FAILURE);
}

if (child == 0){

	if(strcmp(b_day,target1)==0){
//printf("Berhasil Target 1\n");
		do_something();
		sleep(40);
	}

	if(strcmp(b_day,target2)==0){
//printf("Berhasil Target 2\n");
		zipfolders();
		sleep(45);
	}

}else{
		sleep(40);
		continue;

}

}

return 0;
}

