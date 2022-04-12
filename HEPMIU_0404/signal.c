#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

void kezelo(){
    printf("Signal kezelese: %d\n", i);
    return;
}
int main(void){

    printf("PID = %d\n", getpid());
    printf("Signal kezelo atvetele: %d\n", signal(SIGTERM,&kezelo));
    while(l){
        printf("lepes \n");
        sleep(3);

    }

}
