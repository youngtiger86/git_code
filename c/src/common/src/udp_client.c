#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_LINE 100

int main(int argc, char const *argv[])
{
	struct sockaddr_in sin;		/* Dest address, which contains the address information of the udp server. */
	struct sockaddr_in cin;
	int port = 8000;
	int n;
	int s_fd;
	char * msg = "Default string: Hello, world";
	int addr_len;
	char buf[MAX_LINE];

	if (2 == argc)
	{
		msg = argv[1];
	}

	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;	/* Using IPv4. */
	inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);
	sin.sin_port = htons(port);

	s_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == s_fd)
	{
		perror("fail to create socket");
		exit(1);
	}

	n = sendto(s_fd, msg, strlen(msg) + 1, 0, (struct sockaddr_in *)&sin, sizeof(sin));
	if (-1 == n)
	{
		perror("fail to send");
		exit(1);
	}

	addr_len = sizeof(cin);
	n = recvfrom(s_fd, buf, MAX_LINE, 0, (struct soackaddr_in *)&cin, &addr_len);
	if (-1 == n)
	{
		perror("fail to receive");
		exit(1);
	}
	else
	{
		printf("receive from server: %s\n", buf);
	}

	if (-1 == close(s_fd))	/* Close the socket. */
	{
		perror("fail to close");
		exit(1);
	}

	return 0;
}
