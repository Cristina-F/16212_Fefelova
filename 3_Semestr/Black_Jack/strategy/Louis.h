#ifndef BLACK_JACK_LOUIS_H
#define BLACK_JACK_LOUIS_H

#include "../Player.h"

class Louis : public Player {
public:
    Louis();

    ~Louis();

    bool step( Card & card ) override;

    void get_card( Deck & deck ) override;

    void print( ) override;

    Card & first_card ( ) override;

    int score() override ;

private:
    Hand hand;
};

#endif //BLACK_JACK_LOUIS_H
