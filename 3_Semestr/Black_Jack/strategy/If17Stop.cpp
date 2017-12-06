#include "If17Stop.h"

#include "../HandEvaluator.h"
#include "../Factory.h"

Player * crIf17 () {
    return new If17Stop;
}

namespace {
    bool b = Factory<Player,Player*(*)(), std::string>::getInstanse()->regist3r("If17Stop", crIf17);
}


If17Stop:: If17Stop(){
    name_ = "If17Stop";
}

If17Stop:: ~If17Stop(){}

bool If17Stop:: step(  Card & card )  {
    HandEvaluator evaluator;
    return ( evaluator.countScore(hand_) < STOP ) ;
}