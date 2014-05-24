#include "common.h"

static int configuration(int * port, char * path)
{
	int i;
	FILE * fp;
	char * p;
	char buf[50];	/* buffer for file content */

	fp = fopen("./config.ini", "r");
	if (NULL == fp)
	{
		perror("fail to open config.ini");
		return -1;
	}

	while (fgets(buf, 50, fp) != NULL)
	{
		if ('\n' != buf[strlen(buf) - 1])
		{
			printf("error in config.ini\n");
			return -1;
		}
		else
		{
			buf[strlen(buf) - 1] = '\0';
		}

		if (strstr(buf, "port") == buf)
		{
			if ((p = strchr(buf, ':')) == NULL)
			{
				printf("config.ini expect ':'\n");
				return -1;
			}

			*port = atoi(p + 2); /* jump over the ':' and blank*/
			if (*port < 0)
			{
				printf("error port\n");
				return -1;
			}
		}
		else if (buf == strstr(buf, "root-path"))
		{
			if (NULL == (p = strchr(buf, ':')))
			{
				printf("config.ini expect ':'\n");
				return -1;
			}

			p += 2;
			strcpy(path, p);
		}
		else
		{
			printf("error in config.ini\n");
			return -1;
		}
	}
	
	return 0;
}

int init(struct sockaddr_in * sin, int * lfd, int * port, char * path)
{
	int tfd;

	configuration(port, path);

	bzero(sin, sizeof(struct sockaddr_in));
	sin->sin_family = AF_INET;
	sin->sin_addr.s_addr = INADDR_ANY;
	sin->sin_port = htons(*port);

	if (-1 == (tfd = socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("fail to create socket");
		return -1;
	}

	if (-1 == bind(tfd, (struct sockaddr *)sin, sizeof(struct sockaddr_in)))
	{
		perror("fail to bind");
		return -1;
	}

	if (-1 == listen(tfd, 20))
	{
		perror("fail to listen");
		return -1;
	}

	*lfd = tfd;

	return 0;
}

int get_path(int cfd, char * path)
{
	char buf[MAX_LINE];

	if (-1 == cm_read(cfd, buf, MAX_LINE))
	{
		return -1;
	}

	if (strstr(buf, "GET") != buf)
	{
		DEBUG_PRINT("wrong request\n");
		return -1;
	}

	if (('/' == buf[4]) && (' ' == buf[5]))
	{
		strcat(path, "/index.html");
	}
	else
	{
		strtok(&buf[4], " ");
		strcat(path, &buf[4]);
	}

	return 0;
}

int error_page(int sock_fd)
{
	char err_str[1024];

#ifdef DEBUG
	sprintf(err_str, "HTTP/1.1 404 %S\r\n", strerror(errno.h));
#else
	sprintf(err_str, "HTTP/1.1 404 Not Exist\r\n");
#endif

	if (-1 == cm_write(sock_fd, err_str, strlen(err_str)))
	{
		return -1;
	}

	if (-1 == cm_write(sock_fd, "content-Type: text/html\r\n\r\n", strlen("content-Type: text/html\r\n\r\n")))
	{
		return -1;
	}

	if (-1 == cm_write(sock_fd, "<html><body> the file dose not exist </body></html>", strlen("<html><body> the file dose not exist </body></html>")))
	{
		return -1;
	}

	return 0;
}

int write_page(int cfd, char * path, int fd)
{
	int n;
	char buf[MAX_LINE];

	if (-1 == cm_write(cfd, "HTTP/1.1 200 OK\r\n", strlen("HTTP/1.1 200 OK\r\n")))
	{
		return -1;
	}

	if (-1 == cm_write(cfd, "Content-Type: ", strlen("Content-Type: ")))
	{
		return -1;
	}

	n = strlen(path);
	if (0 == strcasecmp(&path[n - 3], "jpg"))
	{
		if (-1 == cm_write(cfd, "image/jpeg", strlen("image/jpeg")))
		{
			return -1;
		}
	}
	else if (0 == strcasecmp(&path[n - 3], "gif"))
	{
		if (-1 == cm_write(cfd, "image/gif", strlen("image/gif")))
		{
			return -1;
		}
	}
	else if (0 == strcasecmp(&path[n - 3], "png"))
	{
		if (-1 == cm_write(cfd, "image/png", strlen("image/png")))
		{
			return -1;
		}
	}
	else
	{
		if (-1 == cm_write(cfd, "text/html", strlen("text/html")))
		{
			return -1;
		}
	}

	if (-1 == cm_write(cfd, "\r\n\r\n", 4))
	{
		return -1;
	}

	while ((n = read(fd, buf, MAX_LINE)) > 0)
	{
		if (-1 == cm_write(cfd, buf, n))
		{
			return -1;
		}
	}

	return 0;
}

