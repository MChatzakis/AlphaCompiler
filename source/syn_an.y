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
            | ID ASSIGN expr            {
                                            switch($3.type){
                                            case INT_T:
                                                printf("ASSIGN to ID: %s the value %d\n", $1, $3.int_val);
                                                break;
                                            case REAL_T:
                                                printf("ASSIGN to ID: %s the value %f\n", $1, $3.real_val);
                                                break;
                                            case STRING_T: 
                                                printf("ASSIGN to ID: %s the value %s\n", $1, $3.string_val);
                                                break;  
                                            }
                                            //printf("ASSIGN expression to ID %s\n", $1);
                                            //assign($1, $3);
                                        }
            | expr OR expr              {
                                            printf("OR expression\n");
                                            //$$ = $1 || $3;
                                        }
            | expr AND expr             {
                                            printf("AND expression\n");
                                            //$$ = $1 && $3;
                                        }
            | expr NOT_EQUAL expr       {
                                            printf("NOT EQUAL expression\n");
                                            //$$ = $1 != $3;
                                        }
            | expr EQUAL expr           {
                                            printf("EQUAL expression\n");
                                            //$$ = $1 == $3;
                                        }
            | expr LESS_EQUAL expr      {
                                            printf("LESS EQUAL expression\n");
                                            //$$ = $1 <= $3;
                                        }
            | expr LESS expr            {
                                            printf("LESS expression\n");
                                            //$$ = $1 < $3;
                                        }
            | expr GREATER_EQUAL expr   {
                                            printf("GREATER EQUAL\n");
                                            //$$ = $1 >= $3;
                                        }
            | expr GREATER expr         {
                                            printf("GREATER expression\n");
                                            //$$ = $1 > $3;
                                        }
            | expr PLUS expr            {
                                            //$$.a = $1.a + $3.a;
                                            if($1.type == REAL_T && $3.type == REAL_T){
                                                $$.type = REAL_T;
                                                $$.real_val = $1.real_val + $3.real_val;
                                                printf("PLUS expression = %f\n", $$.real_val);
                                            }else if($1.type == INT_T && $3.type == INT_T){
                                                $$.type = INT_T;
                                                $$.int_val = $1.int_val + $3.int_val;
                                                printf("PLUS expression = %d\n", $$.int_val);
                                            }else if($1.type == REAL_T && $3.type == INT_T){
                                                $$.type = REAL_T;
                                                $$.real_val = $1.real_val + $3.int_val;
                                                printf("PLUS expression = %f\n", $$.real_val);
                                            }else if($1.type == INT_T && $3.type == REAL_T){
                                                $$.type = REAL_T;
                                                $$.real_val = $1.int_val + $3.real_val;
                                                printf("PLUS expression = %f\n", $$.real_val);
                                            }else{
                                                yyerror("Addition with string is not valid!\n");
                                            }

                                        }
            | expr MINUS expr           {
                                            printf("MINUS expression\n");
                                            //$$ = $1 - $3;
                                        }
            | expr MUL expr             {
                                            printf("MULTIPLICATION expression\n");
                                            //$$ = $1 * $3;
                                        }
            | expr DIV expr             {
                                            printf("DIVISION expression\n");
                                            //$$ = $1 / $3;
                                        }
            | expr MODULO expr          {
                                            printf("MODULO expression\n");
                                            //$$ = $1 % $3;
                                        }
            ;

exprs : exprs expr | expr;


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
