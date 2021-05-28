LEX_FILE = ../source/lex_an.l
LEX_C_FILE = ../source/scanner.c

YACC_FILE = ../source/syn_an.y
YACC_C_FILE = ../source/parser.c
YACC_H_FILE = ../source/parser.h

STACK_FILE = ../source/lex_libs/comment_stack/comment_stack.h
STACK_IMP_FILE = ../source/lex_libs/comment_stack/comment_stack.c

UTIL_FILE = ../source/utils/utils.h
UTIL_IMP_FILE = ../source/utils/utils.c

STRUCTS = ../source/yacc_libs/structs.h

SYMBOL_TABLE = ../source/symboltable/symboltable.h
SYMBOL_TABLE_IMP = ../source/symboltable/symboltable.c

YACC_API = ../source/yacc_libs/yacc_api.h

EXEC = calc

all: yacc lex gcc

yacc: $(YACC_FILE)
	bison --yacc -v --defines --output=$(YACC_C_FILE) $(YACC_FILE)

lex: $(LEX_FILE)
	lex -o $(LEX_C_FILE) $(LEX_FILE)

gcc: $(LEX_C_FILE) $(YACC_C_FILE) $(YACC_H_FILE) $(SYMBOL_TABLE) $(SYMBOL_TABLE_IMP) $(UTIL_FILE) $(UTIL_IMP_FILE) $(STACK_FILE) $(STACK_IMP_FILE) $(YACC_API) $(STRUCTS)
	gcc $(LEX_C_FILE) $(YACC_C_FILE) $(STACK_IMP_FILE) $(UTIL_IMP_FILE) $(SYMBOL_TABLE_IMP) -lm -o $(EXEC)

test: script.py
	python3 script.py

cleanAll: clean
	rm -f quads.txt

clean:
	rm -f $(EXEC)
	rm -f $(LEX_C_FILE)
	rm -f $(YACC_C_FILE)
	rm -f $(YACC_H_FILE)
	rm -f ../source/parser.output
