//DONE
x = 2;
function foo() {
    function foo(bar){
        local foo = 2;
        return bar + foo;
    }
    {
        local foo = [{foo:[{foo:foo}]}];
        foo.foo..foo(::foo);
    }
    x = (function(){});
}
