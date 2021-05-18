//DONE
++x;

/*
1: ADD x 1 x
2: ASSIGN x _t0
*/
a = ++t.x;
/*
2: TABLEGETELEM t “x” _t0
3: ADD _t0 1 _t0
4: TABLESETELEM t “x” _t0
5: ASSIGN _t0 a
*/
a = --t.x.y;
/*
6: TABLEGETELEM t “x” _t1
7: TABLEGETELEM _t1 “y” _t2
8: SUB _t2 1 _t2
9: TABLESETELEM _t1 “y” _t2
10: ASSIGN _t2 a
*/
