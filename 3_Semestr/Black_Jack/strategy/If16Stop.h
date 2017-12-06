#ifndef BLACK_JACK_If16Stop_H
#define BLACK_JACK_If16Stop_H

#include "../Player.h"

class If16Stop : public Player {
public:
    If16Stop();

    ~If16Stop() override ;

    bool step(  Card & card ) override ;

private:
    const int STOP = 16;
};

#endif //BLACK_JACK_If16Stop_H
