#include <iostream>
#include <sstream>
#include <random>

#include "card.h"

/* Card Class Functions */
Card::Card(Suit s, int value, string& name) : m_s(s), m_value(value), m_name(name){}

Card::~Card(){}

int Card::getValue(){
    return m_value;
}

string Card:: getName(){
    return m_name;
}

Suit Card::getSuit(){
    return m_s;
}

/* Deck related functions */

Deck::Deck(vector<string> names, vector<int> pts){
    for(unsigned int i = SUIT_MIN; i <= SUIT_MAX; ++i){
        Suit suit = static_cast<Suit>(i);
        for(unsigned int j = 0; j < names.size(); ++j){
            Card newCard(suit, pts[j], names[j]);
            m_cards.emplace_back(newCard);
        }
    }
}

Deck::Deck(deque<Card> cards) : m_cards(cards){}

Deck::~Deck(){}

Card Deck::getCard(){
    Card c = m_cards.front();
    m_cards.pop_front();
    return c;
}

void Deck::addCardBottom(Card c){
    m_cards.push_back(c);
}

void Deck::addCardTop(Card c){
    m_cards.push_front(c);
}

void Deck::shuffle(){
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> dist(0, m_cards.size()-1);

    for(unsigned int i = 0; i < m_cards.size(); ++i){
        int randInt = dist(rng);
        Card tmp = m_cards[randInt];
        m_cards[randInt] = m_cards[i];
        m_cards[i] = tmp;
    }
}

void Deck::fixedShuffle(int seed){
    mt19937 rng(seed);
    uniform_int_distribution<int> dist(0, m_cards.size()-1);

    for(unsigned int i = 0; i < m_cards.size(); ++i){
        int randInt = dist(rng);
        Card tmp = m_cards[randInt];
        m_cards[randInt] = m_cards[i];
        m_cards[i] = tmp;
    }
}


int Deck::size(){
    return m_cards.size();
}

Deck createBlackJackDeck(){
    vector<string> names = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    vector<int> pts = {1,2,3,4,5,6,7,8,9,10,10,10,10,11};
    Deck deck(names, pts);
    return deck;
}

/* Hand Class related functions */

Hand::Hand(vector<Card> faceUp, vector<Card> faceDown) : m_faceUp(faceUp), m_faceDown(faceDown){}

Hand::~Hand(){}

int Hand::sum(){
    int sum = 0;
    for(unsigned int i = 0; i < m_faceUp.size(); ++i){
        sum += m_faceUp[i].getValue();
    }
    for(unsigned int i = 0; i < m_faceDown.size(); ++i){
        sum += m_faceDown[i].getValue();
    }
    return sum;
}

void Hand::emptyHand(){
   m_faceDown.clear();
   m_faceUp.clear();
}

string Hand::showHand(){
    string res;
    vector<string> suits{"♠", "♥", "♣", "♦"};
    for(unsigned int i = 0; i < m_faceUp.size(); ++i){
        res += m_faceUp[i].getName();
        res += suits[static_cast<int>(m_faceUp[i].getSuit())];
        res += "  ";
    }

    for(unsigned int i = 0; i < m_faceDown.size(); ++i){
        res += "XX ";
    }
     
    return res;
}

ostream& operator<<(ostream& os, Hand& hd){
    os << hd.showHand();
    return os;
}


