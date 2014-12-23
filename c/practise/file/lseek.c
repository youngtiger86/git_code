#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_BUF_SIZE 1024
int main()
{
	int fd;
	off_t pos;
	char buf[MAX_BUF_SIZE];

	fd = open("test.txt", O_RDONLY);
	if (-1 == fd)
	{
		perror("Fail to open.");
		exit(1);
	}

	pos = lseek(fd, 0, SEEK_CUR);
	if (-1 == pos)
	{
		perror("Fail to lseek.");
		exit(1);
	}
	printf("Before read, the position is: %d.\n", (int)pos);

	if (-1 == read(fd, buf, 5))
	{
		perror("Fail to read.");
		close(fd);
		exit(1);
	}

	pos = lseek(fd, 0, SEEK_CUR);
	if (-1 == pos)
	{
		perror("Fail to lseek.");
		exit(1);
	}

	printf("After read, the position is: %d.\n", (int)pos);

	pos = lseek(fd, 4, SEEK_SET);
	if (-1 == pos)
	{
		perror("Fail to lseek.");
		exit(1);
	}

	memset(buf, 0, MAX_BUF_SIZE);
	if (-1 == read(fd, buf, 5))
	{
		perror("Fail to read.");
		exit(1);
	}

	printf("From the 4th position of the file, the content is: %s.\n", buf);

	close(fd);

	return 0;
}

