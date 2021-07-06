/*
proper output for this test

Creating & manipulating point...
moving point to 10,10
Getting & creating line...
getting line from 10,10 to 100,100
drawing line

*/

///--- Generator of Line objects
function Line(x0, y0, x1, y1)
{
        return [
                { "draw" : (function() { print("drawing line\n"); }) }
        ];
}

///--- Generator of Point objects
function Point(x, y)
{
        return [
                { "x" : x },
                { "y" : y },
                { "move" : (function(pt, x, y) {
                                                print("moving point to ", x, ",", y, "\n");
                                                pt.x = x; pt.y = y;
                                        })
                },
                { "get_line" : (function(pt, x, y) {
                                                        print("getting line from ",
                                                                pt.x, ",", pt.y, " to ",
                                                                x, ",", y, "\n"
                                                        );

                                                        return Line(pt.x, pt.y, x, y);
                                                })
                }
        ];
}

///--- testbed
print("Creating & manipulating point...\n");
pt = Point(0, 0);               ///< create a point
pt.move(pt, 10, 10);

print("Getting & creating line...\n");
line = pt.get_line(pt, 100, 100);
line.draw();

