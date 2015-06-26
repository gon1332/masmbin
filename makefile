OBJ_FILES	= strdup.o asm.o parser.o lex.o main.o
EXEC		= ./masmbin

## PATHS
INCLUDE		= ./include
LIB			= ./src/lib
SURFACE 	= ./src
BUILD   	= ./build
OBJS    	= $(addprefix $(BUILD)/, $(OBJ_FILES))

## BUILD TOOLS
CC      	= gcc
CFLAGS		= -std=c99 -Iinclude/ -ggdb3 -Wall -Wextra
CLIBS		= -lfl

masmbin: info build_dir $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(CLIBS)

build_dir:
	mkdir -p $(BUILD)

info:
	$(info	+ ===========================================================)
	$(info  | Compiling and building *masmbin*                           )
	$(info  + ===========================================================)

$(BUILD)/%.o:
	$(CC) $(CFLAGS) -c -o $@ $<

## LIBRARIES
$(BUILD)/strdup.o: $(SURFACE)/strdup.c $(INCLUDE)/strdup.h
$(BUILD)/asm.o: $(SURFACE)/asm.c $(INCLUDE)/asm.h

## PARSER
$(BUILD)/parser.o: $(SURFACE)/parser.c

$(SURFACE)/parser.c: $(SURFACE)/parser.y
	bison -dv $(SURFACE)/parser.y
	mv parser.output $(SURFACE)/parser.output
	mv parser.tab.c $(SURFACE)/parser.c
	cmp -s parser.tab.h $(SURFACE)/tok.h ||\
	mv parser.tab.h $(SURFACE)/tok.h


## LEXICAL ANALYZER
$(BUILD)/lex.o: $(SURFACE)/lex.c

$(SURFACE)/lex.c: $(SURFACE)/lex.l
	flex $(SURFACE)/lex.l
	mv lex.yy.c $(SURFACE)/lex.c

## MAIN PROGRAM
$(BUILD)/main.o: $(SURFACE)/main.c
	$(CC) $(CFLAGS) -c $(SURFACE)/main.c -o $(BUILD)/main.o

## CLEAN
clean:
	$(info  + ===========================================================)
	$(info  | Cleaning build directory and temporary files               )
	$(info  + ===========================================================)
	rm -f	$(SURFACE)/*~ $(INCLUDE)/*~ $(LIB)/*~
	rm -rf	$(BUILD) $(EXEC)
	rm -f 	$(SURFACE)/lex.c $(SURFACE)/lex.yy.c $(SURFACE)/parser.c\
			$(SURFACE)/tok.h $(SURFACE)/parser.tab.c $(SURFACE)/parser.tab.h\
			$(SURFACE)/parser.output












