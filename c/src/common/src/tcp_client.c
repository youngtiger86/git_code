#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

#define MAX_LINE 100

void print_help()
{
	printf("Usage:\n");
	printf("Syntax\n");
	printf("\ttcp_client argument_string\n");
	printf("Parameter\n");
	printf("\targument_stirng -- String to be send to server to check the length.\n");
}
int main(int argc, char const *argv[])
{
	struct sockaddr_in sin;
	int s_fd;
	int port = 8000;
	int n;
	char msg[MAX_LINE];
	char buf[MAX_LINE];

	if (2 != argc)
	{
		print_help();
		exit(1);
	}

	snprintf(msg, MAX_LINE, argv[1]);
	msg[MAX_LINE -1] = '\0';

	sin.sin_family = AF_INET;	/* Using IPv4. */
	inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);
	sin.sin_port = htons(port);

	if (-1 == (s_fd = socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("fail to create socket");
		exit(1);
	}

	if (-1 == connect(s_fd, (struct sockaddr_in *)&sin, sizeof(sin)))
	{
		perror("fail to connect");
		exit(1);
	}

	n = send(s_fd, msg, strlen(msg) + 1, 0);
	if (-1 == n)
	{
		perror("fail to send");
		exit(1);
	}

	n = recv(s_fd, buf, MAX_LINE, 0);
	if (-1 == n)
	{
		perror("fail to receive");
		exit(1);
	}

	printf("the length of the string is: %s\n", buf);

	if (-1 == close(s_fd))
	{
		perror("fail to close");
		exit(1);
	}

	return 0;
}
