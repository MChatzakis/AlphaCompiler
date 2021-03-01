/* Definition Section */
%{

    #ifdef WIN32
    #define YY_NO_UNISTD_H
    static int isatty(int i) {return 0;}
    #elif _WIN32_WCE
    #define YY_NO_UNISTD_H
    static int isatty(void *i) {return 0;}
    #endif
    
    #include <stdlib.h>
    #include <stdio.h>

    #include "token/Token.h"
    #include "../utils/Colors.h"

    #define YY_DECL int yylex(void* ylval)
    
    #define LEX_EOF 0
    #define DEBUG 1
    
    #define DEFAULT_STR_SIZE 128

    /*
        NOTES:
            1) Na apofasisoume gia to output
            2) Apothikeysi twn ipoloipwn tokens sto struct list (comments)
            3) Dedomena twn tokens?
            4) Enumerators?//
            5) Polla tests, mazema kwdika
            6) 
    
    */
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
string      \"

line_comment    "//".* 
block_comment   "/*"

/*integer     (0[xX][0-9A-Fa-f]+)|([0-9]+)*/
/*real [0-9]*\.[0-9](e|E)?[0-9]* */
/*string,block comment not ready*/

/* Rule Section */
%%


{left_curly_brace}      { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika Left Curly Brace: %s\n", yytext);  
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{right_curly_brace}     {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Right Curly Brace: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{left_square_brace}     {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Left Square Brace: %s\n", yytext); 
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }
                        
{right_square_brace}    {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Right Square Brace: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{left_parenthesis}      {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Left Parenthesis: %s\n", yytext); 
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{right_parenthesis}     {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Right Parenthesis: %s\n", yytext); 
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{semicolon}             { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika Semicolon: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }
                        
{comma}                 {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Comma: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }
                        
{fullstop}              {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Fullstop: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }
                        
{colon}                 {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Colon: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }
                        
{double_colon}          {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Double Colon: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }
                        
{ellipsis_mark}         {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Ellipsis Mark: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{if}                    { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika IF: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{else}                  { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika ELSE: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{while}                 { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika WHILE: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");  
                        }

{for}                   { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika FOR: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{function}              { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika FUNCTION: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!"); 
                        }

{return}                { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika RETURN: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!"); 
                        }

{break}                 { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika BREAK: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{continue}              { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika CONTINUE: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{and}                   { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika AND: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{not}                   { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika NOT: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }
                    
{or}                    { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika OR: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{local}                 { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika LOCAL: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{true}                  { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika TRUE: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{false}                 { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika FALSE: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{nil}                   { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika NIL: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                        }

{assign}                {
                            fprintf(stderr, "Vrika =: %s\n", yytext);
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
                        fprintf(stderr, "Vrika ==: %s\n", yytext);
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                    }
                    
{not_equal}         {
                        fprintf(stderr, "Vrika !=: %s\n", yytext);
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                    }
                    
{plus_plus}         {
                        fprintf(stderr, "Vrika ++: %s\n", yytext);
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
                        //fprintf(stderr, "Vrika <: %s\n", yytext);
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");

                    }

{less_equal}        {
                        //fprintf(stderr, "Vrika <: %s\n", yytext);
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");
                    }

{id}            {
                    fprintf(stderr, "Vrika Identifier: %s\n", yytext);
                    alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");

                }
                
{integer}       {
                    fprintf(stderr, "Vrika Akeraio: %s\n", yytext);
                    alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");

                }
                
{real}          {
                    fprintf(stderr, "Vrika Pragmatiko: %s\n", yytext);
                    alpha_token_insert((alpha_token_t *)ylval, yylineno, yytext, "DEN TO EXOYME FTIAXEI AKOMA!");

                }
                
{space}         {
                    fprintf(stderr, "Vrika Keno: %s\n", yytext);
                }

{newline}       { 
                    fprintf(stderr, "Vrika Newline: %s\n", yytext);
                }
                 
{string}        {
                    char *str;
                    int c, size_change = 1, counter = 0;
                                       
                    str = (char *)malloc(DEFAULT_STR_SIZE*sizeof(char));
                    memset((void*)str, 0, DEFAULT_STR_SIZE);

                    while((c = input()) != LEX_EOF){
                        if( c == '\\'){
                            
                            if( (c = input()) == 'n'){
                                *(str+counter) = '\n';
                            }
                            else if( c == 't'){
                                *(str+counter) = '\t';
                            }
                            else if( c == '"'){
                                *(str+counter) = '\"';
                            }
                            else{ 
                                unput(c);
                                *(str+counter) = '\\';
                                fprintf(stderr,"Warning: Used \\ without special sequence.\n");
                            }
                        }
                        else if(c == '"'){
                            *(str+counter) = '\0';
                            break;
                        }
                        else{
                            
                           *(str+counter) =  c; 
                        }
                        
                        counter++;
                        if(counter >= size_change * DEFAULT_STR_SIZE){
                            size_change++;
                            str = (char *)realloc((void*)str, size_change * DEFAULT_STR_SIZE);
                        }

                    }

                    if(DEBUG){
                        fprintf(stderr, "Vrika String: %s\n", str);
                    }

                    alpha_token_insert((alpha_token_t *)ylval, yylineno, str, "DEN TO EXOYME FTIAXEI AKOMA!");
                    free(str);
                }
                

{line_comment}  {
                    if(DEBUG){
                        fprintf(stderr, "Vrika Line Comment: %s\n", yytext);
                    }
                    alpha_token_insert((alpha_token_t *)ylval, yylineno, " ", "DEN TO EXOYME FTIAXEI AKOMA!");
                }
                
{block_comment} {
                    int c;
                    int c_stack = 1;
                    int starting_line = yylineno;

                    if(DEBUG){
                        fprintf(stderr, "Vrika Block Comment: %s\n", yytext);
                    }

                    while((c = input()) != LEX_EOF){
                        if( c == '*'){
                            if( (c = input()) == '/' ){
                                c_stack--;
                                printf("Vrika comment pou kleinei. To stack einai %d.\n",c_stack);
                                if(c_stack == 0){
                                    printf("Block comment apo %d ews %d.\n", starting_line, yylineno);
                                    break;
                                }
                            }
                            else{
                                unput(c);
                            }
                        }
                        else if( c == '/') {
                            if( (c = input()) == '*' ){
                                c_stack++;
                                printf("Vrika nested comment. To stack einai %d.\n",c_stack);
                            }
                            else{
                                unput(c);
                            }
                        }
                    }

                    if(c_stack != 0 ){
                        printf("Den exoun kleisei ta sxolia!\n");
                        exit(-1);
                    }       
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