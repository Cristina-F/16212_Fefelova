#ifndef BLACK_JACK_GAME_H
#define BLACK_JACK_GAME_H

#include "Dealer.h"
#include "Player.h"

class Game {
public:
    Game ();

    virtual ~Game();

    virtual  Player * game( ) = 0;

};


#endif //BLACK_JACK_GAME_H
