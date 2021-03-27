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

//%type <expr_type> expr


/*Grammar*/
%%

program:    stmts
            |
            ;

stmt:       expr SEMICOLON              {printf("Expression Found\n");}
            | ifstmt                    {printf("IF Found\n");}
            | whilestmt                 {printf("WHILE Found\n");}
            | forstmt                   {printf("FOR Found\n");}
            | returnstmt                {printf("RETURN Found\n");}
            | BREAK SEMICOLON           {printf("BREAK Found\n");}
            | CONTINUE SEMICOLON        {printf("CONTINUE Found\n");}
            | block                     {printf("BLOCK Found\n");}
            | funcdef                   {printf("FUNCDEF Found\n");}
            | SEMICOLON                 {printf("COLON Found\n");}
            ;

stmts:      stmts stmt
            | stmt
            ;
            
expr:       lvalue ASSIGN expr          {printf("ASSIGNMENT Found\n");}
            | expr OR expr              {printf("OR Expression\n");}
            | expr AND expr             {printf("AND Expression\n");}
            | expr NOT_EQUAL expr       {printf("NOT_EQUAL Expression\n");}
            | expr EQUAL expr           {printf("EQUAL Expression\n");}
            | expr LESS_EQUAL expr      {printf("LESS_EQUAL Expression\n");}
            | expr LESS expr            {printf("LESS Expression\n");}
            | expr GREATER_EQUAL expr   {printf("GREATER_EQUAL Expression\n");}
            | expr GREATER expr         {printf("GREATER Expression\n");}
            | expr PLUS expr            {printf("PLUS Expression\n");}
            | expr MINUS expr           {printf("MINUS Expression\n");}
            | expr MUL expr             {printf("MUL Expression\n");}
            | expr DIV expr             {printf("DIV Expression\n");}
            | expr MODULO expr          {printf("MODULO Expression\n");}
            | LEFT_PARENTHESIS expr RIGHT_PARENTHESIS {printf("PARENTHESIS Expression\n");}
            | MINUS expr %prec UMINUS   {printf("UMINUS Expression\n");}
            | NOT expr                  {printf("NOT Expression\n");}
            | PLUS_PLUS lvalue          {printf("PLUSPLUS Expression\n");}
            | lvalue PLUS_PLUS          {printf("Expression PLUSPLUS\n");}
            | MINUS_MINUS lvalue        {printf("MINUSMINUS Expression\n");}
            | lvalue MINUS_MINUS        {printf("Expression MINUSMINUS\n");}
            | primary
            ;


primary:    lvalue
            | call
            | objectdef
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS
            | const
            ;

lvalue:    ID
            | LOCAL ID
            | DOUBLE_COLON ID
            | member
            ;


member:     lvalue FULLSTOP ID
            | lvalue LEFT_BRACKET expr RIGHT_BRACKET
            | call FULLSTOP ID
            | call LEFT_BRACKET expr RIGHT_BRACKET
            ;


call:       call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS
            | lvalue callsuffix
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS
            ;


callsuffix: normcall
            | methodcall
            ;


normcall:   LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  {printf("Gamw to spiti sou\n");}
            ;

methodcall: DOUBLE_COLON ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS
            ;

elist:       expr COMMA elist         {printf("Elist found\n");}
            | expr
            ;

objectdef:  LEFT_BRACKET indexed RIGHT_BRACKET
            | LEFT_BRACKET elist RIGHT_BRACKET
            | LEFT_BRACKET RIGHT_BRACKET
            ;

indexed:    PLUS PLUS PLUS PLUS indexedelem;

indexedelem:LEFT_BRACE expr COLON expr RIGHT_BRACE
            ;

block:      LEFT_BRACE RIGHT_BRACE
            | LEFT_BRACE stmts RIGHT_BRACE
            ;

funcdef:    FUNCTION ID LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS block
            ;

const:      INTEGER         {printf("Found INTEGER\n");}
            | REAL
            | STRING
            | NIL
            | TRUE
            | FALSE
            ;

idlist:     ;

ifstmt:     IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt 
            | IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt ELSE stmt
            ;

whilestmt:  WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt
            ;

forstmt:    FOR LEFT_PARENTHESIS elist SEMICOLON expr SEMICOLON elist SEMICOLON RIGHT_PARENTHESIS stmt
            ;

returnstmt: RETURN SEMICOLON
            | RETURN expr SEMICOLON
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
