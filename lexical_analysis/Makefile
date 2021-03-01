#Manos Chatzakis
#Nikos Fanourakis

CC = gcc #C compiler
LC = lex #LEX compiler

LEX_FILE = lex_an.l #Lex filename
C_FILE = Scanner.c #Produced c filename

LIB_FILE = token/Token.h #The lib file
LIB_IMP_FILE = token/Token.c #The lib implementation

COLOR_FILE = ../utils/Colors.h
COLOR_IMP_FILE = ../utils/Colors.c

GCC_FLAGS = -o #Link the lex lib to gcc (optional? may remove)

EXEC_FILE = al  #.out filename

#create everything
all: $(LEX_FILE) $(LIB_FILE) $(LIB_IMP_FILE) $(COLOR_FILE) $(COLOR_IMP_FILE)
	$(LC) $(LEX_FILE)
	$(CC) $(C_FILE) $(LIB_IMP_FILE) $(COLOR_IMP_FILE) $(GCC_FLAGS) $(EXEC_FILE)

#create everything and run
run: $(LEX_FILE) $(LIB_FILE) $(LIB_IMP_FILE) $(COLOR_FILE) $(COLOR_IMP_FILE)
	$(LC) $(LEX_FILE)
	$(CC) $(C_FILE) $(LIB_IMP_FILE) $(COLOR_IMP_FILE) $(GCC_FLAGS) $(EXEC_FILE)
	./$(EXEC_FILE)

#create .c only
lex: $(LEX_FILE)
	$(LC) $(LEX_FILE)

#create .out 
gcc: $(C_FILE) $(LIB_FILE) $(LIB_IMP_FILE) $(COLOR_FILE) $(COLOR_IMP_FILE)
	$(CC) $(C_FILE) $(LIB_IMP_FILE) $(COLOR_IMP_FILE) $(GCC_FLAGS) $(EXEC_FILE)

#clean all
clean:
	rm -f $(EXEC_FILE)
	rm -f $(C_FILE)

