#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

int exec_mmap()
{
	int fd;
	char * buf;
	struct stat stat_buf;

	if (-1 == stat("hello", &stat_buf))
	{
		perror("Fail to stat.\n");
		return -1;
	}

	fd = open("hello", O_RDONLY);
	if (-1 == fd)
	{
		perror("Fail to open file hello.\n");
		return -1;
	}

	buf = (char *)mmap(NULL, stat_buf.st_size, PROT_EXEC, MAP_PRIVATE, fd, 0);
	if (MAP_FAILED == buf)
	{
		perror("Fail to mmap.\n");
		close(fd);
		return -1;
	}

	system(buf);

	if (-1 == munmap(buf, stat_buf.st_size))
	{
		perror("Fail to munmap.\n");
		close(fd);
		return -1;
	}

	close(fd);

	return 0;
}

int unmap_shared_mmap(int fd, size_t size)
{
	char * buf;

	printf("Now mapping test.txt in MAP_SHARE mode.\n");
	buf = (char *)mmap(NULL, size, PROT_WRITE, MAP_SHARED, fd, 0);
	if (MAP_FAILED == buf)
	{
		perror("Fail to mmap.\n");
		return -1;
	}

	printf("Noew change the memory mapping.\n");
	strcpy(buf, "THis should not be in the file on the disk.\n");

	printf("Now unmap.\n");
	if (-1 == munmap(buf, size))
	{
		perror("Fail to munmap.\n");
		return -1;
	}

	printf("Now please check the file. Change should be there.\n");

	return 0;
}

int unmap_private_mmap(int fd, size_t size)
{
	char * buf;

	printf("Now mapping test.txt in MAP_PRIVATE mode.\n");
	buf = (char *)mmap(NULL, size, PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (MAP_FAILED == buf)
	{
		perror("Fail to mmap.\n");
		return -1;
	}

	printf("Noew change the memory mapping.\n");
	strcpy(buf, "THis should not be in the file on the disk.\n");

	printf("Now unmap.\n");
	if (-1 == munmap(buf, size))
	{
		perror("Fail to munmap.\n");
		return -1;
	}

	printf("Now please check the file. No change should be there.\n");

	return 0;
}

int main()
{
	int fd;
	char * buf;
	int i;
	struct stat stat_buf;

	exec_mmap();

	if (-1 == stat("test.txt", &stat_buf))
	{
		perror("Failed to stat.\n");
		exit(1);
	}

	fd = open("test.txt", O_RDWR);
	if (-1 == fd)
	{
		perror("Failed to open.\n");
		exit(1);
	}

	//unmap_private_mmap(fd, stat_buf.st_size);
	unmap_shared_mmap(fd, stat_buf.st_size);


#if 0
	//buf = (char *)mmap(NULL, stat_buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	buf = (char *)mmap(NULL, stat_buf.st_size, PROT_NONE, MAP_PRIVATE, fd, 0);
	if (MAP_FAILED == buf)
	{
		perror("Failed to mmap.\n");
		exit(1); 
	}

	i = 0;
	while (i < stat_buf.st_size)
	{
		//printf("%c", buf[i]);
		i++;
	}

	printf("\n");

	printf("Now try to modify the memory map. Error should be reported...\n");
	//buf[0] = 'a';

	if (-1 == munmap(buf, stat_buf.st_size))
	{
		perror("Failed to munmap.\n");
		exit(1);
	}
#endif
	close(fd);

	return 0;
}
