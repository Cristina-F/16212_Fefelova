#ifndef FORMATRLE_H
#define FORMATRLE_H

#include <string>
#include <vector>

class Field;

class FormatRLE
{
public:
    FormatRLE( Field * field);

    ~FormatRLE();

    bool load( std::string & fileName, std:: vector <bool> & dead_rule, std:: vector <bool> &life_rule );

    bool save( std::string & fileName, std:: vector <bool> & dead_rule, std:: vector <bool> &life_rule);
private:
    Field * field_;

    const bool LIFE_CELL = 1;
    const bool DEAD_CELL = 0;

    const std:: string RLE_LIFE_CELL = "o";
    const std:: string RLE_DEAD_CELL = "b";
    const std:: string RLE_HEIGHT = "y = ";
    const std:: string RLE_WIDTH = "x = ";
    const std:: string NEW_LINE = "$";
    const std:: string END_FIELD = "!";
    const std:: string RLE_S = "S";
    const std:: string RLE_SLASH = "/";
    const std:: string RLE_B= "B";
    const std:: string RLE_RULE = "rule = ";
    const std:: string RLE_SYMBOL = "ob$!";

    void saveRule(std::ofstream & file, std:: vector <bool> & dead_rule, std:: vector <bool> &life_rule);
    void writeInFile(std::ofstream& file, bool & status, int & count );
    int min( int a, int b );
};

#endif // FORMATRLE_H
