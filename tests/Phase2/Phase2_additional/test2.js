input(x); //Αυτόματη δήλωση global x, χρήση global input library function

read(a); //FIXME:error undefined func

a = input();

function foo(x) {
    local print = "hello"; //FIXME:error         
    print(x + y);          //FIXME:error ?? or define y?
    local hello = a;
    local hello = 35;
    function hello() {    // FIXME:error
        print(::a + ::x);  
    }
    function cos(){}// FIXME:error
}

function f() {}

local f; //ok, found locally

local print; //ok, found in scope 0
local y;    //new global var in scope 0
{
    local f; //new local var in scope 1
    local print; //FIXME:error: trying to
    //shadow libfunc
}
function g(a, b) { local a =  local b; }
x = y = 1; //new variables x, y
{
    x = 2; //ok, refers to global x
    h = 3; //new var a in scope 1
    function f (z) {
        x = 4; //ok, refers to global x
        h = 5; // FIXME: THIS REDECLARES FIXME:error: cannot access
        //h in scope 1
        y = 6; //ok, refers to global y
        {
            z = 7; //ok, refers to formal
            function g() { return z; }
                        //FIXME:error: cannot access z
        }
    }
}

function j() { // j in scope 0
    function j() {}// j in scope 1
    function j() {}//FIXME:error: j exists
}

k = 1;

function k() {} //FIXME:error:  k is var

function sin() {}; //FIXME:error: func shadows libfunc

//l(1, 2); //new variable y, not
 //function y

function p(x, y, z) {}
//ok, f with formals x, y, z
function o(x, y, x) {}  //FIXME:error:
                       //formal redeclaration
function i(x, cos) {} //FIXME:error:
                     //formal shadows libfunc 

print(typeof(r));   //define r

::print(::typeof(::r)); //use r

function w(x,y) {  // fine
    print(x+y);   // fine
    local print = y; //FIXME:error: trying to shadow libfunc
    ::print(print);
    function q() {
        return x+y;
    }
    return q;
}

add = (function(x,y){return x+y; });

{
    local x = ::x;
    x++;
    local s = (function(){return x; });
}

function f(a,b){ 
    local a = local b; 
}
