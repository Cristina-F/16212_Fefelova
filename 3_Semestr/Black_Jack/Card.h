//
// Created by cristina on 19.10.17.
//

#ifndef BLACK_JACK_CARD_H
#define BLACK_JACK_CARD_H

#include <iostream>
#include <string>

class Card {
public:
    Card( std:: string suit_, std:: string value_, unsigned int weight_): suit(suit_), value( value_ ) {
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

    Card (unsigned int weight_): weight(weight_) {
    }

    Card( ) {};

    ~Card(){}
    void print( ) {
        std::cout<<suit<<"  "<<value<<"  "<<weight<<std::endl;
    }
    int weight_() {
        return weight;
    }
private:
    std:: string suit;
    std:: string value;
    unsigned int weight = 0;
};

#endif //BLACK_JACK_CARD_H
