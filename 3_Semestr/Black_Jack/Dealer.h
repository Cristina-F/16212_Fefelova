#ifndef BLACK_JACK_DEALER_H
#define BLACK_JACK_DEALER_H

#include "Deck.h"
#include "Hand.h"
#include "Player.h"

class Dealer {
public:
    Dealer();

    Dealer( unsigned int size_deck );

    ~Dealer();

    void shuffle( );

    void give_out_cards( std:: vector <Player*>  players);

    void give_cards_to_players( std:: vector <Player*>   players );

    void give_card_player( Player*  player );

    void print( std:: vector <Player*>  players );

    void winner( Player * first, Player * second );
private:
    Deck deck;
};


#endif //BLACK_JACK_DEALER_H
