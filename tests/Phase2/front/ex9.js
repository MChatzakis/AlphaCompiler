//DONE
input(x);
print(typeof(x));
::print(::typeof(::x));

function g(x,y) {
    print(x+y);
    local print = y; //error
    ::print(print);
    function h() {
        return x+y; //error
    }
    return h;
}

add = (function(x,y){return x+y; });

{ 
 local x = ::x; 
 local f = (function(){return x; }); //error
}

function f(a,b) 
{ local a = local b; }