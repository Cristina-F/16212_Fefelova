//
// Created by cristina on 26.10.17.
//

#ifndef BLACK_JACK_FACTORY_H
#define BLACK_JACK_FACTORY_H

#include "flat_map.h"
#include <unordered_map>
#include "Player.h"

class Factory {
public:
    typedef Player * (* creator_t )();

    static Factory * get_instance( ){
        if ( !(p_instance) ) {
            p_instance = new Factory;
        }
        return p_instance;
    }

    Player * create( const std:: string & id ){
        return  creatorz[id]();
    }
    bool register_player( const std:: string & id, creator_t creator){
        creatorz[id] = creator;
        return true;
    }
    bool unregister( const  std:: string & id ) {
        return true;
    }
private:
    static Factory * p_instance ;
    Factory(){}
    Factory( const Factory & obj );
    Factory & operator = ( const Factory& );
    ~Factory();
    std:: unordered_map <std::string, creator_t> creatorz;
};


#endif //BLACK_JACK_FACTORY_H
