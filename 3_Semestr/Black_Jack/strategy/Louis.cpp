#include "Louis.h"

#include "../HandEvaluator.h"
#include "../Factory.h"

Player * crLouis () {
    return new Louis;
}

namespace {
    bool b = Factory<Player,Player*(*)(), std::string>::getInstanse()->regist3r("Louis", crLouis);
}

Louis:: Louis(){
    name_ = "Louis";
}

Louis:: ~Louis(){ }

bool Louis:: step( Card & card ) {
    HandEvaluator evaluator;
    int score = evaluator.countScore(hand_);
    int opponentScore = card.getWeight();
    if ( score < 12 ) {
        return true;
    }
    else if ( 12 == score ) {
        if ( opponentScore < 4 ) {
            return true;
        }
    }
    else if ( 16  == score ) {
        if ( 10 != opponentScore ) {
            return true;
        }
    }
    else if ( score > 12 && score < 16 ) {
        if ( opponentScore > 6 ) {
            return true;
        }
    }
    return false;

}
