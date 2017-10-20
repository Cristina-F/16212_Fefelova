//
// Created by cristina on 19.10.17.
//

#ifndef BLACK_JACK_HAND_H
#define BLACK_JACK_HAND_H

#include <iostream>
#include <vector>

#include "Card.h"
#include "Deck.h"

class Hand {
public:
    Hand(){ }
    ~Hand(){ }

    void print() {
        std::cout<<"_______________"<<std::endl;
        for( Card i: hand )  {
            i.print();
        }
        std::cout<<score()<<std::endl;
        std::cout<<"_______________"<<std::endl;
    }

    int score(  ){
        int score = 0;
        for( Card i: hand )  {
            score += i.weight_();
        }
        return score;
    }

    void get_card ( Deck & deck ){
        hand.push_back( deck.get_card( ) );
    }

    friend bool operator==( Hand & a, Hand & b ) {
        int first_score = a.score();
        int second_score = b.score();
        return ( first_score == second_score );
    }
private:
    std:: vector <Card> hand;
};


#endif //BLACK_JACK_HAND_H
