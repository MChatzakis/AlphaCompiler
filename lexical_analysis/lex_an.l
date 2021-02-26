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

    #define YY_DECL int yylex (void* ylval)
%}

%option prefix = "alpha_yy"
%option outfile = "Scanner.c"
%option noyywrap
%option yylineno 

/* Flex Macros */

/*id          [letter|Uletter][letter|Uletter|_|digit]* */
id          [a-zA-Z][a-zA-Z_0-9]*
letter      [a-z]
Uletter     [A-Z]
digit       [0-9]


/* Rule Section */
%%

{letter}    { fprintf(stderr, "Vrika Pezo Xaraktika: %s\n", yytext);}
{Uletter}   { fprintf(stderr, "Vrika Kefalaio Xaraktika: %s\n", yytext);}
{digit}     { fprintf(stderr, "Vrika Psifio: %s\n", yytext);}
{id}        { fprintf(stderr, "Vrika Identifier: %s\n", yytext);}

%%

/* Code Section */
int main(int argc, char **argv){
    if(argc > 1){
        if(!(yyin = fopen(argv[1], "r"))){
            fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return 1;
        }
    }
    else{
        yyin = stdin;
    }

    alpha_yylex(NULL);
    return 0;
}