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

#commence fuckery

cp /root/sources/etc_profile  /etc/profile
cp /root/sources/bash_profile /home/*/.bash_profile
cp /root/sources/bash_profile /root/.bash_profile

cp /root/sources/etc_environment /etc/environment
cp /root/sources/vimrc /root/.vimrc
cp /root/sources/vimrc /home/*/.vimrc
cp /root/sources/vimrc /etc/vimrc

cp /root/sources/wgetrc /etc/wgetrc
cp /root/sources/wgetrc /root/.wgetrc
cp /root/sources/wgetrc /home/*/.wgetrc

cp /root/sources/ld_so_conf /etc/ld.so.conf
