# A collection of m4 macros to make writing Makefiles easier.
# Recommended for a two-pass m4 system.











# Define the implicit rules






# A collection of m4 macros to make writing Makefiles easier.
# Recommended for a two-pass m4 system.











# Define the implicit rules






# Makefile for gemeral UNIX operating systems

M4=m4

CC=cc
CFLAGS=
PREFIX=/usr/local
TESTS=tests/length tests/enqueue tests/free tests/addremov tests/is_empty tests/peek tests/init tests/dequeue 
DOCS=doc/M4QUEUE_DEQUEUE.cware doc/m4queue-intro.cware doc/M4QUEUE_PEEK.cware doc/M4QUEUE_INIT.cware doc/M4QUEUE_LENGTH.cware doc/M4QUEUE_DECLARE.cware doc/M4QUEUE_ENQUEUE.cware doc/m4queue-example-tree.cware doc/M4QUEUE_IS_EMPTY.cware doc/m4queue.cware doc/M4QUEUE_FREE.cware 

all: $(TESTS)

install: maninstall

maninstall:
	mkdir -p $(PREFIX)/share/man/mancware
	cp $(DOCS) $(PREFIX)/share/man/mancware

clean:
	rm -f $(TESTS)
	rm -f $(EXAMPLES)

.SUFFIXES:

tests/dequeue: tests/dequeue.c 
	$(CC) tests/dequeue.c $(CFLAGS) -o tests/dequeue
tests/addremov: tests/addremov.c 
	$(CC) tests/addremov.c $(CFLAGS) -o tests/addremov
tests/enqueue: tests/enqueue.c 
	$(CC) tests/enqueue.c $(CFLAGS) -o tests/enqueue
tests/init: tests/init.c 
	$(CC) tests/init.c $(CFLAGS) -o tests/init
tests/peek: tests/peek.c 
	$(CC) tests/peek.c $(CFLAGS) -o tests/peek
tests/is_empty: tests/is_empty.c 
	$(CC) tests/is_empty.c $(CFLAGS) -o tests/is_empty
tests/free: tests/free.c 
	$(CC) tests/free.c $(CFLAGS) -o tests/free
tests/length: tests/length.c 
	$(CC) tests/length.c $(CFLAGS) -o tests/length


.PHONY: all clean install maninstall
