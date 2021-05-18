//DONE

if (1 > 2) x = 1;

/*
    if_greater 1 2 4 // first 4 quads evaluate logic expr 1>2 2 assign false _t1
    jump 5
    assign true _t1
    if_eq true _t1 7 // based on the result of logic expr (i.e. _t1), exec or not x = 1
    jump 9
    assign 1 x
    assign x _t2 9.
*/
