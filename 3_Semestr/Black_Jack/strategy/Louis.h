#ifndef BLACK_JACK_LOUIS_H
#define BLACK_JACK_LOUIS_H

#include "../Player.h"

class Louis : public Player {
public:
    Louis();

    ~Louis() override ;

    bool step( Card & card ) override;

private:
};

#endif //BLACK_JACK_LOUIS_H
