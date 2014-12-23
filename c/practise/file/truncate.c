#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

#define MAX_RESERVE_SIZE 32

int main(int argc, char * argv[])
{
	unsigned int reserv_size;
	unsigned int i;
	unsigned int rest;
	int fd;
	char buf[MAX_RESERVE_SIZE] = {0};
	off_t pos;

	if (3 != argc)
	{
		reserv_size = MAX_RESERVE_SIZE;
		rest = 0;
	}
	else
	{
		reserv_size = atoi(argv[1]);
		rest = atoi(argv[2]);
	}

	if (-1 == truncate("test.txt", reserv_size))
	{
		perror("Failed to truncate.");
		exit(1);
	}

	for (i = 0; i < rest; ++i)
	{
		buf[i] = 'a';
	}

	fd = open("test.txt", O_RDWR | O_APPEND);
	if (-1 == fd)
	{
		perror("Failed to open.");
		exit(1);
	}

	pos = lseek(fd, 0, SEEK_CUR);
	if (-1 == pos)
	{
		perror("Failed to seek.");
		close(fd);
		exit(1);
	}

	printf("current pos: %d\n", pos);

	if (-1 == ftruncate(fd, 20))
	{
		perror("Failed to ftruncate.");
		close(fd);
		exit(1);
	}

	printf("buf: %s\n", buf);
	if (-1 == write(fd, buf, rest))
	{
		perror("Failed to write.");
		exit(1);
	}

	close(fd);

	return 0;
}


