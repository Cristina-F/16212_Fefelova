#include "Rule2.h"
#include "Field.h"
#include "Factory.h"

Rule * crRule2 () {
    return new Rule2;
}

namespace {
    bool b = Factory<Rule,Rule*(*)(), std::string>::getInstanse()->regist3r("B4567/S234", crRule2);
}

Rule2::Rule2()
{

}

Rule2::~Rule2(){}

void Rule2::change( Field * field, Field * newField, int liveNeighbors, int x, int y ) {
    if ( !field -> getStatus( x, y ) && liveNeighbors >= FOUR_NEIGHBORS && liveNeighbors <= SEVEN_NEIGHBORS ) {
        newField -> addCell( x, y, LIFE_CELL );
    }
    else if ( field -> getStatus( x, y ) ) {
        if ( liveNeighbors > FOUR_NEIGHBORS || liveNeighbors < TWO_NEIGHBORS) {
            newField -> addCell( x, y, DEAD_CELL);
        }
    }
}

const std::string  Rule2:: getName(){
    return name_;
}
