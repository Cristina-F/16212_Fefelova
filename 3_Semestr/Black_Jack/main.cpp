#include <iostream>
#include <ctime>
#include <vector>

#include "Factory.h"
#include "Player.h"
#include "Dealer.h"
#include "GameDetailed.h"
#include "GameFast.h"
#include "GameTournament.h"

const std:: string detailed = "--detailed";
const std:: string fast = "--fast";
const std:: string tournament = "--tournament";

std:: string getMode( char * argv[], int * idx ) {
    if ( fast == argv[(*idx)] ) {
        (*idx)++;
        return fast;
    }
    else if ( tournament == argv[(*idx)] ) {
        (*idx)++;
        return tournament;
    }
    else if ( detailed == argv[(*idx)]) {
        (*idx)++;
    }
    return detailed;
}

void deletePlayers( std:: vector<Player*> players ) {
    for ( Player * player : players ) {
        delete player;
    }
}

std:: vector <Player*> createPlayers ( int argc, char * argv[], int * idx, Factory<Player, Player*(*)(), std:: string> * f ) {
    std:: vector <Player*> players;
    for ( ; (*idx) < argc; (*idx)++) {
        Player * new_player = f -> create(std::string(argv[*idx]));
            if( new_player ) {
                players.push_back( new_player );
            }
            else{
                deletePlayers(players);
                throw std::runtime_error("bad key!!!!!!1111111oneoneoneoneone");
            }
    }
    return players;
}

Dealer createDealer ( char * argv[], int * idx ) {
    if ( atoi(argv[*idx]) ) {
        (*idx)++;
        return  Dealer( ( unsigned int )atoi(argv[1] ) ) ;
    }
    return Dealer();
}

int main( int argc, char * argv[] ) {
    const int MIN_PLAYERS = 2;
    srand( (unsigned int)time( 0 ) );
    if ( argc < 3) {
        std::cout<<"ERROR"<<std::endl;
        return  -1;
    }
    int idx = 1;
    Dealer dealer = createDealer( argv, & idx );
    std:: string mode = getMode( argv, & idx );
    Factory<Player, Player*(*)(), std:: string> * f = Factory<Player,Player*(*)(), std:: string>::getInstanse();
    std:: vector <Player * > players;
    try {
         players = createPlayers( argc, argv, & idx, f );
    }
    catch ( std::runtime_error ) {
        std::cout<<"Invalid data"<<std::endl;
        return -1;
    }
    if( players.size() < MIN_PLAYERS ){
        std::cout<<"НЕДОСТАТОЧНО ИГРОКОВ"<<std::endl;
        deletePlayers( players );
        return  -1;
    }
    if ( players.size() > MIN_PLAYERS ) {
        mode = tournament;
    }

    Game * game = nullptr;
    if ( detailed == mode ) {
        game  = new GameDetailed( dealer, players );
    }
    else if ( fast == mode ) {
        game  = new GameFast( dealer, players );
    }
    else {
        game = new GameTournament(dealer, players);
    }
    Player * winner = game -> game();
    dealer.printWinner(winner);
    delete game;
    deletePlayers(players);
    return 0;
}