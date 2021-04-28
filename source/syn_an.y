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
    unsigned un_value;
    char* string_value;
    double real_value;
    expr* exprVal;
    call* callFunc;
    indexedPair* indPair;
    SymbolTableEntry *symTabEntry;
    forPrefixJumps* forPrefJumps;
    stmt_t *st;
}

%token <int_value> INTEGER
%token <real_value> REAL
%token <string_value> ID STRING

%token LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET LEFT_PARENTHESIS RIGHT_PARENTHESIS SEMICOLON COMMA FULLSTOP COLON DOUBLE_FULLSTOP DOUBLE_COLON
%token IF ELSE WHILE FOR FUNCTION BREAK CONTINUE RETURN AND NOT OR LOCAL TRUE FALSE NIL
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

%type <exprVal> lvalue expr member primary call elist objectdef const 
%type <indPair> indexedelem indexed
%type <callFunc> callsuffix normcall methodcall
%type <string_value> funcname
%type <un_value>    funcbody ifprefix elseprefix whilestart whilecond M N
%type <symTabEntry>  funcprefix funcdef
%type <forPrefJumps> forprefix
%type <st> stmt stmts loopstmt whilestmt

/*Grammar*/
%%

program:    stmts
            |
            ;

stmt:       expr SEMICOLON              {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Expr Statement (stmt -> expr;)\n");
                                            }
                                            $$ = newstmt();
                                            resettemp();
                                        }
            | ifstmt                    {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>If/Ifelse Statement (stmt -> ifstmt)\n");
                                            }
                                            $$ = newstmt();
                                            resettemp();
                                        }
            | whilestmt                 {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>While Statement (stmt -> whilestmt)\n");
                                            }
                                            //$$ = newstmt();
                                            
                                            $$ = $1;
                                            resettemp();
                                        }
            | forstmt                   {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>For Statement (stmt -> forstmt)\n");
                                            }

                                            resettemp();
                                            $$ = newstmt();
                                        }
            | returnstmt                {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Return Statement (stmt -> return)\n");
                                            }

                                            resettemp();

                                            $$ = newstmt();
                                        }
            | BREAK SEMICOLON           {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Break Statement (stmt -> break)\n");
                                            }
                                            $$ = ManageBreak();
                                            //$$ = newstmt();
                                            resettemp();
                                        }
            | CONTINUE SEMICOLON        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Continue Statement (stmt -> continue;)\n");
                                            }
                                            $$ = ManageContinue();
                                            resettemp();
                                        }
            | block                     {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Block Statement (stmt -> block)\n");
                                            }

                                            resettemp();
                                            $$ = newstmt();
                                        }
            | funcdef                   {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Func Def Statement (stmt -> funcdef)\n");
                                            }

                                            resettemp();
                                            $$ = newstmt();
                                        }
            | SEMICOLON                 {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Semicolon Statement (stmt -> ;)\n");
                                            }

                                            resettemp();
                                            $$ = newstmt();
                                        }
            ;

stmts:      stmts stmt                  {
                                           
                                            //$$ = newstmt();
                                            $$->breakList = mergelist($1->breakList, $2->breakList);
                                            $$->contList = mergelist($1->contList, $2->contList); 
                                        
                                        }
            | stmt                      {
                                            $$ = $1;
                                        }
            ;

expr:       lvalue ASSIGN expr          {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Assignment Expression (expr -> lvalue = expr)\n");
                                            }
                                            $$ = ManageAssignValue($1, $3);
                                        }
            | expr OR expr              {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>OR Expression (expr -> expr or expr)\n");
                                            }
                                            
                                        }
            | expr AND expr             {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>AND Expression (expr -> expr and expr)\n");
                                            }
                                        }
            | expr NOT_EQUAL expr       {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>NOT EQUAL Expression (expr -> expr != expr)\n");
                                            }

                                            $$ = ManageRelationExpression($1, if_noteq_op, $3);
                                        }
            | expr EQUAL expr           {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>EQUAL Expression (expr -> expr == expr)\n");
                                            }
                                            $$ = ManageRelationExpression($1, if_eq_op, $3);
                                        }
            | expr LESS_EQUAL expr      {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>LESS EQUAL Expression (expr -> expr <= expr)\n");
                                            }
                                            $$ = ManageRelationExpression($1, if_lesseq_op, $3);
                                        }
            | expr LESS expr            {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>LESS Expression (expr -> expr < expr)\n");
                                            }
                                            $$ = ManageRelationExpression($1, if_less_op, $3);
                                        }
            | expr GREATER_EQUAL expr   {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>GREATER EQUAL Expression (expr -> expr >= expr)\n");
                                            }
                                            $$ = ManageRelationExpression($1, if_greatereq_op, $3);
                                        }
            | expr GREATER expr         {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>GREATER Expression (expr -> expr > expr)\n");
                                            }
                                            $$ = ManageRelationExpression($1, if_greater_op, $3);
                                        }
            | expr PLUS expr            {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>PLUS Expression (expr -> expr + expr)\n");
                                            }
                                            $$ = ManageArithmeticExpression($1,add_op,$3);
                                        }
            | expr MINUS expr           {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MINUS Expression (expr -> expr - expr)\n");
                                            }
                                            $$ = ManageArithmeticExpression($1,sub_op,$3);
                                        }
            | expr MUL expr             {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MUL Expression (expr -> expr * expr) \n");
                                            }
                                            $$ = ManageArithmeticExpression($1,mul_op,$3);
                                        }
            | expr DIV expr             {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>DIV Expression (expr -> expr / expr) \n");
                                            }
                                            $$ = ManageArithmeticExpression($1,div_op,$3);
                                        }
            | expr MODULO expr          {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MODULO Expression (expr -> expr MOD expr)\n");
                                            }
                                            $$ = ManageArithmeticExpression($1,mod_op,$3);
                                        }
            | LEFT_PARENTHESIS expr RIGHT_PARENTHESIS 
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>PARENTHESIS EXPR Expression (expr -> (expr) )\n");
                                            }
                                            $$ = $2;
                                        }
            | MINUS expr %prec UMINUS   {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>-EXPR Expression (expr -> -expr)\n");
                                            }

                                            $$ = ManageUminus($2);
                                        }
            | NOT expr                  {
                                           if(TRACE_PRINT){
                                                fprintf(ost, "=>NOT Expression (expr -> not expr)\n");
                                            }

                                            $$ = ManageNot($2);
                                        }
            | PLUS_PLUS lvalue          {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>PLUS PLUS lvalue Expression (expr -> ++lvalue)\n");
                                            }
                                            $$ = ManagePlusPlusLvalue($2);
                                        }
            | lvalue PLUS_PLUS          {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>lvalue PLUS PLUS Expression (expr -> lvalue++ )\n");
                                            }
                                            $$ = ManageLvaluePlusPlus($1);
                                        }
            | MINUS_MINUS lvalue        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MINUS MINUS lvalue Expression (expr -> --lvalue)\n");
                                            }
                                            $$ = ManageMinusMinusLvalue($2);
                                        }
            | lvalue MINUS_MINUS        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>lvalue MINUS MINUS Expression (expr -> lvalue--)\n");
                                            }
                                            ManageLvalueMinusMinus($1);
                                        }
            | primary                   {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>PRIMARY Expression (expr -> primary)\n");
                                            }
                                            $$ = $1;
                                        }
            ;

primary:    lvalue                      {                                 
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>lvalue (primary -> lvalue)\n");
                                            }
                                            $$ = ManagePrimaryLValue($1);    
                                        }
            | call                      {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>CALL (primary -> call)\n");
                                            }
                                            $$ = ManagePrimaryFunction($1);

                                        }
            | objectdef                 {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>OBJECT DEF (primary -> objectdef)\n");
                                            }

                                            $$ = $1;
                                        }
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS    
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>(funcdef) (primary -> (funcdef))\n");
                                            }

                                            $$ = newexpr(programfunc_e);
                                            $$->sym = $2;
                                        }
            | const                     {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>CONST (primary -> const)\n");
                                            }

                                            $$ = $1;
                                        }
            ;

lvalue:     ID                          {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>ID %s (lvalue -> ID)\n", $1);
                                            }
                                            $$ = EvaluateLValue($1);
                                        }

            | LOCAL ID                  {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=> local ID %s (lvalue -> local ID)\n", $2);
                                            }
                                            $$ = EvaluateLocalLValue($2);
                                        }
            | DOUBLE_COLON ID           {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>global ID %s (lvalue -> global ID)\n", $2);
                                            }
                                            $$ = EvaluateGlobalLValue($2);
                                        }
            | member                    {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MEMBER (lvalue -> member)\n");
                                            }

                                            $$ = $1;
                                        }
            ;

member:     lvalue FULLSTOP ID                          {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>lvalue . ID %s (member -> lvalue.ID)\n", $3);
                                                            }

                                                            $$ = member_item($1, $3); 
                                                        }
            | lvalue LEFT_BRACKET expr RIGHT_BRACKET    {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>lvalue [ EXPR ] (member -> lvalue[expr])\n");
                                                            }

                                                            $1 = emit_iftableitem($1);
                                                            $$ = newexpr(tableitem_e);
                                                            $$->sym = $1->sym;
                                                            $$->index = $3;
                                                        }
            | call FULLSTOP ID                          {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>Call.ID %s (member -> call.ID)\n", $3);
                                                            }

                                                            //ti sto kalo kanoume edw?
                                                            $$ = member_item($1, $3); 
                                                        }
            | call LEFT_BRACKET expr RIGHT_BRACKET      {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>CALL [ EXPR ] (member -> call[expr])\n");
                                                            }

                                                            //oute edw xerw ti kanoume
                                                            $1 = emit_iftableitem($1);
                                                            $$ = newexpr(tableitem_e);
                                                            $$->sym = $1->sym;
                                                            $$->index = $3;
                                                        }
            ;

call:       call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS   {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>CALL ( ELIST ) (call -> call(elist))\n");
                                                                }           

                                                                $$ = make_call($1, $3);
                                                            }
            | call LEFT_PARENTHESIS RIGHT_PARENTHESIS       {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>CALL ( empty ) (call -> call())\n");
                                                                }                                       
                                                                
                                                                $$ = make_call($1, NULL);

                                                            }
            | lvalue callsuffix                             {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>lvalue ( CALL SUFFIX ) (call -> lvalue callsuffix)\n");                                       
                                                                }
                                                                //$$ = $1;
                                                                $$ = ManageLvalueCallsuffix($1, $2);
                                                            }
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS   
                                                            {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>(FUNCDEF)(ELIST) (call -> ( funcdef(elist) ))\n");
                                                                }
                                                                
                                                                expr* func = newexpr(programfunc_e);
                                                                func->sym = $2;
                                                                $$ = make_call(func, $5);
                                                            }
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS RIGHT_PARENTHESIS 
                                                            {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>(FUNCDEF)(empty) (call -> ( funcdef() ))\n");
                                                                }

                                                                expr* func = newexpr(programfunc_e);
                                                                func->sym = $2;
                                                                $$ = make_call(func, NULL);
                                                            }                                                                                        
            ;

callsuffix: normcall        {
                                if(TRACE_PRINT){
                                    fprintf(ost, "=>NORMAL CALL (callsuffix -> normcall)\n");
                                }
                                $$ = $1;
                            }
            | methodcall    {
                                if(TRACE_PRINT){
                                    fprintf(ost, "=>METHOD CALL (callsuffix -> methodcall)\n");
                                }
                                $$ = $1;
                            }
            ;

normcall:   LEFT_PARENTHESIS elist RIGHT_PARENTHESIS    {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>(ELIST) (normcall -> (elist) )\n");
                                                            }
                                                            $$ = ManageNormalCall($2);
                                                        }
            | LEFT_PARENTHESIS RIGHT_PARENTHESIS        {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>(empty) (normcall -> ())\n");
                                                            }

                                                            $$ = ManageNormalCall(NULL);
                                                        }                                            
            ;

methodcall: DOUBLE_FULLSTOP ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS     {
                                                                                if(TRACE_PRINT){
                                                                                    fprintf(ost, "=> ..%s (ELIST) (methodcall -> ..ID(elist))\n", $2);
                                                                                }

                                                                                $$ = ManageMethodCall($4,$2);
                                                                            }
            | DOUBLE_FULLSTOP ID LEFT_PARENTHESIS RIGHT_PARENTHESIS         {
                                                                                if(TRACE_PRINT){
                                                                                    fprintf(ost, "=> ..%s (empty) (methodcall -> ..ID())\n", $2);
                                                                                }

                                                                                $$ = ManageMethodCall(NULL,$2);
                                                                            }                                                                
            ;

elist:      expr                {
                                    if(TRACE_PRINT){
                                        fprintf(ost, "=>EXPR (elist -> expr)\n");
                                    }
                                    $$ = $1; //kseroume $1->next = NULL 
                                }
            | elist COMMA expr  {
                                    if(TRACE_PRINT){
                                        fprintf(ost, "=>ELIST , EXPR (elist -> elist COMMA expr)\n");
                                    }
                                    
                                    $3->next = $1;
                                    $$ = $3;
                                }
            ;

objectdef:  LEFT_BRACKET indexed RIGHT_BRACKET  {
                                                    if(TRACE_PRINT){
                                                        fprintf(ost, "=>[INDEXED] (objectdef -> [indexed])\n");
                                                    }

                                                    indexedPair* ptr;
                                                    expr* t = newexpr(newtable_e);
                                                    
                                                    t->sym = newtemp();
                                                    emit(tablecreate_op, t, NULL, NULL, 0, yylineno);
                                                    ptr = $2;
                                                    
                                                    while(ptr){
                                                        emit(tablesetelem_op, t, ptr->key, ptr->val, 0, yylineno);
                                                        ptr = ptr->next;
                                                    }

                                                    $$ = t;
                                                }
            | LEFT_BRACKET elist RIGHT_BRACKET  {
                                                    if(TRACE_PRINT){
                                                        fprintf(ost, "=>[ELIST] (objectdef -> [ELIST])\n");
                                                    }
                                                    $$ = ManageObjectDef($2);
                                                }
            | LEFT_BRACKET RIGHT_BRACKET        {
                                                    if(TRACE_PRINT){
                                                        fprintf(ost, "=>[empty] (objectdef -> [])\n");
                                                    }
                                                    $$ = ManageObjectDef(NULL);
                                                }
            ;

indexed:    indexedelem                 {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>INDEXED_ELEM (indexed -> indexedelem)\n");
                                            }

                                            $$ = $1;

                                        }
            | indexed COMMA indexedelem {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=> INDEXED , INDEXED_ELEM (indexed -> indexed COMMA indexedelem)\n");
                                            }

                                            $3->next = $1;
                                            $$ = $3;
                                        }
            ;

indexedelem:LEFT_BRACE expr COLON expr RIGHT_BRACE  {
                                                        if(TRACE_PRINT){
                                                            fprintf(ost, "=>{EXPR : EXPR} (indexedelem -> { expr : expr })\n");
                                                        }
                                                        /*We are not sure for this -- Check again*/
                                                        $$ = newIndexPair($2, $4);
                                                    }
            ;

block:      LEFT_BRACE {scope++;} RIGHT_BRACE           {
                                                            ScopeTable_hide_scope(scopeTab, scope);
                                                            scope--;
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>{Empty} (block -> {})\n");
                                                            }
                                                        }
            | LEFT_BRACE {scope++;} stmts RIGHT_BRACE   {
                                                            ScopeTable_hide_scope(scopeTab, scope);
                                                            scope--;
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>{STMTS} (block -> {stmts})\n");
                                                            }
                                                        }
            ;

funcname:   ID      {
                        $$ = $1;
                    }
            |       {
                        GenerateFuncName();
                        $$ = anonymous_func_prefix;
                    }
            ;

funcprefix:     FUNCTION funcname   {
                                        $$ = ManageIDFunctionDefinition($2);
                                        if($$ != NULL){
                                            emit(funcstart_op, lvalue_expr($$), NULL, NULL, 0, yylineno);
                                        }
                                        NumberStack_push(scopeoffsetstack, currscopeoffset());
                                        scope++;
                                        enterscopespace();
                                        resetformalargsoffset();
                                    }
                ;

funcargs:       LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS   {
                                                                enterscopespace();
                                                                resetfunctionlocalsoffset(); 
                                                                scope--;
                                                            }
                | LEFT_PARENTHESIS RIGHT_PARENTHESIS        {
                                                                enterscopespace();
                                                                resetfunctionlocalsoffset(); 
                                                                scope--;
                                                            }
                ;

funcbody:       block   {
                            $$ = currscopeoffset();
                            exitscopespace();
                        }
                ;

funcblockstart:         {
                            NumberStack_push(loopStack, loopcounter);
                            loopcounter = 0;
                        }
                ;

funcblockend:           {
                            loopcounter = NumberStack_pop(loopStack);
                        }
                ;

funcdef:    funcprefix funcargs funcblockstart funcbody funcblockend    {
                                                if(TRACE_PRINT){
                                                    fprintf(ost, "=>FUNCDEF (funcdef -> function ID () block)\n");
                                                }

                                                exitscopespace();
                                                if($1 != NULL){
                                                    ($1->value).funcVal->totalLocals = $4; //check
                                                    emit(funcend_op, lvalue_expr($1), NULL, NULL, 0, yylineno);
                                                }

                                                int offset = NumberStack_pop(scopeoffsetstack);
                                                restorecurrscopeoffset(offset);
                                                
                                                //FuncStack_print(functionStack);
                                                FuncStack_pop(functionStack);
                                                
                                                $$ = $1;
                                            }
            ;


const:      INTEGER     {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>INTEGER %d (const -> INTEGER)\n", $1);
                            }

                            $$ = newexpr_constnum($1 * 1.0);
                        }
            | REAL      {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>Real %f (const -> REAL)\n", $1);
                            }

                            $$ = newexpr_constnum($1);
                        }
            | STRING    {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>String %s (const -> STRING)\n", $1);
                            }

                            $$ = newexpr_conststring($1); //strdup inside!
                        }
            | NIL       {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>NIL (const -> NIL)\n");
                            }

                            $$ = newexpr_nil();
                        }
            | TRUE      {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>TRUE (const -> TRUE)\n");
                            }

                            $$ = newexpr_constbool(1);
                        }
            | FALSE     {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>FALSE (const -> FALSE)\n");
                            }

                            $$ = newexpr_constbool(0);
                        }
            ;

idlist:     ID                  {
                                    if(TRACE_PRINT){
                                        fprintf(ost, "=>ID %s (idlist -> ID)\n", $1);
                                    }
                                    CheckAddFormal($1);
                                }
            | idlist COMMA ID   {
                                    if(TRACE_PRINT){
                                        fprintf(ost, "=>IDLIST , ID %s (idlist -> idlist, ID)\n", $3);
                                    }
                                    CheckAddFormal($3);
                                }
            ;

ifprefix:   IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS      {
                                                                $$ = ManageIfPrefix($3);                                             
                                                            }
            ;

elseprefix: ELSE                    {
                                        $$ = nextquadlabel();
                                        emit(jump_op, NULL, NULL, NULL, 0, yylineno);
                                    }
            ;

ifstmt: ifprefix stmt elseprefix stmt       {
                                                if(TRACE_PRINT){
                                                    fprintf(ost, "=>IF ELSE (ifstmt -> if(expr)stmt else stmt)\n");
                                                }

                                                patchlabel($1, $3 + 1);
                                                patchlabel($3, nextquadlabel());
                                            }
        | ifprefix stmt                     {
                                                if(TRACE_PRINT){
                                                    fprintf(ost, "=>IF ELSE (ifstmt -> if(expr) stmt)\n");
                                                }

                                                patchlabel($1, nextquadlabel());
                                            }
        ;                          

loopstart:              {
                            ++loopcounter;
                        }
            ;

loopend:                {
                            --loopcounter;
                        }
            ;            

loopstmt:   loopstart stmt loopend  {
                                        $$ = $2; //todo
                                    }
            ;                        

whilestart: WHILE       {
                            $$ = nextquadlabel();
                        }
            ;

whilecond:  LEFT_PARENTHESIS expr RIGHT_PARENTHESIS {
                                                        emit(if_eq_op, $2, newexpr_constbool(1), NULL, nextquadlabel() + 2, yylineno);
                                                        $$ = nextquadlabel();
                                                        emit(jump_op, NULL, NULL, NULL, 0, yylineno);
                                                    }
            ;

whilestmt:  whilestart whilecond loopstmt   {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>while(EXPR) (whilestmt -> while(expr) stmt)\n");
                                            }
                                            emit(jump_op, NULL, NULL, NULL, $1, yylineno);
                                            patchlabel($2, nextquadlabel());
                                            patchlist($3->breakList, nextquadlabel());
                                            patchlist($3->contList, $1);

                                            $$ = $3;
                                        }
            ;                                                                                               

N:          {
                $$ = nextquadlabel();
                emit(jump_op, NULL, NULL, NULL, 0, yylineno);
            }
    ;

M:          {
                $$ = nextquadlabel();
            }
    ;

forprefix:  FOR LEFT_PARENTHESIS elist SEMICOLON M expr SEMICOLON   {
                                                                        $$ = ManageForPrefix($6, $5);
                                                                    }
            | FOR LEFT_PARENTHESIS SEMICOLON M expr SEMICOLON       {
                                                                        $$ = ManageForPrefix($5, $4);
                                                                    }
            ;

forstmt:    forprefix N elist RIGHT_PARENTHESIS N loopstmt N    {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>FOR (forstmt -> for(elist; expr; elist))\n");
                                                                }
                                                                ManageForStatement($1, $2, $5, $7, $6);
                                                            }
            | forprefix N RIGHT_PARENTHESIS N loopstmt N        {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>FOR (forstmt -> for(elist; expr; elist))\n");
                                                                }
                                                                ManageForStatement($1, $2, $4, $6, $5);
                                                                
                                                            }
            ;

returnstmt: RETURN SEMICOLON        {
                                        if(TRACE_PRINT){
                                            fprintf(ost, "=>ret; (returnstmt -> return;)\n");
                                        }
                                        ManageReturnStatement(NULL);
                                        
                                    }
            | RETURN expr SEMICOLON {
                                        if(TRACE_PRINT){
                                            fprintf(ost, "=>ret EXPR; (returnstmt -> return expr;)\n");
                                        }
                                        ManageReturnStatement($2);
                                       
                                    }
            ;

%%

int yyerror(char *message){
    fprintf_red(stderr, "[Syntax Analysis] -- ERROR: %s: at line %d, on token: %s\n", message, yylineno, yytext);
    compileError = 1;
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

    InitFuncNames();
    resettemp();

    symTab = SymbolTable_init();
    scopeTab = ScopeTable_init();
    functionStack = FuncStack_init();
    loopStack = NumberStack_init();
    scopeoffsetstack = NumberStack_init();

    SymbolTable_add_libfun(symTab, scopeTab);

    yyparse();

    ScopeTable_print(scopeTab, ost);
    //SymbolTable_print(symTab, ost);

    if(!compileError){
        printQuads();
    }
    else{
        fprintf_red(stderr, "[Alpha Compiler] -- COMPILATION ERROR: Intermediate code generation failed.\n");
    }

    fclose(ost);
    fclose(yyin);
    
    return 0;   
}
