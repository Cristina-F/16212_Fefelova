//
// Created by cristina on 08.11.17.
//

#ifndef BLACK_JACK_GameFast_H
#define BLACK_JACK_GameFast_H

#include "Dealer.h"
#include "Player.h"
#include "Game.h"
class GameFast : public Game {

public:

    GameFast( const Dealer &  dealer,  std:: vector <Player*> players);

    ~GameFast() override ;

    Player * game( ) override ;

private:
    Dealer dealer_;
    std::vector <Player*> players_;
};


#endif //BLACK_JACK_GameFast_H
