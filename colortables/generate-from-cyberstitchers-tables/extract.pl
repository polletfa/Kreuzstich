#!/usr/bin/perl

use strict;
use warnings;

my $prefix = shift;
if(!defined $prefix) {
    print "Usage: $0 prefix < in > out\n";
    exit;
}
        
my $startFound = 0;
my $nameFound = 0;
my $name;
my $previousName = "";
my $previousColor = "";

while(<>) {
    if(/^<tr>$/) {
        $startFound = 1;
    } elsif($startFound && !$nameFound && /^\s*([a-zA-Z0-9_]+)\s*$/) {
        $nameFound = 1;
        $name = $1;
    } elsif($nameFound && /background-color:#?([0-9a-fA-F]{6});.*<\/span>\s*(.*)\s*/) {
        if(!(lc $previousName eq lc $name && lc $1 eq lc $previousColor)) {
            print $prefix." ".$name.":".$1."     # ".$2."\n";
            $startFound = $nameFound = 0;
            $previousName = $name;
            $name = "";
            $previousColor = $1;
        } else {
            # else: identical to previous entry. ignore
            print STDERR "Warning: Identical entries (".$name.":".$1.")\n";
            $startFound = $nameFound = 0;
        }
    } elsif($startFound && /^<\/tr>$/) {
        print STDERR "Warning: no color found for ".$name.". Ignored.\n";
        $startFound = 0;
        $previousName = "";
        $previousColor = "";
        $name = "";
        $nameFound = 0;
    }
            
}

exit 0;
