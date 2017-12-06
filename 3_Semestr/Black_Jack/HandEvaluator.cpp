//
// Created by cristina on 04.12.17.
//

#include "HandEvaluator.h"

HandEvaluator:: HandEvaluator() {}

HandEvaluator:: ~HandEvaluator() {}

bool HandEvaluator:: isSoftHand( std:: vector <Card*> hand ) {
    return ( score_ <= MAX && ace( hand ) );
}

unsigned int HandEvaluator:: countScore( std:: vector <Card*> hand ) {
    score_ = 0;
    for( Card * i: hand )  {
        score_ += i -> getWeight();
    }
    return score_;
}

bool HandEvaluator:: checkTwoAce ( std:: vector <Card*> hand ) {
    for( Card *  i: hand )  {
        if ( !( i -> isAce() ) ){
            return false;
        }
    }
    return true;
}

bool  HandEvaluator:: isBlackJack ( std:: vector <Card*> hand ) {
    if ( hand[0] -> getWeight() == 10 && hand[1] -> getWeight() == 11) {
        return true;
    }
    else if ( hand[1] -> getWeight() == 10 && hand[0] -> getWeight() == 11) {
        return true;
    }
    return false;
}

unsigned int HandEvaluator:: checkAce( std:: vector <Card*> hand ){
    if ( MAX + 1 == score_ ) {
        if( checkTwoAce( hand ) ) {
            return score_;
        }
    }
    score_ = 0;
    for( Card * i: hand )  {
        if (  i -> сhangeWeightAce(  ) ) {
            break;
        }
    }
    score_ = countScore( hand );
    return score_;
}

int HandEvaluator:: checkPrioritet(std:: vector <Card*> hand ) {
    int prioritet  = 0;
    if ( checkTwoAce(hand) ) {
        prioritet = GOLD_POINT;
    }
    else if ( isBlackJack(hand) ) {
        prioritet = BLACK_JACK;
    }
    else{
        prioritet = COMBINATION;
    }
    return prioritet;
}

bool HandEvaluator:: ace(std:: vector <Card*> hand ) {
    for ( Card * card: hand ) {
        if ( WEIGHT_ACE == card -> getWeight()  ) {
            return true;
        }
    }
    return false;
}