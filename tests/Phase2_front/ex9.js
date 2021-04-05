input(x);
print(typeof(x));
::print(::typeof(::x));

function g(x,y) {
    print(x+y);
    local print = y;
    ::print(print);
    function h() {
        return x+y;
    }
    return h;
}

add = (function(x,y){return x+y; });

{ 
 local x = ::x; 
 local f = (function(){return x; });
}

function f(a,b) 
{ local a = local b; }