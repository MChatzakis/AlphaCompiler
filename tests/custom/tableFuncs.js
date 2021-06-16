/*function f(a,b){
    return a+b;
}

t = [1,2,3,5];
p = [ {"string" : 100}, {true : "boolean value!"}, {print: "Hello!"}, {12.2 : 10}, {false: 0}, {2:"duo"}, {"call_print":print}];
simple = [{"hello" : 10},{f:100}];

keys = objectmemberkeys(simple);
softCopy = objectcopy(p);

print("COPY __________________ ", softCopy);

print("--------------------- KEYS OF p: ", keys);
*/
function f(a, b) {
  return a + b;
}
simple = [{ "hello": 10 }, { f: 100 }];

print("---------------------- ", objectmemberkeys(simple));
print("---------------------- ", objectcopy(simple));

