#!/usr/bin/perl -w
use File::Basename;
my $dirname = dirname(__FILE__);

print "V2\n";
for (my $i = 100; $i <= 1000; $i += 100) {
  my $tot = 0;
  for my $j (1..5){
    my $msg = `$dirname/PingPongProtocol_v2 -n $i -p 0.1 -s 5000 -r 242345555434`;
    $tot += $msg;
    #print "$i\t$msg";
  }
  $tot = $tot/5;
  print "$i\t$tot\n";
}

print "V3\n";
for (my $i = 100; $i <= 1000; $i += 100) {
  my $tot = 0;
  for my $j (1..5){
    my $msg = `$dirname/PingPongProtocol_v3 -n $i -p 0.1 -s 5000 -r 242345555434`;
    $tot += $msg;
    #print "$i\t$msg";
  }
  $tot = $tot/5;
  print "$i\t$tot\n";
}
