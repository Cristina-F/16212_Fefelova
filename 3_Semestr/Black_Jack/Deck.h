#ifndef BLACK_JACK_DECK_H
#define BLACK_JACK_DECK_H

#include <iostream>
#include <string>

#include "Card.h"

class Deck {
public:
    Deck ( unsigned int n );

    Deck ( );

    ~Deck();

    void shuffle( );

    Card* get_card ( );

    void print();

    Deck& operator= ( Deck & obj );

private:
    Card * deck = nullptr;
    int top = 0;
    int size = 0;
    const std::string  data[13] = { std::string("TWO"), std::string("THREE"),  std::string("FOUR"), std::string("FIVE"),
                                std::string("SIX"), std::string("SEVEN"), std::string("EIGHT"),
                                std::string("NINE"), std::string("TEN"), std::string("JACK"), std::string("QUEEN"),
                                std::string("KING"), std::string("ACE")};
    const std::string  suit[4] = { std::string("HEARTS"), std::string("DIAMONDS"), std::string("CLUBS"), std::string("SPADES")};
};


#endif //BLACK_JACK_DECK_H
