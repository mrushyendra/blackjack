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
        Card getCard();
        void addCardBottom(Card c);
        void addCardTop(Card c);
        void shuffle();
        void fixedShuffle(int seed);
        int size();
    private:
        deque<Card> m_cards;
};

Deck createBlackJackDeck();

class Hand {
    public:
        Hand(vector<Card> faceUp, vector<Card> faceDown);
        ~Hand();
        void emptyHand();
        int sum();
        friend ostream& operator<<(ostream& os, Hand& hd);
        string showHand();
        vector<Card> m_faceUp;
        vector<Card> m_faceDown;
};

#endif
