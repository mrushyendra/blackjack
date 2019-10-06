#include <iostream>
#include "actions.h"
#include "agents.h"
#include "card.h"

using namespace std;

/*
 * split
 */


int checkBlackJack(Agent* own, Agent* other, Deck& deck){
    return (own->m_ownHand.sum() == 21);
}

int getMoreThan16(Agent* own, Agent* other, Deck& deck){
    //Flip over face down card
    own->m_ownHand.m_faceUp.insert(own->m_ownHand.m_faceUp.end(), own->m_ownHand.m_faceDown.begin(), own->m_ownHand.m_faceDown.end());
    own->m_ownHand.m_faceDown.clear();
    int sum = own->m_ownHand.sum();
    int otherScore = other->calcScore();

    //Get more cards if score less than or equal to 16, and other player has not busted
    if(otherScore <= 21){
        while(sum <= 16){
            Card card = deck.getCard();
            sum += card.getValue();
            own->m_ownHand.m_faceUp.emplace_back(card);
        }
    }
    cout << "Dealer's Cards: " << own->m_ownHand << endl;
    return 0;
}

// Player stands pat with his cards.
int stand(Agent* own, Agent* other, Deck& deck){
    return 0;
}

// Player draws another card. If player's total then exceeds 21, or if deck is initially empty, returns 1. Else returns 0.
int hit(Agent* own, Agent* other, Deck& deck){
    if(deck.size() > 0){
        own->m_ownHand.m_faceUp.emplace_back(deck.getCard());
        cout << "Your Cards: " << own->m_ownHand << endl;
        if(own->m_ownHand.sum() > 21){
            return 0;
        }
        return 1;
    }
    return 0;
}

//Draws an additional card. Doubling of wager takes place in Player::play() method.
int doubleMove(Agent* own, Agent* other, Deck& deck){
    if(deck.size() > 0){
        Card card = deck.getCard();
        own->m_ownHand.m_faceUp.emplace_back(deck.getCard());
        cout << "Your Cards: " << own->m_ownHand << endl;
    }
    return 0;
}


