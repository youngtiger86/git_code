#ifndef __CM_LOG_H__
#define __CM_LOG_H__

#define CM_MAX_LOG_MSG_LEN	512

#define CM_RUN_LOG(module_name, level, msg)	\
	log_write(LOG_TYPE_RUN, module_name, level, msg, __FILE__, __LINE__)

#define CM_DEBUG_LOG(module_name, level, msg)	\
	log_write(LOG_TYPE_DEBUG, module_name, level, msg, __FILE__, __LINE__)

#define CM_AUDIT_LOG(module_name, level, msg)	\
	log_write(LOG_TYPE_AUDIT, module_name, level, msg, __FILE__, __LINE__)

typedef enum taglog_type
{
	LOG_TYPE_RUN = 0,
	LOG_TYPE_DEBUG,
	LOG_TYPE_AUDIT
}log_type_e;

typedef enum taglog_level
{
	ERR = 0,
 	WARN,
	INFO	
}log_level_e;

/**********************************************************************************************************************
 Description: 
 Input: 
 Output: 
 Return value: 
 Note: 
 History: 
 1. Author: yangshangde
 Modification: 2014-- Create this function.
 **********************************************************************************************************************/
int log_init(char * app_name, char * log_root_path);

/**********************************************************************************************************************
 Description: 
 Input: 
 Output: 
 Return value: 
 Note: 
 History: 
 1. Author: yangshangde
 Modification: 2014-- Create this function.
 **********************************************************************************************************************/
int log_init_by_type(char * app_name, char * log_root_path, log_type_e log_type);

/**********************************************************************************************************************
 Description: 
 Input: 
 Output: 
 Return value: 
 Note: 
 History: 
 1. Author: yangshangde
 Modification: 2014-- Create this function.
 **********************************************************************************************************************/
int log_write(log_type_e log_type, char * module_name, log_level_e level, char * msg, ...);

/**********************************************************************************************************************
 Description: 
 Input: 
 Output: 
 Return value: 
 Note: 
 History: 
 1. Author: yangshangde
 Modification: 2014-- Create this function.
 **********************************************************************************************************************/

/**********************************************************************************************************************
 Description: 
 Input: 
 Output: 
 Return value: 
 Note: 
 History: 
 1. Author: yangshangde
 Modification: 2014-- Create this function.
 **********************************************************************************************************************/


/**********************************************************************************************************************
 Description: 
 Input: 
 Output: 
 Return value: 
 Note: 
 History: 
 1. Author: yangshangde
 Modification: 2014-- Create this function.
 **********************************************************************************************************************/
#endif /* __CM_LOG_H__ */

