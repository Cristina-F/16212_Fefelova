#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "Model.h"
#include "Window.h"

class Controller : public QObject
{
    Q_OBJECT
public:
   Controller( Model * model, Window * window);
   Controller(){  }
signals:
    void changedField();
    void changedWidth(int);
    void changedHeight(int);
    void changedGeneration();
    void activatedLife(int, bool);
    void activatedDead(int, bool);
    void activetedLife( std:: vector <bool>);
    void activetedDead( std:: vector <bool>);
private slots:
    void activateLife(int, bool);
    void activateDead(int, bool);
    void changeSizeField();
    void addFieldInHistory();
    void pauseGame();
    void game();
    void clearField();
    void changeWidth(int);
    void changeHeight(int);
    void loadFile(QString& fileName);
    void saveFile(QString& fileName);
    void changeCell(int x, int y, bool status);
    void changeGeneration(int);
    void changeRule();
private:
    Model * model_;
    Window * window_;


};

#endif // CONTROLLER_H
