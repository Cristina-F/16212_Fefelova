#ifndef LAB1_FLAT_MAP_H
#define LAB1_FLAT_MAP_H

#include <iostream>
#include <string>
#include <stdexcept>

template <typename Tkey, typename Tdata> class Flat_map {
public:
    Flat_map( size_t initial_size = 10 );

    Flat_map( const Flat_map& obj );

    ~Flat_map( );

    Tdata& operator[]( const Tkey& key );

    bool insert( const Tkey& key, const Tdata& value);

    bool erase( const Tkey& key );

    Flat_map& operator=(const Flat_map& obj);

    void clear();

    bool  contains(const Tkey& key ) const;

    Tdata& at( const Tkey& key );

    const Tdata&  at(const Tkey& key) const;

    bool empty() const;

   void print( );

    void swap( Flat_map& obj );

    size_t size_() const;

    size_t capacity_() const;

    friend bool operator==(const Flat_map< Tkey, Tdata>& a, const Flat_map<Tkey, Tdata>& b) {
        if ( a.capacity != b.capacity || a.size != b.size ) {
            return false;
        }
        for ( int i = 0; i < a.capacity; i++ ) {
            if ( a.arr[i].first != b.arr[i].first ||  a.arr[i].second != b.arr[i].second ) {
                return false;
            }
        }
        return true;
    }

    friend bool operator!=(const Flat_map <Tkey, Tdata> & a, const Flat_map<Tkey,  Tdata>& b) {
        return !(a == b);
    }


private:
    std::pair <Tkey, Tdata> *arr = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    size_t bin_search( const Tkey ) const;

    void increase_the_size();
};

template <typename TKey, typename Tdata>
Flat_map <TKey, Tdata>:: Flat_map( size_t initial_size ): size( initial_size ) {
    arr = new std::pair<TKey, Tdata> [initial_size];
}

template <typename TKey, typename Tdata>
Flat_map<TKey, Tdata>::  Flat_map( const Flat_map& obj ): size( obj.size ), capacity(obj.capacity) {
    arr = new std::pair<TKey, Tdata> [size];
    std::copy(obj.arr, (obj.arr + obj.capacity ), this->arr);
}

template <typename TKey, typename Tdata>
Flat_map<TKey, Tdata>:: ~Flat_map( ) {
    delete [] arr;
}

template <typename TKey, typename Tdata>
size_t Flat_map<TKey, Tdata>:: bin_search( const TKey key ) const {
        if ( capacity > 0 && key == arr[0].first) {
            return 0;
        }
        size_t low = 0;
        size_t middle = 0;
        size_t high = capacity - 1;
        while (high > 0 && low < capacity) {
            middle = ( low + high ) >> 1;
            if ((key > arr[middle].first && key < arr[middle + 1].first)) {
                return middle + 1;
            } else if (arr[middle].first == key) {
                return middle;
            } else if (key < arr[middle].first) {
                high = middle - 1;
            } else {
                low = middle + 1;
            }
        }
    return size_t(-1);
}

template <typename TKey, typename Tdata>
void Flat_map <TKey, Tdata>:: increase_the_size() {
    size *= 2;
    std::pair <TKey, Tdata> *new_arr = new std::pair<TKey, Tdata> [size];
    std::copy(arr, (arr + capacity ), new_arr);
    delete [] arr;
    this -> arr = new_arr;
};

template <typename TKey, typename Tdata>
bool Flat_map <TKey, Tdata>:: insert( const TKey& key, const Tdata& value) {
    if ( 0 == size ) {
        return false;
    }
    if ( size == capacity ) {
        increase_the_size();
    }
    std::pair <TKey, Tdata> data( key,value );
    if ( 0 == capacity || key > arr[capacity - 1].first  ) {
        arr[capacity++]= data;
    }
    else {

        size_t index = 0;
        if ( key > arr[0].first ) {
            index = bin_search( key );
        }
        if( key != arr[index].first ) {
            std::copy_backward( arr + index, arr + capacity, arr + capacity + 1);
            capacity++;
        }
        arr[index] = data;
    }
    return true;
}

template <typename TKey, typename Tdata>
bool Flat_map<TKey, Tdata>:: erase( const TKey& key ) {
    size_t index = bin_search( key );
    if ( -1 != index && key == arr[index].first ) {
        std::copy(arr + index + 1, arr + capacity, arr + index);
        capacity--;
        return true;
    }
    return false;
}

template <typename TKey, typename Tdata>
void Flat_map<TKey, Tdata>:: clear() {
    std::fill(arr, (arr + capacity), std::pair <TKey, Tdata>() );
    capacity = 0;
}

template <typename TKey, typename Tdata>
bool Flat_map<TKey, Tdata>:: empty() const {
    return 0 == capacity;
}

template <typename TKey, typename Tdata>
void Flat_map<TKey, Tdata>:: print( ) {
    std::cout<<"capacity = "<<capacity<<" size = "<<size<<std::endl;
    for( int i = 0; i < capacity; i++) {
        std::cout<<"i = "<<i<<" key = "<<arr[i].first<<std::endl;
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
    size_t index = bin_search( key );
    if ( size_t(-1) != index && key == arr[index].first ) {
        return true;
    }
    return false;
}

template <typename TKey, typename Tdata>
Tdata& Flat_map<TKey, Tdata>:: at( const TKey& key ) {
    size_t index = bin_search( key );
    if ( -1 != index && key == arr[index].first ) {
        return arr[index].second;
    }
    throw std::runtime_error("bad key!!!!!!1111111oneoneoneoneone");
}

template <typename TKey, typename Tdata>
const Tdata& Flat_map<TKey, Tdata>:: at( const TKey& key) const {
    size_t index = bin_search( key );
    if ( -1 != index && key == arr[index].first ) {
        return arr[index].second;
    }
    throw std::runtime_error("bad key!!!!!!1111111oneoneoneoneone");
}

template <typename TKey, typename Tdata>
Tdata& Flat_map<TKey, Tdata>:: operator[]( const TKey& key ) {
    size_t index = bin_search( key );
    if ( size_t(-1) == index ||  !(key == arr[index].first ) ) {
        insert( key, Tdata());
        if ( size_t(-1) == index ){
            index = bin_search( key );
        }
    }
    return arr[index].second;
}

template <typename TKey, typename Tdata>
Flat_map<TKey, Tdata>& Flat_map<TKey, Tdata>:: operator=( const Flat_map& obj ) {
    if (this != &obj) {
        delete[] arr;
        this->capacity = obj.capacity;
        this->size = obj.size;
        this->arr = new std::pair<TKey, Tdata>[this -> size];
        std::copy(obj.arr, (obj.arr + obj.capacity ), this -> arr);
    }
    return *this;
}

#endif //LAB1_FLAT_MAP_H
