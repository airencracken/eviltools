#!/bin/bash

if [ -z $1 ];then
	echo "Needs a team number!"
fi

team=$1
ethfile="/etc/sysconfig/ifconfig.eth0"
resolv="/etc/resolv.conf"
hosts="/etc/hosts"

#change interface
sed -i "s/10.10.0.1/10.10.$team.1/" $ethfile
sed -i "s/10.10.0.69/10.10.$team.69/" $ethfile
sed -i "s/10.10.0.255/10.10.$team.255/" $ethfile

#change dns
sed -i "s/10.10.0.211/10.10.$team.211" $resolv
sed -i "s/192.168.0.211/192.168.$team.211" $resolv

#change hosts
sed -i "s/10.10.0.69/10.10.$team.69" $hosts
