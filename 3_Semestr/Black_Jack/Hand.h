#ifndef BLACK_JACK_HAND_H
#define BLACK_JACK_HAND_H

#include <iostream>
#include <vector>

#include "Card.h"
#include "Deck.h"

class Hand {
public:
    Hand();

    ~Hand();

    void print();

    int count_score();

    int score();

    bool check_two_ace ( );

    bool Black_Jack ();

    void check_ace();

    void get_card ( Deck & deck );

    Card & first_card( );

    friend bool operator==( Hand & a, Hand & b ) {
        int first_score = a.score();
        int second_score = b.score();
        return ( first_score == second_score );
    }

private:
    std:: vector <Card*> hand;
    unsigned int score_ = 0;
};


#endif //BLACK_JACK_HAND_H
