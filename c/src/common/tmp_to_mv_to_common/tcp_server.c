#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_LINE 100

int main()
{
	struct sockaddr_in sin;
	struct sockaddr_in cin;
	int l_fd;
	int c_fd;
	socklen_t len;
	char buf[MAX_LINE];
	char addr_p[INET_ADDRSTRLEN];
	int port = 8000;
	int n;

	bzero(&sin, sizeof(sin));

	sin.sin_family = AF_INET;	/* Use IPv4 */
	sin.sin_addr.s_addr = INADDR_ANY;	/* Server port accept connection from any address. */
	sin.sin_port = htons(port);	/* Convert the port to network endian. */

	if (-1 == (l_fd = socket(AF_INET, SOCK_STREAM, 0)))	/* Create a socket using TCP protocol. */
	{
		perror("fail to create socket");
		exit(1);
	}

	if (-1 == bind(l_fd, (struct sockaddr_in *)&sin, sizeof(sin)))	/* Bind the socket and the address. */
	{
		perror("fail to bind");
		exit(1);
	}

	if (-1 == listen(l_fd, 10))	/* Begin to listen for connection request. */
	{
		perror("fail to listen");
		exit(1);
	}

	printf("waitting...\n");

	while (1)
	{
		if (-1 == (c_fd = accept(l_fd, (struct sockaddr_in *)&cin, &len)))
		{
			perror("fail to accept");
			exit(1);
		}

		n = recv(c_fd, buf, MAX_LINE, 0);
		if (-1 == n)
		{
			perror("fail to receive");
			exit(1);
		}
		else 
		{
			if (0 == n)	/* The peer side is closed. */
			{
				printf("the connect has been closed.\n");
				close(c_fd);
				continue;
			}
		}

		inet_ntop(AF_INET, &cin.sin_addr, addr_p, sizeof(addr_p));

		printf("client IP is %s, port is %d\n", addr_p, ntohs(cin.sin_port));
		printf("content is %s\n", buf);

		n = strlen(buf);
		sprintf(buf, "%d", n);

		n = send(c_fd, buf, strlen(buf) + 1, 0);
		if (-1 == n)
		{
			perror("fail to send");
			exit(1);
		}

		if (-1 == close(c_fd))
		{
			perror("fail to close");
			exit(1);
		}
	}

	return 0;
}