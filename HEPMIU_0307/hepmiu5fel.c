#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include < sys/wait.h>
#include <unistd.h>

int main(void){
    pid_t pid, status;

    if((pid = fork()) < 0){
        perror("Error in the fork!");
        exit(7);
    }
    else if(pid == 0){
       abort();
        if(wait(&status) != pid){
         perror("Error at the wait!");  
        }

    }
    if(WIFEXITED(status)){
        printf("Succesful!");

    }
    exit(0);
}
