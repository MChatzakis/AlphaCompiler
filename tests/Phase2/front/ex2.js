//DONE
x = input(); 
g = 12.4; 
print(typeof(x)); 
function foo(x, y) { 
    print(x + y); 
    local p = y; 
    ::print(p); 
    function h(a) { 
        return a + x + y; //error
    }  
    y = h(::x); 
} 
