#include <iostream>
#include <sstream>
#include <ncurses.h>
#include <cstdlib>
#include <string>
#include <random>
#include <deque>
#include <unordered_map>
#include "Cards/card.h"
#include "Agents/agents.h"
#include "Actions/actions.h"

using namespace std;

int handleResult(Player& player, Agent& dealer, int playerScore, int dealerScore);
void showState(Player& player, Dealer& dealer);
string showResult(int result);

int main(int argc, char** argv){
    Deck deck = createBlackJackDeck();
    deck.shuffle();

    //Initialize player and dealer, and add available moves
    unordered_map<string, Action> playerMoves({{"Double", doubleMove}, {"Stand", stand}, {"Hit", hit}});
    unordered_map<string, Action> dealerMoves({{"CheckBlackJack", checkBlackJack}, {"GetMoreThan16", getMoreThan16}});
    Player player(vector<Card>(), vector<Card>(), playerMoves, deck, 500);
    Dealer dealer(vector<Card>(), vector<Card>(), dealerMoves, deck);
    player.setCompetitor(&dealer);
    dealer.setCompetitor(&player);

    int round = 0;

    while(player.cash > 0){
        cout << "-- Round " << round << " --" << endl;
        player.pickCards(deck);
        dealer.pickCards(deck);

        showState(player, dealer);
        player.askWager();
        cout << "Your wager: $" << player.wager << endl;

        int playerScore = 0;
        int dealerScore = 0;
        if(dealer.checkBlackJack()){
            cout << "Dealer gets a Blackjack!" << endl;
        } else {
            while(true){
                if(!player.play()){
                    break;
                }
            }
            dealer.play();
        }

        playerScore = player.calcScore();
        dealerScore = dealer.calcScore();
        cout << "Your Score: " << playerScore << endl;
        cout << "Dealer Score: " << dealerScore << endl;
        int result = handleResult(player, dealer, playerScore, dealerScore);
        cout << showResult(result) << endl << endl;
        round++;

        player.discardHand();
        dealer.discardHand();
        if(deck.size() < 2){
            cout << "No more cards in deck." << endl;
            break;
        }
    }

    cout << "Game Over! You are left with: $" << max(0, player.cash) << endl;
    return 0;
}

// Determines who wins among `player` and `dealer`, if any, and deals with player's wager appropriately. (Assumes Even odds)
int handleResult(Player& player, Agent& dealer, int playerScore, int dealerScore){
    if(playerScore <= 21 && ((playerScore > dealerScore) || (dealerScore > 21))){ //win
        player.cash += player.wager;
        player.wager = 0;
        return 2;
    } else if ((dealerScore <= 21) && ((playerScore > 21) || (playerScore < dealerScore))) { //lose
        player.cash -= player.wager;
        player.wager = 0;
        return 0;
    }
    return 1; //draw
}

// Outputs `player`'s available cash, and face up cards of both players to stdout.
void showState(Player& player, Dealer& dealer){
    cout << "Cash: $" << player.cash << endl;
    cout << "Your cards: " << player.m_ownHand << endl << "Dealer's Cards: " << dealer.m_ownHand << endl;
}

string showResult(int result){
    string msg;
    switch(result){
        case 0: 
            msg = "You lose this round.";
            break;
        case 1:
            msg = "It's a draw";
            break;
        case 2:
            msg = "You win this round!";
            break;
    }
    return msg;
}
