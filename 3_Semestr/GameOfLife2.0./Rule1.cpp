#include "Rule1.h"
#include "Field.h"
#include "Factory.h"

Rule * crRule1 () {
    return new Rule1;
}

namespace {
    bool b = Factory<Rule,Rule*(*)(), std::string>::getInstanse()->regist3r("B3/S23", crRule1);
}

Rule1::Rule1()
{

}

Rule1::~Rule1(){}

void Rule1::change( Field * field, Field * newField, int liveNeighbors, int x, int y ) {
    if ( !field -> getStatus( x, y ) && THREE_NEIGHBORS == liveNeighbors) {
        newField -> addCell( x, y, LIFE_CELL );
    }
    else if ( field -> getStatus( x, y ) ) {
        if ( liveNeighbors > THREE_NEIGHBORS || liveNeighbors < TWO_NEIGHBORS) {
            newField -> addCell( x, y, DEAD_CELL);
        }
    }
}

const std::string  Rule1:: getName(){
    return name_;
}
