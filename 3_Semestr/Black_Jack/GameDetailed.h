#ifndef BLACK_JACK_GameDetailed_H
#define BLACK_JACK_GameDetailed_H

#include "Dealer.h"
#include "Player.h"
#include "Game.h"

class GameDetailed : public Game {
public:

    GameDetailed( const Dealer &  dealer,  std:: vector <Player*> players);

    ~GameDetailed() override ;

    Player * game( ) override ;

private:
    Dealer dealer_;
    std::vector <Player*> players_;
};


#endif //BLACK_JACK_GameDetailed_H
