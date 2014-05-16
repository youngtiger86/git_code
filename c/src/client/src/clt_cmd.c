#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "comm_def.h"
#include "cm_io.h"
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

    bzero(sin, sizeof(struct sockaddr_in));
    sin->sin_family = AF_INET;
    if (-1 == inet_pton(AF_INET, ip, &sin->sin_addr))
    {
        perror("Wrong format of ip address.");
        return -1;
    }

    if (-1 == inet_pton(AF_INET, ip, &sin->sin_addr))
    {
        perror("Wrong format of IP address.");
        return -1;
    }

    sin->sin_port = htons(SERVER_SERVICE_PORT);
    if (-1 == socket(AF_INET, SOCK_STREAM, 0))
    {
        perror("Fail to create socket.");
        return -1;
    }

    if (-1 == (sfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        perror("Fail to socket.");
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
	int res = -1;
	int dest_fd;
	struct stat file_stat;
	cmd_info_t * cmd_info;
	prepare_ack_t * prepare_ack;
	char buf[MAX_MSG_LEN] = {0};

	cmd_info = (cmd_info_t *)buf;
	cmd_info->type = CMD_TYPE_GET;
	cmd_info->arg_len = strlen(src);
	
	if (strlen(src) > MAX_MSG_LEN - sizeof(cmd_info_t) -1)
	{
		printf("File path is too long. File: %s. Function: %s. Line no: %u.\n", __FILE__, __FUNCTION__, __LINE__);
		return -1;
	}

	strncpy(buf + sizeof(cmd_info_t), src, MAX_MSG_LEN - sizeof(cmd_info_t));

	/* Create the dest file. */
	if (NULL == dest)
	{
		printf("Dest file path is not given.\n");
		return -1;
	}

	dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (-1 == dest_fd)
	{
		printf("Fail to open dest file: %s.\n", dest);
		return -1;
	}

	if (-1 == fstat(dest_fd, &file_stat))
	{
		perror("Fail to stat dest-file.\n");
		goto end1;
	}

	/* If the file exists and it's not a regular file, we can not cover it. */
	if (!S_ISREG(file_stat.st_mode))
	{
		printf("Dest file should be a regular file.\n");
		goto end1;
	}	

	//sprintf(buf, "GET %s", src);

	if ( -1 == cm_write(sock_fd, buf, sizeof(cmd_info_t) + cmd_info->arg_len))
	{
		printf("Fail to send command 'get' to server.\n");
		return -1;
	} 

	if (-1 == cm_read(sock_fd, buf, MAX_MSG_LEN))
	{
		printf("Fail to get prepare ack from server.\n");
		return -1;	
	}

	memset(buf, 0, MAX_MSG_LEN);
	if (-1 == cm_read(sock_fd, buf, 2))
	{
		goto end1;
	}

	if (-1 == cm_write(dest_fd, buf, 2))
	{
		goto end1;
	}

	res = CM_SUCCESS;
end1:
	close(dest_fd);

	return res;
}

int do_put(const char * src, const char * dest, int sock_fd)
{
	return 0;
}

int do_serv_pwd(int sock_fd)
{
    cmd_info_t * cmd_info;
    char buf[MAX_MSG_LEN] = {0};

    cmd_info = (cmd_info_t *)buf;
    cmd_info->type = CMD_TYPE_SERV_PWD;
    cmd_info->arg_len = 0;

    if (-1 == cm_write(sock_fd, buf, sizeof(cmd_info_t)))
    {
        perror("Fail to send command 'pwd' to server.\n");
        return -1;
    }

    memset(buf, 0, MAX_MSG_LEN);

    if (-1 == cm_read(sock_fd, buf, MAX_MSG_LEN))
    {
        perror("Fail to read respond for 'pwd' from server.\n");
        return -1;
    }

    printf("%s\n", buf);
    return 0;
}

int do_serv_cd(char * path, int sock_fd)
{
    cmd_info_t * cmd_info; 
    char buf[MAX_MSG_LEN] = {0};

	cmd_info = (cmd_info_t *)buf;
    cmd_info->type = CMD_TYPE_CD;
    cmd_info->arg_len = strlen(path);
    if (cmd_info->arg_len > MAX_MSG_LEN - sizeof(cmd_info_t))
	{
		printf("Path is too long: %s.\n", path);
		return -1;
	}

	strncpy(buf + sizeof(cmd_info_t), path, cmd_info->arg_len);
    if (-1 == cm_write(sock_fd, buf, sizeof(cmd_info_t) + cmd_info->arg_len))
	{
		printf("Fail to send command 'cd' to server.\n");
		return -1;
	}

	if (-1 == cm_read(sock_fd, buf, MAX_MSG_LEN))
	{
 		printf("Fail to cm_read.\n");
		return -1;
	}

	return 0;
}

int do_serv_ls(char * path, int sock_fd)
{
	cmd_info_t * cmd_info;
	char buf[MAX_MSG_LEN] = {0};
	int len;

	//sprintf(buf, "LS %s", path);
	cmd_info = (cmd_info_t *)buf;
	cmd_info->type = CMD_TYPE_LS;
	cmd_info->arg_len = strlen(path);
	if (cmd_info->arg_len > MAX_MSG_LEN - sizeof(cmd_info_t))
	{
		printf("Path is too long: %s.\n", path);
		return -1;
	}

	strncpy(buf + sizeof(cmd_info_t), path, cmd_info->arg_len);
	//printf("Server ls path: %s\n", );			
	if (-1 == cm_write(sock_fd, buf, sizeof(cmd_info_t) + cmd_info->arg_len))
	{
		printf("Fail to send command 'ls' to server.\n");
		return -1;	
	}

	if (-1 == cm_read(sock_fd, buf, MAX_MSG_LEN))
	{
		perror("Fail to cm_read.\n");
		return -1;
	}

	printf("%s\n", buf);

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
    char cwd[MAX_PATH_LEN] = {0};

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
    char cmd[MAX_CMD_LEN] = {0};
    char buf[MAX_FILE_LINE_LEN] = {0};

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

