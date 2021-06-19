nl = "\n";

circle = [ {"pi" : pi = 3.141628}, {"r" : 0}, {"x" : 0}, {"y" : 0}];

function Area (circle){
	return ::pi * circle.r * circle.r;
}

function Perimeter(circle) {
	return 2 * circle.pi * circle.r;
}

function InitCircle() {
	circle.r = (local defaultVal = 5);
	circle.x = defaultVal;
	circle.y = defaultVal;
}

InitCircle();
print("pi (must be 3.141628}): ", pi, "\n");
print("circle Area (must be 78.540700000000001): ", Area(circle), nl);
print("circle Perimeter (must be 31.41628): ", Perimeter(circle), "\n\n");

