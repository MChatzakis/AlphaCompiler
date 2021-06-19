/*
The proper output must be:
cnt 	: 10
even 	: 1
odd 	: 0
0 is evan
1 is odd
2 is evan
3 is odd
4 is evan
5 is odd
6 is evan
7 is odd
8 is evan
9 is odd
10 is evan
Assertion
*/

nl = "\n";

function Assert(con){
	if (not con)
		print("Assertion", nl);
}

function IsEven(num) {
	return num % 2 == 0;
}

function IsOdd(num) {
	return not IsEven(num);
}

function CanDivideByTen(num) {
	return num % 10;
}

function PrintParityOfNumbers(MAX) {
	local exit = true;
	for(local i = 0; i < MAX + 1; ++i){
	
		if (IsEven(i))
			print(i, " is evan", nl);
		else if (IsOdd(i))
			print(i, " is odd", nl);
		else {
			
			exit = false;
			break;
		}
	}

	return exit;
}

for (local even = 0, local odd = 1, local cnt = 0; (IsEven(even) and IsOdd(odd)) or (CanDivideByTen(10)); ) {
	if (cnt == 10)
		break;
	if (cnt == 0) {
		even = 1;
		odd	 = 0;
		cnt  = 10;
	}		
}

function Print() {
	print("cnt\t: ", cnt, nl);	//must print 10
	print("even\t: ", even, nl);	//must print 1
	print("odd\t: ", odd, nl);	//must print 0
}

Print();
Assert(PrintParityOfNumbers(10));
Assert(not "wtf");










