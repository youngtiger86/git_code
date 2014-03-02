#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define MAX_LINE 100

int main(void)
{
	struct sockaddr_in sin;
	struct sockaddr_in cin;
	int port = 8000;
	int s_fd;
	int n;
	char buf[MAX_LINE];
	socklen_t addr_len;

	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);
	sin.sin_port = htons(port);

	s_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == s_fd)
	{
		perror("fail to create a socket");
		exit(1);
	}

	if (-1 == fgets(buf, MAX_LINE, stdin))
	{
		perror("fail to fgets");
		exit(1);
	}

	n = sendto(s_fd, buf, strlen(buf) + 1, 0, (struct sockaddr *)&sin, sizeof(sin));
	if (-1 == n)
	{
		perror("fail to send\n");
		exit(1);
	}

	addr_len = sizeof(cin);
	n = recvfrom(s_fd, buf, MAX_LINE, 0, (struct sockaddr *)&cin, &addr_len);
	if (-1 == n)
	{
		perror("fail to recvfrom\n");
		exit(1);
	}
	else
	{
		printf("receive from server: %s\n", buf);
	}

	if (-1 == close(s_fd))
	{
		perror("fail to close");
		exit(1);
	}

	return 0;
}
