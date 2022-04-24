#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY 4L
#define PERM 00666

int main()
{
	int file, ret;
	char buf[32];

	int 	id; 		
struct sembuf up[1]  =  {0,  1, SEM_UNDO};
struct sembuf down[1] = {0, -1, SEM_UNDO};

	file=open("pr.txt",O_CREAT);
	file=open("pr.txt",O_RDWR);
	if (file == 1) {
	    perror("open() hiba!");
	    exit(-1);
	}

	
	

	ret=lseek(file,0,SEEK_SET); 
	strcpy(buf,"valami szoveg");
	if ((id = semget(KEY, 1, 0)) < 0) {
		if ((id = semget(KEY, 1, PERM | IPC_CREAT)) < 0) {
		 	perror(" A szemafor nem nyitható meg. ");
			exit(-1);
		}
	}
	else    {
		perror(" Már létezik a szemafor. ");
		exit(0);
	}

	if (semctl(id, 0, SETVAL, 1) < 0) {
		perror(" Nem lehetett inicializálni. ");
	} else {
		puts(" Kész és inicializált a szemafor. ");
	}
	
	puts(" Itt fut a nem kritikus szakasz. ");

	semop(id, down, 1);   
	puts("    Itt fut a kritikus szakasz. ");	
	
	
	ret=write(file,buf,strlen(buf)); 
	printf("write() mondja: %d\n",ret);
	semop(id, up, 1);   

	puts(" Itt ismét nem kritikus szakasz fut. ");
	if (semctl(id, 0, IPC_RMID, 0) < 0) {
		perror(" Nem sikerült törölni.");
		exit(-1);
	}

	puts(" A szemafort megszüntettük. \n");

	close(file);
}
