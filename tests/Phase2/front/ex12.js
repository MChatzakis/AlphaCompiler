//DONE
x = 5;

function foo(){
   ::x = 3;
   function g(){
       x = 9;
    }
}
