//
// Created by cristina on 01.11.17.
//

#ifndef BLACK_JACK_BuyIn_H
#define BLACK_JACK_BuyIn_H

#include "../Player.h"

class BuyIn: public Player {
public:
    BuyIn();

    ~BuyIn() override;


    BuyIn( std:: vector < Card* > hand ) {
        hand_ = hand;
    }

    bool step( Card & card ) override;

private:

};


#endif //BLACK_JACK_BuyIn_H
