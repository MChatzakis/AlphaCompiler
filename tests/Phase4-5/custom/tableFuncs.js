function f(a, b) {
  return a + b;
}

simple = [{ "hello": 10 }, { f: 100 }];

print("---------------------- ", objectmemberkeys(simple));
print("---------------------- ", objectcopy(simple));

