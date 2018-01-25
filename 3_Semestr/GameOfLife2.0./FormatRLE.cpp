#include <fstream>
#include <sstream>

#include "FormatRLE.h"
#include "Field.h"

FormatRLE::FormatRLE(Field * field ): field_(field)
{

}

FormatRLE:: ~FormatRLE() {
}


bool FormatRLE:: save( std::string & fileName, std:: vector <bool> & dead_rule, std:: vector <bool> &life_rule ) {
    std::ofstream file(fileName);
    if(!file.is_open()){
        return false;
    }
    int width = field_ -> getWidth();
    int height = field_ -> getHeight();
    file << RLE_WIDTH << width << "," << RLE_HEIGHT << height << ",";
    saveRule( file, dead_rule, life_rule);
    int countCell = 0;
    bool statusCell = DEAD_CELL;
    int countNewLine = 1;
    bool writeNewLine = false;
    for ( int j = 0; j < height; j++ ) {
        for( int i = 0; i < width; i++ ) {
            if( 0 == countCell){
                statusCell = field_ -> getStatus(i,j);
                countCell++;
            }
            else if( statusCell == field_ -> getStatus(i,j) ) {
                countCell++;
            }
            else{
                if ( writeNewLine ) {
                    if ( countNewLine > 1){
                        countNewLine--;
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
                    countNewLine--;
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

void FormatRLE::writeInFile( std::ofstream& file, bool & status, int & count) {
    if( count > 1){
        file << count;
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

bool FormatRLE:: load ( std:: string & fileName,  std:: vector <bool> & dead_rule, std:: vector <bool> & life_rule){
    std::ifstream file(fileName);
    if(!file.is_open()){
        return false;
    }
    else {
        for ( int i = 0; i < 9; i++){
            life_rule[i] = 0;
            dead_rule[i] = 0;
        }
        std:: string buf;

        Field field( field_ -> getWidth(), field_ -> getHeight());

        if ( std:: getline( file, buf ) && !( buf.compare(0, RLE_WIDTH.size(), RLE_WIDTH) ) ) {
            int width = 0;
            int height = 0;

            int begin = RLE_WIDTH.size();
            int end = buf.find(",");
            std::istringstream ( buf.substr(begin, end) ) >> width;

            begin = buf.find(RLE_HEIGHT, end) +  RLE_HEIGHT.size();
            end = buf.find(",", begin);
            std::istringstream ( buf.substr(begin, end) ) >> height;

            begin = buf.find(RLE_RULE, end) + RLE_RULE.size() + 1;

            end = buf.find(RLE_SLASH, end);
            int rule_ = 0;
            std::istringstream ( buf.substr(begin, end - begin) ) >> rule_;
            for ( int i = 0; rule_ > 0 ; i++) {
                int idx = rule_ % 10 ;
                rule_ = rule_ / 10;
                dead_rule[idx] = true;
            }
            begin = buf.find(RLE_S, end) + 1;
            end = buf.size() - begin;

            std::istringstream ( buf.substr(begin, end - begin) ) >> rule_;
            for ( int i = 0; rule_ > 0 ;i++ ) {
                int idx = rule_ % 10;
                rule_ = rule_ / 10;
               life_rule[idx] = true;
            }
            field.setWidth(width);
            field.setHeight(height);
        }
        else{
            return  false;
        }
        int xPos = 0;
        int yPos = 0;
        int countCell = 1;
        while ( std:: getline( file, buf ) ) {
            for( int i = 0; i < int( buf.size() ); i++ ) {
                if ( ( buf.compare(i, 1, "0") > 0) && ( buf.compare( i, 1, "9" ) <= 0)){
                    int begin = i;            
                    int end = buf.find_first_of(RLE_SYMBOL, i) - begin;
                    std::istringstream ( buf.substr(begin, end) ) >> countCell;
                    i += end - 1;
                }
                else if( 0 == buf.compare( i, 1, RLE_LIFE_CELL ) ) {
                    for( int j = 0; j < countCell; j++ ) {
                        field.addCell( xPos, yPos, LIFE_CELL );
                        xPos++;
                    }
                    countCell = 1;
                }
                else if( 0 == buf.compare(i, 1, RLE_DEAD_CELL ) ) {
                    xPos += countCell;
                    countCell = 1;
                }
                else if( 0 == buf.compare(i, 1, NEW_LINE ) ) {
                    yPos += countCell;
                    xPos = 0;
                    countCell = 1;
                }
                else if( 0 == buf.compare( i, 1, END_FIELD ) ) {
                    break;
                }
                else {
                    return false;
                }
            }
        }
        (*field_)= field;
    }
    return true;
}

void FormatRLE:: saveRule(std::ofstream &file, std::vector<bool> &dead_rule, std::vector<bool> &life_rule){
    file << RLE_RULE<< RLE_B;
    for ( int i = 1; i < 9; i++ ){
        if ( dead_rule[i]) {
            file<<i;
        }
    }
    file << RLE_SLASH << RLE_S;
    for ( int i = 1; i < 9; i++ ){
        if ( life_rule[i]) {
            file<<i;
        }
    }
    file << std::endl;
}

int FormatRLE:: min(int a, int b) {
    if ( a < b && a > 0) {
        return a;
    }
    return b;
}
