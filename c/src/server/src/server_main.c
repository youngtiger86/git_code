#include "server_cmd.h"

int main(void)
{
    struct sockaddr_in sin;     /* Address structure of the server. */
    struct sockaddr_in cin;     /* Address structure of the client. */
    int lsn_fd, cfd;
    socklen_t len = sizeof(struct sockaddr_in); /* IP address length, including the null terminator of the string. */
    char send_buf[MAX_MSG_LEN]; /* Store the message to send to client. */
    char addr[IP_ADDR_LEN];     /* Buffer of the address. */
    int sock_opt = 1;           /* Option of the socket. */
    int n;
    pid_t pid;

    /* Init the server, getting the address structure and the socket descriptor. */
    if (-1 == server_init(&sin, &lsn_fd, sock_opt))
    {
        exit(1);
    }

    printf("Server is waiting for connectons...\n");

    while (1)
    {
        if (-1 == (cfd = accept(lsn_fd, (struct sockaddr *)&cin, &len)))
        {
            perror("Fail to accept");
            exit(1);
        }

        if (pid = fork() < 0)
        {
            perror("Fail to fork");
            exit(1);
        }
        else if (0 == pid)
        {
            /* Client process does not listen. It handle the command sent by the client. */
            close(lsn_fd);
            server_service_proc(cfd);
        }
        else
        {
            /* Parent process closes the socket and keep on listening. */
            close(cfd);
        }
    }
}