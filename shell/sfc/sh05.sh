#!/bin/bash
# Program:
#	User input a filename, program will check the following:
#   1）exist?	2)file/directory?	3)file permissions
# History:
# 2013/10/21	tom	First release

echo -e "Please input a filename, I will check the filename's type and permission. \n\n"
read -p "Input a filename: " filename
test -z $filename && echo "You MUST input a filename." && exit 0
test ! -e $filename && echo "The file '$filename' DOES NOT EXIST" && exit 0
test -f $filename && filetype='regulare file'
test -d $filename && filetype='directory'
test -r $filename && perm="readable"
test -w $filename && perm="$perm writable"
test -x $filename && perm="$perm executable"

echo "The filename: $filename is a $filetype"
echo "And the permissions are: $perm"
