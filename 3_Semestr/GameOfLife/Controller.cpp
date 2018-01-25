#include "Controller.h"
#include <QTimer>
#include <string>

Controller:: Controller( Model * model, Window * window): model_(model), window_(window) {
    RenderArea * renderArea =  window_ -> getRenderArea();
    connect( window_ -> getTimer(), SIGNAL( timeout() ), this, SLOT( game() ) );
    connect( this, SIGNAL(changedGeneration() ), window_, SLOT( addGeneration() ) );
    connect( renderArea, SIGNAL( pauseGame() ), this, SLOT( pauseGame() ) );
    connect( this, SIGNAL( changedField() ), renderArea, SLOT( repaint() ) );
    connect( window_, SIGNAL( clearField() ), this, SLOT( clearField() ) );
    connect( window_, SIGNAL( changedWidth( int ) ), this, SLOT( changeWidth( int ) ) );
    connect( window_, SIGNAL( changedHeight( int ) ), this, SLOT( changeHeight( int ) ) );
    connect( window_, SIGNAL( loadFile( QString & ) ), this, SLOT( loadFile( QString & ) ) );
    connect( window_, SIGNAL( saveFile( QString & ) ), this, SLOT( saveFile( QString & ) ) );
    connect( this, SIGNAL(changedWidth( int ) ), window_, SLOT( changeWidth( int ) ) );
    connect( this, SIGNAL( changedHeight( int ) ), window_, SLOT( changeHeight( int ) ) );
    connect( renderArea, SIGNAL( changedCell( int, int, bool ) ), this, SLOT( changeCell( int, int, bool ) ) );
    connect( window_, SIGNAL( addFieldInHistory() ), this, SLOT( addFieldInHistory( ) ));
    connect( window_, SIGNAL( changedGeneration(int) ), this, SLOT( changeGeneration(int) ));
    connect( window_, SIGNAL( loadFile( QString & ) ), this, SLOT( changeRule() ) );
    connect( window_, SIGNAL( changedGeneration(int) ), this, SLOT( changeSizeField() ));

    connect(window_, SIGNAL(activatedLife(int, bool)), this, SLOT(activateLife(int, bool)));
    connect(window_, SIGNAL(activatedDead(int, bool)), this, SLOT(activateDead(int, bool)));
    connect(this, SIGNAL(activetedDead(std::vector<bool>)), window_, SLOT(activeDead(std::vector<bool>)));
    connect(this, SIGNAL(activetedLife(std::vector<bool>)), window_, SLOT(activeLife(std::vector<bool>)));


}

void Controller:: activateLife( int x, bool status ){
    model_ -> setLifeRule( x, status);
}
void Controller:: activateDead( int x, bool status ){
    model_ -> setDeadRule( x, status);
}

void Controller:: changeRule (){
    std::vector <bool> lifeRule = model_ -> getLifeRule();
    emit activetedLife(lifeRule);
    std::vector <bool> deadRule = model_ -> getDeadRule();
    emit activetedDead(deadRule);
}

void Controller:: changeSizeField(){
    emit changedWidth(model_ -> getWidth());
    emit changedHeight(model_ -> getHeight());
}

void Controller:: game() {
    model_ -> game();
    emit changedGeneration();
    emit changedField();
}

void Controller:: changeGeneration( int generation ) {
    model_ -> fastGame( generation );
    emit changedField();
}

void Controller::addFieldInHistory(){
    model_ -> addFieldInHistory();
}

void Controller:: pauseGame(){
    window_ -> pressPauseButton();
}

void Controller:: clearField(){
    model_ -> clearField();
    emit changedField();
}

void Controller:: changeWidth( int width ) {
    model_ -> setWidth( width );
}

void Controller:: changeHeight(int height ) {
    model_ -> setHeight(height);
}

void Controller:: loadFile( QString & fileName ) {
    std::string loadFileName = fileName.toStdString();
    model_ -> load(loadFileName);
    emit changedWidth(model_ -> getWidth());
    emit changedHeight(model_ -> getHeight());
    emit changedField();
}

void Controller:: saveFile( QString & fileName ) {
    std::string saveFileName = fileName.toStdString();
    model_ -> save(saveFileName);
}

void Controller:: changeCell( int x, int y, bool status ) {
    model_ -> addCell( x, y, status );
    emit changedField();
}



