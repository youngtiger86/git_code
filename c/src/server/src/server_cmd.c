#include "server_cmd.h"

int server_init(struct sockaddr_in * sin, int * lfd, int sock_opt)
{
    int sfd;
    //CM_POINTER2(sin, lfd);
    bzero(sin, sizeof(struct sockaddr_in));
    sin->sin_family = AF_INET;
    sin->sin_addr.s_addr = INADDR_ANY;
    sin->sin_port = htons(SERVER_SERVICE_PORT);

    if (-1 == (sfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        perror("Fail to socket.");
        return -1;
    }

    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &sock_opt, sizeof(int));

    if (-1 == bind(sfd, (struct sockaddr*)sin, sizeof(struct sockaddr_in)))
    {
        perror("Fail to bind.");
        return -1;
    }

    if (-1 == listen(sfd, 20))
    {
        perror("Fail to listen.");
        return -1;
    }

    *lfd = sfd;

    return 0;
}

#if 0
static int server_get_cmd_info(int sockfd, char * cmd_buff, unsigned int buff_len, cmd_info_t * cmd_info)
{
    int n;

    if (-1 == recv(sockfd, cmd_buff, buff_len, 0))
    {
        perror("Fail to receive.");
        return -1;
    }

    *cmd_info = (cmd_info_t *)cmd_buff;

    return 0;
}
#endif

int server_service_proc(int sockfd)
{
	int ret;
	int len;
	char buf[MAX_MSG_LEN];

	len = cm_read(sockfd, buf, MAX_MSG_LEN);
	if (0 == len)
	{
		perror("fail to read");
		return -1;
	}

	if (strstr(buf, "GET") == buf)
	{
		ret = server_process_get_cmd(sockfd, buf[4]);
		if (-1 == ret)
		{
			perror("fail to process get cmd");
			return -1;
		}
	}
}

#if 0
int server_service_proc(int sockfd)
{
    int ret;
    cmd_info_t * cmd_info;
    char cmd_buff[MAX_CMD_LEN];
    char cmd_add_info[MAX_CMD_LEN];
    //char arg[MAX_CMD_LEN];
    int disconn = FALSE;
    
/*
    if (-1 == server_get_cmd_info(sockfd, cmd_buff, MAX_CMD_LEN))
    {
        perror("Fail to get command information.");
        return -1
    }
*/
    while (!disconn)
    {
        if (-1 == recv(sockfd, cmd_buff, MAX_CMD_LEN, 0))
        {
            perror("Fail to receive.");
            return -1;
        }

        cmd_info  = (cmd_info_t *)cmd_buff;
	//cmd_add_info = cmd_buff + sizeof(cmd_info_t);
	strncpy(cmd_add_info, (char *)cmd_info + sizeof(cmd_info_t), cmd_info->arg_len);
        cmd_add_info[cmd_info->arg_len] = '\0';
//        cmd_add_info = (char *)cmd_info + sizeof(cmd_info_t);
//		snprintf(arg, cmd_addr_info, cmd_info->arg_len);
//		arg[cmd
        switch (cmd_info->type)
        {
            case CMD_TYPE_PUT:
                ret = server_do_put(sockfd, cmd_add_info);
                break;
            case CMD_TYPE_GET:
                ret = server_process_get_cmd(sockfd, cmd_add_info);
                break;
            case CMD_TYPE_CD:
                ret = server_do_cd(sockfd, cmd_add_info);
                break;
            case CMD_TYPE_LS:
                ret = server_do_ls(sockfd, cmd_add_info);
                break;
            case CMD_TYPE_BYE:
                disconn = TRUE;
                break;
            default:
                perror("Unknown command type");
        }    
    }

    return ret;
}
#endif

int server_do_put(int cfd, char * file)
{
    return 0;
}

int server_process_get_cmd(int cfd, char * file)
{
	struct stat statbuf;
	int n, fd;
	char buf[MAX_MSG_LEN];
	int res = -1;

	if (-1 == (fd = open(file, O_RDONLY)))
	{
		cm_write(cfd, "ERR open server file.\n", strlen("Err open server file.\n"));
		return res;
	}

	if (-1 == fstat(fd, &statbuf))
	{
		cm_write(cfd, "ERR stat server file\n", strlen("ERR stat server file\n"));
		goto end;
	}

	/* Check whether it's a ragular file. If not, report error. */
	if (!S_ISREG(statbuf.st_mode))
	{
		if (-1 == cm_write(cfd, "ERR server path should be a regular file.\n", strlen("ERR server path should be a regular file.\n")))
		{
			goto end;
		}

		res = 0;
		goto end;
	}

	sprintf(buf, "OK %d", statbuf.st_size);

	if (-1 == cm_write(cfd, buf, strlen(buf)))
	{
		goto end;
	}

	if (-1 == cm_read(cfd, buf, MAX_MSG_LEN))
	{
		goto end;
	}

	while (1)
	{
		n = read(fd, buf, MAX_MSG_LEN);
		if (n > 0)
		{
			if (-1 == cm_write(cfd, buf, n))
			{
				goto end;
			}
		}
		else if (0 == n)
		{
			printf("OK\n");
			break;
		}
		else
		{
			perror("Fail to read");
			goto end;
		}
	}

	res = 0;

end:
	close(fd);
	return res;
}

#if 0
int server_process_get_cmd(int cfd, char * file)
{
	prepare_ack_t * ack;
	char buf[MAX_MSG_LEN] = {0};

	if (-1 == cm_read(cfd, buf, MAX_MSG_LEN))
	{
		printf("Fail to cm_write.\n");
		return -1;
	}

	ack = (prepare_ack_t *)buf;
	ack->code = CM_SUCCESS;
	ack->len = 2;

	if (-1 == cm_write(cfd, buf, sizeof(prepare_ack_t)))
	{
		printf("Fail to cm_write.\n");
		return -1;
	}
	
	if (-1 == cm_read(cfd, buf, sizeof(cmd_info_t)))
	{
		printf("Fail to cm_read to get confrim.\n");
		return -1;
	}

	memset(buf, 0, MAX_MSG_LEN);
	strncpy(buf, "ab", 2);
	if (-1 == cm_write(cfd, buf, 2))
	{
		printf("Fail to cm_write file to client.\n");
		return -1;
	}

    return 0;
}
#endif

int server_do_cd(int cfd, char * path)
{
    return 0;
}

int server_do_ls(int cfd, char * path)
{
	FILE *  fd;
	int read_len;
	char cmd[MAX_CMD_LEN];
	char result_buf[MAX_MSG_LEN];
	char read_buf[MAX_FILE_LINE_LEN];
    char * tmp_result_file = "/tmp/server_ls_result.txt";

	printf("Get the command: server ls. Path:%s\n", path);

	snprintf(cmd, MAX_CMD_LEN, "ls -lrt %s > %s", path, tmp_result_file);
	system(cmd);

	fd = fopen(tmp_result_file, "r");
	if (NULL == fd)
	{
		perror("Fail to open file\n");
		return -1;
	}

	read_len = 0;
	while (NULL != fgets(read_buf, MAX_FILE_LINE_LEN, fd))
	{
		if (read_len + strlen(read_buf) >= MAX_MSG_LEN)
		{
			/* Here it should send by more than once. But only break now. */
			break;
		}

		strncpy(result_buf + read_len, read_buf, strlen(read_buf));
		read_len += strlen(read_buf);
	}

	if (read_len > 0)
	{
		if (-1 == cm_write(cfd, result_buf, read_len))
		{
			perror("Fail to my_send.\n");
			return -1;
		}
	}
	
	return 0;
}

