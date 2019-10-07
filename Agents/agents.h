#ifndef AGENTS_H
#define AGENTS_H

#include <string>
#include <unordered_map>
#include "../Cards/card.h"

using namespace std;

/* Base class for any player in game */
class Agent {
    public:
        Agent(vector<Card> faceUp, vector<Card> faceDown, unordered_map<string, int (*)(Agent*, Agent*, Deck&)> actions, Deck& deck);
        virtual ~Agent();
        virtual int play() = 0;
        void setCompetitor(Agent* other); //Sets `m_other` to the value of `other`
        void discardHand(); //Removes all cards from Agent's `m_ownHand`
        virtual void pickCards(Deck& deck) = 0;
        int calcScore(); //Calculates sum of points of all Cards in `m_ownHand`
        Agent* m_other;
        unordered_map<string, int (*)(Agent*, Agent*, Deck&)> m_actions;
        Deck& m_deck; //Reference to common Deck of the game
        Hand m_ownHand;
};

typedef int (*Action)(Agent*, Agent*, Deck&);

/* Non-Dealer player */
class Player : public Agent {
    public:
        Player(vector<Card> faceUp, vector<Card> faceDown, unordered_map<string, Action> actions, Deck& deck, int cash);
        ~Player();
        int play(); //Asks user for choice of action, and performs selected actions if valid. Returns result of action performed.
        int playTest(vector<string>& moves, int& idx); //Test version of `play` that takes vector `moves` of list of actions to choose.
        int wager; //Money wagered in each round.
        int cash; //Total amount in possession.
        int askWager(); //Asks user for money they wish to wager.
        void pickCards(Deck& deck); //Gets two Cards from the top of deck, and adds to face up cards in `m_ownHand`
        string getAction();
};

class Dealer : public Agent {
    public:
        Dealer(vector<Card> faceUp, vector<Card> faceDown, unordered_map<string, Action> actions, Deck& deck);
        ~Dealer();
        int checkBlackJack(); //Returns 1 if sum of points of cards in `m_ownHand` equals 21, 0 otherwise.
        int play(); //Calls the "GetMoreThan16" action. Assumes it is present in `m_actions`.
        void pickCards(Deck& deck); //Gets two cards from top of deck. Adds one to face up pile, and the other to the face down pile.
};

#endif
