#!/usr/bin/perl
 
use warnings;
use strict;
  
use File::Basename;
   
$ENV{PATH} = "/bin:/sbin:/usr/bin:/usr/sbin";
    
my $magic = "please";
print "Say the magic word:\n";
while(<STDIN>) {
  chomp;
  last if $. >= 3;
  $_ eq $magic and exec(basename($0), @ARGV);
  print "WRONG\n";
}
print "Go away\n";
