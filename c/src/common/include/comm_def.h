#ifndef _COMM_DEF_H__
#define _COMM_DEF_H__

#define MAX_PATH_LEN        256
#define MAX_CMD_LEN         256
#define MAX_FILE_LINE_LEN   256
#define MAX_MSG_LEN			1024
#define IP_ADDR_LEN         17
#define MAX_NAME_LEN        256

typedef enum tagcmd_type
{
    CMD_TYPE_UNKNOWN = 0,
    CMD_TYPE_PUT,
    CMD_TYPE_GET,
    CMD_TYPE_CD,
    CMD_TYPE_LS
}cmd_type_e;

typedef struct tagcmd_info
{
    cmd_type_e type;
    //unsigned int add_info_len;
}cmd_info_t;

#endif /* _COMM_DEF_H__ */
