CC=g++
CPPFLAGS=-std=c++11 -Wall -pedantic
INCLUDES= -I/usr/include
 
all: blackjack test

blackjack: blackjack.o card.o agents.o actions.o
	$(CC) blackjack.o card.o agents.o actions.o -o $@

test: test.o card.o agents.o actions.o
	$(CC) test.o card.o agents.o actions.o -o $@

blackjack.o: main.cpp Cards/card.h Agents/agents.h Actions/actions.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -o blackjack.o -c main.cpp

test.o: Tests/test.cpp Cards/card.h Agents/agents.h Actions/actions.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -o test.o -c Tests/test.cpp

actions.o : Actions/actions.cpp Actions/actions.h Agents/agents.h Cards/card.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -o $@ -c Actions/actions.cpp

agents.o : Agents/agents.cpp Agents/agents.h Cards/card.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -o $@ -c Agents/agents.cpp

card.o : Cards/card.cpp Cards/card.h
	$(CC) $(CPPFLAGS) $(INCLUDES) -o $@ -c Cards/card.cpp

clean:
	$(RM) blackjack test *.o 
