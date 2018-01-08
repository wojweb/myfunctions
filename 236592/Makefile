CC=gcc
CFLAGS= -g -Wall -m32

OUTNAME = run

ALL: main

main:: main.c basicfunctions.c myprintf.c myscanf.c
	$(CC) $(CFLAGS) -o $(OUTNAME) main.c basicfunctions.c myprintf.c myscanf.c

clean:
	$(RM) $(OUTNAME)
