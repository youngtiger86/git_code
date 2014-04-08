#ifndef __SERVER_CMD_H__
#define __SERVER_CMD_H__
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include "comm_def.h"
//#include "iolib.h"  /* Self-made I/O library. */

/* Global macro definitions. */
#define SERVER_SERVICE_PORT     8000

/* Function declarations. */
int server_init(struct sockaddr_in * sin, int * lfd, int sock_port);
int server_service_proc(int sockfd);
int server_do_put(int cfd, char * file);
int server_do_get(int cfd, char * file);
int server_do_cd(int cfd, char * path);
int server_do_ls(int cfd, char * path);

#endif /* __SERVER_CMD_H__ */