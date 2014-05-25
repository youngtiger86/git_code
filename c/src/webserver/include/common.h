#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include "cm_io.h"

#define MAX_LINE 1024	/* buffer size */

#define DEBUG 1

#ifdef DEBUG
#define DEBUG_PRINT(str); printf(str);
#else
#define DEBUG_PRINT(str);
#endif

/**********************************************************************************************************************
 Description:	Initialize the webserver service, get the configurations and start listner for connections. 
 Input:			None.	
 Output: 		sin -- Address of the server socket.
 				lfd -- Listner socket file descriptor.
				path -- Root path of the webserver services.
 Return value:	0 -- Initialization succeeded.
				-1 -- Initialization failed. 
 Note: 
 History: 
 1. Author: yangshangde
    Modification: 2014-05-20 Create this function.
 **********************************************************************************************************************/
extern int init(struct sockaddr_in * sin, int * lfd, char * path);

/**********************************************************************************************************************
 Description: 
 Input: 
 Output: 
 Return value: 
 Note: 
 History: 
 1. Author: yangshangde
 Modification: 2014-- Create this function.
 **********************************************************************************************************************/
extern int error_page(int sock_fd);

/**********************************************************************************************************************
 Description: 
 Input: 
 Output: 
 Return value: 
 Note: 
 History: 
 1. Author: yangshangde
 Modification: 2014-- Create this function.
 **********************************************************************************************************************/
extern int get_path(int cfd, char * path);

/**********************************************************************************************************************
 Description: 
 Input: 
 Output: 
 Return value: 
 Note: 
 History: 
 1. Author: yangshangde
 Modification: 2014-- Create this function.
 **********************************************************************************************************************/
extern int write_page(int cfd, char * path, int fd);
