//DONE

t =[ {"x": 0},{"y": a+b},{-1: 0} ]; 
/*
1: ADD a b _t1
2: UMINUS 1 _t2
3: TABLECREATE _t3 
4: TABLESETELEM _t3 “x” 0
5: TABLESETELEM _t3 “y” _t1
6: TABLESETELEM _t3 _t2 0
7: ASSIGN _t3 t
*/