#ifndef RULE1_H
#define RULE1_H

#include "Rule.h"

class Field;

class Rule1 : public Rule
{
public:
    Rule1();
    ~Rule1() override;
    void change(  Field * field, Field * newField, int liveNeighbors, int x, int y ) override;
    const std::string  getName() override;
private:
    const int THREE_NEIGHBORS = 3;
    const int TWO_NEIGHBORS = 2;
    const bool LIFE_CELL = 1;
    const bool DEAD_CELL = 0;

    const std:: string name_ = "B3/S23";
};

#endif // RULE1_H
