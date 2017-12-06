#ifndef BLACK_JACK_HandEvaluator_H
#define BLACK_JACK_HandEvaluator_H


#include "Card.h"
#include <vector>

enum PRIORITET{
    COMBINATION,
    BLACK_JACK,
    GOLD_POINT
};


class HandEvaluator {
public:
    HandEvaluator();

    ~HandEvaluator();

    bool isSoftHand( std:: vector <Card*> hand );

    unsigned int countScore( std:: vector <Card*> hand );

    bool checkTwoAce ( std:: vector <Card*> hand );

    bool  isBlackJack ( std:: vector <Card*> hand );

    unsigned int checkAce( std:: vector <Card*> hand );

    int checkPrioritet(std:: vector <Card*> hand );

    bool ace(std:: vector <Card*> hand );
private:
    unsigned int score_ = 0;
    const int WEIGHT_ACE = 11;
};


#endif //BLACK_JACK_HandEvaluator_H
