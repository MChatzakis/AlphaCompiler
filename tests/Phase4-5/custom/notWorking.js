a = b = 5;

function f1(a,b)
{
	if(a > b) 
		return true;
	else	
		return false;
}

function sum(i)
{
	sumV = 0;
    j = 0;
	
	while(j < i and i<20)
	{
		sumV = sumV + j++;
	}
    
	return sumV;
}

{
    /*print("a2 = 2 + 2 * 2 / 8;\n");
	a2 = 2 + 2 * 2 / 8;

    print("c = f1(3,4);");
	c = f1(3,4);
    
	print("local a = (1>2 and ::b <= 6) or (c != false);\n");
	local a = (1>2 and ::b <= 6) or (c != false);
    
	print("global b = not a;\n");
	::b = not a;
*/
	if(false) {
		// never here
        	print("The impossible happened\n");
    }
	else
	{
		i = 0;
        res = 0;
		
		while((res <= 15))
		{
			res = sum(i);
			print("sum: ",i," = ",res,"\n");
			i++;
		}
	}

	c = 3 + -2 * -2;
	print(c);
}
