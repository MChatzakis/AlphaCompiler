//DONE
function foo (a,b) { }

/*
funcstart foo
funcend foo
*/

f(1,2);
/*
PARAM 2
PARAM 1
CALL f
*/
f(a(1), b(2, 3));
/*
0: PARAM 1 
1: CALL a
2: GETRETVAL _r0
3: PARAM 3
4: PARAM 2
5: CALL b
6: GETRETVAL _r1
7: PARAM _r1
8: PARAM _r0
9: CALL f
10:GETRETVAL _r2
*/