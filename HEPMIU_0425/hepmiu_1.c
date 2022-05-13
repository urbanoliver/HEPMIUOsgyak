#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define KEY 126K

union semun {
    int val;                 
    struct semid_ds *buf;    
    unsigned short *array;   
    struct seminfo *__buf; 
};

void main() {
    union semun arg;
    
    int semID = semget(KEY, 0, 0);
    if (errno == ENOENT) 
    {
        semID = semget(KEY, 1, IPC_CREAT | 0666);
        printf("Szam: ");
        scanf("%d" ,&(arg.val));        
    } 
    else 
    {
        arg.val = 1;
    }
    
    semctl(semID, 0, SETVAL, arg);

    printf("A szemafor erteke (1) : %d\n", semctl(semID, 0, GETVAL));    
    
}
