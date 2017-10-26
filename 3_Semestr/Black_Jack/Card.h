#ifndef BLACK_JACK_CARD_H
#define BLACK_JACK_CARD_H

#include <iostream>

class Card {
public:
    Card( std:: string suit_, std:: string value_, unsigned int weight_);

    Card (unsigned int weight_);

    Card();

    ~Card();

    bool ace();

    void print( );

    int weight_();

    void сhange_weight_ace( );
private:
    std:: string suit;
    std:: string value;
    unsigned int weight = 0;
};

#endif //BLACK_JACK_CARD_H
