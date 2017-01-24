#!/bin/bash

if [ $# -lt 2 ]; then
cat << HELP
you have to input one parameter!
FORMATE: ./help para1 para2
HELP

exit 0

else
echo "输入正确！ Bye"
fi
