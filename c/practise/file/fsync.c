#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	int fd;
	int wr_times;

	if (-1 == (fd = open("test.txt", O_RDWR | O_CREAT)))
	{
		perror("Failed to open file test.txt.\n");
		exit(1);
	}

	wr_times = 0;
	while (wr_times < 1000)
	{
		if (-1 == write(fd, "hello\n", strlen("hello\n")))
		{
			perror("Fail to write.\n");
			exit(1);
		}

		printf("Written!\n");

		if (-1 == fdatasync(fd))
		{
			perror("Fail to fsync");
			exit(1);
		}

		wr_times++;
		//sleep(5);
	}

	close(fd);

	return 0;	
}
