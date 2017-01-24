#!/bin/bash

help() {
cat << HELP
titlebar -- change the name of an xterm

USAGE:
	titlebar [-h] "string_for_titlebar"
OPTION: 
	-h: help documents
EXAMPLE:
	titlebar "SY"
HELP

exit 0
}

if [[ $1 == '' || $1 == "help" ]]; then
	help
fi

echo "Change the titlebar to "$1!

