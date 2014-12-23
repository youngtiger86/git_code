#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
	FILE * fp;

	perror("123");
	fp = fopen("notthere", "r");	
	printf("%s\n", strerror(errno));
	printf("%s\n", strerror(EISDIR));
	printf("%s\n", strerror(EIO));
	exit(0);
}

