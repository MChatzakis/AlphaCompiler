print("Simple table calls...\n");
//t = [-1, 2, 3, 4];
//c = [{"c" : 5}];
//b = [{"b": c}];
t = [{"a" : [{"b": [{"c" : 5}]}]}];
//t = [{"a" : b}];

//t1 = [{"a" :1}];
x = t.a.b.c;

print(x);
//x= 1;