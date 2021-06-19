function createTable(){
    return [
        {"name": "Manos"},
        {"hello" : "world"}
    ];
}

function getTab(){
    return [
        {"tab" : createTable()},
        {"csd" : (function f(){while(1)break;})},
        {"bool" : true}
    ];
}

x = getTab();
print(x);