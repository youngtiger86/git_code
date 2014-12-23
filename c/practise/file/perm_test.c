#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char * argv[])
{
	struct stat stat_buf;

	if ((1 != argc) && (NULL == argv[1]))
	{
		perror("argument wrong.\n");
		exit(1);
	}

	if (-1 == stat(argv[1], &stat_buf))
	{
		perror("Fail to stat.\n");
		exit(1);
	}

	if (0 == (stat_buf.st_mode & S_IRGRP))
	{
		printf("Group user has no read permission.\n");
	}
	else
	{
		printf("Group user has read permission.\n");
	}

	return 0;
}

