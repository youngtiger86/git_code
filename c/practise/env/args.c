#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG '-'

int main(int argc, char *argv[])
{
	int arg;

	for (arg = 0; arg < argc; ++arg)
	{
		if (OPTION_FLAG == argv[arg][0])
		{
			printf("Option: %s\n", argv[arg] + 1);
		}
		else
		{
			printf("Argument %d: %s\n", arg, argv[arg]);
		}	
	}

	exit(0);
}
