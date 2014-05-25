#!/bin/sh

func_comm_template="
/**********************************************************************************************************************\n
Description:    \n
Input:          \n 
Output:         \n
Return value:   \n
Note:           \n
History:        \n 
1. Author:      yangshangde\n
   Modification: 2014-- Create this function.\n
**********************************************************************************************************************/\n"

file_name=$1
#echo ${func_comm_template}
echo ${func_comm_template} >> ${file_name}
