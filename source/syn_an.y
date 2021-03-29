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
    #include "yacc_libs/structs.h"

    #include "symboltable/symboltable.h"

    int yyerror(char *message);
    int yylex(void);

    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;

    unsigned int scope = 0;
    SymbolTable *symTab;

    short idRequired = 0;

%}

/*Declarations*/
%start program

%union {
    int int_value;
    char* string_value;
    double real_value;

    gen_value g_val;
    SymbolTableEntry symTabEntry;
}

%token <int_value> INTEGER
%token <real_value> REAL
%token <string_value> ID
%token <string_value> STRING

%token LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET LEFT_PARENTHESIS RIGHT_PARENTHESIS SEMICOLON COMMA FULLSTOP COLON DOUBLE_FULLSTOP DOUBLE_COLON
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

%type <g_val> expr
%type <g_val> primary
%type <g_val> const
%type <string_value> lvalue

/*Grammar*/
%%

program:    stmts
            |
            ;

stmt:       expr SEMICOLON              {
                                            //printf("STMT: Expression Found\n");
                                        }
            | ifstmt                    {
                                            //printf("STMT: IF Found\n");
                                        }
            | whilestmt                 {
                                            //printf("STMT: WHILE Found\n");
                                        }
            | forstmt                   {
                                            //printf("STMT: FOR Found\n");
                                        }
            | returnstmt                {
                                            //printf("STMT: RETURN Found\n");
                                        }
            | BREAK SEMICOLON           {
                                            //printf("STMT: BREAK Found\n");
                                        }
            | CONTINUE SEMICOLON        {
                                            //printf("STMT: CONTINUE Found\n");
                                        }
            | block                     {
                                            //printf("STMT: BLOCK Found\n");
                                        }
            | funcdef                   {
                                            //printf("STMT: FUNCDEF Found\n");
                                        }
            | SEMICOLON                 {
                                            //printf("STMT: COLON Found\n");
                                        }
            ;

stmts:      stmts stmt
            | stmt
            ;
            
expr:       lvalue ASSIGN expr          {
                                            //lookup - insert lvalue
                                            printf("Assign -- LookUp -> Insert\n");
                                            SymbolTableEntry *entry;
                                            entry = SymbolTable_lookup_general(symTab, $1, scope);
                                            if(entry->type >= 3 ){ //|| (entry->value).funcval->scope < scope ||  (entry->value).funcval->scope > 0
                                                printf("error found function\n");
                                            }

                                        }
            | expr OR expr              {
                                            //printf("EXPR: OR Expression\n");
                                        }
            | expr AND expr             {
                                            //printf("EXPR: AND Expression\n");
                                        }
            | expr NOT_EQUAL expr       {
                                            //printf("EXPR: NOT_EQUAL Expression\n");
                                        }
            | expr EQUAL expr           {
                                            //printf("EXPR: EQUAL Expression\n");
                                        }
            | expr LESS_EQUAL expr      {
                                            //printf("EXPR: LESS_EQUAL Expression\n");
                                        }
            | expr LESS expr            {
                                            //printf("EXPR: LESS Expression\n");
                                        }
            | expr GREATER_EQUAL expr   {
                                            //printf("EXPR: GREATER_EQUAL Expression\n");
                                        }
            | expr GREATER expr         {
                                            //printf("EXPR: GREATER Expression\n");
                                        }
            | expr PLUS expr            {
                                            //printf("EXPR: PLUS Expression\n");
                                            //$$.type = INT_VAL;
                                            //$$.int_val = $1.int_val + $3.int_val;
                                        }
            | expr MINUS expr           {
                                            //printf("EXPR: MINUS Expression\n");
                                        }
            | expr MUL expr             {
                                            //printf("EXPR: MUL Expression\n");
                                        }
            | expr DIV expr             {
                                            //printf("EXPR: DIV Expression\n");
                                        }
            | expr MODULO expr          {
                                            //printf("EXPR: MODULO Expression\n");
                                        }
            | LEFT_PARENTHESIS expr RIGHT_PARENTHESIS {
                                            //printf("EXPR: PARENTHESIS Expression\n");
                                        }
            | MINUS expr %prec UMINUS   {
                                            //printf("EXPR: UMINUS Expression\n");
                                        }
            | NOT expr                  {
                                            //printf("EXPR: NOT Expression\n");
                                        }
            | PLUS_PLUS lvalue          {
                                            //printf("EXPR: PLUS_PLUS Expression\n");
                                        }
            | lvalue PLUS_PLUS          {
                                            //printf("EXPR: Expression PLUS_PLUS\n");
                                        }
            | MINUS_MINUS lvalue        {
                                            //printf("EXPR: MINUS_MINUS Expression\n");
                                        }
            | lvalue MINUS_MINUS        {
                                            //printf("EXPR: Expression MINUS_MINUS\n");
                                        }
            | primary                   {
                                            //printf("EXPR: Primary\n");
                                            //print_gen($$);
                                        }
            ;

primary:    lvalue                      {
                                            //seeking variable
                                            printf("PRIMARY RULE: Variable Call -- Required\n");
                                            SymbolTableEntry *entry;
                                            entry = SymbolTable_lookup_general(symTab, $1, scope);
                                            if(entry->type >= 3 ){
                                                printf("error found function\n");
                                            }
                                        }
            | call                      {
                                            //calling function
                                            printf("PRIMARY RULE: Function Call -- Required\n");

                                        }
            | objectdef                 {
                                            printf("PRIMARY: Found objectdef\n");

                                        }
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS    {
                                                                //printf("PRIMARY: Found (func def)\n");
                                                            }
            | const                     {
                                            //printf("PRIMARY: Found const\n");
                                            //print_gen($$);
                                        }
            ;

lvalue:     ID                          {
                                            SymbolTableEntry *entry;
                                            printf("ID: %s\n", $1);
                                            
                                            
                                            if(!(entry = SymbolTable_lookup(symTab, $1, scope))){
                                                if(scope > 0){
                                                    SymbolTable_insert(symTab, $1, scope, yylineno, LOCAL_ID);
                                                }
                                                else{
                                                    SymbolTable_insert(symTab, $1, scope, yylineno, GLOBAL_ID);
                                                }
                                            }

                                            $$ = strdup($1);
                                        }

            | LOCAL ID                  {
                                            printf("LOCAL ID: %s\n", $2);
                                        }
            | DOUBLE_COLON ID           {
                                            /*printf("GLOBAL ID: %s\n", $2);
                                            if(!lookup($2, 0)){
                                                error
                                            }*/
                                        }
            | member                    {
                                            
                                        }
            ;


member:     lvalue FULLSTOP ID                          {
                                                            //printf("MEMBER: Found lvalue . ID\n");
                                                        }
            | lvalue LEFT_BRACKET expr RIGHT_BRACKET    {
                                                            //printf("MEMBER: Found lvalue[expr]\n");
                                                        }
            | call FULLSTOP ID                          {
                                                            //printf("MEMBER: Found call . ID\n");
                                                        }
            | call LEFT_BRACKET expr RIGHT_BRACKET      {
                                                            //printf("MEMBER: Found call[expr]\n");
                                                        }
            ;


call:       call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS                                           {
                                                                                                        printf("CALL: Found call(elist)\n");
                                                                                                    }
            | lvalue callsuffix                                                                     {
                                                                                                        printf("CALL: Found lvalue callsuffix\n");
                                                                                                    }
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS   {
                                                                                                        printf("CALL: Found (funcdef)(elist)\n");
                                                                                                    }
            ;


callsuffix: normcall        {
                                printf("CALLSUFFIX: Found normcall\n");
                            }
            | methodcall    {
                                //printf("CALLSUFFIX: Found methodcall\n");
                            }
            ;


normcall:   LEFT_PARENTHESIS elist RIGHT_PARENTHESIS    {
                                                            printf("NORMCALL: (elist)\n");
                                                        }
            ;

methodcall: DOUBLE_FULLSTOP ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS     {
                                                                                //printf("METHODCALL: ..ID(elist)\n");
                                                                            }
            ;

elist:      expr                        {
                                            printf("SINGLE ELIST: Found FORMAL argument in scope\n");
                                        }
            | elist COMMA expr          {
                                            printf("MULTI ELIST: Found FORMAL argument\n");
                                        }
            |                           {
                                            printf("ELIST: Empty eList\n");
                                        }
            ;

objectdef:  LEFT_BRACKET indexed RIGHT_BRACKET  {
                                                    //printf("OBJECTDEF: Defined Object with indexed elems\n");
                                                }
            | LEFT_BRACKET elist RIGHT_BRACKET  {
                                                    //printf("OBJECTDEF: Defined Object with elist elems\n");
                                                }
            ;

indexed:    indexedelem                         {
                                                    //printf("INDEXED: Single indexed elem\n");
                                                }
            | indexed COMMA indexedelem         {
                                                    //printf("INDEXED: Multi indexed elem\n");
                                                }
            ;

indexedelem:LEFT_BRACE expr COLON expr RIGHT_BRACE      {
                                                            //printf("INDEXEDELEM: expr : expr found\n");
                                                        }
            ;

block:      LEFT_BRACE {scope++;} RIGHT_BRACE                   {
                                                                    scope--;
                                                                    //printf("BLOCK: {}\n");
                                                                }
            | LEFT_BRACE {scope++;} stmts RIGHT_BRACE           {
                                                                    scope--;
                                                                    //printf("BLOCK: { ... }\n");
                                                                }
            ;



funcdef:    FUNCTION LEFT_PARENTHESIS {scope++;} idlist RIGHT_PARENTHESIS {scope--;} block      {
                                                                                                   
                                                                                                    //printf("FUNCDEF: Function def WITHOUT ID found\n");
                                                                                                }
            |FUNCTION ID {printf("Function name %s in scope %u\n", $2, scope);} LEFT_PARENTHESIS {scope++;} idlist RIGHT_PARENTHESIS {scope--;} block  {
                                                                                                    //edw to id prepei na min iparxei!
                                                                                                    //printf("FUNCDEF: Function def WITH ID found\n");
                                                                                                    SymbolTableEntry *entry = NULL;
                                                                                                    entry = SymbolTable_lookup(symTab, $2, scope);
                                                                                                    if(entry != NULL){
                                                                                                        printf("error found function declaration\n");

                                                                                                    }
                                                                                                    else{
                                                                                                        SymbolTable_insert(symTab, $2, scope, yylineno, USERFUNC_ID);
                                                                                                    }
                                                                                                }
            ;

const:      INTEGER         {
                                //printf("CONST: Found INTEGER: ");
                                //$$.type = INT_VAL;
                                //$$.int_val = $1;
                                //print_gen($$);
                            }
            | REAL          {
                                //printf("CONST: Found REAL\n");
                            }
            | STRING        {
                                //printf("CONST: Found STRING\n");
                            }
            | NIL           {
                                //printf("CONST: Found NIL\n");
                            }
            | TRUE          {
                                //printf("CONST: Found TRUE\n");
                            }
            | FALSE         {
                                //printf("CONST: Found FALSE\n");
                            }
            ;

idlist:     ID                  {
                                    printf("SINGLE IDLIST: Found FORMAL argument %s in scope %u\n", $1, scope);
                                    SymbolTable_insert(symTab, $1, scope, yylineno, FORMAL_ID);
                                }
            | idlist COMMA ID   {
                                    //printf("IDLIST: Found ID %s in scope %u\n", $3, scope);
                                    //printf("MULTI IDLIST: Found FORMAL argument %s in scope %u\n", $3, scope);
                                    SymbolTable_insert(symTab, $3, scope, yylineno, FORMAL_ID);
                                }
            |                   {
                                    //printf("IDLIST: Empty\n");
                                }
            ;

ifstmt:     IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt                 {
                                                                                //printf("IFSTMT: IF statement\n");
                                                                            }
            | IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt ELSE stmt     {
                                                                                //printf("IFSTMT: IF ELSE statement\n");
                                                                            }
            ;

whilestmt:  WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt              {
                                                                                //printf("WHILE: ..\n");
                                                                            }
            ;

forstmt:    FOR LEFT_PARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESIS stmt    {
                                                                                                    //printf("FOR: ..\n");
                                                                                                }
            ;

returnstmt: RETURN SEMICOLON            {
                                            //printf("RETURN: WITHOUT expr\n");
                                        }
            | RETURN expr SEMICOLON     {
                                            //printf("RETURN: WITH expr\n");
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

    symTab = SymbolTable_init();
    SymbolTable_add_libfun(symTab);

    yyparse();

    SymbolTable_print(symTab);

    fclose(ost);
    fclose(yyin);
    
    return 0;   
}
