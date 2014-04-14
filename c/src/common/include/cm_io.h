#ifndef __CM_IO_H__
#define __CM_IO_H__
#include <sys/types.h>

ssize_t cm_read(int fd, void * buffer, size_t length);
ssize_t cm_write(int fd, void * buffer, size_t lenght);

#endif /* __CM_IO_H__ */
