//
// Created by cristina on 24.09.17.
//

#ifndef LAB1_FLAT_MAP_H
#define LAB1_FLAT_MAP_H

#include <iostream>
#include <string>
#include "student.h"


int max (int x, int y ) {
    if ( x > y ) {
        return x;
    }
    return y;
}

template <typename Tkey, typename Tdata> class Flat_map {
public:
    Flat_map( int initial_size );
    Flat_map( );
    Flat_map( const Flat_map& obj );

    ~Flat_map( );

    Tdata& operator[]( const Tkey& key );

    bool insert( const Tkey& key, const Tdata& value);

    bool erase( const Tkey& key );

    Flat_map& operator=(const Flat_map& obj);

    void clear();

    bool  contains(const Tkey& key ) const;

    Tdata& at(  Tkey& key );

    const Tdata&  at(const Tkey& key) const;

    bool empty() const;

    void print( );

    void swap( Flat_map& obj );

    size_t size_() const;

    size_t capacity_() const;

    friend bool operator==(const Flat_map< Tkey, Tdata>& a, const Flat_map<Tkey, Tdata>& b) {
        int size_ = max(a.capacity, b.capacity );
        for ( int i = 0; i < size_; i++ ) {
            if ( a.arr[i].first != b.arr[i].first ||  a.arr[i].second != b.arr[i].second ) {
                return false;
            }
        }
        return true;
    }

    friend bool operator!=(const Flat_map <Tkey, Tdata> & a, const Flat_map<Tkey,  Tdata>& b) {
        if ( a == b ) {
            return false;
        }
        return true;
    }


private:
    std::pair <Tkey, Tdata> *arr = nullptr;
    int size = 0;
    int capacity = 0;
    int bin_search( const Tkey ) const;
};

template <typename TKey, typename Tdata>
Flat_map <TKey, Tdata>:: Flat_map( int initial_size): size( initial_size ) {
    arr = new std::pair<TKey, Tdata> [initial_size];
}

template <typename TKey, typename Tdata>
Flat_map <TKey, Tdata>:: Flat_map( ){
    arr = new std::pair<TKey, Tdata>[1];
}

template <typename TKey, typename Tdata>
Flat_map<TKey, Tdata>::  Flat_map( const Flat_map& obj ): size( obj.size ) {
    arr = new std::pair<TKey, Tdata> [size];
}

template <typename TKey, typename Tdata>
Flat_map<TKey, Tdata>:: ~Flat_map( ) {
    delete [] arr;
}

template <typename TKey, typename Tdata>
int Flat_map<TKey, Tdata>:: bin_search( const TKey key ) const {
    if ( key <= arr[0].first ) {
        return 0;
    }
    int low = 0;
    int middle = 0;
    int high = capacity - 1;
    while( high > 0 || low < capacity ) {
        middle = ( low / 2 ) + ( high / 2) + ( low % 2 + high % 2 ) / 2;
        if ( ( key > arr[middle].first && key < arr[middle + 1].first ) ) {
            return middle + 1;
        }
        else if ( arr[middle].first == key ) {
            return middle;
        }
        else if ( key < arr[middle].first ){
            high = middle - 1;
        }
        else {
            low = middle + 1;
        }
    }
    return -1;
}

template <typename TKey, typename Tdata>
bool Flat_map <TKey, Tdata>:: insert( const TKey& key, const Tdata& value) {
    if ( 0 == size ) {
        return false;
    }
    std::pair <TKey, Tdata> data( key,value );
    if ( 0 == capacity || key > arr[capacity - 1].first  ) {
        arr[capacity++] = data;
    }
    else {
        int index = bin_search( key );
        if( key != arr[index].first ) {
            for (int i = capacity - 1; i >= index; i--) {
                arr[i + 1] = arr[i];
            }
            capacity++;
        }
        arr[index] = data;
    }
    return true;
}

template <typename TKey, typename Tdata>
bool Flat_map<TKey, Tdata>:: erase( const TKey& key ) {
    int index = bin_search( key );
    if ( -1 != index && key == arr[index].first ) {
        for( int i = index; i < capacity; i++ ) {
            arr[i] = arr[i+1];
        }
        capacity--;
        return true;
    }
    return false;
}

template <typename TKey, typename Tdata>
void Flat_map<TKey, Tdata>:: clear() {
    for( int i = 0; i < capacity; i++ ) {
        Tdata data;
        arr[i].first.clear();
        arr[i].second = data;
    }
    capacity = 0;
}

template <typename TKey, typename Tdata>
bool Flat_map<TKey, Tdata>:: empty() const {
    if ( 0 == capacity ) {
        return true;
    }
    return false;
}

template <typename TKey, typename Tdata>
void Flat_map<TKey, Tdata>:: print( ) {
    std::cout<<"capacity = "<<capacity<<" size = "<<size<<std::endl;
    for( int i = 0; i < capacity; i++) {
        std::cout<<"i = "<<i<<" key = "<<arr[i].first<<" age = "<<arr[i].second.age<<" weight = "<<arr[i].second.weight<<std::endl;
    }
}

template <typename TKey, typename Tdata>
void Flat_map<TKey, Tdata>:: swap( Flat_map& obj) {
    std::swap( this -> capacity, obj.capacity);
    std::swap( this -> size, obj.size );
    std::swap( this -> arr, obj.arr);
}

template <typename TKey, typename Tdata>
size_t Flat_map<TKey, Tdata>:: size_() const {
    return size;
}

template <typename TKey, typename Tdata>
size_t Flat_map<TKey, Tdata>:: capacity_() const {
    return capacity;
}

template <typename TKey, typename Tdata>
bool  Flat_map<TKey, Tdata>:: contains( const TKey& key ) const {
    int index = bin_search( key );
    if ( -1 != index && key == arr[index].first ) {
        return true;
    }
    return false;
}

template <typename TKey, typename Tdata>
Tdata& Flat_map<TKey, Tdata>:: at(  TKey& key ) {
    int index = bin_search( key );
    if ( -1 != index && key == arr[index].first ) {
        return arr[index].second;
    }
    throw 123;
}

template <typename TKey, typename Tdata>
const Tdata& Flat_map<TKey, Tdata>:: at( const TKey& key) const {
    int index = bin_search( key );
    if ( -1 != index && key == arr[index].first ) {
        return arr[index].second;
    }
    throw 123;
}

template <typename TKey, typename Tdata>
Tdata& Flat_map<TKey, Tdata>:: operator[]( const TKey& key ) {
    for ( int i = 0; i < capacity; i++ ) {
        if ( key == arr[i].first ) {
            return arr[i].second;
        }
    }
    Tdata data;
    arr[capacity].first = key;
    arr[capacity].second = data;
    return arr[capacity++].second;
}

template <typename TKey, typename Tdata>
Flat_map<TKey, Tdata>& Flat_map<TKey, Tdata>:: operator=( const Flat_map& obj ) {
    if (this != &obj) {
        delete[]arr;
        this->capacity = obj.capacity;
        this->size = obj.size;
        this->arr = new std::pair<TKey, Tdata>[this->size];
        std::copy(obj.arr, (obj.arr + obj.capacity ), this->arr);
    }
    return *this;
}

#endif //LAB1_FLAT_MAP_H
