CC = gcc

EXECUTABLES = baseball_ticketing

all: $(EXECUTABLES)

baseball_ticketing: baseball_ticketing.c -lcurses 
	$(CC) -o baseball_ticketing baseball_ticketing.c  -lcurses

clean:
	rm -f $(EXECUTABLES)

