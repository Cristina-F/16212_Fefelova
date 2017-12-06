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

    Card * give ( );

    void print();

    Deck & operator= ( const Deck & obj );

     void printLastCard (  ) const;

private:
    Card * deck_ = nullptr;
    unsigned int top_ = 0;
    unsigned int size_ = 0;
    const unsigned  int DEFAULT_SIZE = 10;
    const unsigned int STEP = 4;
    const unsigned int STANDART_SIZE_DECK = 52;
    const std::string  DATA[13] = { std::string("TWO"), std::string("THREE"),  std::string("FOUR"), std::string("FIVE"),
                                std::string("SIX"), std::string("SEVEN"), std::string("EIGHT"),
                                std::string("NINE"), std::string("TEN"), std::string("JACK"), std::string("QUEEN"),
                                std::string("KING"), std::string("ACE")};
    const std::string  SUIT[4] = { std::string("HEARTS"), std::string("DIAMONDS"), std::string("CLUBS"), std::string("SPADES")};
};


#endif //BLACK_JACK_DECK_H
