/*Prologue*/
%{
    #ifdef WIN32
    #define YY_NO_UNISTD_H
    static int isatty(int i) {return 0;}
    #elif _WIN32_WCE
    #define YY_NO_UNISTD_H
    static int isatty(void *i) {return 0;}
    #endif

    #include "yacc_libs/yacc_api.h"

%}

/*Declarations*/
%start program

%union {
    int int_value;
    char* string_value;
    double real_value;

    SymbolTableEntry *symTabEntry;
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

%type <symTabEntry> lvalue
%type <symTabEntry> funcdef
%type <symTabEntry> call
%type <symTabEntry> member


/*Grammar*/
%%

program:    stmts
            |
            ;

stmt:       expr SEMICOLON              {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Expr Statement\n");
                                            }
                                        }
            | ifstmt                    {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>If/Ifelse Statement\n");
                                            }
                                        }
            | whilestmt                 {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>While Statement\n");
                                            }
                                        }
            | forstmt                   {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>For Statement\n");
                                            }
                                        }
            | returnstmt                {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Return Statement\n");
                                            }
                                        }
            | BREAK SEMICOLON           {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Break Statement\n");
                                            }
                                        }
            | CONTINUE SEMICOLON        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Continue Statement\n");
                                            }
                                        }
            | block                     {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Block Statement\n");
                                            }
                                        }
            | funcdef                   {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Func Def Statement\n");
                                            }
                                        }
            | SEMICOLON                 {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Semicolon Statement\n");
                                            }
                                        }
            ;

stmts:      stmts stmt
            | stmt
            ;

expr:       lvalue ASSIGN expr          {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Assignment\n");
                                            }
                                            ManageAssignValue($1);
                                        }
            | expr OR expr              {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>OR\n");
                                            }
                                        }
            | expr AND expr             {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>AND\n");
                                            }
                                        }
            | expr NOT_EQUAL expr       {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>NOT EQUAL\n");
                                            }
                                        }
            | expr EQUAL expr           {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>EQUAL\n");
                                            }
                                        }
            | expr LESS_EQUAL expr      {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>LESS EQUAL\n");
                                            }
                                        }
            | expr LESS expr            {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>LESS\n");
                                            }
                                        }
            | expr GREATER_EQUAL expr   {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>GREATER EQUAL\n");
                                            }
                                        }
            | expr GREATER expr         {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>GREATER\n");
                                            }
                                        }
            | expr PLUS expr            {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>PLUS\n");
                                            }
                                        }
            | expr MINUS expr           {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MINUS\n");
                                            }
                                        }
            | expr MUL expr             {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MUL\n");
                                            }
                                        }
            | expr DIV expr             {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>DIV\n");
                                            }
                                        }
            | expr MODULO expr          {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MODULO\n");
                                            }
                                        }
            | LEFT_PARENTHESIS expr RIGHT_PARENTHESIS 
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>PARENTHESIS EXPR\n");
                                            }
                                        }
            | MINUS expr %prec UMINUS   {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>-EXPR\n");
                                            }
                                        }
            | NOT expr                  {
                                           if(TRACE_PRINT){
                                                fprintf(ost, "=>NOT\n");
                                            }
                                        }
            | PLUS_PLUS lvalue          {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>PLUS PLUS lvalue\n");
                                            }
                                            ManageAssignValue($2);
                                        }
            | lvalue PLUS_PLUS          {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>lvalue PLUS PLUS\n");
                                            }
                                            ManageAssignValue($1);
                                        }
            | MINUS_MINUS lvalue        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MINUS MINUS lvalue\n");
                                            }
                                            ManageAssignValue($2);
                                        }
            | lvalue MINUS_MINUS        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>lvalue MINUS MINUS\n");
                                            }
                                            ManageAssignValue($1);
                                        }
            | primary                   {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>PRIMARY\n");
                                            }
                                        }
            ;

primary:    lvalue                      {                                 
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>lvalue \n");
                                            }
                                            ManagePrimaryLValue($1);    
                                        }
            | call                      {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>CALL\n");
                                            }
                                            ManagePrimaryFunction($1);
                                        }
            | objectdef                 {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>OBJECT DEF\n");
                                            }
                                        }
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS    
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>(funcdef)\n");
                                            }
                                        }
            | const                     {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>CONST\n");
                                            }
                                        }
            ;

lvalue:     ID                          {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>ID %s\n", $1);
                                            }
                                            $$ = EvaluateLValue($1);
                                        }

            | LOCAL ID                  {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=> local ID %s\n", $2);
                                            }
                                            $$ = EvaluateLocalLValue($2);
                                        }
            | DOUBLE_COLON ID           {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>global ID %s\n", $2);
                                            }
                                            $$ = EvaluateGlobalLValue($2);
                                        }
            | member                    {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MEMBER\n");
                                            }
                                            $$ = NULL;
                                        }
            ;

member:     lvalue FULLSTOP ID                          {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>lvalue . ID %s\n", $3);
                                                            }
                                                        }
            | lvalue LEFT_BRACKET expr RIGHT_BRACKET    {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>lvalue [ EXPR ]\n");
                                                            }
                                                        }
            | call FULLSTOP ID                          {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>Call.ID %s\n", $3);
                                                            }
                                                        }
            | call LEFT_BRACKET expr RIGHT_BRACKET      {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>CALL [ EXPR ]\n");
                                                            }
                                                        }
            ;

call:       call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS   {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>CALL ( ELIST )\n");
                                                                }                                    
                                                                $$ = $1;
                                                            }
            | call LEFT_PARENTHESIS RIGHT_PARENTHESIS       {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>CALL ( empty )\n");
                                                                }                                       
                                                                $$ = $1;
                                                            }
            | lvalue callsuffix                             {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>lvalue ( CALL SUFFIX )\n");                                       
                                                                }
                                                                $$ = $1;
                                                            }
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS   
                                                            {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>(FUNCDEF)(ELIST)\n");
                                                                }
                                                                $$ = $2;    
                                                            }
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS RIGHT_PARENTHESIS 
                                                            {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>(FUNCDEF)(empty)\n");
                                                                }
                                                                $$ = $2;    
                                                            }                                                                                        
            ;

callsuffix: normcall        {
                                if(TRACE_PRINT){
                                    fprintf(ost, "=>NORMAL CALL\n");
                                }
                            }
            | methodcall    {
                                if(TRACE_PRINT){
                                    fprintf(ost, "=>METHOD CALL\n");
                                }
                            }
            ;

normcall:   LEFT_PARENTHESIS elist RIGHT_PARENTHESIS    {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>(ELIST)\n");
                                                            }
                                                        }
            | LEFT_PARENTHESIS RIGHT_PARENTHESIS        {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>(empty)\n");
                                                            }
                                                        }                                            
            ;

methodcall: DOUBLE_FULLSTOP ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS     {
                                                                                if(TRACE_PRINT){
                                                                                    fprintf(ost, "=> ..%s (ELIST)\n", $2);
                                                                                }
                                                                            }
            | DOUBLE_FULLSTOP ID LEFT_PARENTHESIS RIGHT_PARENTHESIS         {
                                                                                if(TRACE_PRINT){
                                                                                    fprintf(ost, "=> ..%s (empty)\n", $2);
                                                                                }
                                                                            }                                                                
            ;

elist:      expr                {
                                    if(TRACE_PRINT){
                                        fprintf(ost, "=>EXPR\n");
                                    }
                                }
            | elist COMMA expr  {
                                    if(TRACE_PRINT){
                                        fprintf(ost, "=>ELIST , EXPR\n");
                                    }
                                }
            ;

objectdef:  LEFT_BRACKET indexed RIGHT_BRACKET  {
                                                    if(TRACE_PRINT){
                                                        fprintf(ost, "=>[INDEXED]\n");
                                                    }
                                                }
            | LEFT_BRACKET elist RIGHT_BRACKET  {
                                                    if(TRACE_PRINT){
                                                        fprintf(ost, "=>[ELIST]\n");
                                                    }
                                                }
            | LEFT_BRACKET  RIGHT_BRACKET       {
                                                    if(TRACE_PRINT){
                                                        fprintf(ost, "=>[empty]\n");
                                                    }
                                                }
            ;

indexed:    indexedelem                 {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>INDEXED_ELEM\n");
                                            }
                                        }
            | indexed COMMA indexedelem {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=> INDEXED , INDEXED_ELEM\n");
                                            }
                                        }
            ;

indexedelem:LEFT_BRACE expr COLON expr RIGHT_BRACE  {
                                                        if(TRACE_PRINT){
                                                            fprintf(ost, "=>{EXPR : EXPR}\n");
                                                        }
                                                    }
            ;

block:      LEFT_BRACE {scope++;} RIGHT_BRACE           {
                                                            ScopeTable_hide_scope(scopeTab, scope);
                                                            scope--;
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>{Empty}\n");
                                                            }
                                                        }
            | LEFT_BRACE {scope++;} stmts RIGHT_BRACE   {
                                                            ScopeTable_hide_scope(scopeTab, scope);
                                                            scope--;
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>{STMTS}\n");
                                                            }
                                                        }
            ;



funcdef:    FUNCTION LEFT_PARENTHESIS   { 
                                            GenerateName(); 
                                            ManageIDFunctionDefinition(noname_prefix);
                                            unamed_functions++;
                                            scope++;
                                        } 
                                        idlist RIGHT_PARENTHESIS {scope--;} block   {
                                                                                        if(TRACE_PRINT){
                                                                                            fprintf(ost, "=>FUNCDEF without ID, with IDLIST\n");
                                                                                        } 
                                                                                        $$ = SymbolTable_lookup(symTab, noname_prefix, scope);
                                                                                        //FuncStack_print(functionStack);
                                                                                        FuncStack_pop(functionStack);                                  
                                                                                    }
            |FUNCTION LEFT_PARENTHESIS RIGHT_PARENTHESIS    { 
                                                                GenerateName();
                                                                ManageIDFunctionDefinition(noname_prefix);
                                                                unamed_functions++;
                                                            }
                                                            block   {
                                                                        if(TRACE_PRINT){
                                                                            fprintf(ost, "=>FUNCDEF without ID, without IDLIST\n");
                                                                        }
                                                                        $$ = SymbolTable_lookup(symTab, noname_prefix, scope);
                                                                        //FuncStack_print(functionStack);
                                                                        FuncStack_pop(functionStack); 
                                                                    }
            |FUNCTION ID LEFT_PARENTHESIS   {
                                                ManageIDFunctionDefinition($2);
                                                scope++;
                                            } 
                                            idlist RIGHT_PARENTHESIS {scope--;} block  
                                                                                    {
                                                                                        if(TRACE_PRINT){
                                                                                            printf("=>FUNCDEF with ID, with IDLIST\n");
                                                                                        }
                                                                                        $$ = SymbolTable_lookup(symTab, $2, scope); //care for libfunc ID
                                                                                        //FuncStack_print(functionStack);
                                                                                        FuncStack_pop(functionStack); 
                                                                                    }
            |FUNCTION ID LEFT_PARENTHESIS RIGHT_PARENTHESIS { 
                                                                ManageIDFunctionDefinition($2);
                                                            } block  
                                                                                    {
                                                                                        if(TRACE_PRINT){
                                                                                            printf("=>FUNCDEF with ID, without IDLIST\n");
                                                                                        }
                                                                                        $$ = SymbolTable_lookup(symTab, $2, scope); //care for libfunc ID
                                                                                        //FuncStack_print(functionStack);
                                                                                        FuncStack_pop(functionStack);
                                                                                    }
            ;

const:      INTEGER     {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>INTEGER %d\n", $1);
                            }
                        }
            | REAL      {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>Real %f\n", $1);
                            }
                        }
            | STRING    {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>String %s\n", $1);
                            }
                        }
            | NIL       {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>NIL\n");
                            }
                        }
            | TRUE      {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>TRUE\n");
                            }
                        }
            | FALSE     {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>FALSE");
                            }
                        }
            ;

idlist:     ID                  {
                                    if(TRACE_PRINT){
                                        fprintf(ost, "=>ID %s\n", $1);
                                    }
                                    CheckAddFormal($1);
                                }
            | idlist COMMA ID   {
                                    if(TRACE_PRINT){
                                        fprintf(ost, "=>IDLIST , ID %s\n", $3);
                                    }
                                    CheckAddFormal($3);
                                }
            ;

ifstmt:     
            IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt ELSE stmt   {
                                                                            if(TRACE_PRINT){
                                                                                fprintf(ost, "=>IF(EXPR)STMT ELSE STMT\n");
                                                                            }
                                                                        }
            | IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt           {
                                                                            if(TRACE_PRINT){
                                                                                fprintf(ost, "=>IF(EXPR) STMT\n");
                                                                            }
                                                                        }                                                                
            ;

whilestmt:  WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt  {
                                                                    if(TRACE_PRINT){
                                                                        fprintf(ost, "=>while(EXPR)\n");
                                                                    }
                                                                }
            ;

forstmt:    FOR LEFT_PARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESIS stmt    {
                                                                                                    if(TRACE_PRINT){
                                                                                                        fprintf(ost, "=>for(ELIST; EXPR; ELIST)\n");
                                                                                                    }
                                                                                                }
            |FOR LEFT_PARENTHESIS SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESIS stmt         {
                                                                                                    if(TRACE_PRINT){
                                                                                                        fprintf(ost, "->for(; EXPR; ELIST)\n");
                                                                                                    }
                                                                                                }
            |FOR LEFT_PARENTHESIS elist SEMICOLON expr SEMICOLON RIGHT_PARENTHESIS stmt         {
                                                                                                    if(TRACE_PRINT){
                                                                                                        fprintf(ost, "->for(ELIST; EXPR;)\n");
                                                                                                    }
                                                                                                }
            |FOR LEFT_PARENTHESIS SEMICOLON expr SEMICOLON RIGHT_PARENTHESIS stmt               {
                                                                                                    if(TRACE_PRINT){
                                                                                                        fprintf(ost, "->for(; EXPR;)\n");
                                                                                                    }
                                                                                                }
            ;

returnstmt: RETURN SEMICOLON        {
                                        if(TRACE_PRINT){
                                            fprintf(ost, "=>ret;\n");
                                        }
                                    }
            | RETURN expr SEMICOLON {
                                        if(TRACE_PRINT){
                                            fprintf(ost, "=>ret EXPR;\n");
                                        }
                                    }
            ;

%%

int yyerror(char *message){
    fprintf_red(stderr, "[Syntax Analysis] -- ERROR: %s: at line %d, on token: %s\n", message, yylineno, yytext);
    return 0;
}

int main(int argc, char **argv){

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

    InitNames();

    symTab = SymbolTable_init();
    scopeTab = ScopeTable_init();

    functionStack = FuncStack_init();

    SymbolTable_add_libfun(symTab, scopeTab);

    yyparse();

    ScopeTable_print(scopeTab, ost);
    //SymbolTable_print(symTab, ost);

    fclose(ost);
    fclose(yyin);
    
    return 0;   
}
