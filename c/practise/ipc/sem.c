#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/sem.h>

int main()
{
	key_t key;
	int sem;

	key = 1;
	sem = semget(key, 1, IPC_CREAT|IPC_EXCL);
	if (-1 == sem)
	{
		printf("Create semaphore failed. Error: %s.\n", strerror(errno));
		exit(1);
	}
	
	printf("Semaphore set identifier: %d\n.", sem);

	sleep(30);

	exit(0);
}
