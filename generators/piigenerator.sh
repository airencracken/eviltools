#!/bin/bash
y=="y"
n=="n"
echo "Path to list of usernames?"
read userpath
echo "Credit card data? (y/n)"
read ccdata
echo "Passwords? (y/n)"
read passdata
if [ "$passdata" == "y" ];
then
	echo "Do you have a current password csv?"
	read csvexist
	if [ "$csvexist" == "n" ];
	then
		echo "Should I generate and apply new passwords? (y/n)"
		read makepass
		if [ "$makepass" == "y" ];
		then
			echo "Would you like to supply a password for all users? (alternative is randomly generated for each) (y/n)"
			read generate
			if [ "$generate" == "n" ];
			then
				if [ "$ccdata" == "n" ];
				then
					for i in `cat $userpath`; do for j in `tr -dc [:alnum:] < /dev/urandom | head -c 20`; do yes $j | passwd $i; echo -e "$i,$j" >> userpass.csv; done; done
					echo "New users and passwords generated and put in userpass.csv"

				elif [ "$ccdata" == "y" ];
				then
					echo "Generating usernames, passwords, and credit card numbers"	
					for i in `cat $userpath`; do for j in `tr -dc [:alnum:] < /dev/urandom | head -c 20`; do for k in `tr -dc 0-9 < /dev/urandom | head -c 16`; do yes $j | passwd $i; echo -e "$i,$j,$k" >> userpass.csv; done; done; done
				else
					echo "Don't know if you want credit card numbers. Try again."
				fi	
			elif [ "$generate" == "y" ]
			then
				echo "What password do you want on all users?"
				read j
				if [ "$ccdata" == "y" ];
				then
						for i in `cat $userpath`; do for k in `tr -dc 0-9 < /dev/urandom | head -c 16`; do yes $j | passwd $i; echo -e "$i,$j,$k" >> userpass.csv; done; done
				elif [ "$ccdata" == "n" ];
				then
					for i in `cat $userpath`; do yes $j | passwd $i; echo -e "$i,$j" >> userpass.csv; done
				else 
					echo "Don't know if you want credit card numbers. Try again."
					exit 0
				fi
			fi
		else
			echo "Fail on your part. Learn what you want."
		fi
	elif [ "$csvexist" == "y" ];
	then
		echo "Path to csv of username,pass?"
		read csvpath
		cp $csvpath /tmp/usercsv.csv
		if [ "$ccdata" == "y" ];
		then
			echo "Username, Password, Credit Card Number" >> userpasscc.csv
			for i in `sed -e "s/,.*$//g" /tmp/usercsv.csv`; do for j in `sed -e "s/^.*,//g" /tmp/usercsv.csv | egrep -m 1 [0-9,A-Z,a-z]`;do for k in `tr -dc 0-9 </dev/urandom | head -c 20`; do echo -e "$i,$j,$k" >> userpasscc.csv  ; sed -ie "s/$i,$j//" /tmp/usercsv.csv; done; done;done
		elif [ "$ccdata" == "n" ]; 
		then
			echo "You already have the CSV, there's nothing more I can do to it if you don't want CC data!"
		else
			echo "fail at typing on CC data"
		fi
	else
		echo "Lern2type"
	fi	
elif [ "$passdata" == "n" ];
then
	if [ "$ccdata" == "y" ];
	then
		echo "Generating CC data as a CSV for the users"
		echo "Username,Credit Credit Number" > ccdata.csv
		for i in `cat $userpath`; do for j in `tr -dc 0-9 < /dev/urandom | head -c 16`; do echo -e "$i,$j" >> ccdata.csv; done; done
	elif ["$ccdata" == "n" ];
	then
		echo "WHAT DO YOU WANT FROM ME?!"
	fi
else
	echo "WHAT DO YOU WANT FROM ME?!"
fi
exit 0
