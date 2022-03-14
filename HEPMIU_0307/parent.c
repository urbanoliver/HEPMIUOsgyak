#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include < sys/wait.h>
pid_t wait(int *wstatus);
pid_t waitpid(pid_t pid, int *wstatus, int options);


int main(){
    pid_t pid;

    if((pid = fork()) < 0 ){
        perror("fork error");
    }
    else if(pid == 0){
            if(execl("./child", "child",(char *)NUll) < 0)
                perror("execl error");

    }
    if(waitpid(pid, NULL , 0) < 0 )
    {   perror("wait error");

        }

    exit(0);
}

