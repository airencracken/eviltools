#!/bin/bash
##In order for this script to work you should have a list of users into a list of users. Usernames must be 1 word seperated by spaces or newlines.
echo "Path to list of usernames, seperated by spaces or newlines. Must be 1 word each. Can't have multi word usernames."
read userpath
dd if=$userpath of=/tmp/usernames conv=lcase
echo "Create home directories? (y/n)"
read homecreate
echo "Create password? (y/n)"
read passcreate
if [ $passcreate == "y" ];
then
	echo "Password for all users?"
	read mainpass
	if [ $homecreate == "y" ];
	then
		for i in `cat /tmp/usernames`; do useradd -m -p $mainpass $i; done
		echo "Users created"
	elif [ $homecreate == "n" ];
	then
		for i in `cat /tmp/usernames`; do useradd -M -p $mainpass $i; done
		echo "Users created"
	else
		echo "Learn to answer questions the way they're asked"

	fi

elif [ $passcreate == "n" ];
	echo "Creating users"
	if [ $homecreate == "y" ];
	then
		for i in `cat /tmp/usernames`; do useradd -m $i; done
		echo "Users created"
	elif [ $homecreate == "n" ];
	then
		for i in `cat /tmp/usernames`; do useradd -M $i; done
		echo "Users created"
	else
		echo "Learn to answer questions the way they're asked"
	fi
else
		echo "Learn to answer questions the way they're asked"
fi
		
