//
// Created by cristina on 22.11.17.
//

#ifndef BLACK_JACK_Strat1_H
#define BLACK_JACK_Strat1_H

#include "../Player.h"

class Strat1 : public Player{
public:
    Strat1();

    ~Strat1() override ;

    bool step(  Card & card ) override ;

private:

};


#endif //BLACK_JACK_Strat1_H
