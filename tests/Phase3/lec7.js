//DONE
a = x--; 
/*
1: ASSIGN x _t0
2: SUB x 1 x
3: ASSIGN _t0 a
*/
a = t.x++; 

/*
4: TABLEGETELEM t “x” _t2
5: ASSIGN _t2 _t1
3: ADD _t2 1 _t2
4: TABLESETELEM t “x” _t2
5: ASSIGN _t1 a
*/