function createTable(){
    return [
        {"name": "Manos"},
        {"hello" : "world"}
    ];
}

function getTab(){
    return [
        {"tab" : createTable()},
        {"csd" : (function f(){return;})},
        {"bool" : true}
    ];
}

x = getTab();
print(x);