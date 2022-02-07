# Alpha Compiler

Alpha Compiler is a complete compiler (acc) and virtual machine (avm) for the Alpha programming language. (For the syntax etc. see the examples provided).

Created by Manos Chatzakis (csd4238@csd.uoc.gr) and Nikos Fanourakis (csd4237@csd.uoc.gr).

To compile:

```language
cd build
make
```

## Lexical Analysis

Lexical Analysis is done using Lex program, following the rules of Alpha Programming language.\
Supported escaped characters: \ + {n,t,\\,"}

## Syntax Analysis

The parser uses Lex to detect the tokens ignoring whitespaces, and manipulates the symboltable using the functions provided in "yacc_api.h" file.

The Symboltable library contains the symboltable structure (to store every symbol), the scope list (to keep together symbols of the same scope), the function argument list (to keep the arguments of a function) and the function stack (to check symbol accessibility and to match every formal argument to its corresponding function).

## Intermediate Code Generation

The quads are printed by default to output filestream and additionally to the file "quads.txt", only when the input has not compilation errors.

We provide two ways to print the quads (verbose and formal). By defaults the quads are printed using the verbose method, but the formal method can be invoked by setting the printQuad(int flag, FILE* stream) flag to 0, manually.

Note: The above features got disabled on final version. They can be re-enabled manually from the syn_an.y file.
The quads produced are printed in stdout using "-p" compiler flag.

## Target Code Generation

The instructions are printed in stdout by default and they are written to the specific Alpha binary file (bin.abc).
To cover corner cases, hidden variables optimization is disabled for the table members, to avoid resetting bugs.

## Alpha Virtual Machine

Alpha applications run on the AVM (Alpha Virtual Machine), which is a complete virtual machine designed to provide a C/C++ based runtime environment.

To compile the AVM executable, use:

``` language
cd build
make #"make avm" works as well
```

Thus, to compile an alpha application, assuming the file is named "code.alpha" (extensions do not matter):

``` language
cd build
make
./acc -i code.alpha #produces the binary file called bin.abc
./avm -f bin.abc #use avm to run the code
```
