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
    Player( );

    ~Player( );

    virtual bool step ( Card & card );

    virtual void get_card( Deck & deck );

    virtual void print( );

    virtual Card & first_card ( );

    virtual int score();
private:
    Hand hand;
};

#endif //BLACK_JACK_PLAYER_H
