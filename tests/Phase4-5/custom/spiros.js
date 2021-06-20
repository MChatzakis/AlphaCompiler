function executor (a) {
    f = a;
    print(f(), "\n");
}

tablefunc = (function() { return (function(){return 3; }); });

print(tablefunc());
executor(tablefunc);    // this does not work