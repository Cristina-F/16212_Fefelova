#ifndef FIELD_H
#define FIELD_H

#include <vector>

class Field{
public:

    Field( int width, int height);
    Field();
    ~Field();
    void setWidth( const int width );
    int getWidth() const;
    void setHeight( const int height);
    int getHeight() const;
    void clear();
    void print() const;
    void addCell ( int x, int y, bool status );
    int  getStatus( const  int x, const int y)const ;
    bool empty();
    Field& operator=(const Field& obj);
    friend bool operator==( const Field & a, const Field & b) {
        if ( a.width_ != b.width_ || a.height_ != b.height_ ) {
            return false;
        }
        for ( int i = 0; i < a.width_; i++ ){
            for ( int j = 0; j < a.height_; j++) {
                if ( a.getStatus(i,j) != b.getStatus(i,j) ) {
                    return false;
                }
            }
        }
        return true;
    }
private:
    std::vector <bool> field_;
    int width_ = 0;
    int height_ = 0;

    int min( int a, int b);
};

#endif // FIELD_H
