#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main()
{
	int fd;

	fd = open("test.txt", O_WRONLY | O_TRUNC);
	if (-1 == fd)
	{
		perror("Failed to open.");
		exit(1);
	}

	if (-1 == write(fd, "Linux ok", strlen("Linux ok")))
	{
		perror("Failed to write.");
		close(fd);
		exit(1);
	}

	close(fd);

	return 0;
}

