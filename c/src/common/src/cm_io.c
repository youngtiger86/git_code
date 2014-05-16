/* iolib.c My own file I/O library. */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

ssize_t cm_read(int fd, void * buffer, size_t length)
{
	ssize_t done = length;

	while (done > 0)
	{
		done = read(fd, buffer, length);
		//if (done != length)
		if (done > length)
		{
			if (EINTR == errno)
			{
				done = length;
			}
			else
			{
				perror("fail to read");
				return -1;
			}
		}
		else
		{
			break;
		}
	}

	return done;
}

ssize_t cm_write(int fd, void * buffer, size_t length)
{
	ssize_t done = length;

	while (done > 0)
	{
		done = write(fd, buffer, length);

		if (done != length)
		{
			if (EINTR == errno)
			{
				done = length;
			}
			else
			{
				perror("fail to write");
				return -1;
			}
		}
		else
		{
			break;
		}
	}

	return done;
}
