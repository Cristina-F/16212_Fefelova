#ifndef BLACK_JACK_GAMETOURNAMENT_H
#define BLACK_JACK_GAMETOURNAMENT_H

#include "GameFast.h"
#include "Dealer.h"
#include "Player.h"
#include "Game.h"
class GameTournament : public Game{
public:
    GameTournament ( const Dealer &  dealer,  const std:: vector<Player*> players);

    ~GameTournament() override;

    Player * game( ) override ;

    Player * findWinnerOfTournament();

private:
    Dealer dealer_;
    std:: vector<Player*> players_;
    int * count_win_ = nullptr;
    size_t size_ = 0;

};


#endif //BLACK_JACK_GAMETOURNAMENT_H
