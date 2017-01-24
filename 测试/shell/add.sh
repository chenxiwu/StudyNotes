#!/bin/bash

val1=2
val1+=1
echo $val1

#算数运算需要添加 (())
val1=2
((val1+=1))
echo $val1
