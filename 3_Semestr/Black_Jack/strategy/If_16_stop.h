#ifndef BLACK_JACK_IF_16_STOP_H
#define BLACK_JACK_IF_16_STOP_H

#include "../Player.h"

class If_16_stop : public Player {
public:
    If_16_stop();

    ~If_16_stop();

    bool step(  Card & card ) override;

    void get_card( Deck & deck ) override;

    void print( ) override;

    Card & first_card ( ) override;

    int score() override ;

private:
    Hand hand;
};

#endif //BLACK_JACK_IF_16_STOP_H
