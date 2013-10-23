#!/bin/bash
# Program:
#	User input dir name, I find the permission of files.
# History:
# 2013/10/23	tom	First release

read -p "Please input a directory:" dir
if [ "$dir" == "" -o ! -d "$dir" ];then
	echo "The directory $dir does not exist in your system!"
	exit 1
fi

filelist=$(ls  $dir)
for filename in $filelist
do
	perm=""
	test -r "$dir/$filename" && perm="$perm readable"
	test -w "$dir/$filename" && perm="$perm writable"
	test -x "$dir/$filename" && perm="$perm executable"
	echo "The file $dir/$filenme's permission is $perm"
done
