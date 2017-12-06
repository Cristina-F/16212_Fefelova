#include "GameFast.h"

GameFast:: GameFast ( const Dealer &  dealer,  std:: vector <Player*> players): dealer_(dealer), players_(players){

}

GameFast:: ~GameFast() {}

Player * GameFast:: game( ) {
    Player * first = players_[0];
    Player * second = players_[1];
    dealer_.shuffle();
    dealer_.addCardsPlayers( first, second );
    std::cout<<std::endl;
    std::cout<<" NEW GAME "<<std::endl;
    bool first_step = 0;
    bool second_step = 0;
    while( ( first_step = first -> step( second -> getFirstCard() ) ) || ( second_step = second -> step( first -> getFirstCard( ) ) ) ) {
        if ( first_step ){
            dealer_.addCardPlayer( first );
        }
        if ( second_step ){
            dealer_.addCardPlayer( second );
        }
    }
    dealer_.print( first );
    dealer_.print(second);

   return  dealer_.getWinner( first, second );

}
