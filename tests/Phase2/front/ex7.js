//DONE
function f() { // f in scope 0
  function f() {} // f in scope 1
  function f() {} //error: f exists
}
x = 1;
function x() {} //error: x is var
function sin() {} //error: func shadows libfunc
y(1, 2); //new variable y, not function y
