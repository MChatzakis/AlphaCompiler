t = [
    {"arithm" : 1+1+1},
    {"func" : (function (){return;})},
    {"func2" : (function (){if(1)return;})},
    {"table" : [{"nestedFunc": (function (){return;})}] }
];

print(t);
x = 1;

