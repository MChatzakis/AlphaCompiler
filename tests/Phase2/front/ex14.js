//DONE
/*{   
    x = 5; // 1

    function g(){ //1
       function s(){}
    } //0

    function h(){ //1
        x = 4; //>0 sc 2
        {
            
        }
    }//0

    
}

1

{
    {
        y = 1; //1
        function x(){ //scope 2
            {
                function xx(){ //scope 4
                }

                y =2; //scope 4
            }
        }

    
    }
}   

y =1;
function x(){
}

{
    y
}

xx: 1
y: 2

if(size){
    if(top() < entry->scope){
        exw prosvasi
    }
    else{
        error
    }
}*/

{
    function y(){}
    x = 1;

    function y(){ //error
        x = 10000; //error
    }

    {
        x = 10;
    }
}

{
    function y(){}

    x = y();
}