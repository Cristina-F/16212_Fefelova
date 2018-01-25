#include "Game.h"

#include <iostream>
#include <fstream>
Game::Game( int width, int height): field_(Field(width, height) ) {
   // field_.fillRandom();
    field_.fill1();
    field_.print();
    history_.add(&field_);
}

Game::~Game() {

}

int Game:: countCoordinat( int x, int size) {
    if ( x < 0 ) {
        return (x + size);
    }
    return x % size;
}

int Game::countLiveNeighbors(int x, int y) {
    int countLiveNeighbors = 0;
    int width = field_.getWidth();
    int height = field_.getHeight();
    for ( int i = -1; i <= 1; i++ ){
        for ( int j = -1; j <= 1; j++ ){
            if ( i == 0 && j == 0 ){
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

bool Game::isPreviousField() {
    if ( generation_ > 0 ) {
        if ( field_ == *(history_.getField(generation_ - 1))) {
            return true;
        }
    }
    return false;
}

bool Game::isRepeatField() {
    for ( int i = 0; i < generation_; i++ ) {
        if ( field_ == *(history_.getField(i))){
            std::cout<<"repeat = "<< i + 1<< std::endl;
            return true;
        }
    }
    return false;
}
bool Game::isEmptyField() {
    return field_.empty();
}
bool Game:: isGameEnd() {
    if ( isPreviousField() || isEmptyField() || isRepeatField() ) {
        return true;
    }
    return false;
}
bool Game::save(std::string &fileName) {
    std::ofstream file(fileName);
    if(!file.is_open()){
        throw std::string("File not found!!!");
    }
    int width = field_.getWidth();
    int height = field_.getHeight();
    file << RLE_WIDTH << width << COMMA << RLE_HEIGHT << height << COMMA << RLE_RULE << "B3/S23" << std::endl;
    int countCell = 0;
    bool statusCell = DEAD_CELL;
    int countNewLine = 1;
    bool writeNewLine = false;
    for ( int j = 0; j < height; j++ ) {
        for( int i = 0; i < width; i++ ) {
            if( 0 == countCell){
                statusCell = field_.getStatus(i,j);
                countCell++;
            }
            else if( statusCell == field_.getStatus(i,j) ) {
                countCell++;
            }
            else{
                if ( writeNewLine ) {
                    if ( countNewLine > 1){
                        file << countNewLine;
                    }
                    file << NEW_LINE;
                    countNewLine = 1;
                    writeNewLine = false;
                }
                writeInFile( file, statusCell, countCell);
            }
        }

        if( width == countCell && !statusCell ){
                writeNewLine = false;
                countNewLine++;
                countCell = 0;
        }
        if ( statusCell ) {
            if ( width == countCell ){
                if ( countNewLine > 1){
                    file << countNewLine;
                    file <<  NEW_LINE;
                    countNewLine = 1;
                    writeNewLine = false;
                }
                if ( writeNewLine ){
                    file <<  NEW_LINE;
                    countNewLine = 1;
                }
                writeInFile(file, statusCell, countCell);
                writeNewLine = true;
            }
            else {
                writeInFile(file, statusCell, countCell);
            }
        }
        countCell = 0;
        if( height - 1 != j  ){
            writeNewLine = true;
        }
        else{
            file<<END_FIELD<<"\n";
        }
    }
    return true;
}

void Game::writeInFile( std::ofstream& file, bool & status, int & count) {
    if( count > 1){
        file<<count;
    }
    if( LIFE_CELL == status ) {
        file << RLE_LIFE_CELL;
    }
    else{
        file << RLE_DEAD_CELL;
    }
    status = !status;
    count = 1;
}
bool Game:: load ( std:: string & fileName){
    std::ifstream file(fileName);
    if(!file.is_open()){
        throw std::string("File not found!!!");
    }
    int xPos = 0;
    int yPos = 0;

    int width = 0;
    int height = 0;

    std:: string rule;
    std:: string buf;
    Field field;

    std:: getline( file, buf );
        if (0 == buf.compare(0, RLE_WIDTH.size(), RLE_WIDTH)) {
            int begin = RLE_WIDTH.size();
            int end = buf.find(COMMA);
            width = std::stoi(buf.substr(begin, end));

            begin = buf.find(RLE_HEIGHT, end);
            begin += RLE_HEIGHT.size();
            end = buf.find(COMMA, begin);
            height = std::stoi(buf.substr(begin, end));

            //Создаю поле
            field.setWidth(width);
            field.setHeight(height);
            field.fill();

            begin = buf.find(RLE_RULE, end);
            begin += RLE_RULE.size();
            end = buf.size() - begin;
            rule = buf.substr(begin, end);

            std::cout << buf.substr(begin, end) << std::endl;
        }
        else{
            return  false;
        }
    field.print();
    int countCell = 1;
    while ( std:: getline( file, buf ) ) {
        for(int i = 0; i < buf.size(); i++){
            if ( ( buf.compare(i, 1, "0") > 0) && ( buf.compare( i, 1, "9" ) <= 0)){
                int begin = i;
                int end = buf.find_first_of(RLE_CHARACTERS, i) - begin;
                countCell = std::stoi( buf.substr( begin, end ) );
                i += end - 1;
            }
            else if( 0 == buf.compare(i, 1, RLE_LIFE_CELL ) ){
                for( int j = 0; j < countCell; j++ ) {
                    field.addCell(xPos, yPos, LIFE_CELL);
                    xPos++;
                }
                countCell = 1;
            }
            else if( 0 == buf.compare(i, 1, RLE_DEAD_CELL ) ) {
                for( int j = 0; j < countCell; j++ ) {
                    xPos++;
                }
                countCell = 1;
            }
            else if( 0 == buf.compare(i, 1, NEW_LINE ) ) {
                for(int j = 0; j < countCell; j++){
                    yPos++;
                }
                xPos = 0;
                countCell = 1;
            }
            else if( 0 == buf.compare( i, 1, END_FIELD ) ) {
                break;
            }
            else {
                throw std::string("Incorrect Data in File!!!");
            }
            std::cout<<countCell<<std::endl;
        }
    }
    field_ = field;
    return true;
}
void Game::game() {
    /*std::string f = "l1.rle";
    load(f);
    std::string l = "life.rle";
    save(l)*/;
    field_.print();
     while (!isGameEnd()) {
        int width = field_.getWidth();
        int height = field_.getHeight();
        Field newField(width, height);
        newField = field_;
//         field_.print();
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                int liveNeighbors = countLiveNeighbors(i, j);
               // std::cout<< "neigh = "<< liveNeighbors<< " x = " << i << " j = "<< j<<std::endl;
                if (!field_.getStatus(i, j) && THREE_NEIGHBORS == liveNeighbors) {
                    newField.addCell(i, j, LIFE_CELL);
                } else if (field_.getStatus(i, j)) {
                    if (liveNeighbors > THREE_NEIGHBORS || liveNeighbors < TWO_NEIGHBORS) {
                        newField.addCell(i, j, DEAD_CELL);
                    }
                }
            }
        }
        field_ = newField;
        history_.add(&field_);
        std::cout << std::endl;
        std::cout << std::endl;
        generation_++;std::cout<<" generation = "<< generation_<<std::endl;
    }
    history_.print();
}