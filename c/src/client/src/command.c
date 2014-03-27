#include "clt_common.h"

/**********************************************************************************************************************
Description:    Connect to server.
Input:          ip -- IP address of the server.
                sockaddr_in -- Address structure of the server. 
                sock_fd -- Socket file descriptor.
Output:         None.
Return value:   0 -- Connect success.
                -1 -- Connect fail.
Note:
History:        
1. 20140327 yangshangde
   Create this function.
**********************************************************************************************************************/
int do_connect(char * ip, struct sockaddr_in * sin, int * sock_fd)
{
    int sfd;

    bzero(&sin, sizeof(struct sockaddr_in));
    sin->sin_family = AF_INET;
    if (-1 == inet_pton(AF_INET, ip, &sin->sin_addr))
    {
        perror("Wrong format of ip address.");
        return -1;
    }

    sin->sin_port = htons(PORT);
    if (-1 == socket(AF_INET, SOCK_STREAM, 0))
    {
        perror("Fail to create socket.");
        return -1;
    }

    if (-1 == connect(sfd, (struct sockaddr *)sin, sizeof(struct sockaddr_in)))
    {
        perror("Fail to connect.");
        return -1;
    }

    *sock_fd = sfd;

	return 0;
}

int do_get(const char * src, const char * dest, int sock_fd)
{
	return 0;
}

int do_put(const char * src, const char * dest, int sock_fd)
{
	return 0;
}

int do_serv_cd(char * path, int sock_fd)
{
	return 0;
}

int do_serv_ls(char * path, int sock_fd)
{
	return 0;
}

int do_cd(char * path)
{
	return 0;
}

int do_ls(char * path)
{
	return 0;
}

int do_bye(int sock_fd)
{
	return 0;
}
		
