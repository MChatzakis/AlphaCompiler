//DONE
/*function f(y) { 
    function g(x) { return x*y; } // error: var f::y not accessible in g
    return g(x); 
}
{
    g(x);
}
{ { {g(a);}} }*/
/*
function f () {
    local f = 10; // f inside f is a new variable now
    function h () { 
        return f;// error, f::f (local) not accessible in h
        return ::f(); // ok, we access global ::f 
    }
}
 */
/*
function g() { 
    function h() { return g(); } // ::g is visible in g::h
}*/
/*
{ 
    y = 1;
    function ex (a) {
     y = 3; // error variable y in line 2 is not accessible in function ex
    }
   }*/
/*
   { 
    y = 1;
     function ex (a) {
      local y = 3; // define new local variable in scope 2 in line 4 
    }
   }*/
/*
   { 
    y = 1;
    function ex (a) {
     ::y = 3; // error, undefined global variable y in line 4 
    }
   }*/

   x = 5;
  function foo(){
     ::x = 3;
     function g(){
         x = 9;
     }
  }