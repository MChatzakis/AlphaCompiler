//DONE

function G(){
       function F(){
                       return G();  
       }
}
return G();	//Use of 'return' while not in a function
break;		//Use of 'break' while not in a loop
continue;	//Use of 'continue' while not in a loop
// Break / Continue / Return in scope != 0
{
	{
		{
			return G(); //error
			break; //error
			continue; //error
		}
	}
}

function g(){
	break; //error
}

while(1){
	break;

}

for(; x<10; x++){
	continue;
}
