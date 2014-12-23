#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int opt;

	while ((opt = getopt(argc, argv, ": if:lr")) != -1)
	{
		switch (opt)
		{
			case 'i':
			case 'l':
			case 'r':
				printf("option: %c\n", opt);
				break;
			case 'f':
				printf("Filename: %s\n", optarg);
				break;
			case ':':
				printf("option needs a value.\n");
				break;
			case '?':
				printf("Unknown option: %c\n", optopt);
				break;
		}
	}

	for (; optind < argc; optind++)
	{
		printf("argument: %s\n", argv[optind]);
	}

	exit(0);
}
