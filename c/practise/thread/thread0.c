#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void * thread_func(void * arg)
{
	int i;
	int job_id;

	job_id = *(int *)arg;

	for (i = 0; i < 100; ++i)
	{
		printf("I'm job %d.\n", job_id);
		sleep(1);
	}

	printf("Job %d: work finish. Exist now.\n", job_id);

	pthread_exit(0);
}

int main()
{
#define THREAD_NUM 2
	int i;
	int j;
	int ret;
	pthread_t tids[THREAD_NUM];

#if 0
	for (i = 0; i < THREAD_NUM; ++i)
	{
		ret = pthread_create(&tids[i], NULL, thread_func, &i);
		if (0 != ret)
		{
			exit(ret);
		}
	}
#endif 
	i = 0;
		ret = pthread_create(&tids[0], NULL, thread_func, &i);
		if (0 != ret)
		{
			exit(ret);
		}

		//i = 1;
		j = 1;
		ret = pthread_create(&tids[1], NULL, thread_func, &j);
		if (0 != ret)
		{
			exit(ret);
		}

	for (i = 0; i < THREAD_NUM; ++i)
	{
		ret = pthread_join(tids[i], NULL);
		if (0 != ret)
		{
			exit(ret);
		}
	}

	exit(0);
}
