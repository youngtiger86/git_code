#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void * thread_func(void * message)
{
	printf("Thread function is running. The message is %s.\n", (char *)message);
	sleep(3);

	//strncpy(message, "Bye", strlen("Bye") + 1);
	strcpy(message, "Bye");
	pthread_exit("Thanks for the CPU time.");
}

int main()
{
	int ret;
	pthread_t tid;
	void * thread_result;
	char message[128] = "Hello, world!"; 

    ret = pthread_create(&tid, NULL, thread_func, (void *)message);
	if (0 != ret)
	{
		perror("Thread creation failed.");
		exit(EXIT_FAILURE);
	}

	ret = pthread_join(tid, &thread_result);
   	if (0 != ret)
	{
		perror("Thread join failed.");
		exit(EXIT_FAILURE);
	}	

	printf("Thread joined. It returned %s.\n", (char *)thread_result);
	printf("Now the message is %s.\n", message);

	exit(EXIT_SUCCESS);
}

