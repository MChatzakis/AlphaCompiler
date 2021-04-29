# Alpha Compiler
Created by Manos Chatzakis (csd4238@csd.uoc.gr) and Nikos Fanourakis (csd4237@csd.uoc.gr)\
Compile using "make" or "make all" inside the corresponding folder.

## Lexical Analysis:
The produced executable "al" supports input and output filestreams, for example:
./al -i "inputfile" -o "outputfile". By default, input filestream is stdin and output filestream is stdout. Use -h for help.

Notes: Supported escaped characters: \ + {n,t,\\,"}

## Syntax Analysis:
The produced executable "calc" supports input and output filestreams, for example:
./calc -i "inputfile" -o "outputfile". By default, input filestream is stdin and output filestream is stdout. Use -h for help. Errors are always printed in stderr.

The parser uses lex to detect the tokens ignoring whitespaces, and manipulates the symboltable using the functions provided in "yacc_api.h" file.

The Symboltable library contains the symboltable structure (to store every symbol), the scope list (to keep together symbols of the same scope), the function argument list (to keep the arguments of a function) and the function stack (to check symbol accessibility and to match every formal argument to its corresponding function).

## Intermediate Code Generation:


