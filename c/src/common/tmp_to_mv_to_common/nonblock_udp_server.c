#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_LINE 100

void my_func(char * str)
{
	
}

int main()
{
	struct sockaddr_in sin;
	struct sockaddr_in cin;
	int s_fd;
	int flags;
	socklen_t addr_len;
	int n;
	char buf[MAX_LINE];
	char addr_p[INET_ADDRSTRLEN];
	int port = 8000;

	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);

	s_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == s_fd)
	{
		perror("fail to create socket");
		exit(1);
	}

	if (-1 == bind(s_fd, (struct sockaddr_in *)&sin, sizeof(sin)))
	{
		perror("fail to bind");
		exit(1);
	}

	/* Now we set the attibute of the socket which make it as a nonblock socket. We use the file manipulate interfaces.*/
	flags = fcntl(s_fd, F_GETFL);
	flags |= O_NONBLOCK;	/* Set the socket as nonblocking mode. */
	if (-1 == fcntl(s_fd, F_SETFL, flags))
	{
		perror("fait to fcntl");
		exit(1);
	}

	while (1)
	{
		sleep(5);	/* Sleep for 5 seconds, waiting for the data become available. */
		addr_len = sizeof(cin);

		n = recvfrom(s_fd, buf, MAX_LINE, 0, (struct sockaddr *)&cin, &addr_len);
		if (-1 == n)
		{
			if (EAGAIN == errno)
			{
				printf("socket are not ready now\n");
				continue;
			}
			else
			{
				perror("fail to recvfrom");
				exit(1);	
			}
		}

		inet_ntop(AF_INET, &cin.sin_addr, addr_p, sizeof(addr_p));

		printf("client IP is %s, port is %d\n", addr_p, ntohs(cin.sin_port));
		printf("content is %s\n", buf);

		my_func(buf);

		n = sendto(s_fd, buf, n, 0, (struct sockaddr_in *)&cin, addr_len);
		if (-1 == n)
		{
			if (EAGAIN == errno)
			{
				printf("socket are not ready now\n");
			}
			else
			{
				perror("fail to sendto");
				exit(1);
			}
		}
	}

	if (-1 == close(s_fd))
	{
		perror("fail to close");
		exit(1);
	}

	return 0;
}

