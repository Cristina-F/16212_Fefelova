#include "Field.h"

#include <iostream>


Field::Field( int width, int height ) : width_(width), height_(height){
    field_.resize( width_ * height, 0 );
}

Field::Field() {}

Field& Field:: operator=( const Field& obj ) {
    if (this != &obj) {
        this->height_ = obj.height_;
        this->width_= obj.width_;
        field_ = obj.field_;
    }
    return *this;
}

void Field:: clear()  {
    for ( int i = 0; i < height_; i++) {
        for ( int j = 0; j < width_; j++){
            field_[ i * width_ + j] = 0;
        }
    }
}

bool Field::empty() {
    return field_.empty();
}

int Field::getStatus( const int x, const int y) const {
    return field_[ y * width_ + x ];
}

void Field::addCell(int x, int y, bool status) {
    if ( x >= 0 && y >= 0 && x < width_ && y < height_ ) {
        field_[ y * width_ + x ] = status;
    }
}

void Field:: print() const {
    for ( int i = 0; i < height_; i++) {
        for ( int j = 0; j < width_; j++){
            std::cout<< field_[i * width_ + j]<<" ";
        }
        std::cout<<std::endl;
    }
}

Field::~Field() {
}

int max ( int a, int b ) {
    if ( a > b ) {
        return a;
    }
    return b;
}
int Field:: min ( int a, int b ) {
    if ( a < b ) {
        return a;
    }
    return b;
}
void Field::setWidth( const int width) {
    std:: vector <bool> newField ( width * height_);
    for(int i = 0; i < height_; i++){
        for(int j = 0; j< min( width, width_); j++){
            newField[i * width + j] = field_[i * width_ + j];
        }
    }
    width_ = width;
    field_ = newField;
}

int Field::getWidth() const {
    return width_;
}

void Field:: setHeight(const int height) {
    std:: vector <bool> newField ( width_ * height);
    for(int i = 0; i < min(height_, height); i++){
        for(int j = 0; j< width_; j++){
            newField[i * width_ + j] = field_[i * width_ + j];
        }
    }
    height_ = height;
    field_ = newField;
}

int Field::getHeight() const{
    return height_;
}

