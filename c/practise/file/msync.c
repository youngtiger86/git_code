#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

int main()
{
	int i;
	int fd;
	char * buf;
	char * p;
	int len;
	struct stat stat_buf;

	if (-1 == stat("test.txt", &stat_buf))
	{
		perror("Fail to stat.\n");
		exit(1);
	}

	fd = open("test.txt", O_RDWR);
	if (-1 == fd)
	{
		perror("Fail to open.\n");
		exit(1);
	}

	buf = (char *)mmap(NULL, stat_buf.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
	if (MAP_FAILED == buf)
	{
		perror("Fail to mmap.\n");
		close(fd);
		exit(1);
	}

	p = buf;
	for (i = 0; i < 10; ++i)
	{
		sleep(3);
		printf("This is a new line.\n");
		len = strlen("This is a new line.\n"); 
		memcpy(p, "This is a new line.\n", len); 
		if (-1 == msync(buf, stat_buf.st_size, MS_SYNC))
		{
			perror("Fail to msync.\n");
			exit(1);
		}

		p += len;
	}

	if (-1 == munmap(buf, stat_buf.st_size))
	{
		perror("Fail to munmap.\n");
		exit(1);
	}

	close(fd);

	return 0;
}
