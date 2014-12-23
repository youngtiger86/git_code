#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	int fd;
	int flag;
	char * p = "1st linux";
	char * q = "2nd linux";

	fd = open("test.txt", O_WRONLY);
	if (-1 == fd)
	{
		perror("Failed to open.\n");
		exit(1);
	}

	if (-1 == write(fd, p, strlen(p)))
	{
		perror("Failed to write.\n");
		exit(1);
	}
	
	flag = fcntl(fd, F_GETFL, 0);
	if (-1 == flag)
	{
		perror("Failed to fnctl.\n");
		exit(1);
	}

	flag |= O_APPEND;

	if (-1 == fcntl(fd, F_SETFL, flag))
	{
		perror("Failed to fnctl.\n");
		exit(1);
	}

	if (-1 == write(fd, q, strlen(q)))
	{
		perror("Failed to write.\n");
		exit(1);
	}

	close(fd);

	return 0;
}
