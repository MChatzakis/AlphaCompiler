/*Prologue*/
%{
    #ifdef WIN32
    #define YY_NO_UNISTD_H
    static int isatty(int i) {return 0;}
    #elif _WIN32_WCE
    #define YY_NO_UNISTD_H
    static int isatty(void *i) {return 0;}
    #endif

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>

    #include "utils/colors.h"
    #include "yacc_libs/macros.h"

    int yyerror(char *message);
    int yylex(void);

    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;

%}

/*Declarations*/
%start program

%union {
    int int_value;
    char* string_value;
    double real_value;

    struct expr_type_t{
        enum type_t{INT_T,REAL_T,STRING_T}type;
        int int_val;
        double real_val;
        char *string_val;
    }expr_type;

}

%token <int_value> INTEGER
%token <real_value> REAL
%token <string_value> ID
%token <string_value> STRING

%token <string_value> LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET LEFT_PARENTHESIS RIGHT_PARENTHESIS SEMICOLON COMMA FULLSTOP COLON DOUBLE_FULLSTOP DOUBLE_COLON
%token <string_value> IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND NOT OR LOCAL TRUE FALSE NIL
%token <string_value> ASSIGN PLUS MINUS MUL DIV MODULO EQUAL NOT_EQUAL PLUS_PLUS MINUS_MINUS GREATER GREATER_EQUAL LESS LESS_EQUAL

%right ASSIGN
%left OR
%left AND
%nonassoc EQUAL NOT_EQUAL
%nonassoc LESS LESS_EQUAL GREATER GREATER_EQUAL
%left PLUS MINUS
%left MUL DIV MODULO
%right NOT PLUS_PLUS MINUS_MINUS UMINUS
%left FULLSTOP DOUBLE_FULLSTOP
%left LEFT_BRACKET RIGHT_BRACKET
%left LEFT_PARENTHESIS RIGHT_PARENTHESIS

%type <expr_type> expr


/*Grammar*/
%%

program:    exprs
            |;


expr:       INTEGER                     {
                                            printf("Vrika INTEGER %d\n", $1);
                                            $$.type = INT_T;
                                            $$.int_val = $1;
                                        }
            | REAL                      {
                                            printf("Vrika REAL %f\n", $1);
                                            $$.type = REAL_T;
                                            $$.real_val = $1;
                                        }
            | STRING                    {
                                            printf("Vrika STRING %s\n", $1);
                                            $$.type = STRING_T;
                                            $$.string_val = strdup($1); //prosoxi
                                        
                                        }
            | ID                        {
                                            printf("Vrika ID %s\n", $1);
                                            //$$ = fetch($1)
                                        }
            | lvalue ASSIGN expr        {;}

            | expr OR expr              {
                                            $$.type = INT_T;
                                            if($1.type == REAL_T && $3.type == REAL_T){
                                                $$.int_val = $1.real_val || $3.real_val;
                                            }else if($1.type == INT_T && $3.type == INT_T){
                                                $$.int_val = $1.int_val || $3.int_val;
                                            }else if($1.type == REAL_T && $3.type == INT_T){
                                                $$.int_val = $1.real_val || $3.int_val;
                                            }else if($1.type == INT_T && $3.type == REAL_T){
                                                $$.int_val = $1.int_val || $3.real_val;
                                            }else{
                                                yyerror("OR with string is not valid!\n");
                                            }
                                            printf("OR expression with result: ");
                                            print_expression($$);
                                            printf("\n");
                                            
                                        }
            | expr AND expr             {
                                            $$.type = INT_T;
                                            if($1.type == REAL_T && $3.type == REAL_T){
                                                $$.int_val = $1.real_val && $3.real_val;
                                            }else if($1.type == INT_T && $3.type == INT_T){
                                                $$.int_val = $1.int_val && $3.int_val;
                                            }else if($1.type == REAL_T && $3.type == INT_T){
                                                $$.int_val = $1.real_val && $3.int_val;
                                            }else if($1.type == INT_T && $3.type == REAL_T){
                                                $$.int_val = $1.int_val && $3.real_val;
                                            }else{
                                                yyerror("AND with string is not valid!\n");
                                            }
                                            
                                            printf("AND expression with result: ");
                                            print_expression($$);
                                            printf("\n");
                                        }
            | expr NOT_EQUAL expr       {
                                            $$.type = INT_T;
                                            if($1.type == REAL_T && $3.type == REAL_T){
                                                $$.int_val = $1.real_val != $3.real_val;
                                            }else if($1.type == INT_T && $3.type == INT_T){
                                                $$.int_val = $1.int_val != $3.int_val;
                                            }else if($1.type == REAL_T && $3.type == INT_T){
                                                $$.int_val = $1.real_val != $3.int_val;
                                            }else if($1.type == INT_T && $3.type == REAL_T){
                                                $$.int_val = $1.int_val != $3.real_val;
                                            }else{
                                                yyerror("NOT EQUAL with string is not valid!\n");
                                            }
                                            printf("NOT EQUAL expression with result: ");
                                            print_expression($$);
                                            printf("\n");
                                        }
            | expr EQUAL expr           {
                                            $$.type = INT_T;
                                            if($1.type == REAL_T && $3.type == REAL_T){
                                                $$.int_val = $1.real_val == $3.real_val;
                                            }else if($1.type == INT_T && $3.type == INT_T){
                                                $$.int_val = $1.int_val == $3.int_val;
                                            }else if($1.type == REAL_T && $3.type == INT_T){
                                                $$.int_val = $1.real_val == $3.int_val;
                                            }else if($1.type == INT_T && $3.type == REAL_T){
                                                $$.int_val = $1.int_val == $3.real_val;
                                            }else{
                                                yyerror("EQUAL with string is not valid!\n");
                                            }
                                            printf("EQUAL expression with result: ");
                                            print_expression($$);
                                            printf("\n");
                                        }
            | expr LESS_EQUAL expr      {
                                            $$.type = INT_T;
                                            if($1.type == REAL_T && $3.type == REAL_T){
                                                $$.int_val = $1.real_val <= $3.real_val;
                                            }else if($1.type == INT_T && $3.type == INT_T){
                                                $$.int_val = $1.int_val <= $3.int_val;
                                            }else if($1.type == REAL_T && $3.type == INT_T){
                                                $$.int_val = $1.real_val <= $3.int_val;
                                            }else if($1.type == INT_T && $3.type == REAL_T){
                                                $$.int_val = $1.int_val <= $3.real_val;
                                            }else{
                                                yyerror("LESS EQUAL with string is not valid!\n");
                                            }
                                            printf("LESS EQUAL expression with result: ");
                                            print_expression($$);
                                            printf("\n");
                                        }
            | expr LESS expr            {
                                            $$.type = INT_T;
                                            if($1.type == REAL_T && $3.type == REAL_T){
                                                $$.int_val = $1.real_val < $3.real_val;
                                            }else if($1.type == INT_T && $3.type == INT_T){
                                                $$.int_val = $1.int_val < $3.int_val;
                                            }else if($1.type == REAL_T && $3.type == INT_T){
                                                $$.int_val = $1.real_val < $3.int_val;
                                            }else if($1.type == INT_T && $3.type == REAL_T){
                                                $$.int_val = $1.int_val < $3.real_val;
                                            }else{
                                                yyerror("LESS with string is not valid!\n");
                                            }
                                            printf("LESS expression with result: ");
                                            print_expression($$);
                                            printf("\n");
                                        }
            | expr GREATER_EQUAL expr   {
                                            $$.type = INT_T;
                                            if($1.type == REAL_T && $3.type == REAL_T){
                                                $$.int_val = $1.real_val >= $3.real_val;
                                            }else if($1.type == INT_T && $3.type == INT_T){
                                                $$.int_val = $1.int_val >= $3.int_val;
                                            }else if($1.type == REAL_T && $3.type == INT_T){
                                                $$.int_val = $1.real_val >= $3.int_val;
                                            }else if($1.type == INT_T && $3.type == REAL_T){
                                                $$.int_val = $1.int_val >= $3.real_val;
                                            }else{
                                                yyerror("GREATER_EQUAL with string is not valid!\n");
                                            }
                                            printf("GREATER_EQUAL expression with result: ");
                                            print_expression($$);
                                            printf("\n");
                                        }
            | expr GREATER expr         {
                                            $$.type = INT_T;
                                            if($1.type == REAL_T && $3.type == REAL_T){
                                                $$.int_val = $1.real_val > $3.real_val;
                                            }else if($1.type == INT_T && $3.type == INT_T){
                                                $$.int_val = $1.int_val > $3.int_val;
                                            }else if($1.type == REAL_T && $3.type == INT_T){
                                                $$.int_val = $1.real_val > $3.int_val;
                                            }else if($1.type == INT_T && $3.type == REAL_T){
                                                $$.int_val = $1.int_val > $3.real_val;
                                            }else{
                                                yyerror("GREATER with string is not valid!\n");
                                            }
                                            printf("GREATER expression with result: ");
                                            print_expression($$);
                                            printf("\n");
                                        }
            | expr PLUS expr            {
                                            if($1.type == REAL_T && $3.type == REAL_T){
                                                $$.type = REAL_T;
                                                $$.real_val = $1.real_val + $3.real_val;
                                            }else if($1.type == INT_T && $3.type == INT_T){
                                                $$.type = INT_T;
                                                $$.int_val = $1.int_val + $3.int_val;
                                            }else if($1.type == REAL_T && $3.type == INT_T){
                                                $$.type = REAL_T;
                                                $$.real_val = $1.real_val + $3.int_val;
                                            }else if($1.type == INT_T && $3.type == REAL_T){
                                                $$.type = REAL_T;
                                                $$.real_val = $1.int_val + $3.real_val;
                                            }else{
                                                yyerror("Addition with string is not valid!\n");
                                            }

                                            printf("PLUS expression with result: ");
                                            print_expression($$);
                                            printf("\n");

                                        }
            | expr MINUS expr           {
                                            if($1.type == REAL_T && $3.type == REAL_T){
                                                $$.type = REAL_T;
                                                $$.real_val = $1.real_val - $3.real_val;
                                            }else if($1.type == INT_T && $3.type == INT_T){
                                                $$.type = INT_T;
                                                $$.int_val = $1.int_val - $3.int_val;
                                            }else if($1.type == REAL_T && $3.type == INT_T){
                                                $$.type = REAL_T;
                                                $$.real_val = $1.real_val - $3.int_val;
                                            }else if($1.type == INT_T && $3.type == REAL_T){
                                                $$.type = REAL_T;
                                                $$.real_val = $1.int_val - $3.real_val;
                                            }else{
                                                yyerror("Abstraction with string is not valid!\n");
                                            }

                                            printf("MINUS expression with result: ");
                                            print_expression($$);
                                            printf("\n");

                                        }
            | expr MUL expr             {
                                            if($1.type == REAL_T && $3.type == REAL_T){
                                                $$.type = REAL_T;
                                                $$.real_val = $1.real_val * $3.real_val;
                                            }else if($1.type == INT_T && $3.type == INT_T){
                                                $$.type = INT_T;
                                                $$.int_val = $1.int_val * $3.int_val;
                                            }else if($1.type == REAL_T && $3.type == INT_T){
                                                $$.type = REAL_T;
                                                $$.real_val = $1.real_val + $3.int_val;
                                            }else if($1.type == INT_T && $3.type == REAL_T){
                                                $$.type = REAL_T;
                                                $$.real_val = $1.int_val * $3.real_val;
                                            }else{
                                                yyerror("Addition with string is not valid!\n");
                                            }

                                            printf("MUL expression with result: ");
                                            print_expression($$);
                                            printf("\n");
                                        }
            | expr DIV expr             {
                                            if($1.type == REAL_T && $3.type == REAL_T){
                                                $$.type = REAL_T;
                                                $$.real_val = $1.real_val / $3.real_val;
                                            }else if($1.type == INT_T && $3.type == INT_T){
                                                $$.type = INT_T;
                                                $$.int_val = $1.int_val / $3.int_val;
                                            }else if($1.type == REAL_T && $3.type == INT_T){
                                                $$.type = REAL_T;
                                                $$.real_val = $1.real_val / $3.int_val;
                                            }else if($1.type == INT_T && $3.type == REAL_T){
                                                $$.type = REAL_T;
                                                $$.real_val = $1.int_val / $3.real_val;
                                            }else{
                                                yyerror("Addition with string is not valid!\n");
                                            }

                                            printf("DIV expression with result: ");
                                            print_expression($$);
                                            printf("\n");
                                        }
            | expr MODULO expr          {
                                            if($1.type == INT_T && $3.type == INT_T){
                                                $$.type = INT_T;
                                                $$.int_val = $1.int_val % $3.int_val;
                                            }
                                            printf("MODULO expression with result: ");
                                            print_expression($$);
                                            printf("\n");
                                        }
            | LEFT_PARENTHESIS expr RIGHT_PARENTHESIS   {printf("vrika paren\n");}
            | MINUS expr %prec UMINUS                {printf("vrika uminus\n");}
            | NOT expr                  {printf("vrika not\n");}
            ;

exprs : exprs expr | expr;

lvalue: ID  {
                //assign($1, $3);
                lvalue.string_val = ID.string_val;
                printf("ASSIGN expression to ID %s the value: ", $1);
                print_expression($3);
                printf("\n");
            }
        ;
%%

int yyerror(char *message){
    fprintf_red(stderr, "[Syntax Analysis] -- ERROR: %s: at line %d, before token: %s\n", message, yylineno, yytext);
    return 0;
}

int main(int argc, char **argv){

    FILE *ost;
    int opt;
    char* file_name;

    ost = stdout;
    yyin = stdin;

    while ((opt = getopt(argc, argv, "i:o:h")) != -1)
    {
        switch (opt)
        { 
        case 'i':
            file_name = strdup (optarg);
            if(!(yyin = fopen(file_name, "r"))){
                fprintf(stderr, "Cannot read file: %s\n", file_name);
                free(file_name);
                return -1;
            }
            free(file_name);
            break;
        case 'o':
            file_name = strdup (optarg);
            if(!(ost = fopen(file_name, "w+"))){
                fprintf(stderr, "Cannot open file: %s\n", file_name);
                free(file_name);
                return -1;
            }
            free(file_name);
            break;
        case 'h':
            printf("Usage:\n[-i]: The input file. By default input file stream is stdin.\n[-o]: The output file. By default output file stream is stdout.\n[-h]: Prints the help prompt.\n");
            return 0;
        default:
            printf("Wrong command line arguments. Run with \"-h\" for help.\n");
            return -1;    
        }
    }    

    yyparse();

    fclose(ost);
    fclose(yyin);
    
    return 0;   
}
