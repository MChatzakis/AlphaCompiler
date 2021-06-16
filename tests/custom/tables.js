t = [1,2,3,5];
p = [ {"string" : 100}, {true : "boolean value!"}, {print: "Hello!"}, {12.2 : 10}, {false: 0}, {2:"duo"}, {"call_print":print}];

print("------------------------------- TABLE t: ", t);

print("------------- TABLE P: ", p, " \n WITH TOTAL ITEMS: ", objecttotalmembers(p));

p["call_print"]("+++++++++++++++++++++ HELLO WORLD! +++++++++++++++++++++++++");
