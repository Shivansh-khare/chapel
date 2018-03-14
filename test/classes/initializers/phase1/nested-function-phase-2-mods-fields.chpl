// This test exercises the case where an initializer defines a function within
// itself (in a different phase than the one where it was called), but the
// function modifies a field.
class Foo {
  var field: int;

  proc init(val) {
    field = val;
    nested();
    this.initDone();

    // Where the function definition was placed shouldn't impact its viability,
    // but where it is called should.  This function modifies a field, doesn't
    // that mean that it shouldn't be callable during Phase 1?  How to detect
    // this?
    proc nested() {
      field = -field;
    }
  }
}

proc main() {
  var f = new Foo(13);
  writeln(f);
  delete f;
}
