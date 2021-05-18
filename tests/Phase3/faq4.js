//DONE

t.a.b = c.d.e=f.g.h; 
/*
0: TABLEGETELEM   t "a" _t0
1: TABLEGETELEM   c "d" _t1
2: TABLEGETELEM   f "g" _t2
3: TABLEGETELEM   _t2 "h" _t3
4: TABLESETELEM   _t1 "e" _t3
5: TABLEGETELEM   _t1 "e" _t4
6: TABLESETELEM   _t0 "b" _t4
7: TABLEGETELEM   _t0 "b" _t5

*/