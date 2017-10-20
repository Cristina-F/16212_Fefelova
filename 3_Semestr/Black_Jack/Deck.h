//
// Created by cristina on 18.10.17.
//

#ifndef BLACK_JACK_DECK_H
#define BLACK_JACK_DECK_H

#include <iostream>
#include <string>

#include "Card.h"

class Deck {
public:
    Deck ( unsigned int n ): size(52 * n) {
        deck =  new Card[size];
        int step = 4 * n;
        unsigned int value = 0;
        for ( unsigned int i = 0; i < size; i = i + step ) {
                for (int j = 0; j < step ; j++) {
                    Card tmp( suit[j/n], data[value], value);
                    deck[i + j] = tmp;
                }
            value++;
        }
    }

    Deck ( ): size( 10 ) {
        deck =  new Card[size];
        for ( unsigned int i = 0; i < size; i++ ) {
            Card tmp( i + 1 );
            deck[i] = tmp;
        }
    }

    ~Deck(){
        delete [] deck;
    }

    void shuffle( ){
        top = 0;
        for ( int i = 0; i < size; i++) {
            int idx = rand() % ( i + 1 );
            if ( idx != i ) {
                std::swap( deck[i], deck[idx] );
            }
        }
    }

    Card& get_card ( ){
        if ( 10 == size ) {
            return deck[rand() % size];
        }
        std::cout<<"????"<<std::endl;
       deck[top].print();
        return deck[top++];
    };

    void print() {
        for ( int i = 0; i < size; i++ ) {
            deck[i].print();
        }
    };

    Deck& operator= ( Deck & obj ) {
        if ( this != &obj ) {
            delete [] deck;
            this -> top = obj.top;
            this -> size = obj.size;
            this -> deck = new Card [this -> size];
            std::copy(obj.deck, (obj.deck + obj.size ), this -> deck);
        }
        return *this;
    }

private:
    Card *deck = nullptr;
    int top = 0;
    int size = 0;
    const std::string  data[13] = { std::string("TWO"), std::string("THREE"),  std::string("FOUR"), std::string("FIVE"),
                                std::string("SIX"), std::string("SEVEN"), std::string("EIGHT"),
                                std::string("NINE"), std::string("TEN"), std::string("JACK"), std::string("QUEEN"),
                                std::string("KING"), std::string("ACE")};
    const std::string  suit[4] = { std::string("HEARTS"), std::string("DIAMONDS"), std::string("CLUBS"), std::string("SPADES")};
};


#endif //BLACK_JACK_DECK_H
