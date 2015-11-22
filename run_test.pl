#!/usr/bin/perl -w
print "V2\n";
for (my $i = 100; $i <= 1000; $i += 100) {
  my $tot = 0;
  for my $j (1..5){
    my $msg = `./main_statistics_v2.out -n $i -c 0.1 -s 10000 -r 242345555434`;
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
    my $msg = `./main_statistics_v3.out -n $i -c 0.1 -s 10000 -r 242345555434`;
    $tot += $msg;
    #print "$i\t$msg";
  }
  $tot = $tot/5;
  print "$i\t$tot\n";
}
