#include <iostream>
#include <ctime>
#include <vector>

#include "Factory.h"

#include "Player.h"
#include "Dealer.h"
#include "strategy/If_16_stop.h"
#include "strategy/Louis.h"

int main() {

    srand( time( 0 ) );

    Dealer dealer(1);
    dealer.shuffle();

    std:: vector <Player *> players;

    players.push_back( new If_16_stop );
    players.push_back( new Louis );

    dealer.give_out_cards( players );

    Player * first = players.front();
    Player * second  = players.back();
    bool first_step ;
    bool second_step;
    while( ( first_step = first-> step( second -> first_card() ) ) || ( second_step = second -> step( first -> first_card( ) ) ) ) {
        if ( first_step ){
            dealer.give_card_player( first );
        }
        if ( second_step ){
            dealer.give_card_player( second );
        }
    }
    dealer.print( players );
    dealer.winner( first, second );
    for ( Player * player : players ) {
        delete player;
    }
    return 0;
}