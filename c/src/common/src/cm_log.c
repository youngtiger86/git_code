#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdarg.h>
#include "comm_def.h"
#include "cm_log.h"

#define CM_RUN_LOG_IDX		0 
#define CM_DEBUG_LOG_IDX 	1
#define CM_AUDIT_LOG_IDX 	2	

int g_log_file_fds[3] = {0};

int log_init(char * app_name, char * log_root_path)
{
	/* check if the target log files exist, if yes, just open them. Otherwise, create and open them. */
	/* 需要检查缓冲区溢出问题 */
	int ret;
	int fd;
	char full_path[MAX_PATH_LEN];
	int path_mode = S_IRUSR | S_IWUSR | S_IXUSR;

	snprintf(full_path, MAX_PATH_LEN, "%s/r%s", log_root_path, app_name);
	if (-1 == access(full_path, F_OK))
	{
		if (-1 == mkdir(full_path, path_mode))
		{
			perror("Failed to create log path.\n");
			return -1;
		}

		strcat(full_path, "/r");
		strcat(full_path, app_name);
		strcat(full_path, ".log");
		fd = open(full_path, O_WRONLY | O_CREAT, 777);
		if (-1 == fd)
		{
			printf("Failed to create log file: %s\n", full_path);
			return -1;
		}

		g_log_file_fds[CM_RUN_LOG_IDX] = fd;
	}

	snprintf(full_path, MAX_PATH_LEN, "%s/d%s", log_root_path, app_name);
	if (-1 == access(full_path, F_OK))
	{
		if (-1 == mkdir(full_path, path_mode))
		{
			perror("Failed to create log path.\n");
			return -1;
		}

		strcat(full_path, "/d");
		strcat(full_path, app_name);
		strcat(full_path, ".log");
		fd = open(full_path, O_WRONLY | O_CREAT, 700);
		if (-1 == fd)
		{
			printf("Failed to create log file: %s\n", full_path);
			return -1;
		}

		g_log_file_fds[CM_DEBUG_LOG_IDX] = fd;
	}

	snprintf(full_path, MAX_PATH_LEN, "%s/a%s", log_root_path, app_name);
	if (-1 == access(full_path, F_OK))
	{
		if (-1 == mkdir(full_path, path_mode))
		{
			perror("Failed to create log path.\n");
			return -1;
		}

		strcat(full_path, "/a");
		strcat(full_path, app_name);
		strcat(full_path, ".log");
		fd = open(full_path, O_WRONLY | O_CREAT, 700);
		if (-1 == fd)
		{
			printf("Failed to create log file: %s\n", full_path);
			return -1;
		}

		g_log_file_fds[CM_AUDIT_LOG_IDX] = fd;
	}

	return 0;
}

int log_init_by_type(char * app_name, char * log_root_path, log_type_e log_type)
{
	return 0;
}


int log_write(char * module_name, log_level_e level, char * msg, ...)
{
	char log_msg[CM_MAX_LOG_MSG_LEN];
	time_t curr_time;
	struct tm * loc_time;
	va_list arg_list;
	char * func_name;
	int line_no;

	if (-1 == (curr_time = time(NULL)))
	{
		perror("Failed to get current time.");
		return -1;
	}

	va_start(arg_list, msg);
	func_name = va_arg(arg_list, char *);
	line_no = (int)va_arg(arg_list, int);

	loc_time = localtime(&curr_time);
	printf("%s", asctime(loc_time));
	strftime(log_msg, CM_MAX_LOG_MSG_LEN, "[ %Y/%m/%d %H:%M:%S ]", loc_time);
	snprintf(log_msg + strlen(log_msg), CM_MAX_LOG_MSG_LEN - strlen(log_msg), " %d %s %s %s:%d\n", level, module_name, msg, func_name, line_no);
	va_end(arg_list);
	if (ERR == level)
	{
		if (-1 == write(g_log_file_fds[CM_RUN_LOG_IDX], log_msg, strlen(log_msg)))
		{
			printf("write log file failed.\n");
			return -1;
		}
	}

	return 0;
}

