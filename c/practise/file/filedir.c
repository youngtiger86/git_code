#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	char path[256];
#if 0
	// Change the permission of test.txt.
	if (-1 == chmod("test.txt", S_IROTH | S_IWOTH | S_IXOTH | S_IRUSR))
	{
		perror("Fail to chmmod");
		exit(1);
	}

	printf("Create a link for file test.txt using link.\n");
	if (-1 == link("test.txt", "test.txt.link"))
	{
		perror("Fail to link");
		exit(1);
	}

	printf("Create a link for file test.txt using syslink.\n");
	if (-1 == symlink("test.txt", "test.txt.syslink"))
	{
		perror("Fail to syslink");
		exit(1);
	}

	printf("New create a directory names ysd. Its permission should be 700.\n");
	if (-1 == mkdir("ysd", S_IRUSR | S_IWUSR | S_IXUSR | S_IWOTH))
	{
		perror("Fail to mkdir");
		exit(1);
	}

	printf("Now remove directory ysd.\n");
	if (-1 == rmdir("ysd"))
	{
		perror("Fail to rmdir");
		exit(1);
	}	

	printf("Now");
#endif

	if (NULL == getcwd(path, 256))
	{
		perror("Fail to getcwd");
		exit(1);
	}

	printf("cwd is: %s\n", path);
	system("ls -lrt");

	if (-1 == chdir("/home/tom"))
	{
		perror("Fail to chdir");
		exit(1);
	}

	if (NULL == getcwd(path, 256))
	{
		perror("Fail to getcwd");
		exit(1);
	}

	printf("cwd is: %s\n", path);
	system("ls -lrt");

	exit(0);
}

