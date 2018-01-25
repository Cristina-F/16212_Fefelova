#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>

#include "Model.h"

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea( Model * model, QWidget *parent = 0);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    int getWidthField();
    int getHeightField();

    void setWidthField(int width);
    void setHeightField(int height);
    void startPosition();
signals:
        void pauseGame();
        void changedCell(int x, int y, bool status);

public slots:
        void repaint();
protected:
        void paintEvent(QPaintEvent * event);
        void mousePressEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent *event);
        void wheelEvent(QWheelEvent *event);

private:
    Model * model_;

    int sizeCell_ = 15;

    int xStart = 0;
    int yStart = 0;

    int xPosition = 0;
    int yPosition = 0;

    void paintCells( QPainter & p );
    void paintCells( QMouseEvent * event );
    void moveField( QMouseEvent * event );


    const float ZOOM = 0.25;
    const int INDENT = 10;
    const int OFFSET = 10;
    const int SIZE_MIN_CELL = 5;
    const bool LIFE_CELL = true;
    const bool DEAD_CELL = false;
};

#endif // RENDERAREA_H
