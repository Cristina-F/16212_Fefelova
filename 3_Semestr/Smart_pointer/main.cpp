#include <iostream>

template <typename Tdata> class Smart_Pointer {
public:
    Smart_Pointer() {
        cnt = new int;
        *cnt = 1;
        a_ = nullptr;
    }//конструктор по умолчанию

    Smart_Pointer( Tdata a): a_(a) {
        cnt = new int;
        *cnt = 1;
    }// конструктор с захватом ресурса

    Smart_Pointer( const Smart_Pointer & ptr ): a_(ptr.a_){
        (*cnt)++;
    }//конструктор копирования

    ~Smart_Pointer() {
        if ( 1 ==  *cnt ) {
            delete a_;
        }
        else {
            (*cnt)--;
        }
    }
/*    Smart_Pointer( Smart_Pointer && ptr): a_(ptr.a_){
        *(ptr.cnt)--;
    }//конструктор перемещения(опционально)*/

    Smart_Pointer& operator=( Smart_Pointer & ptr ){
        if ( this != &ptr ) {
            delete a_;
            if ( nullptr != ptr.a_ ) {
                this -> a_ = new Tdata;
            }
            this -> a_ = ptr.a_;
            (*( this -> cnt ))++;
        }
        return *this;
    }//операция присваивания

   /* Smart_Pointer& operator=( Smart_Pointer && ptr){
       // ~Smart_Pointer();
        a_= ptr.a_;
        if ( 1 == *( ptr.cnt) ) {
            ptr.a_ = nullptr;
        }
       // *(ptr.cnt )--;
    }*///операция перемещения опционально

    Tdata* get(){
        return a_;
    }//вернуть указатель

    Tdata* reset( Tdata* other ) {
        if ( 1 == (*cnt) ) {
            delete a_;
        }
        if ( nullptr != other ){
            a_ = new Tdata;
        }
        a_ = other;
        (*cnt)--;
        return  a_;
    }//освободить старый, записать новый

    Tdata* release(){
        (*cnt)--;
        a_ = nullptr;
        return a_;
    }//отдать владения

    Tdata* operator->() {
        return a_;
    }

    Tdata& operator* () {
        return *(a_);
    }

    operator bool() {
        if (nullptr ==  a_ ) {
            return false;
        }
        return true;
    }

private:
    Tdata* a_ = nullptr;
    int* cnt = 0;
};

int main() {
    Smart_Pointer<int> ptr;
    return 0;
}