#ifndef BLACK_JACK_CARD_H
#define BLACK_JACK_CARD_H

#include <iostream>

const unsigned int MAX = 21;

class Card {
public:
    Card( const std:: string suit, const std:: string value, unsigned int weight);

    Card (unsigned int weight);

    Card();

    ~Card();

    bool isAce() const;

    void print( ) const;

    int getWeight() const;

    bool сhangeWeightAce( );
private:
    std:: string suit_;
    std:: string value_;
    unsigned int weight_ = 0;
};

#endif //BLACK_JACK_CARD_H
