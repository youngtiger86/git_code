#!/bin/bash
# Program:
#	Use id, finger command to check system account's information.
# History:
# 2013/10/23	tom	First release

users=$(cut -d ':' -f1 /etc/passwd)
for username in $users
do
	id $username
	finger $username
done
