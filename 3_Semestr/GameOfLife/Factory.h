#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <iostream>
#include <memory>

#include "FlatMap.h"

template <class Product>
class DefaultErrorPolicy {
public:
    static Product * error() {
        std::cout<<"ERROR!!!!"<<std::endl;
        return nullptr;
    }
};

template <class Product, class Creator, class Id, class ErrorPolicy = DefaultErrorPolicy<Product> >
class Factory {
public:
    // Синглтон
    static Factory * getInstanse( ){
        static  Factory f;
        return &f;
    }
    Product * create( const Id & id ){
        if ( !(creatorz.contains(id) ) ) {
            //ошибка!!!
            return ErrorPolicy::error();
        }
        return  creatorz[id]();
    }
    bool regist3r( const Id & id, Creator creator){
        creatorz[id] = creator;
        return true;
    }
private:
   Flat_map < Id, Creator > creatorz;
};


#endif //FACTORY_H
