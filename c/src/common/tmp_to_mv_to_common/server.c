#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
//#include < arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include "iolib.h"
#define MAX_LINE 100	

void my_func(char * p)
{
	if (NULL == p)
	{
		return;
	}

	for (; *p != '\0'; ++p)
	{
		if (*p >= 'A' && *p <= 'Z')
		{
			*p = *p + 'a' - 'A';
		}
	}
}

int main()
{
	/* code */
	struct sockaddr_in sin;	/* sockaddr_in is the network communication structure in Linux. */
	struct sockaddr_in cin;
	int l_fd;
	int c_fd;
	socklen_t len;
	char buf[MAX_LINE];
	char addr_p[INET_ADDRSTRLEN];
	int port = 8000;
	int n;

	bzero(&sin, sizeof(sin));				/* Clean the structure. */
	sin.sin_family = AF_INET;				/* Use IPv4. */
	sin.sin_addr.s_addr = INADDR_ANY;		/* The server will accept connection from any address. */
	sin.sin_port = htons(port);				/* Convert the endian of the port to network endian. */

	if (-1 == (l_fd = socket(AF_INET, SOCK_STREAM, 0)))	/* Use TCP protocol to create a socket. */
	{
		perror("fail to create socket");
		exit(1);
	}

	if (-1 == bind(l_fd, (struct sockaddr *)&sin, sizeof(sin)))
	{
		perror("fail to bind");
		exit(1);
	}

	if (-1 == listen(l_fd, 10))
	{
		perror("fail to listen");
		exit(1);
	}

	printf("waiting ...\n");

	while (1)
	{
		/* Most servers are in dead loop. */
		/* Accept the connect requirement. When the function accept return, the communication can start. */
		if (-1 == (c_fd = accept(l_fd, (struct sockaddr *)&cin, &len)))
		{
			perror("fail to accept");
			exit(1);
		}

		n = read(c_fd, buf, MAX_LINE);
		if (-1 == n)
		{
			exit(1);
		}
		else if (0 == n)
		{
			printf("The connection has been closed.\n");
			close(c_fd);
			continue;		/* This connection has finish. Ready for the next one. */
		}

		/* Convert the address of the client into string. */
		inet_ntop(AF_INET, &cin.sin_addr, addr_p, sizeof(addr_p));
		printf("client IP is %s, port is %d\n", addr_p, ntohs(cin.sin_port));
		printf("content is : %s \n", buf);

		my_func(buf);

		n = my_write(c_fd, buf, n);	/* Send the content which has been converted into lower case to the client. */
		if (-1 == n)
		{
			exit(1);
		}

		if (-1 == close(c_fd))
		{
			perror("fail to close");
			exit(1);
		}
	}

	if (-1 == close(l_fd))
	{
		perror("fail to close");
		exit(1);
	}

	return 0;
}