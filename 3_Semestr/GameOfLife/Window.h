#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QIntValidator>

#include "RenderArea.h"
#include "Field.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    Window( Model * model_, QWidget * parent = 0);
    RenderArea * getRenderArea();
     void chooseRule();
    ~Window();
    QTimer * getTimer(){
        return timer;
    }
signals:
    void clearField();
    void changedWidth(int);
    void changedHeight(int);
    void changedGeneration(int);
    void loadFile(QString & fileName);
    void saveFile(QString & fileName);
    void addFieldInHistory();
    void activatedLife(int, bool);
    void activatedDead(int, bool);

public slots:
    void activeLife(std::vector<bool>);
    void activeDead(std::vector<bool>);

    void changeWidth(int width);
    void changeHeight(int height);
    void pressPauseButton();
    void addGeneration();
private slots:
    void changeLifeRule1();
    void changeLifeRule2();
    void changeLifeRule3();
    void changeLifeRule4();
    void changeLifeRule5();
    void changeLifeRule6();
    void changeLifeRule7();
    void changeLifeRule8();

    void changeDeadRule1();
    void changeDeadRule2();
    void changeDeadRule3();
    void changeDeadRule4();
    void changeDeadRule5();
    void changeDeadRule6();
    void changeDeadRule7();
    void changeDeadRule8();

    void pressPlayButton();
    void pressEndButton();
    void changeLoadFile();
    void changeSaveFile();
    void changeWidthFieldLineEdit();
    void changeHeightFieldLineEdit();
    void changeSpeed(int speed);
    void changeGeneration();

private:
    QTimer * timer;

    RenderArea *renderArea;

    QLabel * widthFieldLabel;
    QLabel * heightFieldLabel;
    QLabel * loadFileLable;
    QLabel * saveFileLable;
    QLabel * ruleLabel;
    QLabel * speedLable;
    QLabel * generationLabel;
    QLabel * lifeRule;
    QLabel * deadRule;

    QLineEdit * widthFieldLineEdit;
    QLineEdit * heightFieldLineEdit;
    QLineEdit * loadFileLineEdit;
    QLineEdit * saveFileLineEdit;
    QLineEdit * generationLineEdit;

    QPushButton * playButton;
    QPushButton * pauseButton;
    QPushButton * endButton;

    QCheckBox * rule_1CheckBox;
    QCheckBox * rule_2CheckBox;


    QCheckBox * life_1CheckBox;
    QCheckBox * life_2CheckBox;
    QCheckBox * life_3CheckBox;
    QCheckBox * life_4CheckBox;
    QCheckBox * life_5CheckBox;
    QCheckBox * life_6CheckBox;
    QCheckBox * life_7CheckBox;
    QCheckBox * life_8CheckBox;

    QCheckBox * dead_1CheckBox;
    QCheckBox * dead_2CheckBox;
    QCheckBox * dead_3CheckBox;
    QCheckBox * dead_4CheckBox;
    QCheckBox * dead_5CheckBox;
    QCheckBox * dead_6CheckBox;
    QCheckBox * dead_7CheckBox;
    QCheckBox * dead_8CheckBox;


    QSpinBox * speedSpinBox;

    QIntValidator * validator;

    const int SPEED_STEP = 50;
    const int SPEED_SPIN_BOX_WIDTH = 200;
    const int SPEED_MAX_VALUE = 1000;
    const int SPEED_MIN_VALUE = 50;

    const int SIZE_MIN_FIELD = 0;
    const int SIZE_MAX_FIELD = 10000;

    const std:: string rule1 = "B3/S23";
    const std:: string rule2 = "B4567/S234";
};

#endif // WINDOW_H
