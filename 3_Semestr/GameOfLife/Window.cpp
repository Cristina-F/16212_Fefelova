#include "Window.h"

#include <iostream>

#include <QGridLayout>
#include <QString>
#include <QTimer>
#include <QIntValidator>


Window::Window( Model * model, QWidget * parent) : QWidget(parent), timer(new QTimer(this) )
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

    life_1CheckBox = new QCheckBox( tr("1"));
    life_2CheckBox = new QCheckBox( tr("2"));
    life_3CheckBox = new QCheckBox( tr("3"));
    life_4CheckBox = new QCheckBox( tr("4"));
    life_5CheckBox = new QCheckBox( tr("5"));
    life_6CheckBox = new QCheckBox( tr("6"));
    life_7CheckBox = new QCheckBox( tr("7"));
    life_8CheckBox = new QCheckBox( tr("8"));

    dead_1CheckBox  = new QCheckBox( tr("1"));
    dead_2CheckBox  = new QCheckBox( tr("2"));
    dead_3CheckBox = new QCheckBox( tr("3"));
    dead_4CheckBox = new QCheckBox( tr("4"));
    dead_5CheckBox = new QCheckBox( tr("5"));
    dead_6CheckBox = new QCheckBox( tr("6"));
    dead_7CheckBox = new QCheckBox( tr("7"));
    dead_8CheckBox = new QCheckBox( tr("8"));


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
    mainLayout->addWidget(life_1CheckBox, 8, 1, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(life_2CheckBox, 8, 1, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(life_3CheckBox, 8, 2, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(life_4CheckBox, 8, 2, 1, 1, Qt::AlignRight);

    mainLayout->addWidget(life_5CheckBox, 9, 1, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(life_6CheckBox, 9, 1, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(life_7CheckBox, 9, 2, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(life_8CheckBox, 9, 2, 1, 1, Qt::AlignRight);

    mainLayout->addWidget(deadRule, 10, 1, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(dead_1CheckBox, 11, 1, 1, 1,  Qt::AlignLeft);
    mainLayout->addWidget(dead_2CheckBox, 11, 1, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(dead_3CheckBox, 11, 2, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(dead_4CheckBox, 11, 2, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(dead_5CheckBox, 12, 1, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(dead_6CheckBox, 12, 1, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(dead_7CheckBox, 12, 2, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(dead_8CheckBox, 12, 2, 1, 1, Qt::AlignRight);

    setLayout(mainLayout);

    playButton -> setEnabled(true);
    pauseButton -> setEnabled(false);
    endButton -> setEnabled(true);

    dead_3CheckBox -> setChecked(true);
    life_2CheckBox -> setChecked(true);
    life_3CheckBox -> setChecked(true);

    connect( playButton, SIGNAL( clicked( bool ) ), this, SLOT( pressPlayButton() ) );
    connect( pauseButton, SIGNAL( clicked( bool ) ), this, SLOT( pressPauseButton() ) );
    connect( endButton, SIGNAL( clicked( bool ) ), this, SLOT( pressEndButton() ) );

    connect( loadFileLineEdit, SIGNAL( editingFinished() ), this, SLOT( changeLoadFile() ) );
    connect(saveFileLineEdit, SIGNAL( editingFinished() ), this, SLOT( changeSaveFile() ) );

    connect( widthFieldLineEdit, SIGNAL( editingFinished() ), this, SLOT( changeWidthFieldLineEdit() ) );
    connect( heightFieldLineEdit, SIGNAL( editingFinished() ), this, SLOT( changeHeightFieldLineEdit() ) );

    connect(generationLineEdit, SIGNAL( editingFinished() ), this, SLOT( changeGeneration() ) );

    connect( speedSpinBox, SIGNAL( valueChanged( int ) ), this, SLOT( changeSpeed( int ) ) );

    connect(life_1CheckBox, SIGNAL( stateChanged ( int ) ), this, SLOT( changeLifeRule1() ) );
    connect(life_2CheckBox, SIGNAL( stateChanged ( int ) ), this, SLOT( changeLifeRule2() ) );
    connect(life_3CheckBox, SIGNAL( stateChanged ( int ) ), this, SLOT( changeLifeRule3() ) );
    connect(life_4CheckBox, SIGNAL( stateChanged ( int ) ), this, SLOT( changeLifeRule4() ) );
    connect(life_5CheckBox, SIGNAL( stateChanged ( int ) ), this, SLOT( changeLifeRule5() ) );
    connect(life_6CheckBox, SIGNAL( stateChanged ( int ) ), this, SLOT( changeLifeRule6() ) );
    connect(life_7CheckBox, SIGNAL( stateChanged ( int ) ), this, SLOT( changeLifeRule7() ) );
    connect(life_8CheckBox, SIGNAL( stateChanged ( int ) ), this, SLOT( changeLifeRule8() ) );

    connect(dead_1CheckBox, SIGNAL( stateChanged ( int ) ), this, SLOT( changeDeadRule1() ) );
    connect(dead_2CheckBox, SIGNAL( stateChanged ( int ) ), this, SLOT( changeDeadRule2() ) );
    connect(dead_3CheckBox, SIGNAL( stateChanged ( int ) ), this, SLOT( changeDeadRule3() ) );
    connect(dead_4CheckBox, SIGNAL( stateChanged ( int ) ), this, SLOT( changeDeadRule4() ) );
    connect(dead_5CheckBox, SIGNAL( stateChanged ( int ) ), this, SLOT( changeDeadRule5() ) );
    connect(dead_6CheckBox, SIGNAL( stateChanged ( int ) ), this, SLOT( changeDeadRule6() ) );
    connect(dead_7CheckBox, SIGNAL( stateChanged ( int ) ), this, SLOT( changeDeadRule7() ) );
    connect(dead_8CheckBox, SIGNAL( stateChanged ( int ) ), this, SLOT( changeDeadRule8() ) );

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

void Window:: changeLifeRule1(){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedLife(1,life_1CheckBox -> isChecked());
}

void Window:: changeLifeRule2(){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedLife(2,life_2CheckBox -> isChecked());
}

void Window:: changeLifeRule3(){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedLife(3,life_3CheckBox -> isChecked());
}

void Window:: changeLifeRule4(){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedLife(4,life_4CheckBox -> isChecked());
}

void Window:: changeLifeRule5(){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedLife(5,life_5CheckBox -> isChecked());
}

void Window:: changeLifeRule6(){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedLife(6,life_6CheckBox -> isChecked());
}

void Window:: changeLifeRule7(){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedLife(7,life_7CheckBox -> isChecked());
}

void Window:: changeLifeRule8(){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedLife(8,life_8CheckBox -> isChecked());
}

void Window:: changeDeadRule1(){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedDead(1,dead_1CheckBox -> isChecked());
}
void Window:: changeDeadRule2(){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedDead(2,dead_2CheckBox -> isChecked());
}
void Window:: changeDeadRule3(){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedDead(3,dead_3CheckBox -> isChecked());
}

void Window:: changeDeadRule4(){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedDead(4,dead_4CheckBox -> isChecked());
}

void Window:: changeDeadRule5(){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedDead(5,dead_5CheckBox -> isChecked());
}

void Window:: changeDeadRule6(){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedDead(6,dead_6CheckBox -> isChecked());
}

void Window:: changeDeadRule7(){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedDead(7,dead_7CheckBox -> isChecked());
}

void Window:: changeDeadRule8(){
    pressPauseButton();
    loadFileLineEdit -> setEnabled(true);
    saveFileLineEdit -> setEnabled(true);
    emit activatedDead(8,dead_8CheckBox -> isChecked());
}


Window::~Window()
{
    delete timer;

    delete renderArea;

    delete widthFieldLabel;
    delete heightFieldLabel;
    delete loadFileLable;
    delete saveFileLable;
    delete ruleLabel;
    delete speedLable;
    delete generationLabel;

    delete widthFieldLineEdit;
    delete heightFieldLineEdit;
    delete loadFileLineEdit;
    delete saveFileLineEdit;
    delete generationLineEdit;

    delete playButton;
    delete pauseButton;
    delete  endButton;

    delete rule_1CheckBox;
    delete rule_2CheckBox;

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
        life_1CheckBox -> setChecked(life[1]);

        life_2CheckBox -> setChecked(life[2]);

        life_3CheckBox -> setChecked(life[3]);

        life_4CheckBox -> setChecked(life[4]);

        life_5CheckBox -> setChecked(life[5]);

        life_6CheckBox -> setChecked(life[6]);

        life_7CheckBox -> setChecked(life[7]);

        life_8CheckBox -> setChecked(life[8]);
}

void Window:: activeDead(std::vector <bool> dead){
        dead_1CheckBox -> setChecked(dead[1]);

        dead_2CheckBox -> setChecked(dead[2]);

        dead_3CheckBox -> setChecked(dead[3]);

        dead_4CheckBox -> setChecked(dead[4]);

        dead_5CheckBox -> setChecked(dead[5]);

        dead_6CheckBox -> setChecked(dead[6]);

        dead_7CheckBox -> setChecked(dead[7]);

        dead_8CheckBox -> setChecked(dead[8]);
}
