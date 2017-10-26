#include "If_16_stop.h"
#include "../Factory.h"

If_16_stop:: If_16_stop(){}

If_16_stop:: ~If_16_stop(){}

bool If_16_stop:: step(  Card & card )  {
    if ( hand.score() < 16 ) {
        return true;
    }
    return false;
}

void If_16_stop:: get_card( Deck & deck )  {
    hand.get_card( deck );
}

void If_16_stop:: print( )  {
    hand.print();
}
Card & If_16_stop:: first_card ( ) {
    return hand.first_card();
}

Player * cr_If_16 () {
    return new If_16_stop;
}
int If_16_stop::score() {
    return  hand.score();
}
bool b = Factory::get_instance() -> register_player("if_16_stop", cr_If_16 );

