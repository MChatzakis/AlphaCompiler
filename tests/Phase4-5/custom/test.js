
t1 = [{"()":(function (self, arg1){print(arg1); return;})}];
t1["h"] = t1; 

t1("hello!");

print(t1["h"]);

t1["h"]("to kalw etsi");