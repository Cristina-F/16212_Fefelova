#include "Louis.h"
#include "../Factory.h"

Louis:: Louis(){ }

Louis:: ~Louis(){ }

bool Louis:: step( Card & card ) {
    int score = hand.score();
    int opponent_score = card.weight_();
    if ( score < 12 ) {
        return true;
    }
    else if ( 12 == score ) {
        if ( opponent_score < 4 ) {
            return true;
        }
    }
    else if ( 16  == score ) {
        if ( 10 != opponent_score ) {
            return true;
        }
    }
    else if ( score > 12 && score < 16 ) {
        if ( opponent_score > 6 ) {
            return true;
        }
    }
    return false;

}

void Louis:: get_card( Deck & deck ) {
    hand.get_card( deck );
}

void Louis:: print( ) {
    hand.print();
}

Card & Louis:: first_card ( ) {
    return hand.first_card();
}

int Louis:: score() {
    return hand.score();
}

Player * cr_Louis () {
    return new Louis;
}

bool l = Factory::get_instance() -> register_player("if_16_stop", cr_Louis );