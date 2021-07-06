//print assertion conditio

vec0 = [];
vec3 = [0,1,0];
vec5 = [1, -2, 1, 0, 1];
vectors = [vec0, vec5];


directory = [
        {"x" : vectors[0] },
        {"y" : vectors[1] },
        {"z" : 42},
        {3 : 2},
        {"f" : (function (x) { return 2*x; } )},
        {345345: 345345},
        {0 : "y" },
        {"o" : "empty_table"},
        {vec3 : "vec3"}
];

function Assert(condition, line)
{
	print("Assert condition is: ", condition, "\n");
        if (not condition)
                print("ASSERTION FAILED! at line: ", line, "\n");
}

Assert(directory[3] == 2, 28); 
Assert(directory[ vec3 ] == "vec3"); 

///--- The following lines are equivalent
Assert(directory["f"](2) == 4); 
Assert(directory.f(2) == 4, 33);

///--- Appending the directory
directory["g"] = Assert;
directory.g(directory.x == vec0, 37);
directory.g = nil;

directory["()"] = (function (this, x) {
                                         return this.z + x;
                                   });
Assert(directory(3) == 45, 43);
