//OK CSD
x = [-4, 13, 12.34, a+b]; 

/*
1: UMINUS 4 _t1
2: ADD a b _t2
3: TABLECREATE _t3 
4: TABLESETELEM _t3 0 _t1
5: TABLESETELEM _t3 1 13
6: TABLESETELEM _t3 2 12.34
7: TABLESETELEM _t3 3 _t2
8: ASSIGN _t3 x
9: ASSIGN x _t4
 */