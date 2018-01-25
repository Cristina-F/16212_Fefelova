#include "Window.h"

#include <iostream>

#include <QGridLayout>
#include <QString>
#include <QTimer>
#include <QIntValidator>


const int SIZE_RULE = 9;

Window::Window( Model * model, QWidget * parent) : QWidget(parent), timer(new QTimer(this) ),
    lifeCheckBox( std::vector<QCheckBox*>(SIZE_RULE)), deadCheckBox( std::vector<QCheckBox*>(SIZE_RULE))
{
    timer -> setInterval( SPEED_MAX_VALUE / 2 );

    renderArea = new RenderArea( model );

//Кнопки
    playButton = new QPushButton( "Play", this);
    pauseButton =  new QPushButton( "Payse", this);
    endButton =  new QPushButton( "End", this);

//Файлы для загрузки и сохранения
    loadFileLineEdit = new QLineEdit;
    loadFileLable = new QLabel(tr("Load:")) ;
    loadFileLable -> setBuddy(loadFileLineEdit);

    saveFileLineEdit = new QLineEdit;
    saveFileLable = new QLabel(tr("Save:"));
    saveFileLable -> setBuddy(saveFileLineEdit);

//Размеры поля
    validator = new QIntValidator( SIZE_MIN_FIELD , SIZE_MAX_FIELD );
    widthFieldLineEdit = new QLineEdit;
    QString width;
    width.setNum( renderArea -> getWidthField() );
    widthFieldLineEdit -> setText(width);
    widthFieldLineEdit -> setValidator (validator );
    widthFieldLabel = new QLabel(tr("Width:"));
    widthFieldLabel -> setBuddy(widthFieldLineEdit);

    heightFieldLineEdit = new QLineEdit;
    QString height;
    height.setNum( renderArea -> getHeightField() );
    heightFieldLineEdit -> setText(height);
    heightFieldLineEdit -> setValidator(validator );
    heightFieldLabel = new QLabel(tr("Height:"));
    heightFieldLabel -> setBuddy(heightFieldLineEdit);

//Скорость
    speedSpinBox = new QSpinBox;
    speedLable = new QLabel(tr("Speed:"));
    speedSpinBox  -> setSingleStep(SPEED_STEP);
    speedSpinBox -> setFixedWidth(SPEED_SPIN_BOX_WIDTH);
    speedSpinBox -> setMaximum(SPEED_MAX_VALUE);
    speedSpinBox -> setMinimum(SPEED_MIN_VALUE);
    speedSpinBox -> setValue(SPEED_MAX_VALUE + SPEED_MIN_VALUE - timer -> interval() );
    speedLable ->setBuddy(speedSpinBox);

//Правила

    lifeRule = new QLabel(tr("Life:"));
    deadRule = new QLabel(tr("Dead:"));

    lifeCheckBox[1] = new QCheckBox( tr("1"));
    lifeCheckBox[2] = new QCheckBox( tr("2"));
    lifeCheckBox[3] = new QCheckBox( tr("3"));
    lifeCheckBox[4] = new QCheckBox( tr("4"));
    lifeCheckBox[5] = new QCheckBox( tr("5"));
    lifeCheckBox[6] = new QCheckBox( tr("6"));
    lifeCheckBox[7] = new QCheckBox( tr("7"));
    lifeCheckBox[8] = new QCheckBox( tr("8"));

    deadCheckBox[1]  = new QCheckBox( tr("1"));
    deadCheckBox[2]  = new QCheckBox( tr("2"));
    deadCheckBox[3] = new QCheckBox( tr("3"));
    deadCheckBox[4] = new QCheckBox( tr("4"));
    deadCheckBox[5] = new QCheckBox( tr("5"));
    deadCheckBox[6] = new QCheckBox( tr("6"));
    deadCheckBox[7] = new QCheckBox( tr("7"));
    deadCheckBox[8] = new QCheckBox( tr("8"));

//Поколения
    generationLineEdit = new QLineEdit;
    generationLineEdit -> setText("0");
    generationLineEdit -> setValidator (validator);
    generationLabel = new QLabel(tr("Generation:"));
    generationLabel -> setBuddy(generationLineEdit);

//Расположение
    QGridLayout * mainLayout = new QGridLayout;

    mainLayout->setColumnStretch(0, 1);
    mainLayout->setRowStretch(13, 1);
    int size = 20;
    for ( int i = 0; i < 13; i++ ){
        mainLayout -> setRowMinimumHeight(i, size);
    }

mainLayout -> setRowMinimumHeight(13, 30);
    mainLayout->setColumnMinimumWidth(4, 41);

    mainLayout->addWidget(renderArea, 0, 0, 21, 1);

    mainLayout->addWidget(playButton, 0, 1, Qt::AlignRight);
    mainLayout->addWidget(pauseButton, 0, 2, Qt::AlignLeft);
    mainLayout->addWidget(endButton, 0, 3, Qt::AlignLeft);

    mainLayout->addWidget(loadFileLable, 1, 1, 1,1);
    mainLayout->addWidget(loadFileLineEdit, 1, 2, 1, 2);

    mainLayout->addWidget(saveFileLable, 2, 1, 1, 1);
    mainLayout->addWidget(saveFileLineEdit, 2, 2, 1, 2);

    mainLayout->addWidget(widthFieldLabel, 3, 1, 1, 1);
    mainLayout->addWidget(widthFieldLineEdit, 3, 2, 1, 2);

    mainLayout->addWidget(heightFieldLabel, 4, 1, 1, 1);
    mainLayout->addWidget(heightFieldLineEdit, 4, 2, 1, 2);

    mainLayout->addWidget(speedLable, 5, 1, 1, 1);
    mainLayout->addWidget(speedSpinBox, 5, 2, 1, 2);

    mainLayout->addWidget(generationLabel, 6, 1, 1, 1);
    mainLayout->addWidget(generationLineEdit, 6, 2, 1, 2);

    mainLayout->addWidget(lifeRule, 7, 1, 1, 1);

    mainLayout->addWidget(lifeCheckBox[1], 8, 1, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(lifeCheckBox[2], 8, 1, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(lifeCheckBox[3], 8, 2, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(lifeCheckBox[4], 8, 2, 1, 1, Qt::AlignRight);

    mainLayout->addWidget(lifeCheckBox[5], 9, 1, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(lifeCheckBox[6], 9, 1, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(lifeCheckBox[7], 9, 2, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(lifeCheckBox[8], 9, 2, 1, 1, Qt::AlignRight);

    mainLayout->addWidget(deadRule, 10, 1, 1, 1, Qt::AlignLeft);

    mainLayout->addWidget(deadCheckBox[1], 11, 1, 1, 1,  Qt::AlignLeft);
    mainLayout->addWidget(deadCheckBox[2], 11, 1, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(deadCheckBox[3], 11, 2, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(deadCheckBox[4], 11, 2, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(deadCheckBox[5], 12, 1, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(deadCheckBox[6], 12, 1, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(deadCheckBox[7], 12, 2, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(deadCheckBox[8], 12, 2, 1, 1, Qt::AlignRight);

    setLayout(mainLayout);

    playButton -> setEnabled(true);
    pauseButton -> setEnabled(false);
    endButton -> setEnabled(true);

    deadCheckBox[3] -> setChecked(true);
    lifeCheckBox[2] -> setChecked(true);
    lifeCheckBox[3] -> setChecked(true);

    connect( playButton, SIGNAL( clicked( bool ) ), this, SLOT( pressPlayButton() ) );
    connect( pauseButton, SIGNAL( clicked( bool ) ), this, SLOT( pressPauseButton() ) );
    connect( endButton, SIGNAL( clicked( bool ) ), this, SLOT( pressEndButton() ) );

    connect( loadFileLineEdit, SIGNAL( editingFinished() ), this, SLOT( changeLoadFile() ) );
    connect(saveFileLineEdit, SIGNAL( editingFinished() ), this, SLOT( changeSaveFile() ) );

    connect( widthFieldLineEdit, SIGNAL( editingFinished() ), this, SLOT( changeWidthFieldLineEdit() ) );
    connect( heightFieldLineEdit, SIGNAL( editingFinished() ), this, SLOT( changeHeightFieldLineEdit() ) );

    connect(generationLineEdit, SIGNAL( editingFinished() ), this, SLOT( changeGeneration() ) );

    connect( speedSpinBox, SIGNAL( valueChanged( int ) ), this, SLOT( changeSpeed( int ) ) );

    connect(lifeCheckBox[1], SIGNAL( stateChanged ( int ) ), this, SLOT( changeLifeRule1() ) );
    connect(lifeCheckBox[2], SIGNAL( stateChanged ( int ) ), this, SLOT( changeLifeRule2() ) );
    connect(lifeCheckBox[3], SIGNAL( stateChanged ( int ) ), this, SLOT( changeLifeRule3() ) );
    connect(lifeCheckBox[4], SIGNAL( stateChanged ( int ) ), this, SLOT( changeLifeRule4() ) );
    connect(lifeCheckBox[5], SIGNAL( stateChanged ( int ) ), this, SLOT( changeLifeRule5() ) );
    connect(lifeCheckBox[6], SIGNAL( stateChanged ( int ) ), this, SLOT( changeLifeRule6() ) );
    connect(lifeCheckBox[7], SIGNAL( stateChanged ( int ) ), this, SLOT( changeLifeRule7() ) );
    connect(lifeCheckBox[8], SIGNAL( stateChanged ( int ) ), this, SLOT( changeLifeRule8() ) );

    connect(deadCheckBox[1], SIGNAL( stateChanged ( int ) ), this, SLOT( changeDeadRule1() ) );
    connect(deadCheckBox[2], SIGNAL( stateChanged ( int ) ), this, SLOT( changeDeadRule2() ) );
    connect(deadCheckBox[3], SIGNAL( stateChanged ( int ) ), this, SLOT( changeDeadRule3() ) );
    connect(deadCheckBox[4], SIGNAL( stateChanged ( int ) ), this, SLOT( changeDeadRule4() ) );
    connect(deadCheckBox[5], SIGNAL( stateChanged ( int ) ), this, SLOT( changeDeadRule5() ) );
    connect(deadCheckBox[6], SIGNAL( stateChanged ( int ) ), this, SLOT( changeDeadRule6() ) );
    connect(deadCheckBox[7], SIGNAL( stateChanged ( int ) ), this, SLOT( changeDeadRule7() ) );
    connect(deadCheckBox[8], SIGNAL( stateChanged ( int ) ), this, SLOT( changeDeadRule8() ) );

    setWindowTitle(tr("Game of Life"));
}

void Window:: pressPlayButton(){

    playButton -> setEnabled(false);
    pauseButton -> setEnabled(true);
    endButton -> setEnabled(true);

    loadFileLineEdit -> setEnabled(false);
    saveFileLineEdit -> setEnabled(false);

    widthFieldLineEdit -> setEnabled(false);
    heightFieldLineEdit -> setEnabled(false);
    generationLineEdit -> setEnabled(false);

    emit addFieldInHistory();
    timer -> start();
}

void Window:: pressPauseButton() {
    timer -> stop();

    playButton -> setEnabled(true);
    pauseButton -> setEnabled(false);
    endButton -> setEnabled(true);

    loadFileLineEdit -> setEnabled(false);
    saveFileLineEdit -> setEnabled(true);
    generationLineEdit -> setEnabled(true);

    widthFieldLineEdit -> setEnabled(true);
    heightFieldLineEdit-> setEnabled(true);
}

void Window:: pressEndButton() {
    pressPauseButton();

    playButton -> setEnabled(true);
    pauseButton -> setEnabled(false);

    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    loadFileLineEdit -> setText("");
    saveFileLineEdit -> setText("");
    generationLineEdit -> setText("0");
    generationLineEdit -> setEnabled(true);

    emit clearField();
}

void Window:: changeLoadFile() {
    QString loadFileName = loadFileLineEdit -> text();
    loadFileLineEdit -> setText("");
    generationLineEdit -> setText("0");
    emit loadFile(loadFileName);
}

void Window:: changeSaveFile() {
    QString saveFileName = saveFileLineEdit -> text();
    saveFileLineEdit -> setText("");
    emit saveFile(saveFileName);
}

void Window::changeSpeed( int speed ) {
    timer -> setInterval( SPEED_MAX_VALUE - speed + SPEED_MIN_VALUE );
}

void Window:: changeWidthFieldLineEdit() {
    QString newWidth = widthFieldLineEdit -> text();
    int width = newWidth.toInt();
    changeWidth( width );
    emit changedWidth(width);
}

void Window::changeWidth( int width ) {
    QString w;
    w.setNum(width);
    widthFieldLineEdit -> setText(w);
    renderArea -> setWidthField(width);
    renderArea -> startPosition();
}

void Window:: changeHeightFieldLineEdit() {
    QString newHeight = heightFieldLineEdit -> text();
    int height = newHeight.toInt();
    changeHeight( height );
    emit changedHeight(height);
}

void Window::changeHeight( int height ) {
    QString h;
    h.setNum(height);
    heightFieldLineEdit -> setText(h);
    renderArea -> setHeightField(height);
    renderArea -> startPosition();
}

void Window:: changeGeneration() {
    QString newGeneration = generationLineEdit -> text();
    int generation = newGeneration.toInt();
    emit addFieldInHistory();
    emit changedGeneration(generation);

}

void Window:: changeLifeRule( int  i){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedLife(i,lifeCheckBox[i] -> isChecked());
}

void Window:: changeDeadRule( int i ){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedDead(i,deadCheckBox[i] -> isChecked());
}
void Window:: changeLifeRule1(){
    changeLifeRule(1);
}

void Window:: changeLifeRule2(){
    changeLifeRule(2);
}

void Window:: changeLifeRule3(){
    changeLifeRule(3);
}

void Window:: changeLifeRule4(){
    changeLifeRule(4);
}

void Window:: changeLifeRule5(){
    changeLifeRule(5);
}

void Window:: changeLifeRule6(){
    changeLifeRule(6);
}

void Window:: changeLifeRule7(){
    changeLifeRule(7);
}

void Window:: changeLifeRule8(){
    changeLifeRule(8);
}

void Window:: changeDeadRule1(){
    changeDeadRule(1);
}
void Window:: changeDeadRule2(){
    changeDeadRule(2);
}
void Window:: changeDeadRule3(){
    changeDeadRule(3);
}

void Window:: changeDeadRule4(){
    changeDeadRule(4);
}

void Window:: changeDeadRule5(){
    changeDeadRule(5);
}

void Window:: changeDeadRule6(){
    changeDeadRule(6);
}

void Window:: changeDeadRule7(){
    changeDeadRule(7);
}

void Window:: changeDeadRule8(){
    changeDeadRule(8);
}


Window::~Window()
{
    delete timer;

    delete renderArea;

    delete widthFieldLabel;
    delete heightFieldLabel;
    delete loadFileLable;
    delete saveFileLable;
    delete speedLable;
    delete generationLabel;

    delete widthFieldLineEdit;
    delete heightFieldLineEdit;
    delete loadFileLineEdit;
    delete saveFileLineEdit;
    delete generationLineEdit;

    delete playButton;
    delete pauseButton;
    delete endButton;

    delete speedSpinBox;

    delete validator;
}


RenderArea * Window:: getRenderArea(){
    return renderArea;
}

void Window:: addGeneration(){
    QString newGeneration = generationLineEdit -> text();
    int generation = newGeneration.toInt() + 1;
    newGeneration.setNum( generation );
    generationLineEdit -> setText(newGeneration);

}


void Window:: activeLife(std::vector <bool> life){
    for ( int i = 1; i < SIZE_RULE; i ++ ){
        lifeCheckBox[i] -> setChecked(life[i]);
    }
}

void Window:: activeDead(std::vector <bool> dead){
    for ( int i = 1; i < SIZE_RULE; i ++ ){
        deadCheckBox[i] -> setChecked(dead[i]);
    }
}
