#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include "iolib.h"
#define MAX_LINE 100

int main(int argc, char const *argv[])
{
	struct sockaddr_in sin;		/* Address of the server. */
	char buf[MAX_LINE];
	int sfd;
	int port = 8000;
	char * str = "test string";	/* Default string if no parameter input by the user. */
	int n;

	if (argc > 1)
	{
		str = argv[1];	/* Get the string from the user input. */
	}

	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;	/* User IPv4 address. */
	inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);
	sin.sin_port = htons(port);

	if (-1 == (sfd = socket(AF_INET, SOCK_STREAM, 0)))	/* Create a socket. */
	{
		perror("fail to create socket");
		exit(1);
	}
	
	if (-1 == connect(sfd, (struct sockaddr_in *)&sin, sizeof(sin)))
	{
		perror("fail to connect");
		exit(1);
	}

	n = my_write(sfd, str, strlen(str) + 1);
	if (-1 == n)
	{
		exit(1);
	}
	
	n = my_read(sfd, buf, MAX_LINE);
	if (-1 == n)
	{
		exit(1);
	}

	printf("receive from server: %s\n", buf);

	if (-1 == close(sfd))
	{
		perror("fail to close");
		exit(1);
	}

	return 0;
}