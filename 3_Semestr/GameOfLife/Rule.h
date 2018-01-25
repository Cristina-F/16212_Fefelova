#ifndef RULE_H
#define RULE_H

#include <iostream>

class Field;
class Rule
{
public:
    Rule();
    virtual ~Rule();
    virtual void change(  Field * field, Field * newField, int liveNeighbors, int x, int y ) = 0;
    virtual const std::string  getName() = 0;
private:
};

#endif // RULE_H
