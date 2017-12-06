#include "Card.h"

Card:: Card( const std:: string suit, const std:: string value, unsigned int weight): suit_(suit), value_( value ) {
    if ( weight < 9 ) {
        weight_ = weight + 2;
    }
    else if ( 12 == weight ) {
        weight_ = 11;
    }
    else {
        weight_ = 10;
    }

}

Card:: Card ( unsigned int weight ): weight_(weight) { }

Card:: Card(){ }

Card:: ~Card(){ }

bool Card:: isAce() const{
    return ( "ACE" == value_ );
}

void Card:: print( ) const{
    std::cout<<suit_<<"  "<<value_<<"  "<<weight_<<std::endl;
}

int Card:: getWeight() const {
    return weight_;
}

bool Card:: сhangeWeightAce( ){
    if( this -> isAce() && weight_ != 1 ){
        this -> weight_ = 1;
        return true;
    }
    return false;
}
