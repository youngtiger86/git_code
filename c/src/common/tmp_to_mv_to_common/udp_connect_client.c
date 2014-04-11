#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include "iolib.h"

#define MAX_LINE 80

int main(int argc, char const *argv[])
{
	struct sockaddr_in sin;
	int port = 8000;
	int s_fd;
	char buf[MAX_LINE];
	char * str = "test";
	char addr_p[INET_ADDRSTRLEN];
	int n;

	if (2 == argc)
	{
		str = argv[1];
	}

	memset(&sin, sizeof(sin), 0);
	sin.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);
	sin.sin_port = htons(port);

	s_fd = socket(AF_INET, SOCK_DGRAM, 0);	/* Create a socket using UPD protocol. */
	if (-1 == s_fd)
	{
		perror("fail to create a socket");
		exit(1);
	}

	/* Use function connect to connect to server. After connecton, it's like to use a TCP socket to communicate. */
	n = connect(s_fd, (struct sockaddr *)&sin, sizeof(sin));
	if (-1 == n)
	{
		perror("fail to connect");
		exit(1);
	}
	else
	{
		printf("Connection has been established.\n");
	}

	n = my_write(s_fd, str, strlen(str) + 1);
	if (-1 == n)
	{
		exit(1);
	}

	n = my_read(s_fd, buf, MAX_LINE);
	if (-1 == n)
	{
		exit(1);
	}

	printf("receive from server: %s\n", buf);

	if (-1 == close(s_fd))
	{
		perror("fail to close");
		exit(1);
	}

	return 0;
}

