#!/usr/bin/perl -w
print "V1\n";
for (my $i = 100; $i <= 1000; $i += 100) {
  my $tot = 0;
  for my $j (1..5){
    my $msg = `./main_statistics_v1.out -n $i -c 0.1 -s 5000 -r 242345555434`;
    $tot += $msg;
    #print "$i\t$msg";
  }
  $tot = $tot/5;
  print "$i\t$tot\n";
}
