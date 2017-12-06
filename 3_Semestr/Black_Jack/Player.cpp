#include "Player.h"
#include "HandEvaluator.h"

Player:: Player( ) {}

Player:: ~Player( ) {}

Player::Player( std:: vector <Card*>  hand ): hand_( hand ) {}

void Player:: add( Deck & deck ) {
    HandEvaluator evaluator;
    hand_.push_back( deck.give() );
    if ( evaluator.countScore(hand_) > MAX ) {
       evaluator.checkAce(hand_);
    }
    evaluator.countScore( hand_ );
}

void Player:: print( ) {
    std::cout<<std::endl;
    std::cout<<name_<<std::endl;
    printHand();
}

void Player:: printHand() {
    std::cout << "_______________" << std::endl;
    for (Card *i: hand_) {
        i->print();
    }
    HandEvaluator evaluator;
    std::cout<<"score = "<<evaluator.countScore(hand_)<<std::endl;
    std::cout << "_______________" << std::endl;
}

Card & Player:: getFirstCard ( ) {
    return  *( hand_.front( ) );
}

const std::string Player:: getName() {
    return name_;
}

std:: vector <Card*>  Player:: getHand( ) {
    return hand_;
}
void  Player:: clear (){
    hand_.clear();
}
