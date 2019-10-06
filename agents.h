#ifndef AGENTS_H
#define AGENTS_H

#include <string>
#include <unordered_map>
#include "card.h"

using namespace std;

class Agent {
    public:
        Agent(vector<Card> faceUp, vector<Card> faceDown, unordered_map<string, int (*)(Agent*, Agent*, Deck&)> actions, Deck& deck);
        virtual ~Agent();
        virtual int play() = 0;
        void setCompetitor(Agent* other);
        void discardHand();
        virtual int pickCards(Deck& deck) = 0;
        int calcScore();
        Agent* m_other;
        unordered_map<string, int (*)(Agent*, Agent*, Deck&)> m_actions;
        Deck& m_deck;
        Hand m_ownHand;
};

typedef int (*Action)(Agent*, Agent*, Deck&);

class Player : public Agent {
    public:
        Player(vector<Card> faceUp, vector<Card> faceDown, unordered_map<string, Action> actions, Deck& deck, int cash);
        ~Player();
        int play();
        int playTest(vector<string>& moves, int& idx);
        int wager;
        int cash;
        int askWager();
        int pickCards(Deck& deck);
        string getAction();
};

class Dealer : public Agent {
    public:
        Dealer(vector<Card> faceUp, vector<Card> faceDown, unordered_map<string, Action> actions, Deck& deck);
        ~Dealer();
        int checkBlackJack();
        int play();
        int pickCards(Deck& deck);
};

#endif
