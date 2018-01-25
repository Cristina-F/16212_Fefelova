#ifndef LIFE_GAME_H
#define LIFE_GAME_H

#include "Field.h"
#include "History.h"
#include <iostream>
class Game {
public:
    Game( int width, int height);

    ~Game();

    bool isGameEnd();

    void game();

    bool load( std::string & fileName);

    bool save( std::string & fileName);
private:
    Field field_;
    History history_;
    int generation_ = 0;

    const int THREE_NEIGHBORS = 3;
    const int TWO_NEIGHBORS = 2;
    const int LIFE_CELL = 1;
    const int DEAD_CELL = 0;

    const std::string RLE_LIFE_CELL = "o";
    const std::string RLE_DEAD_CELL = "b";
    const std::string RLE_HEIGHT = "y = ";
    const std::string RLE_WIDTH = "x = ";
    const std::string NEW_LINE = "$";
    const std::string END_FIELD = "!";
    const std::string RLE_RULE = "rule = ";
    const std::string COMMA = ", ";
    const std::string RLE_CHARACTERS = "ob$!";

    void writeInFile(std::ofstream& file, bool & status, int & count );
    bool isEmptyField();
    bool isPreviousField();
    bool isRepeatField();
    int countCoordinat( int x, int size);
    int countLiveNeighbors( int x, int y);
};


#endif //LIFE_GAME_H
