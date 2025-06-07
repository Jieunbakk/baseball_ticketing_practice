CC = gcc
LDLIBS = -lcurses

EXECUTABLES = baseball_ticketing

all: $(EXECUTABLES)

baseball_ticketing: baseball_ticketing.c 
	$(CC) -o baseball_ticketing baseball_ticketing.c  $(LDLIBS)

clean:
	rm -f $(EXECUTABLES)

