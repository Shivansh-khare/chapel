use Spawn;

var sub = spawnshell("cat 1>&2", stdin=PIPE, stdout=FORWARD, stderr=PIPE);

config const n = 10000;
for i in 1..n {
  writeln("writing line: ", i);
  sub.stdin.writeln(i);
}

sub.communicate();

var i = 1;
var x:int;
while sub.stderr.read(x) {
  if x != i then
    writeln("got stderr ", x, " expected ", i);
  assert(x == i);
  i += 1;
}

assert(sub.running == false);
assert(sub.exit_status == 0);

writeln("OK");

