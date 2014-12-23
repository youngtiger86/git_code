#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_BUF_SIZE 1024

int main(int argc, char * argv[])
{
	int src_fd;
	int dest_fd;
	int rd_len;
	int wr_len;
	char buf[MAX_BUF_SIZE];

	if (3 != argc)
	{
		perror("Argument number is wrong.");
		exit(1);
	}

	if ((NULL == argv[1]) || (NULL == argv[2]))
	{
		perror("Argument number is wrong.");
		exit(1);
	}

	if (-1 == (src_fd = open(argv[2], O_RDONLY)))
	{
		perror("Failed to open source file.");
		exit(1);
	}

	if (-1 == (dest_fd = open(argv[1], O_WRONLY | O_CREAT)))
	{
		perror("Failed to open destination file.");
		exit(1);
	}

	while ((rd_len = read(src_fd, buf, MAX_BUF_SIZE)) > 0)
	{
		if (-1 == (wr_len = write(dest_fd, buf, rd_len)))
		{
			perror("Write destination file failed.");
			break;
		}
	}

	close(src_fd);
	close(dest_fd);

	if (0 == rd_len)
	{
		printf("Copy file %s to %s successfully.\n", argv[2], argv[1]);
		return 0;
	}
	else
	{
		if (-1 == remove(argv[1]))
		{
			perror("Failed to remove destination file when copy failed.\n");
			return 1;
		}	
	}
}

