#ifndef ACTIONS_H
#define ACTIONS_H

#include "../Agents/agents.h"
#include "../Cards/card.h"

using namespace std;

int checkBlackJack(Agent* own, Agent* other, Deck& deck);

int getMoreThan16(Agent* own, Agent* other, Deck& deck);

int stand(Agent* own, Agent* other, Deck& deck);

int hit(Agent* own, Agent* other, Deck& deck);

int doubleMove(Agent* own, Agent* other, Deck& deck);
 
#endif
