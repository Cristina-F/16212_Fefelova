#include "Model.h"

#include <stdexcept>

const int STANDART_WIDTH = 62;
const int STANDART_HEIGHT = 48;

Model::Model(): field_( Field( STANDART_WIDTH, STANDART_HEIGHT ) ), life_rule( std:: vector <bool> (9)), dead_rule( std:: vector <bool> (9))
{
    rle_.reset(new FormatRLE (&field_));
    dead_rule[3] = 1;
    life_rule[2] = 1;
    life_rule[3] = 1;
    history_.add(&field_);

}


Model::~Model() {

}
Field * Model:: getField(){
    return &field_;
}

void Model:: rule(Field * field, Field * newField, int liveNeighbors, int x, int y) {
    if ( !field -> getStatus( x, y )) {
        for ( int i = 1; i < SIZE_RULE; i++ ){
            if ( dead_rule[i] &&  liveNeighbors == i  ) {
                newField -> addCell( x, y, LIFE_CELL );
                break;
            }
        }
    }
    else if ( field -> getStatus( x, y ) ) {
        for ( int i = 1; i < SIZE_RULE; i++ ){
            if ( life_rule[i] &&  liveNeighbors == i  ) {
                newField -> addCell( x, y, LIFE_CELL );
                break;
            }
            if ( i == SIZE_RULE - 1){
                newField -> addCell( x, y, DEAD_CELL );
            }
        }
    }
}

bool Model:: getStatus( int x, int y){
    return field_.getStatus(x,y);
}

void Model::clearField(){
    field_.clear();
    clearHistory();
}
int Model:: getWidth(){
    return field_.getWidth();
}

int Model:: getHeight(){
    return field_.getHeight();
}

void Model:: setWidth(int width){
    field_.setWidth(width);
}
void Model:: setHeight(int height){
    field_.setHeight(height);
}

void Model:: addCell(int x, int y, bool status){
    field_.addCell(x,y, status);
}

bool Model::load ( std::string & fileName ){
   return rle_ -> load(fileName, dead_rule, life_rule) ;
}

bool Model::save ( std::string & fileName ){
    return rle_ -> save(fileName, dead_rule, life_rule);
}

int Model:: countCoordinat( int x, int size) {
    if ( x < 0 ) {
        return (x + size);
    }
    return x % size;
}

void Model:: clearHistory(){
    history_.clear();
    generation_ = 0;
}

int Model::countLiveNeighbors(int x, int y) {
    int countLiveNeighbors = 0;
    int width = field_.getWidth();
    int height = field_.getHeight();
    for ( int i = -1; i <= 1; i++ ){
        for ( int j = -1; j <= 1; j++ ){
            if ( 0 == i  && 0 == j ){
                continue;
            }
            int x1 = countCoordinat( x + i, width);
            int y1 = countCoordinat( y + j, height );
            if ( LIFE_CELL == field_.getStatus(x1, y1)){
                countLiveNeighbors++;
            }
        }
    }
    return countLiveNeighbors;
}

bool Model::isPreviousField() {
    if ( generation_ > 0 ) {
        if ( field_ == *(history_.getField(generation_ - 1))) {
            return true;
        }
    }
    return false;
}

bool Model::isRepeatField() {
    for ( int i = 0; i < generation_; i++ ) {
        if ( field_ == *(history_.getField(i))){
            return true;
        }
    }
    return false;
}

bool Model::isEmptyField() {
    return field_.empty();
}

bool Model:: isGameEnd() {
    if ( isPreviousField() || isEmptyField() || isRepeatField() ) {
        return true;
    }
    return false;
}

void Model::game() {
        int width = field_.getWidth();
        int height = field_.getHeight();
        Field newField(width, height);
        newField = field_;
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                int liveNeighbors = countLiveNeighbors(i, j);

                rule(&field_, &newField, liveNeighbors, i, j );
            }
        }
        field_ = newField;
        history_.add(&field_);
        generation_++;

}

void Model:: fastGame(int generation) {
    if ( generation > generation_) {
        for ( int i = generation_; i < generation; i++ ) {
            game();
        }
    }
    else {
        field_ = *( history_.getField( generation ) );
    }
}

void Model:: addFieldInHistory(){
    if ( !isPreviousField()){
        history_.add(&field_);
    }
}

void Model:: setLifeRule(int i, bool status) {
    life_rule[i] = status;
}

void Model:: setDeadRule(int i, bool status) {
    dead_rule[i] = status;
}

std::vector <bool> Model:: getLifeRule(){
    return life_rule;
}

std::vector <bool> Model:: getDeadRule(){
    return dead_rule;
}
