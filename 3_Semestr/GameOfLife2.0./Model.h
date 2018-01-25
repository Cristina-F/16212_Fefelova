#ifndef MODEL_H
#define MODEL_H

#include <memory>

#include "Field.h"
#include "History.h"
#include "FormatRLE.h"


class Model {
public:
    Model();

    ~Model();

    bool isGameEnd();

    void game();

    Field * getField();

    void clearField();

    int getWidth();
    int getHeight();

    bool getStatus( int x, int y);

    void setWidth(int width);
    void setHeight(int height);

    void addCell( int x, int y, bool status);

    bool load( std::string & fileName );

    bool save( std::string & fileName );


    void addFieldInHistory();

    void clearHistory();

    void fastGame( int generation );

    void rule(Field * field, Field * newField, int liveNeighbors, int x, int y);

    void setLifeRule( int i, bool status );
    void setDeadRule( int i, bool status );

    std::vector <bool> getLifeRule();
    std::vector <bool> getDeadRule();
private:
    Field field_;
    History history_;
    int generation_ = 0;

    std:: vector <bool> life_rule ;
    std:: vector <bool> dead_rule;

    std::unique_ptr<FormatRLE> rle_;

    const bool LIFE_CELL = 1;
    const bool DEAD_CELL = 0;
    const int SIZE_RULE = 9;

    bool isEmptyField();
    bool isPreviousField();
    bool isRepeatField();
    int countCoordinat( int x, int size);
    int countLiveNeighbors( int x, int y);
};

#endif // MODEL_H
