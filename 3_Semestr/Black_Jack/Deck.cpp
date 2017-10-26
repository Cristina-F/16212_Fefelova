#include "Deck.h"

Deck:: Deck ( unsigned int n ): size(52 * n) {
    deck =  new Card[size];
    int step = 4 * n;
    unsigned int value = 0;
    for ( unsigned int i = 0; i < size; i = i + step ) {
        for (int j = 0; j < step ; j++) {
            Card tmp( suit[j/n], data[value], value);
            deck[i + j] = tmp;
        }
        value++;
    }
}

Deck:: Deck ( ): size( 10 ) {
    deck =  new Card[size];
    for ( unsigned int i = 0; i < size; i++ ) {
        Card tmp( i + 1 );
        deck[i] = tmp;
    }
}

Deck:: ~Deck() {
    delete [] deck;
}

void Deck:: shuffle( ) {
    top = 0;
    for ( int i = 0; i < size; i++) {
        int idx = rand() % ( i + 1 );
        if ( idx != i ) {
            std::swap( deck[i], deck[idx] );
        }
    }
}

Card* Deck:: get_card ( ){
    if ( 10 == size ) {
        return &deck[rand() % size];
    }
    return &deck[top++];
};

void Deck:: print() {
    for ( int i = 0; i < size; i++ ) {
        deck[i].print();
    }
};

Deck& Deck:: operator= ( Deck & obj ) {
    if ( this != &obj ) {
        delete [] deck;
        this -> top = obj.top;
        this -> size = obj.size;
        this -> deck = new Card [this -> size];
        std::copy(obj.deck, (obj.deck + obj.size ), this -> deck);
    }
    return *this;
}
