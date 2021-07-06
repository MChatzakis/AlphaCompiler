/*
proper output for this test:

pt.x: 21
pt.y: 32
sq.p1.x: 6
sq.p1.y: 12
sq.p2.x: 26
sq.p2.y: 32
first hello
second hello
third hello
fourth hello
table1_2 ok1
table2_3 ok2
*/
function Point(x, y) {

        return [
                {"x": x},
                {"y": y},
                {"move": (function(p,dx,dy) {
                                p.x = p.x + dx;
                                p.y = p.y + dy;
                                }
                        )}
                ];
}

pt = Point(20,30);
pt.move(pt, 1, 2);

print("pt.x: ", pt.x, "\n");
print("pt.y: ", pt.y, "\n");

function Square(p1, p2) {

        return [
                {"p1": p1},
                {"p2": p2},
                {"move": (function(p, dx, dy) {
                                p.p1.move(p.p1, dx, dy);
                                p.p2.move(p.p2, dx, dy);
                                }
                        )}
                ];
}

sq = Square(Point(10,20), Point(30,40));
sq.move(sq, -4, -8);

print("sq.p1.x: ", sq.p1.x, "\n");
print("sq.p1.y: ", sq.p1.y, "\n");
print("sq.p2.x: ", sq.p2.x, "\n");
print("sq.p2.y: ", sq.p2.y, "\n");

// Dispatch table

dispatchTable = [ {1: (function (x){ print("first ", x);})},
                  {2: (function (x){ print("second ", x);})},
                  {3: (function (x){ print("third ", x);})},
                  {4: (function (x){ print("fourth ", x);})}
                ];

for(i=1; i<= 4; ++i)
        dispatchTable[i]("hello\n");

//

table = [{"table1" : [{1: (function (x){ print("table1_1 ", x);})},
                      {2: (function (x){ print("table1_2 ", x);})},
                      {3: (function (x){ print("table1_3 ", x);})}
                     ]
         },
         {"table2" : [{1: (function (x){ print("table2_1 ", x);})},
                      {2: (function (x){ print("table2_2 ", x);})},
                      {3: (function (x){ print("table2_3 ", x);})}
                     ]
         }
        ];

table.table1[2]("ok1\n");
table.table2[3]("ok2\n");
                                

