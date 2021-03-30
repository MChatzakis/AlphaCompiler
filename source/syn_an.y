/*Prologue*/
%{
    #ifdef WIN32
    #define YY_NO_UNISTD_H
    static int isatty(int i) {return 0;}
    #elif _WIN32_WCE
    #define YY_NO_UNISTD_H
    static int isatty(void *i) {return 0;}
    #endif

    #define TRACE_PRINT 1

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
%}

/*Declarations*/
%start program

%union {
    int int_value;
    char* string_value;
    double real_value;

    SymbolTableEntry symTabEntry;
}

%token <int_value> INTEGER
%token <real_value> REAL
%token <string_value> ID
%token <string_value> STRING

%token LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET LEFT_PARENTHESIS RIGHT_PARENTHESIS SEMICOLON COMMA FULLSTOP COLON DOUBLE_FULLSTOP DOUBLE_COLON
%token IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND NOT OR LOCAL TRUE FALSE NIL
%token ASSIGN PLUS MINUS MUL DIV MODULO EQUAL NOT_EQUAL PLUS_PLUS MINUS_MINUS GREATER GREATER_EQUAL LESS LESS_EQUAL

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

%type <string_value> lvalue

/*Grammar*/
%%

program:    stmts
            |
            ;

stmt:       expr SEMICOLON              {
                                            if(TRACE_PRINT){
                                                printf("-> Expr Statement\n");
                                            }
                                        }
            | ifstmt                    {
                                            if(TRACE_PRINT){
                                                printf("-> If/Ifelse Statement\n");
                                            }
                                        }
            | whilestmt                 {
                                            if(TRACE_PRINT){
                                                printf("-> While Statement\n");
                                            }
                                        }
            | forstmt                   {
                                            if(TRACE_PRINT){
                                                printf("-> For Statement\n");
                                            }
                                        }
            | returnstmt                {
                                            if(TRACE_PRINT){
                                                printf("-> Return Statement\n");
                                            }
                                        }
            | BREAK SEMICOLON           {
                                            if(TRACE_PRINT){
                                                printf("-> Break Statement\n");
                                            }
                                        }
            | CONTINUE SEMICOLON        {
                                            if(TRACE_PRINT){
                                                printf("-> Continue Statement\n");
                                            }
                                        }
            | block                     {
                                            if(TRACE_PRINT){
                                                printf("-> Block Statement\n");
                                            }
                                        }
            | funcdef                   {
                                            if(TRACE_PRINT){
                                                printf("-> Func Def Statement\n");
                                            }
                                        }
            | SEMICOLON                 {
                                            if(TRACE_PRINT){
                                                printf("-> Semicolon Statement\n");
                                            }
                                        }
            ;

stmts:      stmts stmt
            | stmt
            ;
            
expr:       lvalue ASSIGN expr          {
                                            SymbolTableEntry *entry;
                                            
                                            if(TRACE_PRINT){
                                                printf("-> Assignment Expression\n");
                                            }

                                            entry = SymbolTable_lookup_general(symTab, $1, scope);
                                            if(entry != NULL){ 
                                               if(entry->type == 3){
                                                    fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Assigned value to User defined function \"%s\" at line %u\n", 
                                                            $1, yylineno);
                                                }
                                                else if(entry->type == 4){
                                                    fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Assigned value to Library function \"%s\" at line %u\n", 
                                                            $1, yylineno);
                                                }
                                            }

                                        }
            | expr OR expr              {
                                            if(TRACE_PRINT){
                                                printf("-> OR Expression\n");
                                            }
                                        }
            | expr AND expr             {
                                            if(TRACE_PRINT){
                                                printf("-> AND Expression\n");
                                            }
                                        }
            | expr NOT_EQUAL expr       {
                                            if(TRACE_PRINT){
                                                printf("-> != Expression\n");
                                            }
                                        }
            | expr EQUAL expr           {
                                            if(TRACE_PRINT){
                                                printf("-> == Expression\n");
                                            }
                                        }
            | expr LESS_EQUAL expr      {
                                            if(TRACE_PRINT){
                                                printf("-> <= Expression\n");
                                            }
                                        }
            | expr LESS expr            {
                                            if(TRACE_PRINT){
                                                printf("-> < Expression\n");
                                            }
                                        }
            | expr GREATER_EQUAL expr   {
                                            if(TRACE_PRINT){
                                                printf("-> >= Expression\n");
                                            }
                                        }
            | expr GREATER expr         {
                                            if(TRACE_PRINT){
                                                printf("-> > Expression\n");
                                            }
                                        }
            | expr PLUS expr            {
                                            if(TRACE_PRINT){
                                                printf("-> + Expression\n");
                                            }
                                            

                                        }
            | expr MINUS expr           {
                                            if(TRACE_PRINT){
                                                printf("-> - Expression\n");
                                            }
                                        }
            | expr MUL expr             {
                                            if(TRACE_PRINT){
                                                printf("-> * Expression\n");
                                            }
                                        }
            | expr DIV expr             {
                                            if(TRACE_PRINT){
                                                printf("-> / Expression\n");
                                            }
                                        }
            | expr MODULO expr          {
                                            if(TRACE_PRINT){
                                                printf("-> MOD Expression\n");
                                            }
                                        }
            | LEFT_PARENTHESIS expr RIGHT_PARENTHESIS {
                                            if(TRACE_PRINT){
                                                printf("-> ( Expression )\n");
                                            }
                                        }
            | MINUS expr %prec UMINUS   {
                                            if(TRACE_PRINT){
                                                printf("-> -Expression\n");
                                            }
                                        }
            | NOT expr                  {
                                           if(TRACE_PRINT){
                                                printf("-> NOT Expression\n");
                                            }
                                        }
            | PLUS_PLUS lvalue          {
                                            if(TRACE_PRINT){
                                                printf("-> ++val Expression\n");
                                            }
                                        }
            | lvalue PLUS_PLUS          {
                                            if(TRACE_PRINT){
                                                printf("-> val++ Expression\n");
                                            }
                                        }
            | MINUS_MINUS lvalue        {
                                            if(TRACE_PRINT){
                                                printf("-> --val Expression\n");
                                            }
                                        }
            | lvalue MINUS_MINUS        {
                                            if(TRACE_PRINT){
                                                printf("-> val-- Expression\n");
                                            }
                                        }
            | primary                   {
                                            if(TRACE_PRINT){
                                                printf("-> Primary Expression\n");
                                            }
                                        }
            ;

primary:    lvalue                      {
                                            SymbolTableEntry *entry;
                                            
                                            if(TRACE_PRINT){
                                                printf("-> lvalue \n");
                                            }
                                            
                                            entry = SymbolTable_lookup_general(symTab, $1, scope);
                                            if(entry != NULL ){
                                                if(entry->type == 3){
                                                    fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used User defined function \"%s\" as variable at line %u\n", 
                                                            $1, yylineno);
                                                }
                                                else if(entry->type == 4){
                                                    fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used Library function \"%s\" as variable at line %u\n", 
                                                            $1, yylineno);
                                                }
                                                
                                            }
                                        }
            | call                      {
                                            //calling function
                                            if(TRACE_PRINT){
                                                printf("-> Function Call\n");
                                            }

                                        }
            | objectdef                 {
                                            if(TRACE_PRINT){
                                                printf("-> Object definition\n");
                                            }
                                        }
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS    {
                                                                if(TRACE_PRINT){
                                                                    printf("-> (func definition)\n");
                                                                }
                                                            }
            | const                     {
                                            if(TRACE_PRINT){
                                                printf("-> Const\n");
                                            }
                                        }
            ;

lvalue:     ID                          {
                                            SymbolTableEntry *entry;

                                            if(TRACE_PRINT){
                                                printf("-> Identifier %s\n", $1);
                                            }
                                            
                                            
                                            if(!(entry = SymbolTable_lookup(symTab, $1, scope))){
                                                if(scope > 0){
                                                    //if(checkForLibFunc($1))
                                                      //  printf("Error this id is forbidden!\n");
                                                    //else
                                                        SymbolTable_insert(symTab, $1, scope, yylineno, LOCAL_ID);
                                                }
                                                else{
                                                    //if(checkForLibFunc($1))
                                                      //  printf("Error this id is forbidden!\n");
                                                    //else
                                                        SymbolTable_insert(symTab, 
                                                                $1, scope, yylineno, GLOBAL_ID);
                                                }
                                            }

                                            $$ = strdup($1);
                                        }

            | LOCAL ID                  {
                                            
                                            SymbolTableEntry *entry;

                                            if(TRACE_PRINT){
                                                printf("-> Local Identifier %s\n", $2);
                                            }

                                            if((entry = SymbolTable_lookup(symTab, $2, scope))){
                                                //fprintf_red(stdout, "Could not find global var!\n");
                                            }
                                            else{
                                                if(scope > 0){
                                                    SymbolTable_insert(symTab, 
                                                                $2, scope, yylineno, LOCAL_ID);
                                                }
                                                else{
                                                    SymbolTable_insert(symTab, 
                                                        $2, scope, yylineno, GLOBAL_ID);
                                                }
                                            }

                                            $$ = strdup($2);
                                        }
            | DOUBLE_COLON ID           {
                                            SymbolTableEntry *entry;

                                            if(TRACE_PRINT){
                                                printf("-> Global Identifier %s\n", $2);
                                            }

                                            if(!(entry = SymbolTable_lookup(symTab, $2, 0))){
                                                fprintf_red(stdout, "[Syntax Analysis] -- ERROR: Undefined global variable \"%s\" at line %lu\n", 
                                                    $2, yylineno);
                                            }

                                            $$ = strdup($2);
                                        }
            | member                    {
                                            if(TRACE_PRINT){
                                                printf("-> Member\n");
                                            }
                                        }
            ;


member:     lvalue FULLSTOP ID                          {
                                                            if(TRACE_PRINT){
                                                                printf("-> %s.%s\n", $1,$3);
                                                            }
                                                        }
            | lvalue LEFT_BRACKET expr RIGHT_BRACKET    {
                                                            if(TRACE_PRINT){
                                                                printf("-> %s [ expression ]\n", $1);
                                                            }
                                                        }
            | call FULLSTOP ID                          {
                                                            if(TRACE_PRINT){
                                                                printf("-> Call.%s\n", $3);
                                                            }
                                                        }
            | call LEFT_BRACKET expr RIGHT_BRACKET      {
                                                            if(TRACE_PRINT){
                                                                printf("-> call [ expr ]\n");
                                                            }
                                                        }
            ;


call:       call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS                                           {
                                                                                                        if(TRACE_PRINT){
                                                                                                            printf("-> Call ( elist )\n");
                                                                                                        }

                                                                                                    }
            | lvalue callsuffix                                                                     {
                                                                                                        if(TRACE_PRINT){
                                                                                                            printf("-> %s callsuffix\n", $1);
                                                                                                        }

                                                                                                    }
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS   {
                                                                                                        if(TRACE_PRINT){
                                                                                                            printf("-> Function Definition\n");
                                                                                                        }                                                                                                    }
            ;


callsuffix: normcall        {
                                if(TRACE_PRINT){
                                    printf("-> Normal Call\n");
                                }
                            }
            | methodcall    {
                                if(TRACE_PRINT){
                                    printf("-> Method Call\n");
                                }
                            }
            ;


normcall:   LEFT_PARENTHESIS elist RIGHT_PARENTHESIS    {
                                                            if(TRACE_PRINT){
                                                                printf("-> ( elist )\n");
                                                            }
                                                        }
            ;

methodcall: DOUBLE_FULLSTOP ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS     {
                                                                                if(TRACE_PRINT){
                                                                                    printf("-> ..%s ( elist )\n", $2);
                                                                                }
                                                                            }
            ;

elist:      expr                        {
                                            if(TRACE_PRINT){
                                                printf("-> expr\n");
                                            }
                                        }
            | elist COMMA expr          {
                                            if(TRACE_PRINT){
                                                printf("-> elist , expr\n");
                                            }
                                        }
            |                           {
                                            if(TRACE_PRINT){
                                                printf("-> Empty Elist\n");
                                            }
                                        }
            ;

objectdef:  LEFT_BRACKET indexed RIGHT_BRACKET  {
                                                    if(TRACE_PRINT){
                                                        printf("-> [ indexed ]\n");
                                                    }
                                                }
            | LEFT_BRACKET elist RIGHT_BRACKET  {
                                                    if(TRACE_PRINT){
                                                        printf("-> [ elist ]\n");
                                                    }
                                                }
            ;

indexed:    indexedelem                         {
                                                    if(TRACE_PRINT){
                                                        printf("-> Indexed Element\n");
                                                    }
                                                }
            | indexed COMMA indexedelem         {
                                                    if(TRACE_PRINT){
                                                        printf("-> Indexed , Indexed Element\n");
                                                    }
                                                }
            ;

indexedelem:LEFT_BRACE expr COLON expr RIGHT_BRACE      {
                                                            if(TRACE_PRINT){
                                                                printf("-> { expr : expr }\n");
                                                            }
                                                        }
            ;

block:      LEFT_BRACE {scope++;} RIGHT_BRACE                   {
                                                                    scope--;
                                                                    if(TRACE_PRINT){
                                                                        printf("-> Empty Block\n");
                                                                    }
                                                                }
            | LEFT_BRACE {scope++;} stmts RIGHT_BRACE           {
                                                                    scope--;
                                                                    if(TRACE_PRINT){
                                                                        printf("-> Statement Block\n");
                                                                    }
                                                                }
            ;



funcdef:    FUNCTION LEFT_PARENTHESIS {scope++;} idlist RIGHT_PARENTHESIS {scope--;} block      {
                                                                                                    if(TRACE_PRINT){
                                                                                                        printf("-> Function Definition without ID\n");
                                                                                                    }
                                                                                                }
            |FUNCTION ID {printf("Function name %s in scope %u\n", $2, scope);} LEFT_PARENTHESIS {scope++;} idlist RIGHT_PARENTHESIS {scope--;} block  {
                                                                                                    SymbolTableEntry *entry = NULL;
                                                                                                    if(TRACE_PRINT){
                                                                                                        printf("-> Function Definition with ID\n");
                                                                                                    }
                                                                                                    entry = SymbolTable_lookup(symTab, $2, scope);
                                                                                                    if(entry != NULL || checkForLibFunc($2)){
                                                                                                        printf("error found function declaration\n");
                                                                                                    }
                                                                                                    else{
                                                                                                        SymbolTable_insert(symTab, $2, scope, yylineno, USERFUNC_ID);
                                                                                                    }
                                                                                                }
            ;

const:      INTEGER         {
                                if(TRACE_PRINT){
                                    printf("-> Integer %d\n", $1);
                                }
                            }
            | REAL          {
                                if(TRACE_PRINT){
                                    printf("-> Real %f\n", $1);
                                }
                            }
            | STRING        {
                               if(TRACE_PRINT){
                                    printf("-> String %s\n", $1);
                                }
                            }
            | NIL           {
                                if(TRACE_PRINT){
                                    printf("-> NIL\n");
                                }
                            }
            | TRUE          {
                                if(TRACE_PRINT){
                                    printf("-> TRUE\n");
                                }
                            }
            | FALSE         {
                                if(TRACE_PRINT){
                                    printf("-> FALSE");
                                }
                            }
            ;

idlist:     ID                  {
                                    if(TRACE_PRINT){
                                        printf("-> Single ID List %s\n", $1);
                                    }
                                    if(checkForLibFunc($1))
                                        printf("Error this id is forbidden!\n");
                                    else
                                        SymbolTable_insert(symTab, $1, scope, yylineno, FORMAL_ID);
                                }
            | idlist COMMA ID   {
                                    if(TRACE_PRINT){
                                        printf("-> , ID List %s\n", $3);
                                    }
                                    if(checkForLibFunc($3))
                                        printf("Error this id is forbidden!\n");
                                    else
                                        SymbolTable_insert(symTab, $3, scope, yylineno, FORMAL_ID);
                                }
            |                   {
                                    if(TRACE_PRINT){
                                        printf("-> , Empty ID List\n");
                                    }
                                }
            ;

ifstmt:     IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt                 {
                                                                                if(TRACE_PRINT){
                                                                                    printf("-> If\n");
                                                                                }
                                                                            }
            | IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt ELSE stmt     {
                                                                                if(TRACE_PRINT){
                                                                                    printf("-> If Else\n");
                                                                                }
                                                                            }
            ;

whilestmt:  WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt              {
                                                                                if(TRACE_PRINT){
                                                                                    printf("-> While\n");
                                                                                }
                                                                            }
            ;

forstmt:    FOR LEFT_PARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESIS stmt    {
                                                                                                    if(TRACE_PRINT){
                                                                                                        printf("-> For\n");
                                                                                                    }
                                                                                                }
            ;

returnstmt: RETURN SEMICOLON            {
                                            if(TRACE_PRINT){
                                                printf("-> Simple Return\n");
                                            }
                                        }
            | RETURN expr SEMICOLON     {
                                            if(TRACE_PRINT){
                                                printf("-> Expr Return\n");
                                            }
                                        }
            ;

%%

int yyerror(char *message){
    fprintf_red(stderr, "[Syntax Analysis] -- ERROR: %s: at line %d, on token: %s\n", message, yylineno, yytext);
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
