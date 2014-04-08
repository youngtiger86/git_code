#include "comm_def.h"
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

/**********************************************************************************************************************
Description:    Get a file from server.
Input:          src -- The file to be gotten.
                dest -- The destination to put the file. 
                sock_fd -- Socket file descriptor.
Output:         None.
Return value:   0 -- Get file success.
                -1 -- Get file fail.
Note:
History:        
1. 20140401 yangshangde
   Create this function.
**********************************************************************************************************************/
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

/**********************************************************************************************************************
Description:    Change the working directory to the specified one.
Input:          path -- The path to change to .
Output:         None.
Return value:   0 -- Change client working directory success.
                -1 -- Fail to change client working directory.
Note:
History:        
1. 20140401 yangshangde
   Create this function.
**********************************************************************************************************************/
int do_cd(char * path)
{
    char cwd[MAX_PATH_LEN];

    if (NULL == path)
    {
        perror("The path to change to is not given for function do_cd.");
        return -1;
    }

    if (-1 == chdir(path))
    {
        perror("Fail to change working directory.");
        return -1;
    }

    getcwd(cwd, MAX_PATH_LEN);
    printf("Current working directory: %s\n", cwd);

	return 0;
}

int do_ls(char * path)
{
    FILE * fp;
    char cmd[MAX_CMD_LEN];
    char buf[MAX_FILE_LINE_LEN];

    snprintf(cmd, MAX_CMD_LEN, "ls -lrt %s > /tmp/ls_tmp.txt", path);
    system(cmd);

    fp = fopen("/tmp/ls_tmp.txt", "r");
    if (NULL == fp)
    {
        perror("Failed to open temprary file fo ls command.");
        return -1;
    }


    while (NULL != fgets(buf, MAX_FILE_LINE_LEN, fp))
    {
        printf("%s", buf);
    }

    fclose(fp);
    unlink("/tmp/ls_tmp.txt");

	return 0;
}

int do_bye(int sock_fd)
{
	return 0;
}
		
