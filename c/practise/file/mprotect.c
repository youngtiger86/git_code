#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>

void sigbus_handler(int signo)
{
	printf("Tom said: permission denied\n");	
}

void sigtrap_handler(int signo)
{
}

int main()
{
	int fd;
	char * buf;
	struct stat stat_buf;

	if (SIG_ERR == signal(SIGSEGV, sigbus_handler))
	{
		perror("Can not set handler for SIGBUS\n");
		exit(1);
	}

	if (SIG_ERR == signal(SIGTRAP, sigtrap_handler))
	{
		perror("Can not set handler for SIGTRAP\n");
		exit(1);
	}

	if (-1 == stat("test.txt", &stat_buf))
	{
		perror("Fail to stat.\n");
		exit(1);
	}

	fd = open("test.txt", O_RDWR);
	if (-1 == fd)
	{
		perror("Fail to open.\n");
		exit(1); 
	}

	buf = (char *)mmap(NULL, stat_buf.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (MAP_FAILED == buf)
	{
		perror("Fail to mmap.\n");
		close(fd);
		exit(1);
	}

	printf("Now try to write.\n");
	strcpy(buf, "China");

	if (-1 == mprotect(buf, stat_buf.st_size, PROT_READ | PROT_WRITE))
	{
		perror("Fail to mprotect.\n");
		exit(1);
	}

	printf("Now try to write again.\n");
	strcpy(buf, "China");

	if (-1 == munmap(buf, stat_buf.st_size))
	{
		perror("Fail to munmap.\n");
		exit(1);
	}

	close(fd);

	return 0;
}

