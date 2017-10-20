#include <iostream>
#include <ctime>

//#include "Deck.h"
//#include "Hand.h"
#include "Player.h"
#include "Dealer.h"

int main() {
    srand( time( 0 ) );

    Dealer dealer(1);
    dealer.shuffle();
    std:: vector <Player*> playrs;
    for ( int i = 0; i < 3; i++ ){
        Player* tmp = new Player;
        playrs.push_back( tmp );
    }
    dealer.give_out_carts( playrs );
    //dealer.print( playrs );
    return 0;
}