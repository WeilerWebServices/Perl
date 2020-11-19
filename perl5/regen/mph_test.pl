use strict;
use warnings;
use Test::More tests => 2;
my @res;@res=`./mph_test '/should-not-match' 'should-not-match/'`;
ok( $res[0] =~ /got: 0/,'proper prefix does not match');
ok( $res[1] =~ /got: 0/,'proper suffix does not match');
