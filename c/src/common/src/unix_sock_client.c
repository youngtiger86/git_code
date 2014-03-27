#include <stdio.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_FILE_PATH "/home/admin/connect.socket"
#define C_PATH "/home/admin"
#define MAX 1024

int main(void)
{
	int cfd, len;
	struct sockaddr_un un_addr;
	char buf[MAX];

	if (-1 == (cfd = socket(AF_UNIX, SOCK_STREAM, 0)))
	{
		perror("fail to create socket");
		exit(1);
	}

	memset(&un_addr, 0, sizeof(un_addr));
	un_addr.sun_family = AF_UNIX;
	sprintf(un_addr.sun_path, "%s%d", C_PATH, getpid());
	len = offsetof(struct sockaddr_un, sun_path) + strlen(un_addr.sun_path);

	if (-1 == connect(cfd, (struct sockaddr *)&un_addr, len))
	{
		perror("fail to connect");
		exit(1);
	}

	strcpy(buf, "CHINA");
	if (-1 == write(cfd, buf, strlen(buf) + 1))
	{
		perror("fail to write");
		exit(1);
	}

	if (-1 == read(cfd, buf, MAX))
	{
		perror("fail to read");
		exit(1);
	}

	printf("receive from server: %s \n", buf);
	close(cfd);

	return 0;
}
