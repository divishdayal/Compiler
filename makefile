CC = gcc
CFLAGS = -Wall
DEPS = queue.h hashtable.h hashDef.h queueDef.h lexer.h parseTable.h parseTableDef.h parseTree.h parseTreeDef.h
OBJ = driver.c lexer.c queue.c hashtable.c parseTable.c parseTree.c

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

stage1exe: $(OBJ)
	gcc $(CFLAGS) -o $@ $^