#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void InterruptHandler(int sig);
void QuitHandler(int sig);
unsigned int Interrupts = 0;


int main(void){

    if(signal(SIGINT,InterruptHandler) == SIG_ERR){
        printf("Nem sikerult handlert beallitani a \"SIGINT\" jelre\n");
        return 0;

    }
    if(signal(SIGQUIT,QuitHandler) == SIG_ERR){
        printf("Nem sikerult handlert beallitani a \"SIGQUIT\" jelre\n");
        return 0;

    }
    while(Interrupts < 2){
        printf("Varakozas a jelre.... \n");
        sleep(1);
    }
    printf("Megerkezett a masodik \"SIGINT\" jel!");
    return 0;


}
void InterruptHandler(int sig){
    printf("SIGINT signal: %d\n", sig);
    Interrupts++;
}
void QuitHandler(int sig){
    printf("SIGQUIT signal: %d\n", sig);

}
