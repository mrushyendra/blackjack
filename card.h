#ifndef CARDS_H
#define CARDS_H

#include <vector>
#include <string>
#include <deque>
#include <unordered_map>

using namespace std;

enum Suit { SPADES, HEARTS, CLUBS, DIAMONDS, SUIT_MIN = SPADES, SUIT_MAX = DIAMONDS };

class Card {
    public:
        Card(Suit s, int value, string& name);
        ~Card();
        int getValue();
        string getName();
        Suit getSuit();
    private:
        Suit m_s;
        int m_value;
        string m_name;
};

class Deck {
    public:
        Deck(vector<string> names, vector<int> pts);
        Deck(deque<Card> cards);
        virtual ~Deck();
        Card getCard(); //Removes a Card from the top of the Deck and returns it. Assumes Deck is not empty.
        void addCardBottom(Card c); //Adds the Card `c` to the bottom of the Deck.
        void addCardTop(Card c); //Adds the Card `c` to the top of the Deck.
        void shuffle(); //Randomly permutes the order of cards in the Deck.
        void fixedShuffle(int seed); //For testing: Permutes the order of cards in the Deck with a fixed seed.
        int size(); //Returns number of cards in Deck.
    private:
        deque<Card> m_cards;
};

/* Creates a standard 52-card sized Deck. Cards '2'-'9' are assigned points according to pip value, '10's and face cards assigned 10 points,
   and Aces as 11 points each. */
Deck createBlackJackDeck();

class Hand {
    public:
        Hand(vector<Card> faceUp, vector<Card> faceDown);
        ~Hand();
        void emptyHand(); //Discards all Cards in Hand
        int sum(); //Returns sum of points of all Cards in Hand, including face-down cards.
        friend ostream& operator<<(ostream& os, Hand& hd);
        string showHand(); //Returns string representation of identities of all face-up Cards in the Hand, as well as number of face-down Cards.
        vector<Card> m_faceUp; //Face-up Cards in Hand, visible to other players.
        vector<Card> m_faceDown; //Face-down Cards in Hand, not visible to other players.
};

#endif
