#include "common.h"
#include "cm_log.h"

int main(void)
{
	struct sockaddr_in sin, cin;
	socklen_t len = sizeof(cin);
	int lfd, cfd, fd;
	pid_t pid;
	int sock_opt = 1;
	char path[MAX_LINE];
	struct stat statbuf;
	char log_msg[CM_MAX_LOG_MSG_LEN];

	signal(SIGCHLD, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);

	if (-1 == log_init("webserver", get_current_dir_name()))
	{
		DEBUG_PRINT("Error during log init\n");
		exit(1);
	}

	CM_RUN_LOG("webserver", INFO, "Log initialization succeed.");

	if (-1 == init(&sin, &lfd, path))
	{
		DEBUG_PRINT("error during initialization\n");
		exit(1);
	}

	CM_RUN_LOG("webserver", INFO, "Webserver service initialization succeed."); 

	while (1)
	{
		DEBUG_PRINT ("waiting connection...\n");
		
		cfd = accept(lfd, (struct sockaddr *)&cin, &len);
		if (-1 == cfd)
		{
			perror("fail to accept");
			exit(1);
		}

		pid = fork();
		if (pid < 0)
		{
			perror("fail to fork");
			exit(1);
		}
		else if (0 == pid)
		{
			close(lfd);

			if (-1 == get_path(cfd, path))
			{
				DEBUG_PRINT ("error during geting filepath\n");
				exit(1);
			}

			if (stat("/home/tom/index.html", &statbuf) < 0)
			{
				perror("fail to get file status\n");
				exit(1);
			}

			if (!S_ISREG(statbuf.st_mode))
			{
				if (-1 == error_page(cfd))
				{
					DEBUG_PRINT("error during writing error-page\n");
					close(cfd);
					exit(1);
				}

				close(cfd);
				exit(0);
			}

			/* If it's a exutable file, execute it and send the result to client. */
			if (statbuf.st_mode & S_IXOTH)
			{
				dup2(cfd, STDOUT_FILENO);
				
				if (-1 == execl(path, path, NULL))
				{
					perror("fail to exec");
					exit(1);
				}
			}

			if ((fd = open(path, O_RDONLY)) < 0)
			{
				if (-1 == error_page(cfd))
				{
					DEBUG_PRINT("error during writing error-page\n");
					close(cfd);
					exit(1);
				}

				close(cfd);
				exit(0);
			}
							
			if (-1 == write_page(cfd, path, fd))
			{
				DEBUG_PRINT("error during writing page\n");
				exit(1);
			}

			close(fd);
			close(cfd);

			exit(0);
		}
		else
		{
			close(cfd);
		}
	}
	
	return 0;
}

