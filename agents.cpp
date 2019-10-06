#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <deque>
#include <unordered_map>
#include "card.h"
#include "agents.h"

using namespace std;

/* Agent class member functions */
Agent::Agent(vector<Card> faceUp, vector<Card> faceDown, unordered_map<string, Action> actions, Deck& deck) : m_actions(actions), m_deck(deck),
    m_ownHand(faceUp, faceDown) {
    m_other = 0;
}

Agent::~Agent(){}

void Agent::setCompetitor(Agent* other){
    m_other = other;
}

void Agent::discardHand(){
    m_ownHand.m_faceDown = vector<Card>();
    m_ownHand.m_faceUp = vector<Card>();
}

int Agent::calcScore(){
    return m_ownHand.sum();
}

/* Player Class */
Player::Player(vector<Card> faceUp, vector<Card> faceDown, unordered_map<string, Action> actions, Deck& deck, int initCash) 
    : Agent(faceUp, faceDown, actions, deck) {
    wager = 0;
    cash = initCash;
}

Player::~Player(){}

int Player::play(){
    string action = this->getAction();
    int res = this->m_actions[action](this, this->m_other, this->m_deck);
    if(action == "Double"){
        this->wager *= 2;
    }
    return res;
}

int Player::playTest(vector<string>& actions, int& idx){
    string action = actions[idx];
    int res = this->m_actions[action](this, this->m_other, this->m_deck);
    if(action == "Double"){
        this->wager *= 2;
    }
    idx++;
    return res;
}

int Player::askWager(){
    int status = 0;
    while(true){
        if(status == 0){
            cout << "How much would you like to wager in this round? Please enter a number." << endl;
        } else {
            cout << "Sorry, you can't bet this amount of money. Please enter a new wager." << endl;
        }
        string response;
        getline(cin, response);
        stringstream ss(response);
        int amount = 0;
        ss >> amount;
        if(amount > this->cash || amount < 0){
            status = 1;
        } else {
            this->wager = amount;
            break;
        }
    }

    return 0;
}

void Player::pickCards(Deck& deck){
    m_ownHand.m_faceUp.push_back(m_deck.getCard());
    m_ownHand.m_faceUp.push_back(m_deck.getCard());
}

string Player::getAction(){
    vector<string> available;
    for(auto& it : m_actions){
        available.push_back(it.first);
    }
    cout << "Please enter the number corresponding to the action you wish to choose." << endl;
    for(unsigned int i = 0; i < available.size(); ++i){
        cout << i << ": " << available[i] << "  ";
    }
    cout << endl;
    int choice;
    while(true){
        cin >> choice;
        if(cin.fail()){
            cin.clear();
            cout << "That is not a valid choice. Please enter a new number." << endl;
            cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
        } else {
            cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
            if(choice < 0 || choice >= (int) available.size()){
                cout << "That is not a valid choice. Please enter a new number." << endl;
            } else {
                break;
            }
        }
    }

    return available[choice];
}

/* Dealer Class */
Dealer::Dealer(vector<Card> faceUp, vector<Card> faceDown, unordered_map<string, Action> actions, Deck& deck) : Agent(faceUp, faceDown, actions, deck) {
}

Dealer::~Dealer(){}

int Dealer::checkBlackJack(){
    return m_actions["CheckBlackJack"](this, this->m_other, this->m_deck);
}

int Dealer::play(){
    return m_actions["GetMoreThan16"](this, this->m_other, this->m_deck);
}

void Dealer::pickCards(Deck& deck){
    m_ownHand.m_faceUp.push_back(m_deck.getCard());
    m_ownHand.m_faceDown.push_back(m_deck.getCard());
}
