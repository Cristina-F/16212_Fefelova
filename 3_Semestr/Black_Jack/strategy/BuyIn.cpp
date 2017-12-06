#include "BuyIn.h"

#include "../HandEvaluator.h"
#include "../Factory.h"

Player * crBuyIn () {
    return new BuyIn;
}

namespace {
    bool b = Factory<Player,Player*(*)(), std::string>::getInstanse()->regist3r("BuyIn", crBuyIn);
}

BuyIn::BuyIn(){
    name_ = "BuyIn";
}

BuyIn:: ~BuyIn(){ }

bool BuyIn:: step( Card & card ) {
    HandEvaluator evaluator;
    int score = evaluator.countScore(hand_);
    int scoreOpponent = card.getWeight();

    if ( evaluator.isSoftHand( hand_ ) ) {
        if ( score < 18 ) {
            return true;
        }
        else if ( score == 18 ) {
            if ( 10 == scoreOpponent || 9 == scoreOpponent ) {
                return true;
            }
        }
        return false;
    }
    else {
        if ( score < 12 ){
            return true;
        }
        else if ( 12 == score ){
            if ( (scoreOpponent > 6 && scoreOpponent <= 11) || 2 == scoreOpponent || 3 == scoreOpponent) {
                return  true;
            }
        }
        else if ( score > 12 && score < 17 ) {
            if (scoreOpponent > 6 && scoreOpponent <= 11) {
                return true;
            }
        }
        return false;
    }
}
