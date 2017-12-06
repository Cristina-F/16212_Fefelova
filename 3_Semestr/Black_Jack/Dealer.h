#ifndef BLACK_JACK_DEALER_H
#define BLACK_JACK_DEALER_H

#include "Deck.h"
#include "Hand.h"
#include "Player.h"

class Dealer {
public:
    Dealer();

    Dealer( unsigned int sizeDeck );

    Dealer( const Dealer & obj );

    ~Dealer();

    void shuffle( );

    void addCardsPlayers( Player * first, Player * second);

    void addCardPlayer( Player * player);

    Player * getWinner( Player * first, Player * second );

    void print( std:: vector <Player*>  players ) const;

    void print( Player * player ) const;

    void  printLastCard(  ) const;// для режима с детализацией

    void printWinner(Player * player) const;
private:
    Deck deck_;
};


#endif //BLACK_JACK_DEALER_H
