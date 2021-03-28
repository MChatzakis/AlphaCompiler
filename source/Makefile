#Manos Chatzakis
#Nikos Fanourakis
LEX_FILE = lex_an.l
LEX_C_FILE = scanner.c

YACC_FILE = syn_an.y
YACC_C_FILE = parser.c
YACC_H_FILE = parser.h

TOKEN_FILE = lex_libs/token/token.h
TOKEN_IMP_FILE = lex_libs/token/token.c

STACK_FILE = lex_libs/comment_stack/comment_stack.h
STACK_IMP_FILE = lex_libs/comment_stack/comment_stack.c

COLOR_FILE = utils/colors.h
COLOR_IMP_FILE = utils/colors.c

SYMBOL_TABLE = symboltable/symboltable.h
SYMBOL_TABLE_IMP = symboltable/symboltable.c

MACROS_FILE = yacc_libs/macros.h

EXEC = calc

all: yacc lex gcc

yacc: $(YACC_FILE)
	bison --yacc -v --defines --output=$(YACC_C_FILE) $(YACC_FILE)

lex: $(LEX_FILE)
	lex $(LEX_FILE)

gcc: $(LEX_C_FILE) $(YACC_C_FILE) $(YACC_H_FILE) $(SYMBOL_TABLE) $(SYMBOL_TABLE_IMP) $(COLOR_FILE) $(COLOR_IMP_FILE) $(STACK_FILE) $(STACK_IMP_FILE) $(MACROS_FILE)
	gcc $(LEX_C_FILE) $(YACC_C_FILE) $(STACK_IMP_FILE) $(COLOR_IMP_FILE) $(SYMBOL_TABLE_IMP) -Werror -Wall -o $(EXEC)

clean:
	rm -f $(EXEC)
	rm -f $(LEX_C_FILE)
	rm -f $(YACC_C_FILE)
	rm -f $(YACC_H_FILE)
	rm -f parser.output
