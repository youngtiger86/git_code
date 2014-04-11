#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

#define MAX 100

int main(void)
{
	int sockfd[2]; 	/* Used to save the UNIX domain socket file descriptors. */
	pid_t pid;
	char buf[MAX];
	int n;

	if (-1 == socketpair(AF_UNIX, SOCK_STREAM, 0, sockfd))
	{
		perror("fail to socketpair");
		exit(1);
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fail to fork");
		exit(1);
	}
	else if (0 == pid)
	{
		/* Subprocess, close the read socket */
		if (-1 == close(sockfd[0]))
		{
			perror("fail to close");
			exit(1);
		}

		strcpy(buf, "hello parent");
		n = strlen(buf);

		if (-1 == write(sockfd[1], buf, n))
		{
			perror("fail to write");
			exit(1);
		}

		printf("The child done\n");
	}
	else
	{
		/* Parent process. Close the write side. It will read what the subprocess writes. */
		if (-1 == close(sockfd[1]))
		{
			perror("fail to close");
			exit(1);
		}

		if (-1 == read(sockfd[0], buf, MAX))
		{
			perror("fail to read");
			exit(1);
		}

		n = strlen(buf);
		buf[n] = '\0';

		printf("receive from child: %s\n", buf);

		if (NULL == wait(NULL))	/* Get the terminate status of subchild. */
		{
			perror("fail to wait");
			exit(1);
		}

		printf("the parent done\n");
	}

	return 0;
}
