#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	int fd, ret;
	char buf[32];

	buf[0]=0;


        ret=mkfifo("fifo",00666);
	if (ret == -1) {
	    perror("mkfifo()");
	    exit(-1);
	}

	fd=open("fifo",O_RDWR);
	if (fd == -1) {
	    perror("open() error!");
	    exit(-1);
	}

	strcpy(buf,"i put this in the fifo\0");
	printf("write in the fifo: %s:%d\n",buf,strlen(buf));
	write(fd,buf,strlen(buf));

	ret=read(fd,buf,32);
	printf("read() read %d byte, these are: %s\n",ret,buf);

	close(fd);

	unlink("fifo");
}
