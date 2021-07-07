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
    print("a2 = 2 + 2 * 2 / 8;\n");
	a2 = 2 + 2 * 2 / 8;
	print(a2);

    print("c = f1(3,4);");
	c = false;//f1(3,4);
	print(c);

	print("local a = (1>2 and ::b <= 6) or (c != false);\n");
	local a = false;//(1>2 and ::b <= 6) or (c != false);
    print(a);
	

	print("global b = not a;\n");
	::b = not a;
	print(b);
	
	if(a) {
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
