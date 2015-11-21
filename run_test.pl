#!/usr/bin/perl -w
print "V3\n";
for (my $i = 100; $i <= 1000; $i += 100) {
  my $msg = `./main_statistics_v3.out -n $i -c 0.1 -s 1000 -r 2423433334`;
  print "$i\t$msg";
}

print "V2\n";
for (my $i = 100; $i <= 1000; $i += 100) {
  my $msg = `./main_statistics_v2.out -n $i -c 0.1 -s 1000 -r 2423433334`;
  print "$i\t$msg";
}
