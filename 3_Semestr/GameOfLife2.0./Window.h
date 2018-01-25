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
    void changeLifeRule(int);

    void changeDeadRule(int);

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

    std:: vector<QCheckBox*> lifeCheckBox;
    std:: vector<QCheckBox*> deadCheckBox;

    QSpinBox * speedSpinBox;

    QIntValidator * validator;

    const int SPEED_STEP = 50;
    const int SPEED_SPIN_BOX_WIDTH = 200;
    const int SPEED_MAX_VALUE = 1000;
    const int SPEED_MIN_VALUE = 50;

    const int SIZE_MIN_FIELD = 0;
    const int SIZE_MAX_FIELD = 10000;
};

#endif // WINDOW_H
