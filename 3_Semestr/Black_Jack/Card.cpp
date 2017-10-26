#include "Card.h"

Card:: Card( std:: string suit_, std:: string value_, unsigned int weight_): suit(suit_), value( value_ ) {
    if ( weight_ < 9 ) {
        weight = weight_ + 2;
    }
    else if ( 12 == weight_ ) {
        weight = 11;
    }
    else {
        weight = 10;
    }

}

Card:: Card ( unsigned int weight_ ): weight(weight_) { }

Card:: Card(){ }

Card:: ~Card(){ }

bool Card:: ace() {
    if ( "ACE" == value  ) { //??????
        return true;
    }
    return false;
}

void Card:: print( ) {
    std::cout<<suit<<"  "<<value<<"  "<<weight<<std::endl;
}

int Card:: weight_() {
    return weight;
}

void Card:: сhange_weight_ace( ){
    if( this -> ace() ){
        this -> weight = 1;
    }
}
