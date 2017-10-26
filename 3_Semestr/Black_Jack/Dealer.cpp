#include "Dealer.h"

Dealer:: Dealer() {
    Deck new_deck;
    this -> deck = new_deck;
}

Dealer:: Dealer( unsigned int size_deck )  {
    Deck new_deck( size_deck);
    this -> deck = new_deck;
}

void Dealer:: shuffle( ) {
    deck.shuffle();
}

Dealer:: ~Dealer() { }

void Dealer:: give_out_cards( std:: vector <Player*> players) {
    give_cards_to_players( players );
    give_cards_to_players( players );
}

void Dealer:: give_cards_to_players( std:: vector <Player*> players ) {
    for( Player * i: players ) {
        give_card_player( i );
    }
}
void Dealer:: give_card_player( Player * player ) {
    player -> get_card( deck );
}

void Dealer:: print( std:: vector <Player*>  players ) {
    for( Player * i: players ) {
        i -> print();
    }
}

void Dealer:: winner( Player *first, Player *second ) {
    int first_score = first -> score();
    int second_score = second -> score();
    if ( )
}