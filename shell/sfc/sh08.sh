#!/bin/bash
# Program:
#	Program shows the effect of shift function.
# History:
# 2013/10/21	tom	First release

echo "Total parameter number is ==> $#"
echo "Your whole parameter is ==> '$@'"
shift 
echo "Total parameter number is ==> $#"
echo "Your whole parameter is ==> '$@'"
shift 3
echo "Total parameter number is ==> $#"
echo "Your whole parameter is ==> '$@'"
