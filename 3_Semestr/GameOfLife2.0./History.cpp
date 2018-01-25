#include "History.h"
#include <stdexcept>
#include <iostream>

History::History()  {

}

History::~History() {
    for( Field * i: history_) {
        delete i;
    }
}

 bool History::add( Field * obj) {
     Field * field_h = new Field( obj->getWidth(), obj->getHeight());
     *field_h = *obj;
     history_.push_back ( field_h );
     return true;
 }

Field * History::getField(unsigned int step) {
    if (  step < history_.size() ){
        return history_[step];
    }
    return history_.back();
}

void History:: clear() {
    for( Field * i: history_) {
           delete i;
     }
    history_.clear();
    print();
}
void History::print() {
    int cnt = 0;
    for ( Field*  i: history_){
        std::cout<<" generation = "<< ++cnt<< std::endl;
        (*i).print();
        std::cout<<std::endl;
        std::cout<<std::endl;
    }

}
