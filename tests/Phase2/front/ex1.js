//DONE
x = input(); 
function g(x, y) { 
    local z = x + y; 
    print(z); 
    return(function f(a, b) { 
        return a + b; 
    }); 
} 