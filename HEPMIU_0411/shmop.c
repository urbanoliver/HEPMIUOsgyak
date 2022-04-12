#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define KEY 123456L


main()
{
	int hallgato;		
	key_t key;		
	int size=512;		
	int shmflg;		
	struct vmi {
		int  hossz;
		char szoveg[512-sizeof(int)];
	} *segm;		
	
	key = KEY;
	shmflg = 0;
	if ((hallgato=shmget( key, size, shmflg)) < 0) {
	    perror("\n Az shmget system-call sikertelen!");
	    exit(-1);
	}


	shmflg = 00666 | SHM_RND;
	segm = (struct vmi *)shmat(hallgato, NULL, shmflg);
	if (segm == (void *)-1) {
		perror(" Sikertelen attach");
		exit (-1);
	}


	if (strlen(segm->szoveg) > 0) 
		printf("\n Regi szoveg: %s (%d hosszon)",segm->szoveg,segm->hossz);
 
	printf("\n Uj szoveget kerek!\n");
	gets(segm->szoveg);
	printf("\n Az uj szoveg: %s\n",segm->szoveg);
	segm->hossz=strlen(segm->szoveg);
		

	shmdt(segm);

	exit(0);

}
