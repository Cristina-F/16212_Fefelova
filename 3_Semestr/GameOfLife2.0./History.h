#ifndef LIFE_HISTORY_H
#define LIFE_HISTORY_H

#include <vector>

#include "Field.h"

class History {
public:
    History();
    bool add(  Field * obj);
    Field * getField ( unsigned int step);
    void clear();
    ~History();
    void print();
private:
    std:: vector<Field *> history_;
};


#endif //LIFE_HISTORY_H
