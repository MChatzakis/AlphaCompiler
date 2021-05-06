
function v(y) {
    function c(x) { 
        return x*y; 
        } // error: var f::y not accessible in g

    return c();    
}

v = 2;

function f() {
    function h() { return v(); } // ::v is visible in f::h
}


local x;
function x(){};

function y(){};
local y;

local z;
{
    local z;
}

local v;
{
    function v(){};
}

function b(){}
{
    local b;
}

function n(){};
n = 4;

function m(){
    m; // 
}

local a;
{
    a = 2; 
}

local s;
s = 2;
