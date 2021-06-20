function loop1() {
  i = 100;
  sum = 0;
  while (i >= 0) {
    sum = i + sum;
    i--;
    print(i);
  }

  print("Sum is ", sum);
}

function loop2(){
    t = ["manos", "nikos", "giorgos", "giannis", "maria", "eleni", "gianna"];
    for(i=0; i<objecttotalmembers(t); i++){
        print(t[i]);
    }
}


function loop3_2(i){
  sumV = 0;
  j = 0;

  while(j < i and i<20)
  {
    sumV = sumV + j++;
  }
  
  return sumV;
}

function loop3_1(){
  
  if(false){

  }else{
    i = 0;
    res = 0;
  
    while((res <= 15))
    {
      res = loop3_2(i);
      print("sum: ",i," = ",res,"\n");
      i++;
    }
  }
  
}


function main() {
    //loop1();
    //loop2();
    loop3_1();
}

main();
