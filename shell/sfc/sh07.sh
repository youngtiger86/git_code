#!/bin/bash
# Program:
#	Program show the script name, parameters...
# History:
# 2013/10/21	tom	First release

echo "The script name is ==> $0"
echo "Total parameter number is ==> $#"
[ "$#" -lt "2" ] && echo "The number of parameters is less than 2. Stop here." && exit 0
echo "Your whole parameter is(use '\$@') ==> $@"
echo "Your whole parameter is(use '\$*') ==> $*"
echo "The first parameter is ==> $1"
echo "The second parameter is ==> $2"
