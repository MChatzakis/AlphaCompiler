//DONE
x = y = 1; //new variables x, y
{ 
    x = 2; //ok, refers to global x 
    a = 3; //new var a in scope 1 
    function f (z) { 
        x = 4; //ok, refers to global x
        a = 5; //error: cannot access a in scope 1 
        y = 6; //ok, refers to global y 
        { 
            z = 7; //ok, refers to formal 
            function g() { return z; }  //error: cannot access z 
        } 
    }
} 