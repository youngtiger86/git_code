#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

int main()
{
	int fd;
	struct stat stat_buf;
	char * buf;

	if (-1 == stat("test.txt", &stat_buf))
	{
		perror("Failed to stat.\n");
		exit(1);
	}

	fd = open("test.txt", O_WRONLY);
	if (-1 == fd)
	{
		perror("Failed to open.\n");
		exit(1);
	}

	buf = (char *)mmap(NULL, stat_buf.st_size, PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (MAP_FAILED == buf)
	{
		perror("Failed to mmap.\n");
		exit(1);
	}

	strcpy(buf, "China Beijing");

	if (-1 == munmap(buf, stat_buf.st_size))
	{
		perror("Faile dto munmap.\n");
		exit(1);
	}

	close(fd);

	return 0;
}

