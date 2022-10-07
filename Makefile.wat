# A collection of m4 macros to make writing Makefiles easier.
# Recommended for a two-pass m4 system.











# Define the implicit rules









# A collection of m4 macros to make writing Makefiles easier.
# Recommended for a two-pass m4 system.











# Define the implicit rules









# Makefile for Watcom

M4=m4

CC=wcc386
LD=wlink
CFLAGS=
TESTS=tests\dequeue.exe tests\addremov.exe tests\enqueue.exe tests\init.exe tests\peek.exe tests\is_empty.exe tests\free.exe tests\length.exe 

all: $(TESTS) .symbolic

clean: .symbolic
	rm -f $(TESTS)

tests\dequeue.obj: tests\dequeue.c 
	$(CC) tests\dequeue.c -fo=tests\dequeue.obj $(CFLAGS)
tests\addremov.obj: tests\addremov.c 
	$(CC) tests\addremov.c -fo=tests\addremov.obj $(CFLAGS)
tests\enqueue.obj: tests\enqueue.c 
	$(CC) tests\enqueue.c -fo=tests\enqueue.obj $(CFLAGS)
tests\init.obj: tests\init.c 
	$(CC) tests\init.c -fo=tests\init.obj $(CFLAGS)
tests\peek.obj: tests\peek.c 
	$(CC) tests\peek.c -fo=tests\peek.obj $(CFLAGS)
tests\is_empty.obj: tests\is_empty.c 
	$(CC) tests\is_empty.c -fo=tests\is_empty.obj $(CFLAGS)
tests\free.obj: tests\free.c 
	$(CC) tests\free.c -fo=tests\free.obj $(CFLAGS)
tests\length.obj: tests\length.c 
	$(CC) tests\length.c -fo=tests\length.obj $(CFLAGS)

tests\dequeue.exe: tests\dequeue.obj 
	$(LD) FILE tests\dequeue.obj NAME tests\dequeue.exe
tests\addremov.exe: tests\addremov.obj 
	$(LD) FILE tests\addremov.obj NAME tests\addremov.exe
tests\enqueue.exe: tests\enqueue.obj 
	$(LD) FILE tests\enqueue.obj NAME tests\enqueue.exe
tests\init.exe: tests\init.obj 
	$(LD) FILE tests\init.obj NAME tests\init.exe
tests\peek.exe: tests\peek.obj 
	$(LD) FILE tests\peek.obj NAME tests\peek.exe
tests\is_empty.exe: tests\is_empty.obj 
	$(LD) FILE tests\is_empty.obj NAME tests\is_empty.exe
tests\free.exe: tests\free.obj 
	$(LD) FILE tests\free.obj NAME tests\free.exe
tests\length.exe: tests\length.obj 
	$(LD) FILE tests\length.obj NAME tests\length.exe


.SUFFIXES:

