//
// Created by cristina on 06.10.17.
//

#ifndef LAB1_STUDENT_H
#define LAB1_STUDENT_H

struct value {
    unsigned  int age;
    unsigned  int weight;

    value( unsigned int a, unsigned int b ) {
        age = a;
        weight = b;
    }

    value() {
        age = 0;
        weight = 0;
    }

    friend bool operator!=( const value& a, const value& b ) {
        if ( a.age != b.age || a.weight != b.weight ) {
            return true;
        }
        return false;
    }
    friend bool operator==( const value& a, const value& b ) {
        if ( a != b ) {
            return false;
        }
        return true;
    }

};

#endif //LAB1_STUDENT_H
