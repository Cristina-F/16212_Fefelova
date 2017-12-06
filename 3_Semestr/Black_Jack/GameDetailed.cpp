#include "GameDetailed.h"

GameDetailed:: GameDetailed ( const Dealer &  dealer, std:: vector< Player* > players): dealer_(dealer), players_(players) {
}

GameDetailed:: ~GameDetailed() {
}

Player * GameDetailed:: game( ) {
    Player * first = players_[0];
    Player * second = players_[1];
    std::cout<<"EXIT: x"<<std::endl;
    const std:: string STOP = "x";
    dealer_.shuffle();
    dealer_.addCardsPlayers( first, second );
    std::cout<<std::endl;
    std::cout<<" NEW GAME "<<std::endl;
    first -> print();
    second -> print();
    HandEvaluator evaluator;
    while (1) {
        std:: string check;
        std::getline(std::cin, check);
        if ( STOP == check ) {
            break;
        }
        else {
            std::cout<<first ->getName()<<": ";
            int oldScore = evaluator.countScore(first -> getHand());
            if ( first -> step( second -> getFirstCard() )){
                dealer_.addCardPlayer( first );
                dealer_.printLastCard();
            }
            std::cout<<std::endl;
            std::cout<<"old score = "<<oldScore<<std::endl;
            std::cout<<"+"<< evaluator.countScore(first -> getHand()) - oldScore<<std::endl;
            std::cout<<"new score = "<< evaluator.countScore(first -> getHand())<<std::endl;
        }
        std::getline(std::cin, check);
        if ( STOP == check ) {
            break;
        }
        else {
            std::cout<<second -> getName()<<": ";
            int oldScore = evaluator.countScore(second -> getHand());
            if ( second -> step( first -> getFirstCard( ) ) ){
                dealer_.addCardPlayer( second );
                dealer_.printLastCard( );
            }
            std::cout<<std::endl;
            std::cout<<"old score = "<<oldScore<<std::endl;
            std::cout<<"+"<< evaluator.countScore(second -> getHand()) - oldScore<<std::endl;
            std::cout<<"new score = "<< evaluator.countScore(second -> getHand())<<std::endl;
        }

    }
    dealer_.print( first );
    dealer_.print(second);
    std::cout<<std::endl;
    return  dealer_.getWinner( first, second );
}