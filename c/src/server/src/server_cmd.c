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
    cmd_info_t * cmd_info;
    char cmd_buff[MAX_CMD_LEN];
    char * cmd_add_info;
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
            case CMD_TYPE_BYE:
                disconn = TRUE;
                break;
            default:
                perror("Unknown command type");
        }    
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
