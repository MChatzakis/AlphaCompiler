//csd ok

function f(){
       local f=10;
       function g(){
               
               f=5;            //Error : Cannot access 'f' inside function 'g'
               return f();     //Error : Cannot access 'f' inside function 'g' autod en paizei
       }
}
