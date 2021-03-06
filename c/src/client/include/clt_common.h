#ifndef CLT_COMMON_H__
#define CLT_COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
//#include <iolib.h>

/* Global MACRO definitions. */
#define MAX_LINE 			1024 	/* Maximum length of the command send to server. */
#define PORT 				8000
#define COMMAND_LINE 		256 	/* Maximum length of the command input by user on client. */
#define MAX_ARG 			10 		/* Maximum number of arguments of command. */
#define MAX_LENGTH			64		/* Maximum length of command or argument. */
#define NAME_LEN 			256		/* Maxinum length of file in the system. */

/* Global variable definitions. */
/* Structure of command. */
typedef struct tagcmd_line{
	char * name;			/* Name of command. */
	char * argv[MAX_ARG];	/* Command name and arguments. */
}cmd_line_t;

/* Function declarations. */
int split(cmd_line_t * command, char cline[]);

int do_connect(char * ip, struct sockaddr_in * sin, int * sock_fd);
int do_get(const char * src, const char * dest, int sock_fd);
int do_put(const char * src, const char * dest, int sock_fd);
int do_serv_pwd(int sock_fd);
int do_serv_cd(char * path, int sock_fd);
int do_serv_ls(char * path, int sock_fd);
int do_cd(char * path);
int do_ls(char * path);
int do_bye(int sock_fd);

#endif /* CLT_COMMON_H__ */
