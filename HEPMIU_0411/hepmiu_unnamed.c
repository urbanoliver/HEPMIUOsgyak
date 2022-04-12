#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
     int pipefd[2];
     pid_t cpid;
     char buf;
     char szoveg[32];
     int ret;

     if (pipe(pipefd) == -1) {
	   perror("pipe");
	   exit(-1);
     }

     printf("%d: fd1: %d, fd2: %d\n",getpid(),pipefd[0],pipefd[1]);

     cpid = fork();
     if (cpid == -1) {
	   perror("fork");
	   exit(-1);
     }

     if (cpid == 0) {
	   printf("%d: i'm a children\n",getpid());
	   close(pipefd[1]);

	   printf("%d: what's int the pipe\n%d: ",getpid(),getpid());
	   while (read(pipefd[0], &buf, 1) > 0) {
		 printf("%c",buf);
	   }
	   printf("\n%d:the pipe's other side is closed\n",getpid());

	   close(pipefd[0]);

   	   exit(0);

     } else {
	   printf("%d: i'm the parent\n",getpid());

   	   close(pipefd[0]);

	   strcpy(szoveg,"this is a text\0");
	   printf("%d: i send the text %s:%d\n",getpid(),szoveg,strlen(szoveg));

	   write(pipefd[1], szoveg, strlen(szoveg));

	   close(pipefd[1]);

	   wait(NULL);

	   exit(0);
     }
}
