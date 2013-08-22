#!/bin/bash

if [ ! $1 ]; then
	echo "Supply the package name as the argument!"
	exit 1
fi

if [ $2 ]; then
	echo "Spawn only accepts one argument at a time!"
	exit 1
fi

elinks http://duckduckgo.com/?q=%5C$1
