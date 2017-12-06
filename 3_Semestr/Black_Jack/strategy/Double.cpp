#include "Double.h"
#include "BuyIn.h"

#include "../Factory.h"
#include "../HandEvaluator.h"

Player * crDouble () {
    return new Double;
}

namespace {
    bool b = Factory<Player,Player*(*)(), std::string>::getInstanse()->regist3r("Double", crDouble);
}

Double:: Double(){
    name_ = "Double";
}

Double:: ~Double(){ }

bool Double:: step( Card & card ) {
    HandEvaluator evaluator;
    int score = evaluator.countScore(hand_);
    int scoreOpponent = card.getWeight();
    if( 2 == hand_.size() ) {
        if( evaluator.isSoftHand(hand_)) {
            if ( score < 19 ) {
                if ( 6 == scoreOpponent &&  score > 12  ){
                    return true;
                }
                else if ( 5 == scoreOpponent &&  score > 13 ) {
                    return true;
                }
                else if ( 4 == scoreOpponent && score > 15 ) {
                    return true;
                }
                else if ( 3 == scoreOpponent && score > 16 ) {
                    return true;
                }
            }
            return false;
        }
        else{
            if ( 9 == score && ( scoreOpponent > 2 && scoreOpponent < 7) ) {
                return  true;
            }
            else if ( score < 9 ){
                return true;
            }
            else if ( ( 10 == score || 11 == score )  &&  scoreOpponent < 10 ) {
                return true;
            }
            return false;
        }
    }
    else{
        Player * newStrategy = new BuyIn(hand_);
        bool result = newStrategy -> step(card);
        delete newStrategy;
        return  result;
    }
}
