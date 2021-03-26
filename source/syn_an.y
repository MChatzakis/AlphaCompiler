/*Prologue*/
%{
    #include <stdio.h>

%}

/*Declarations*/
%start program

%union {
    char* string_value;
    int int_value;
    double real_value;
}

%token <int_value> INTEGER
%token <string_value> STRING
%token <real_value> REAL
%token <string_value> OR "or"

%right OR
/*%right '='
%left "or"
%left "and"
%nonassoc "==" "!="
%nonassoc '>' ">=" '<' '<='
%left '+' '-'
%left '*' '/' '%'
%right "not" "++" "--" UMINUS
%left '.' ".."
%left '[' ']'
%left '(' ')'*/

/*Grammar*/
%%

program:    stmt*

stmt:       expr;
            | ifstmt
            | whilestmt
            | forstmt
            | returnstmt
            | break; 
            | continue;
            | block
            | funcdef
            | ;

expr:       assignexpr
            | expr op expr
            | term

op:         + | - | * | / | % | > | >= | < | <= | == | != | and | or           

term:       (expr)
            | - expr
            | not expr
            | ++lvalue
            | lvalue++
            | --lvalue
            | lvalue--
            | primary

assignexpr: lvalue = expr

primary:    lvalue
            | call
            | objectdef
            | (funcdef)
            | const

lvalue:     id
            | local id
            | :: id
            | member


member:     lvalue . id
            | lvalue [ expr ]
            | call . id
            | call [ expr ]


call:       call ( elist )
            | lvalue callsuffix
            | ( funcdef) ( elist )


callsuffix:     normcall
                | methodcall


normcall:       ( elist )
        

methodcall:     .. id ( elist ) // equivalent to lvalue.id(lvalue, elist)

elist:          [ expr [, expr] * ]
        
objectdef:      [ [elist | indexed] ]
        
indexed:        [indexedelem [, indexedelem] * ]

indexedelem:    { expr : expr }

block:          { [stmt*] }
        
funcdef:        function [id] (idlist) block

const:          number | string | nil | true | false

idlist:         [id [, id] * ]

ifstmt:         if ( expr ) stmt [ else stmt ]
        
whilestmt:      while ( expr ) stmt

forstmt:        for ( elist; expr; elist) stmt
        
returnstmt:     return [expr];

%%

int main(){

}
