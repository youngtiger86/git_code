#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void check_file_type_by_mode(mode_t mode)
{
	if (S_ISREG(mode))
	{
		printf("Regular file.\n");
	}
	else if (S_ISDIR(mode))
	{
		printf("Directory file.\n");
	}
	else if (S_ISBLK(mode))
	{
		printf("Block file.\n");
	}
	else if (S_ISCHR(mode))
	{
		printf("Character file.\n");
	}
	else if (S_ISFIFO(mode))
	{
		printf("FIFO file.\n");
	}
	else if (S_ISLNK(mode))
	{
		printf("Link file.\n");
	}
	else if (S_ISSOCK(mode))
	{
		printf("Socket file.\n");
	}
	else
	{
		printf("Invalid mode.\n");
	}
}

int main(int argc, char * argv[])
{
	struct stat stat_buf;

	if ((1 != argc) && (NULL == argv[1]))
	{
		printf("Argument wong.\n");
		exit(1);
	}

	if (-1 == stat(argv[1], &stat_buf))
	{
		printf("Fail to stat.\n");
		exit(1);
	}

	check_file_type_by_mode(stat_buf.st_mode);	

	return 0;
}
