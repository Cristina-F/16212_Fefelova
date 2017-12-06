//
// Created by cristina on 22.11.17.
//

#ifndef BLACK_JACK_If17Stop_H
#define BLACK_JACK_If17Stop_H

#include "../Player.h"

class If17Stop : public  Player{
public:
    If17Stop();

    ~If17Stop() override ;

    bool step(  Card & card ) override ;

private:
    const int STOP = 17;
};


#endif //BLACK_JACK_If17Stop_H
