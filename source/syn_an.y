/*Prologue*/
%{
    #include <stdio.h>

%}

/*Declarations*/
%start program
%token ID INTEGER

%right '='

/*Grammar*/
%%

program: ;

%%

int main(){

}



