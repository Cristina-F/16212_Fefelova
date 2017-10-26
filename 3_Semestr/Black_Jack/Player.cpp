#include "Player.h"

Player:: Player( ) {}

Player:: ~Player( ) {}

bool Player:: step ( Card & card ){
    if ( hand.score() < 15 ) {
        return true;
    }
    return false;
}

void Player:: get_card( Deck & deck ) {
    hand.get_card( deck );
}

void Player:: print( ) {
    hand.print();
}

Card & Player:: first_card ( ) {
    return hand.first_card();
}

int Player:: score() {
    return hand.score();
}
