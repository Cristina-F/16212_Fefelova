#include "Dealer.h"
#include <iomanip>

Dealer:: Dealer(): deck_(Deck()) {
}

Dealer:: Dealer( unsigned int sizeDeck ): deck_(Deck(sizeDeck))  {
}

Dealer:: Dealer( const Dealer & obj ) {
    this -> deck_ = obj.deck_;
}

Dealer:: ~Dealer() { }

void Dealer:: shuffle( ) {
    deck_.shuffle();
}

void Dealer:: addCardsPlayers( Player * first, Player * second){
    for ( int i = 0; i < 2; i ++ ) {
        addCardPlayer(first);
        addCardPlayer(second);
    }
}

void Dealer:: addCardPlayer( Player * player){
        player -> add( deck_ );
}

void Dealer:: print( std:: vector <Player*>  players ) const{
    for( Player * i: players ) {
        i -> print();
    }
}

void Dealer:: print( Player * player ) const{
    player -> print();
}

void Dealer:: printWinner(Player * player) const {
    if ( player ){
        std::cout<<"Winner: "<< player -> getName()<<std::endl;
    }
}

Player *  Dealer:: getWinner( Player * first, Player * second ) {
    HandEvaluator evaluator;
    std:: vector <Card*> firstHand = first -> getHand();
    std:: vector <Card*>  secondHand = second -> getHand();
    int firstScore = evaluator.countScore(firstHand);
    int secondScore = evaluator.countScore(secondHand);
    std::cout<<first -> getName()<<std::setw(20)<<"score = "<<firstScore<<std::endl;
    std::cout<<second -> getName()<<std::setw(20)<<"score = "<<secondScore<<std::endl;
    int firstPrioritet = evaluator.checkPrioritet(firstHand);
    int secondPrioritet = evaluator.checkPrioritet(secondHand);
    if ( firstPrioritet == secondPrioritet ) {
        if ( firstPrioritet == COMBINATION ) {
            if ( ( firstScore > secondScore || secondScore > MAX ) && firstScore <= 21  ) {
                return first;
            }
            else if ( ( secondScore > firstScore || firstScore > MAX ) && secondScore <= 21 ) {
                return second;
            }
            else if ( firstScore > MAX && secondScore > MAX ) {
                std::cout<<" No Winner :( "<<std::endl;
            }
            else {
                std::cout<<"Dead heat"<<std::endl;
            }
        }
        else {
            std::cout<<"Dead heat"<<std::endl;
        }
    }
    else {
        if ( firstPrioritet > secondPrioritet ) {
            return first;
        }
        else{
            return second;
        }
    }
    return nullptr;
}

void Dealer:: printLastCard(  ) const {
    deck_.printLastCard();
}

