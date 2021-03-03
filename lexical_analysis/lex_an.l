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
    #include "comment_stack/comment_stack.h"
    #include "../utils/Colors.h"

    #define YY_DECL int yylex(void* ylval)
    
    #define LEX_EOF 0
    #define DEBUG 0
    
    #define DEFAULT_STR_SIZE 128

    
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

unknown_token .

/*integer     (0[xX][0-9A-Fa-f]+)|([0-9]+)*/
/*real [0-9]*\.[0-9](e|E)?[0-9]* */
/*string,block comment not ready*/

/* Rule Section */
%%


{left_curly_brace}      { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika Left Curly Brace: %s\n", yytext);  
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, PUNCTUATION, "PUNCTUATION LEFT_CURLY_BRACE");
                        }

{right_curly_brace}     {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Right Curly Brace: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, PUNCTUATION, "PUNCTUATION RIGHT_CURLY_BRACE");
                        }

{left_square_brace}     {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Left Square Brace: %s\n", yytext); 
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, PUNCTUATION, "PUNCTUATION LEFT_SQUARE_BRACE");
                        }
                        
{right_square_brace}    {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Right Square Brace: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, PUNCTUATION, "PUNCTUATION RIGHT_SQUARE_BRACE");
                        }

{left_parenthesis}      {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Left Parenthesis: %s\n", yytext); 
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, PUNCTUATION, "PUNCTUATION LEFT_PARENTHESIS");
                        }

{right_parenthesis}     {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Right Parenthesis: %s\n", yytext); 
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, PUNCTUATION, "PUNCTUATION RIGHT_PARENTHESIS");
                        }

{semicolon}             { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika Semicolon: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, PUNCTUATION, "PUNCTUATION SEMICOLON");
                        }
                        
{comma}                 {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Comma: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, PUNCTUATION, "PUNCTUATION COMMA");
                        }
                        
{fullstop}              {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Fullstop: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, PUNCTUATION, "PUNCTUATION FULLSTOP");
                        }
                        
{colon}                 {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Colon: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, PUNCTUATION, "PUNCTUATION COLON");
                        }
                        
{double_colon}          {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Double Colon: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, PUNCTUATION, "PUNCTUATION DOUBLE COLON");
                        }
                        
{ellipsis_mark}         {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Ellipsis Mark: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, PUNCTUATION, "PUNCTUATION ELLIPSIS MARK");
                        }

{if}                    { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika IF: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, KEYWORD, "KEYWORD IF");
                        }

{else}                  { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika ELSE: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, KEYWORD, "KEYWORD ELSE");
                        }

{while}                 { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika WHILE: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, KEYWORD, "KEYWORD WHILE");  
                        }

{for}                   { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika FOR: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, KEYWORD, "KEYWORD FOR");
                        }

{function}              { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika FUNCTION: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, KEYWORD, "KEYWORD FUNCTION"); 
                        }

{return}                { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika RETURN: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, KEYWORD, "KEYWORD RETURN"); 
                        }

{break}                 { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika BREAK: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, KEYWORD, "KEYWORD BREAK");
                        }

{continue}              { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika CONTINUE: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, KEYWORD, "KEYWORD CONTINUE");
                        }

{and}                   { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika AND: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, KEYWORD, "KEYWORD AND");
                        }

{not}                   { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika NOT: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, KEYWORD, "KEYWORD NOT");
                        }
                    
{or}                    { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika OR: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, KEYWORD, "KEYWORD OR");
                        }

{local}                 { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika LOCAL: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, KEYWORD, "KEYWORD LOCAL");
                        }

{true}                  { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika TRUE: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, KEYWORD, "KEYWORD TRUE");
                        }

{false}                 { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika FALSE: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, KEYWORD, "KEYWORD FALSE");
                        }

{nil}                   { 
                            if(DEBUG){
                                fprintf(stderr, "Vrika NIL: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, KEYWORD, "KEYWORD NIL");
                        }

{assign}                {
                            if(DEBUG){
                                fprintf(stderr, "Vrika =: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, OPERATOR, "OPERATOR ASSIGN");
                        }

{plus}                  {
                            if(DEBUG){
                                fprintf(stderr, "Vrika +: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, OPERATOR, "OPERATOR PLUS");
                        }

{minus}                 {
                            if(DEBUG){
                                fprintf(stderr, "Vrika -: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, OPERATOR, "OPERATOR MINUS");
                        }
                    
{mul}                   {
                            if(DEBUG){
                                fprintf(stderr, "Vrika *: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, OPERATOR, "OPERATOR MUL");
                        }

{div}                   {
                            if(DEBUG){
                                fprintf(stderr, "Vrika /: %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, OPERATOR, "OPERATOR DIV");
                        }

{modulo}                {
                            if(DEBUG){
                                fprintf(stderr, "Vrika Modulo : %s\n", yytext);
                            }
                            alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, OPERATOR, "OPERATOR MODULO");
                        }
                    
{equal}             {
                        if(DEBUG){
                            fprintf(stderr, "Vrika ==: %s\n", yytext);
                        }
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, OPERATOR, "OPERATOR EQUAL");
                    }
                    
{not_equal}         {
                        if(DEBUG){
                            fprintf(stderr, "Vrika !=: %s\n", yytext);
                        }
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, OPERATOR, "OPERATOR NOT_EQUAL");
                    }
                    
{plus_plus}         {
                        if(DEBUG){
                            fprintf(stderr, "Vrika ++: %s\n", yytext);
                        }
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, OPERATOR,"OPERATOR PLUS_PLUS");
                    }
                    
{minus_minus}       {
                        if(DEBUG){
                            fprintf(stderr, "Vrika --: %s\n", yytext);
                        }
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, OPERATOR,"OPERATOR MINUS_MINUS");
                    }
                    
{greater}           {
                        if(DEBUG){
                            fprintf(stderr, "Vrika >: %s\n", yytext);
                        }
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, OPERATOR, "OPERATOR GREATER");

                    }
                    
{greater_equal}     {
                        if(DEBUG){
                            fprintf(stderr, "Vrika >=: %s\n", yytext);
                        }
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, OPERATOR,"OPERATOR GREATER_EQUAL");
                    }
                    
{less}              {
                        if(DEBUG){
                            fprintf(stderr, "Vrika <: %s\n", yytext);
                        }
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, OPERATOR, "OPERATOR LESS");

                    }

{less_equal}        {
                        if(DEBUG){
                            fprintf(stderr, "Vrika <: %s\n", yytext);
                        }
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, OPERATOR, "OPERATOR LESS_EQUAL");
                    }

{id}            {
                    if(DEBUG){
                        fprintf(stderr, "Vrika Identifier: %s\n", yytext);
                    }
                    alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, IDENT, "ID");

                }
                
{integer}       {
                    if(DEBUG){
                        fprintf(stderr, "Vrika Akeraio: %s\n", yytext);
                    }
                    alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, CONST_INT, "CONST_INT");

                }
                
{real}          {
                    if(DEBUG){
                        fprintf(stderr, "Vrika Pragmatiko: %s\n", yytext);
                    }
                    alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, yytext, CONST_REAL, "CONST_REAL");

                }
                
{space}         {
                    if(DEBUG){
                        fprintf(stderr, "Vrika Keno: %s\n", yytext);
                    }
                }

{newline}       {
                    if(DEBUG){
                        fprintf(stderr, "Vrika Newline: %s\n", yytext);
                    } 
                }
                 
{string}        {
                    char *str;
                    int c, size_change = 1, counter = 0, valid = 0, starting_line = yylineno;
                                       
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
                                fprintf_yellow(stderr,"[Lexical Analysis] -- WARNING: Used \\ without special sequence. for string starting at line %u.\n", starting_line);
                            }
                        }
                        else if(c == '\"'){ //<- auto prepei nanai etsi h sketo "..
                            *(str+counter) = '\0';
                            valid = 1;
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

                    if(!valid){
                        fprintf_red(stderr, "[Lexical Analysis] -- ERROR: String starting at line %u has not closed.\n", starting_line);
                        //free(str);
                        //exit(-1);
                    }
                    else{
                        alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, str, STRING, "STRING"); 
                    }
                    free(str);
                }
                

{line_comment}  {
                    if(DEBUG){
                        fprintf(stderr, "Vrika Line Comment: %s\n", yytext);
                    }
                    alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, "", LINE_COMMENT, "COMMENT LINE_COMMENT");
                }
                
{block_comment} {
                    int c;
                    int c_stack = 1;
                    int starting_line = yylineno;
                    comment_stack_t* cs;

                    cs = comment_stack_init();
                    comment_stack_push(cs, yylineno);

                    if(DEBUG){
                        fprintf(stderr, "Vrika Block Comment: %s\n", yytext);
                    }

                    while((c = input()) != LEX_EOF){
                        if( c == '*'){
                            if( (c = input()) == '/' ){
                                //c_stack--;
                                starting_line = comment_stack_pop(cs);
                                if(DEBUG){
                                    printf("Vrika comment pou kleinei. To stack einai %d.\n",cs->size);
                                }
                                if(comment_stack_is_empty(cs)){
                                    if(DEBUG){
                                        printf("Block comment apo %d ews %d.\n", starting_line, yylineno);
                                    }
                                    alpha_token_insert((alpha_token_t *)ylval, starting_line, yylineno, "", BLOCK_COMMENT, "COMMENT BLOCK_COMMENT");
                                    break;
                                }
                                else{
                                    if(DEBUG){
                                        printf("Vrika nested comment. To stack einai %d.\n",cs->size);
                                    }
                                    alpha_token_insert((alpha_token_t *)ylval, starting_line, yylineno, "", NESTED_COMMENT, "COMMENT NESTED_COMMENT");
                                }
                            }
                            else{
                                unput(c);
                            }
                        }
                        else if( c == '/') {
                            if( (c = input()) == '*' ){
                                //c_stack++;
                                comment_stack_push(cs, yylineno);
                                /*if(DEBUG){
                                    printf("Vrika nested comment. To stack einai %d.\n",cs->size);
                                }
                                alpha_token_insert((alpha_token_t *)ylval, yylineno, yylineno, "", NESTED_COMMENT, "COMMENT NESTED_COMMENT");
                                */
                            }
                            else{
                                unput(c);
                            }
                        }
                    }

                    while(!comment_stack_is_empty(cs)){
                        if(DEBUG){
                            printf("Den exoun kleisei ta sxolia!\n");
                        }
                        fprintf_red(stderr ,"[Lexical Analysis] -- ERROR: Comment Never Ends at line %u\n", comment_stack_pop(cs));
                        /*if(comment_stack_is_empty(cs)){
                            exit(-1);
                        }*/
                    }
                    
                    comment_stack_free(cs);
                }


{unknown_token}     {
                        fprintf_red(stderr, "[Lexical Analysis] -- ERROR: Unkown token \"%s\" given at line %d\n",yytext, yylineno);
                        //exit(-1);
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
    
    printf(" ---------------- Lexical Analysis ---------------- \n\n");

    alpha_token_print_list(head);
    
    alpha_token_free_list(head);
    return 0;
}