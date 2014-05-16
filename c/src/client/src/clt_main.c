#include "clt_common.h"

int main(void)
{
	char cline[COMMAND_LINE];
	cmd_line_t command;
	int sock_fd;
	struct sockaddr_in sin;

	printf("myftp$: ");
	fflush(stdout);

	/* Only when the user input "bye" that this loop will end. */
	while (fgets(cline, MAX_LINE, stdin))
	{
		/* Split the command as command name and arguments. */
		if (-1 == split(&command, cline))
		{
			exit(1);
		}

		if (0 == strcasecmp(command.name, "get"))
		{
			if (-1 == do_get(command.argv[1], command.argv[2], sock_fd))
			{
				exit(1);
			}
		}
		else if (0 == strcasecmp(command.name, "put"))
		{
			if (-1 == do_put(command.argv[1], command.argv[2], sock_fd))
			{
				exit(1);
			}
		}
		else if (0 == strcasecmp(command.name, "cd"))
		{
			if (-1 == do_cd(command.argv[1]))
			{
				exit(1);
			}
		}
		else if (0 == strcasecmp(command.name, "!pwd"))
		{
			if (-1 == do_serv_pwd(sock_fd))
			{
				exit(1);
			}
		}
		else if (0 == strcasecmp(command.name, "!cd"))
		{
			if (-1 == do_serv_cd(command.argv[1], sock_fd))
			{
				exit(1);
			}
		}
		else if (0 == strcasecmp(command.name, "ls"))
		{
			if (-1 == do_ls(command.argv[1]))
			{
				exit(1);
			}
		}
		else if (0 == strcasecmp(command.name, "!ls"))
		{
			if (-1 == do_serv_ls(command.argv[1], sock_fd))
			{
				exit(1);
			}
		}
		else if (0 == strcasecmp(command.name, "connect"))
		{
			if (-1 == do_connect(command.argv[1], &sin, &sock_fd))
			{
				exit(1);
			}
		}
		else if (0 == strcasecmp(command.name, "bye"))
		{
			if (-1 == do_bye(sock_fd))
			{
				exit(1);
			}

			break;
		}
		else /* Wrong command */
		{
			printf("Wrong command\n");
			printf("Usage : command arg1, arg2, ..., argn\n");
		}

		printf("myftp$ : ");
		fflush(stdout);
	}

	if (-1 == close(sock_fd))
	{
		perror("fail to close");
		exit(1);
	}

	return 0;
}
