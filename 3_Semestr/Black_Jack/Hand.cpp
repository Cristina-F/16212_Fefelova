#include "Hand.h"

Hand:: Hand(){}
Hand:: ~Hand(){ }

void Hand:: print() {
    std::cout<<"_______________"<<std::endl;
    for( Card * i: hand )  {
        i -> print();
    }
    std::cout<<"score = "<<score()<<std::endl;
    std::cout<<"_______________"<<std::endl;
}

int Hand:: count_score(  ) {
    score_ = 0;
    for( Card * i: hand )  {
        score_ += i -> weight_();
    }
    return score_;
}

int Hand:: score( ) {
    return score_;
}

bool Hand:: check_two_ace ( ) {
    for( Card *  i: hand )  {
        if ( !( i -> ace( ) ) ){
            return false;
        }
    }
    return true;
}

bool Hand:: Black_Jack ( ) {//??????
    if ( hand[0] -> weight_() == 10 && hand[1] -> weight_() == 11) {
        return true;
    }
    else if ( hand[1] -> weight_() == 10 && hand[0] -> weight_() == 11) {
        return true;
    }
    return false;
}

void Hand:: check_ace(){
    if ( 22 == score_ ) {
        if( check_two_ace() ){
            return;
        }
    }
    score_ = 0;
    for( Card * i: hand )  {
        i -> сhange_weight_ace(  );
        score_ += i -> weight_();
    }

}
void Hand:: get_card ( Deck & deck ){
    hand.push_back( deck.get_card( ) );
    if ( count_score() > 21 ) {
        check_ace();
    }
}

Card & Hand::first_card( ) {
    return  *( hand.front( ) );
}