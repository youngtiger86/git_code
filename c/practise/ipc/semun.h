#ifndef __SEMUN_H__
#define __SEMUN_H__

#include <sys/sem.h>

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

#endif /* __SEMUN_H__ */
