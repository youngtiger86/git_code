#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
	FILE * fp;

	fp = fopen("stdio.txt", "r");
	if (NULL == fp)
	{
		//perror("Fail to fopen");
		perror("");
		//printf("Failed to fopen. Error message: %s.\n", strerror(errno));
		return 1;
	}

	return 0;
}

