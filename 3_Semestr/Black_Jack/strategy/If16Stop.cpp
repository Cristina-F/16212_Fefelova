#include "If16Stop.h"

#include "../Factory.h"
#include "../HandEvaluator.h"

Player * crIf16 () {
    return new If16Stop;
}

namespace {
    bool b = Factory<Player,Player*(*)(), std::string>::getInstanse()->regist3r("If16Stop", crIf16);
}


If16Stop:: If16Stop(){
    name_ = "If16Stop";
}

If16Stop:: ~If16Stop(){}

bool If16Stop:: step(  Card & card )  {
    HandEvaluator evaluator;
    return (evaluator.countScore(hand_) < STOP ) ;
}
