/* Definition Section */
%{

    /*#ifdef WIN32
    #define YY_NO_UNISTD_H
    static int isatty(int i) {return 0;}
    #elif _WIN32_WCE
    #define YY_NO_UNISTD_H
    static int isatty(void *i) {return 0;}
    #endif*/
    
    #include <stdlib.h>
    #include <stdio.h>
    #include "token/Token.h"

    #define YY_DECL int yylex(void* ylval)
    #define DEBUG 0
%}

%option prefix = "alpha_yy"
%option outfile = "Scanner.c"
%option noyywrap
%option yylineno 

/* Flex Macros */

left_curly_brace   "{"
right_curly_brace  "}"
left_square_brace  "["
right_square_brace "]"
left_parenthesis   "("
right_parenthesis  ")"
semicolon          ";"
comma              ","
fullstop           "."
colon              ":"
ellipsis_mark      ".."
double_colon       "::"

if          "if" 
else        "else"
while       "while"
for         "for"
function    "function"
return      "return"
break       "break"
continue    "continue"
and         "and"
not         "not"
or          "or"
local       "local"
true        "true"
false       "false"
nil         "nil"

assign          "="
plus            "+"
minus           "-"
mul             "*"
div             "/"
modulo          "%"
equal           "=="
not_equal       "!="
plus_plus       "++"
minus_minus     "--"
greater         ">"
greater_equal   ">="
less            "<"
less_equal      "<="

id          [a-zA-Z][a-zA-Z_0-9]* 
integer     [0-9]+
real        [0-9]+\.[0-9]+
space       [\r \t\v] 
newline     \n
string      \"[^\n"]*\" 

line_comment    "//".* 
block_comment   "/*".*"*/"

/*integer     (0[xX][0-9A-Fa-f]+)|([0-9]+)*/
/*real [0-9]*\.[0-9](e|E)?[0-9]* */
/*string,block comment not ready*/
/* Rule Section */
%%


{left_curly_brace}      { 
                            //fprintf(stderr, "Vrika Left Curly Brace: %s\n", yytext);  
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{right_curly_brace}     {
                            //fprintf(stderr, "Vrika Right Curly Brace: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{left_square_brace}     {
                            //fprintf(stderr, "Vrika Left Square Brace: %s\n", yytext); 
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }
                        
{right_square_brace}    {
                            //fprintf(stderr, "Vrika Right Square Brace: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{left_parenthesis}      {
                            //fprintf(stderr, "Vrika Left Parenthesis: %s\n", yytext); 
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{right_parenthesis}     {
                            //fprintf(stderr, "Vrika Right Parenthesis: %s\n", yytext); 
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{semicolon}             { 
                            //fprintf(stderr, "Vrika Semicolon: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }
                        
{comma}                 {
                            fprintf(stderr, "Vrika Comma: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }
                        
{fullstop}              {
                            fprintf(stderr, "Vrika Fullstop: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }
                        
{colon}                 {
                            fprintf(stderr, "Vrika Colon: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }
                        
{double_colon}          {
                            fprintf(stderr, "Vrika Double Colon: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }
                        
{ellipsis_mark}         {
                            fprintf(stderr, "Vrika Ellipsis Mark: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{if}                    { 
                            //fprintf(stderr, "Vrika IF: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{else}                  { 
                            fprintf(stderr, "Vrika ELSE: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{while}                 { 
                            fprintf(stderr, "Vrika WHILE: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");  
                        }

{for}                   { 
                            fprintf(stderr, "Vrika FOR: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{function}              { 
                            fprintf(stderr, "Vrika FUNCTION: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!"); 
                        }

{return}                { 
                            fprintf(stderr, "Vrika RETURN: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!"); 
                        }

{break}                 { 
                            fprintf(stderr, "Vrika BREAK: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{continue}              { 
                           fprintf(stderr, "Vrika CONTINUE: %s\n", yytext);
                           alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{and}                   { 
                            fprintf(stderr, "Vrika AND: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{not}                   { 
                            fprintf(stderr, "Vrika NOT: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }
                    
{or}                    { 
                            fprintf(stderr, "Vrika OR: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{local}                 { 
                            fprintf(stderr, "Vrika LOCAL: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{true}                  { 
                            //fprintf(stderr, "Vrika TRUE: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{false}                 { 
                            fprintf(stderr, "Vrika FALSE: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{nil}                   { 
                            fprintf(stderr, "Vrika NIL: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{assign}                {
                            //fprintf(stderr, "Vrika =: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{plus}                  {
                            fprintf(stderr, "Vrika +: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{minus}                 {
                            fprintf(stderr, "Vrika -: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }
                    
{mul}                   {
                            fprintf(stderr, "Vrika *: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{div}                   {
                            fprintf(stderr, "Vrika /: %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{modulo}                {
                            fprintf(stderr, "Vrika Modulo : %s\n", yytext);
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }
                    
{equal}             {
                        //fprintf(stderr, "Vrika ==: %s\n", yytext);
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                    }
                    
{not_equal}         {
                        //fprintf(stderr, "Vrika !=: %s\n", yytext);
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                    }
                    
{plus_plus}         {
                        //fprintf(stderr, "Vrika ++: %s\n", yytext);
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                    }
                    
{minus_minus}       {
                        fprintf(stderr, "Vrika --: %s\n", yytext);
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                    }
                    
{greater}           {
                        fprintf(stderr, "Vrika >: %s\n", yytext);
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");

                    }
                    
{greater_equal}     {
                        fprintf(stderr, "Vrika >=: %s\n", yytext);
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                    }
                    
{less}              {
                        fprintf(stderr, "Vrika <: %s\n", yytext);
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");

                    }

{less_equal}        {
                        fprintf(stderr, "Vrika <: %s\n", yytext);
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                    }

{id}            {
                    //fprintf(stderr, "Vrika Identifier: %s\n", yytext);
                    alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");

                }
                
{integer}       {
                    //fprintf(stderr, "Vrika Akeraio: %s\n", yytext);
                    alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");

                }
                
{real}          {
                    //fprintf(stderr, "Vrika Pragmatiko: %s\n", yytext);
                    alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");

                }
                
{space}         {
                    //fprintf(stderr, "Vrika Keno: %s\n", yytext);
                }

{newline}       { 
                        //fprintf(stderr, "Vrika Newline: %s\n", yytext);
                }
                 
{string}        {
                    fprintf(stderr, "Vrika String: %s\n", yytext);
                    alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");

                }

{line_comment}  {
                    //fprintf(stderr, "Vrika Line Comment: %s\n", yytext);
                    alpha_token_insert((alpha_token_t *)ylval, yylineno, " ", "DEN TO EXOYME FTIAXEI AKOMA!");

                }
                
{block_comment} {
                    //fprintf(stderr, "Vrika Block Comment: %s\n", yytext);
                }

%%

/* Code Section */
int main(int argc, char **argv){
    yylineno = 1;
    alpha_token_t *head;
    head = alpha_token_init();

    if(argc > 1){
        if(!(yyin = fopen(argv[1], "r"))){
            fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return 1;
        }
    }
    else{
        yyin = stdin;
    }


    alpha_yylex( (void *) head);
    
    alpha_token_print_list(head);
    return 0;
}