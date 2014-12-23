#include <stdio.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
	int fd;

	if (2 != argc || NULL == argv[1])	
	{
		perror("One parameter should be specified.\n");
		return 1;
	}

	if (-1 == (fd = open(argv[1], O_RDWR | O_CREAT, 700)))
	{
		perror("Open file failed.\n");
		return 1;
	}

	printf("Open file %s succeed.\n", argv[1]);

	return 0;
}
