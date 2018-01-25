#ifndef RULE2_H
#define RULE2_H

#include "Rule.h"

class Field;

class Rule2 : public Rule
{
public:
    Rule2();
    ~Rule2() override;
    void change(  Field * field, Field * newField, int liveNeighbors, int x, int y ) override;
    const std::string  getName() override;
private:

    const int TWO_NEIGHBORS = 2;
    const int FOUR_NEIGHBORS = 4;
    const int SEVEN_NEIGHBORS = 7;

    const bool LIFE_CELL = 1;
    const bool DEAD_CELL = 0;

    const std:: string name_ = "B4567/S234";
};

#endif // RULE2_H
