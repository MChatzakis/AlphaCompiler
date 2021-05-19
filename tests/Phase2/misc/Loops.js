//DONE
while(1){
    function (){
        break; //error!
    }
}

for(i=0; i<N; i++){

    break;
    continue;

    return; //error
}

while(y<100){
    function g(){
        return 10;
    }

    if(g() < 12){
        break;
    }else{
        continue;
    }
}

break; //error
return; //error 
continue; //error

while(1){
    while(2) break;
    break;
    {
        {
            {
                function f(){
                    while(1) continue; break; //error
                }
            }
        }
    }
}
