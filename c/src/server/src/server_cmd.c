#include "server_cmd.h"

int server_init(struct sockaddr_in * sin, int * lfd, int sock_port)
{
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
    cmd_info_t * cmd_info;
    char cmd_buff[MAX_CMD_LEN];
    char * cmd_add_info;
    
/*
    if (-1 == server_get_cmd_info(sockfd, cmd_buff, MAX_CMD_LEN))
    {
        perror("Fail to get command information.");
        return -1
    }
*/
    if (-1 == recv(sockfd, cmd_buff, MAX_CMD_LEN, 0))
    {
        perror("Fail to receive.");
        return -1;
    }

    cmd_info  = (cmd_info_t *)cmd_buff;
    cmd_add_info = (char *)cmd_info + sizeof(cmd_info_t);
    switch (cmd_info->type)
    {
        case CMD_TYPE_PUT:
            ret = server_do_put(sockfd, cmd_add_info);
            break;
        case CMD_TYPE_GET:
            ret = server_do_get(sockfd, cmd_add_info);
            break;
        case CMD_TYPE_CD:
            ret = server_do_cd(sockfd, cmd_add_info);
            break;
        case CMD_TYPE_LS:
            ret = server_do_ls(sockfd, cmd_add_info);
            break;
        default:
            perror("Unknown command type");
            ret = -1;
    }

    return ret;
}

int server_do_put(int cfd, char * file)
{
    return 0;
}

int server_do_get(int cfd, char * file)
{
    return 0;
}

int server_do_cd(int cfd, char * path)
{
    return 0;
}

int server_do_ls(int cfd, char * path)
{
    return 0;
}