CC = gcc
CFLAGS = -ggdb

main: main.c logtree.o
	$(CC) $(CFLAGS) main.c logtree.o -o main

logtree.o: logtree.c
	$(CC) $(CFLAGS) -c logtree.c

clean:
	rm -rf *.o main
