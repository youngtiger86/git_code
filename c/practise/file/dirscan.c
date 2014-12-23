#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printdir(char *dir, int depth)
{
	DIR *dp;

	struct dirent *entry;
	struct stat statbuf;
	
	/* Once enter this function, the dir is sure to be a directory. This is checked before invoking this function. */
	if ((dp = opendir(dir)) == NULL)
	{
		fprintf(stderr, "Can not open directory %s.\n", dir);
		return;
	}

	chdir(dir);

	while ((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode))
		{
			/* Found a directory, but ignore  and .. */
			if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
			{
				continue;
			}

			printf("%*s%s/\n", depth, "", entry->d_name);

			/* Recurse at a new indent level */
			/* Why plus depth with 4, not 1 ? */
			printdir(entry->d_name, depth + 4);
		}
		else
		{
			printf("%*s%s\n", depth, "", entry->d_name);
		}
	}

	chdir("..");
	closedir(dp);
}

int main(int argc, char **argv)
{
	if (2 != argc)
	{
		fprintf(stderr, "One parameter should be specified.\n");
		exit(1);
	}

	printf("Directory scan of %s.\n", argv[1]);
	printdir(argv[1], 0);
	printf("done.\n");

	exit(0);
}


