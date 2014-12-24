#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <errno.h>
#include <string.h>

#include "semun.h"

static int set_semvalue(void);
static int del_semvalue(void);
static int sem_p(void);
static int sem_v(void);

static int sem_id;

int main(int argc, char *argv[])
{
	int i;
	char op_char = 'O';
	int pause_time;

	srand(getpid());

	sem_id = semget((key_t)123, 1, 0666 | IPC_CREAT); 
	if (-1 == sem_id)
	{
		perror("Failed to create semaphore. ");
		printf("Error: %s\n", strerror(errno));
		exit(1);
	}

	if (argc > 1)
	{
		if (!set_semvalue())
		{
			fprintf(stderr, "Failed to initialize semaphore.\n");
			exit(EXIT_FAILURE);
		}

		op_char = 'X';
		sleep(2);
	}

	for (i = 0; i < 10; ++i)
	{
		if (!sem_p())
		{
			exit(EXIT_FAILURE);
		}

		printf("%c", op_char);
		fflush(stdout);
		pause_time = rand() % 3;
		sleep(pause_time);
		printf("%c", op_char);
		fflush(stdout);
		
		if (!sem_v())
		{
			exit(EXIT_FAILURE);
		}

		pause_time = rand() % 2;
		sleep(pause_time);
	}

	printf("\n%d - finished\n", getpid());

	if (argc > 1)
	{
		sleep(10);
		del_semvalue();
	}

	exit(EXIT_SUCCESS);
}

static int set_semvalue()
{
	union semun sem_union;

	sem_union.val = 1;

	if (-1 == semctl(sem_id, 0, SETVAL, sem_union))
	{
		fprintf(stderr, "set_semvalue failed. Error: %s\n", strerror(errno));
		return 0;
	}

	return 1;
}

static int del_semvalue()
{
	union semun sem_union;

	if (-1 == semctl(sem_id, 0, IPC_RMID, sem_union))
	{
		fprintf(stderr, "del_semvalue failed. Error: %s\n", strerror(errno));
		return 0;
	}

	return 1;
}

static int sem_p()
{
	struct sembuf sem_buf;

	sem_buf.sem_num = 0;
	sem_buf.sem_op = -1;
	sem_buf.sem_flg = SEM_UNDO;
	if (-1 == semop(sem_id, &sem_buf, 1))
	{
		fprintf(stderr, "%s%s", "sem_p failed\n", strerror(errno));
		return 0;
	}

	return 1;
}

static int sem_v()
{
	struct sembuf sem_buf;
	
	sem_buf.sem_num = 0;
	sem_buf.sem_op = 1;
	sem_buf.sem_flg = SEM_UNDO;
	if (-1 == semop(sem_id, &sem_buf, 1))
	{
		fprintf(stderr, "sem_v failed\n");
		return 0;
	}

	return 1;
}

