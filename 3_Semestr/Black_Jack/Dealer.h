//
// Created by cristina on 19.10.17.
//

#ifndef BLACK_JACK_DEALER_H
#define BLACK_JACK_DEALER_H

#include "Deck.h"
#include "Hand.h"
#include "Player.h"

class Dealer {
public:
    Dealer() {

    }

    Dealer( unsigned int size_deck ) {
        Deck new_deck( size_deck);
        this -> deck = new_deck;
    }

   void shuffle( ) {
        deck.shuffle();
    }

    ~Dealer() {
    }
    void get_card ( ){
        hand.get_card( deck );
    }
    void give_out_carts( std:: vector <Player*>  players) {
        get_card();
        give_cards_to_players( players );
        //give_cards_to_players( players );
        /*for( Player* i: players ) {
            i -> print( );
        }*/
    }

    void give_cards_to_players( std:: vector <Player*>   players ) {
        int k = 0;
        for( Player*  i: players ) {
            std::cout<<k<<std::endl;
            i -> get_card( deck );
            k++;
        }
        return ;
    }

    void print( std:: vector <Player> & players ) {
        hand.print();
        for( Player i: players ) {
            i.print();
        }
    }
private:
    Deck deck;
    Hand hand;
};


#endif //BLACK_JACK_DEALER_H
