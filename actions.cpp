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
    own->m_ownHand.m_faceUp.insert(own->m_ownHand.m_faceUp.end(), own->m_ownHand.m_faceDown.begin(), own->m_ownHand.m_faceDown.end());
    own->m_ownHand.m_faceDown.clear();

    int sum = own->m_ownHand.sum();
    while(sum <= 16){
        Card card = deck.getCard();
        sum += card.getValue();
        own->m_ownHand.m_faceUp.emplace_back(card);
    }
    cout << "Dealer's Cards: " << own->m_ownHand << endl;
    return 0;
}

int stand(Agent* own, Agent* other, Deck& deck){
    return 0;
}

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

int doubleMove(Agent* own, Agent* other, Deck& deck){
    if(deck.size() > 0){
        Card card = deck.getCard();
        own->m_ownHand.m_faceUp.emplace_back(deck.getCard());
        cout << "Your Cards: " << own->m_ownHand << endl;
    }
    return 0;
}


