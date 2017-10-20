//
// Created by cristina on 19.10.17.
//

#ifndef BLACK_JACK_PLAYER_H
#define BLACK_JACK_PLAYER_H

#include <vector>

#include "Deck.h"
#include "Hand.h"

class Player {
public:
    Player( ) {

    }
    ~Player( ) {

    }
    void step ( ){ }//Ход в зависимости от стратегии
    void get_card( Deck & deck ) {
        hand.get_card( deck );
    }
    void print( ) {
        hand.print();
    }
private:
Hand hand;
};


#endif //BLACK_JACK_PLAYER_H
