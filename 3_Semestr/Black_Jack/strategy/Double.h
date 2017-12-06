//
// Created by cristina on 01.11.17.
//

#ifndef BLACK_JACK_DOUBLE_H
#define BLACK_JACK_DOUBLE_H

#include "../Player.h"

class Double :public Player{
public:
    Double();

    ~Double() override ;

    bool step( Card & card ) override;

private:

};


#endif //BLACK_JACK_DOUBLE_H
