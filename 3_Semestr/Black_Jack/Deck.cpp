#include "Deck.h"

Deck:: Deck ( unsigned int n ) {
    size_ = STANDART_SIZE_DECK * n;
    deck_ =  new Card[size_];
    int step = STEP * n;
    unsigned int value = 0;
    for ( unsigned int i = 0; i < size_; i = i + step ) {
        for (int j = 0; j < step ; j++) {
            Card tmp( SUIT[j/n], DATA[value], value);
            deck_[i + j] = tmp;
        }
        value++;
    }
}

Deck:: Deck ( ) {
    size_ = DEFAULT_SIZE;
    deck_ =  new Card[size_];
    for ( unsigned int i = 0; i < size_; i++ ) {
        Card tmp( i + 1 );
        deck_[i] = tmp;
    }
}

Deck:: ~Deck() {
    delete [] deck_;
}

void Deck:: shuffle( ) {
    top_ = 0;
    for ( int i = 0; i < size_; i++) {
        int idx = rand() % ( i + 1 );
        if ( idx != i ) {
            std::swap( deck_[i], deck_[idx] );
        }
    }
}

Card* Deck:: give ( ){
    if ( DEFAULT_SIZE == size_ ) {
        return & deck_[rand() % size_];
    }
    return & deck_[top_++];
};

void Deck:: print() {
    for ( int i = 0; i < size_; i++ ) {
        deck_[i].print();
    }
};

Deck & Deck:: operator= ( const Deck & obj ) {
    if ( this != &obj ) {
        delete [] deck_;
        this -> top_ = obj.top_;
        this -> size_ = obj.size_;
        this -> deck_ = new Card [this -> size_];
        std::copy(obj.deck_, (obj.deck_ + obj.size_ ), this -> deck_);
    }
    return *this;
}

void Deck:: printLastCard (  ) const{
    deck_[top_ -1].print();
}
