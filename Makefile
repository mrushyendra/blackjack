CC=g++
CPPFLAGS=-std=c++11 -Wall -pedantic
INCLUDES= -I/usr/include
LDFLAGS= -L/usr/lib/x86_64-linux-gnu
 
all: blackjack test

blackjack: blackjack.o card.o agents.o actions.o /usr/lib/x86_64-linux-gnu/libncurses.a
	$(CC) blackjack.o card.o agents.o actions.o $(LDFLAGS) -lncurses -o $@

test: test.o card.o agents.o actions.o /usr/lib/x86_64-linux-gnu/libncurses.a
	$(CC) test.o card.o agents.o actions.o $(LDFLAGS) -lncurses -o $@
  
blackjack.o: main.cpp card.h agents.h actions.h /usr/include/ncurses.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -o blackjack.o -c main.cpp

test.o: test.cpp card.h agents.h actions.h /usr/include/ncurses.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -o test.o -c test.cpp

actions.o : actions.cpp actions.h agents.h card.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -o $@ -c actions.cpp

agents.o : agents.cpp agents.h card.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -o $@ -c agents.cpp

card.o : card.cpp card.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -o $@ -c card.cpp

clean:
	$(RM) blackjack test *.o 
