#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

/* Use /home/admin/connect.socket as the communication socket file. */
#define SOCK_FILE_PATH "/home/admin/connect.socket"

#define STALE 30
#define MAX 1024

void my_func(char *p)
{
	if (NULL == p)
	{
		return;
	}

	for (; *p != '\0'; ++p)
	{
		if (*p >= 'A' && *p <= 'Z')
		{
			*p = *p - 'A' + 'Z';
		}
	}
}

int init(int *lfd, char * path)
{
	int fd, len;
	struct sockaddr_un un_addr;

	if (-1 == (fd = socket(AF_UNIX, SOCK_STREAM, 0)))
	{
		perror("fail to socket");
		return -1;
	}

	/* If the socket file has already been removed, unlink will return error. So here we do not check the return
	   value of it.
	 */
	unlink(path);

	memset(&un_addr, 0, sizeof(un_addr));
	un_addr.sun_family = AF_UNIX;
	strcpy(un_addr.sun_path, path);

	/* Calculate the length of the file path. */
	len = offsetof(struct sockaddr_un, sun_path) + strlen(path);

	/* Bind the socket to an address structure, and then can communicate with the socket. */
	if (-1 == bind(fd, (struct sockaddr *)&un_addr, len))
	{
		perror("fail to bind");
		goto err;
	}

	if (-1 == listen(fd, 10))
	{
		perror("fail to listen");
		goto err;
	}

	*lfd = fd;
	return 0;

err:
	close(fd);
	return -1;
}

int main(void)
{
	int lfd, cfd;
	time_t staletime;	/* Test the time of the client process. */
	struct sockaddr_un un_addr;
	struct stat statbuf;
	char buf[MAX];
	int len, n;

	if (-1 == init(&lfd, SOCK_FILE_PATH))
	{
		exit(1);
	}

	while (1)
	{
		len = sizeof(struct sockaddr_un);

		if (-1 == (cfd = accept(lfd, (struct sockaddr *)&un_addr, &len)))
		{
			perror("fail to accept");
			exit(1);
		}

		len -= offsetof(struct sockaddr_un, sun_path);
		un_addr.sun_path[len] = '\0';

		if (-1 == stat(un_addr.sun_path, &statbuf))
		{
			perror("fail to get status");
			exit(1);
		}

		/*if ((statbuf.st_mode & (S_IRWXG | S_IRWXO)) || (statbuf.st_mode & S_IRWXU) != _IRWXU)
		{
			printf("wrong permissions\n");
			exit(1);
		}
		*/

		staletime = time(NULL) - STALE;
		if (statbuf.st_atime < staletime || statbuf.st_ctime < staletime || statbuf.st_mtime < staletime)
		{
			printf("client is too old\n");
			close(cfd);
			break;
		}

		if (-1 == unlink(un_addr.sun_path))
		{
			perror("fail to unlink");
			exit(1);
		}

		my_func(buf);
		if (-1 == write(cfd, buf, n))
		{
			perror("fail to write");
			exit(1);
		}

		close(cfd);
	}

	if (-1 == unlink(SOCK_FILE_PATH))
	{
		perror("fail to unlink");
		exit(1);
	}

	close(lfd);
	return 0;
}
