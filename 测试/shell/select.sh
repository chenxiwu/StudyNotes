#!/bin/bash

echo "what is your favorite OS:"

select var in "Linux" "Windows" "MAC" "Other"; 
do
break;
done

echo "you select OS is $var!"

