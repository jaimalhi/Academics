CC=gcc
CFLAGS=-g -Wall -Wextra -I.
PROG=UnixLs 
OBJS=UnixLs.o

UnixLs: $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(PROG)