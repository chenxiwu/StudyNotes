#!/bin/bash

path="/etc/rc.d/rc.local"
[ -x $path ] || echo $path"不可执行"

path="/etc/vimrc"
[ -x $path ] || echo $path"不可执行"
