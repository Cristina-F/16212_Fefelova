//
// Created by cristina on 19.10.17.
//

#ifndef BLACK_JACK_PLAYER_H
#define BLACK_JACK_PLAYER_H

#include <vector>

#include "Deck.h"

class Player {
public:
    Player( );

    Player( std:: vector < Card* > hand );

    virtual ~Player( );

    virtual bool step ( Card & card ) = 0;

    void add( Deck & deck );

    void print( );

    Card & getFirstCard ( );

    const std::string getName();

    std::vector <Card*> getHand( );

    void printHand();

    void clear ();
protected:
    std:: string name_;
    std:: vector <Card*> hand_;
};

#endif //BLACK_JACK_PLAYER_H
