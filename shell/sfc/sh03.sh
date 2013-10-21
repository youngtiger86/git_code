#!/bin/bash
# Program:
#	Program creates three files, which named by user's input and date command.
# History:
# 2013/10/21	tom	First release

echo -e "I will use 'touch' to create three files."
read -p "Please input your filename: " filename

filename=${filename:-"filename"}

date1=$(date --date='2 days ago' +%Y%m%d)
date2=$(date --date='1 days ago' +%Y%m%d)
date3=$(date +%Y%m%d)
file1=${filename}${date1}
file2=${filename}${date2}
file3=${filename}${date3}

touch "${file1}"
touch "${file2}"
touch "${file3}"
