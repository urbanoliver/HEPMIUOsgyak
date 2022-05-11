#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd, ret;
	char buf[32];

	


	
	fd=open("pr.txt",O_RDWR);
	if (fd == -1) {
	    perror("open() hiba!");
	    exit(-1);
	}
	ret=lseek(fd,0,SEEK_SET);
	ret=read(fd,buf,32); 
	printf("read() olvasott %d byteot, ami a kovetkezo: %s\n",ret,buf);
	close(fd);
}
