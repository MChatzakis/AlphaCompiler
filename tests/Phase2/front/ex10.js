//DONE
x = 10;
function x(){} // error: var redefined as a function

function f(){} 
f = 10; // error: function used as an l-value

function f(y) { //error
    function g(x) { return x*y; } // error: var f::y not accessible in g
    return g(x); 
}

function g() { 
    function h() { return g(); } // ::g is visible in g::h
}

function f () { //error
    local f = 10; // f inside f is a new variable now
    function h () { 
        return f;// error, f::f (local) not accessible in h
        return ::f(); // ok, we access global ::f 
    }
}