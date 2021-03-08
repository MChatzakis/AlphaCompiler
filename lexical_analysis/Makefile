#Manos Chatzakis
#Nikos Fanourakis

CC = gcc
LC = lex

LEX_FILE = lex_an.l
C_FILE = scanner.c

LIB_FILE = token/token.h
LIB_IMP_FILE = token/token.c

STACK_FILE = comment_stack/comment_stack.h
STACK_IMP_FILE = comment_stack/comment_stack.c

COLOR_FILE = ../utils/colors.h
COLOR_IMP_FILE = ../utils/colors.c

GCC_FLAGS = -Werror -o
EXEC_FILE = al

all: lex gcc

run: all
	./al

lex: $(LEX_FILE)
	$(LC) $(LEX_FILE)

gcc: $(C_FILE) $(LIB_FILE) $(LIB_IMP_FILE) $(COLOR_FILE) $(COLOR_IMP_FILE) $(STACK_FILE) $(STACK_IMP_FILE)
	$(CC) $(C_FILE) $(LIB_IMP_FILE) $(STACK_IMP_FILE) $(COLOR_IMP_FILE) $(GCC_FLAGS) $(EXEC_FILE)

clean:
	$(warning Only Producable files will be deleted!)
	rm -f $(EXEC_FILE)
	rm -f $(C_FILE)

