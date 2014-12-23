#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	int fd;

	fd = open("test.txt", O_WRONLY);
	if (-1 == fd)
	{
		perror("Failed to open.");
		exit(1);
	}

	if (-1 == ftruncate(fd, 0))
	{
		perror("Failed to ftruncate.");
		close(fd);
		exit(1);
	}

	close(fd);

	return 0;
}
