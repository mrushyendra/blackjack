#include <iostream>
#include <sstream>
#include <ncurses.h>
#include <cstdlib>
#include <string>
#include <random>
#include <deque>
#include <unordered_map>
#include "card.h"
#include "agents.h"
#include "actions.h"

int compareScores(int playerScore, int dealerScore, int expectedPl, int expectedDl);

/* Test suite. Can potentially be extended to take in multiple different gameplay scenarios, and unit tests for individual functions */
int main(int arg, char** argv){
    Deck deck = createBlackJackDeck();
    deck.fixedShuffle(500);

    unordered_map<string, Action> playerMoves({{"Double", doubleMove}, {"Stand", stand}, {"Hit", hit}});
    unordered_map<string, Action> dealerMoves({{"CheckBlackJack", checkBlackJack}, {"GetMoreThan16", getMoreThan16}});
    Player player(vector<Card>(), vector<Card>(), playerMoves, deck, 500);
    Dealer dealer(vector<Card>(), vector<Card>(), dealerMoves, deck);

    vector<pair<int,int>> expected({{0,0}});
    vector<string> actions;
    int idx = 0;

    unsigned int round = 0;
    while(player.cash > 0){
        player.pickCards(deck);
        dealer.pickCards(deck);
        player.wager = 100;

        int playerScore = 0;
        int dealerScore = 0;
        if(dealer.checkBlackJack()){
        } else {
            while(true){
                if(!player.playTest(actions, idx)){
                    break;
                }
            }
            dealer.play();
        }

        playerScore = player.calcScore();
        dealerScore = dealer.calcScore();
        if(!compareScores(playerScore, dealerScore, expected[round].first, expected[round].second)){
            return -1;
        }

        player.discardHand();
        dealer.discardHand();
        if(deck.size() < 2){
            break;
        }
        round++;
    }

    if(round != expected.size()){
        cout << "Test failed. Game ended prematurely." << endl;
        return -1;
    }

    cout << "Tests Passed" << endl;
    return 0;
}

int compareScores(int playerScore, int dealerScore, int expectedPl, int expectedDl){
    if((playerScore != expectedPl) || (dealerScore != expectedDl)){
        cout << "Mismatch between actual and expected scores" << endl;
        return 0;
    }
    return 1;
}




