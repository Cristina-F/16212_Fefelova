#include "Strat1.h"

#include "../HandEvaluator.h"
#include "../Factory.h"

Player * crStrat1 () {
    return new Strat1;
}

namespace {
    bool b = Factory<Player,Player*(*)(), std::string>::getInstanse()->regist3r("Strat1", crStrat1);
}

Strat1:: Strat1(){
    name_ = "Strat1";
}

Strat1:: ~Strat1(){}

bool Strat1:: step(  Card & card )  {
    HandEvaluator evaluator;
    int score = evaluator.countScore(hand_);
    int opponentScore = card.getWeight();
    if (  ( score < 16 && opponentScore > 7 ) || score < 14 ) {
        return true;
    }
    else {
        return (score < 18 && opponentScore > 8);
    }
}