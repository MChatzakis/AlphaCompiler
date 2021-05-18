//DONE

test().x = 1;
/*
1: call test
2: getretval _t0
3: tablesetelem _t0 "x" 1
*/

print (y.z.x, "-");
/*
4: tablegetelem    y   "z" _t1
5: tablegetelem _t1   "x" _t2
6: param "-"
7: param _t2
8: call print
9: getreval _t3
*/