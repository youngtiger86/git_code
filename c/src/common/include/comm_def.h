#ifndef _COMM_DEF_H__
#define _COMM_DEF_H__

#include <assert.h>

#define TRUE                1
#define FALSE               0
#define MAX_PATH_LEN        256
#define MAX_CMD_LEN         256
#define MAX_FILE_LINE_LEN   256
#define MAX_MSG_LEN			1024
#define IP_ADDR_LEN         17
#define MAX_NAME_LEN        256

#define SERVER_SERVICE_PORT 8000

typedef enum tagcmd_type
{
    CMD_TYPE_UNKNOWN = 0,
    CMD_TYPE_PUT,
    CMD_TYPE_GET,
    CMD_TYPE_CD,
    CMD_TYPE_LS,
    CMD_TYPE_BYE
}cmd_type_e;

typedef struct tagcmd_info
{
    cmd_type_e type;
    //unsigned int add_info_len;
}cmd_info_t;

#if 0
#define CM_POINTER(ptr)\
{ \
    if (NULL == ptr) \
    { \
#ifdef DEBUG_VERSION \
        assert(0); \
#else \
        exit(1); \
#endif \
    } \
}

#define CM_POINTER2(ptr1, ptr2) \
    if ((NULL == (ptr1)) || (NULL == (ptr2))) \
    { \
#ifdef DEBUG_VERSION \
        assert(0); \
#else \
        exit(1); \
#endif \
    }
#endif

#endif /* _COMM_DEF_H__ */
