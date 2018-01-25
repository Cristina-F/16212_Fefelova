#include<iostream>

#include "RenderArea.h"

#include <QPainter>
#include <QPen>


RenderArea:: RenderArea( Model * model, QWidget *parent) : QWidget(parent), model_( model) {
      setBackgroundRole(QPalette::Base);
      setAutoFillBackground(true);
}

QSize RenderArea::minimumSizeHint() const {
    return QSize(200, 200);
}

QSize RenderArea::sizeHint() const {
    return QSize(400, 300);
}

int RenderArea:: getWidthField(){
    return model_ -> getWidth();
}
int RenderArea:: getHeightField(){
    return model_ -> getHeight();
}

void RenderArea:: setWidthField( int width ) {
    model_ -> setWidth(width);
    update();
}

void RenderArea:: setHeightField(int height) {
    model_ -> setHeight(height);
    update();
}

void RenderArea:: paintEvent ( QPaintEvent * /* event */ ) {
    int width = getWidthField();
    int height = getHeightField();
    QColor fieldColor = Qt::gray;
    QPainter p(this);

    QPen pen( Qt:: black );
    pen.setWidth(2);

    p.fillRect( xStart, yStart, width * sizeCell_, height * sizeCell_, fieldColor );

    //горизонтальные линии
    for ( int i = 0; i <= height; i ++ ){
        p.drawLine( xStart, i * sizeCell_ + yStart, width * sizeCell_ + xStart, i * sizeCell_ + yStart );

    }
    //Вертикальные линии
    for ( int i = 0; i <= width; i ++ ){
       p.drawLine( i * sizeCell_ + xStart, yStart, i * sizeCell_ + xStart, height * sizeCell_ + yStart);
    }
    paintCells(p);
}


void RenderArea:: paintCells(QPainter &p){
    int width = getWidthField();
    int height = getHeightField();
    for( int i = 0; i < height; i++ ) {
        for( int j = 0; j < width; j++ ) {
            int left = sizeCell_ * j + xStart + 1;
            int top  = sizeCell_ * i + yStart + 1;
            QRect rect( left, top, sizeCell_ - 1 , sizeCell_ - 1 );
            if( model_ -> getStatus( j, i ) ) {
               p.fillRect(rect, Qt::magenta);
            }
            else{
                p.fillRect(rect, Qt::gray);
            }
        }
    }
}

void RenderArea:: mousePressEvent( QMouseEvent * event ) {
    if ( Qt::LeftButton == event -> buttons() )  {
        emit pauseGame();
        int yIndex = ( event -> y() - yStart) / sizeCell_;
        int xIndex = ( event -> x() - xStart) / sizeCell_;
        if( xIndex >= 0  &&  xIndex < getWidthField() && yIndex >= 0  &&  yIndex < getHeightField() ) {
           emit changedCell( xIndex, yIndex, !(model_ -> getStatus( xIndex, yIndex ) ) );
           update();
        }
    }
}

void RenderArea:: mouseMoveEvent( QMouseEvent * event ) {
    if( Qt::LeftButton == event -> buttons() ) {
        paintCells(event);
    }

    if( Qt::RightButton == event -> buttons() ){
        moveField(event);
    }

}

void RenderArea:: paintCells( QMouseEvent * event ) {
    int yIndex = ( event -> y() - yStart) / sizeCell_;
    int xIndex = ( event -> x() - xStart) / sizeCell_;
    if ( xIndex >= 0  &&  xIndex < getWidthField()  &&  yIndex >= 0  &&  yIndex < getHeightField() ) {
        if( !( model_ -> getStatus( xIndex, yIndex ) ) ) {
            emit changedCell( xIndex , yIndex, LIFE_CELL );
            update();
        }
    }
}

void RenderArea:: moveField( QMouseEvent * event ) {
    if( event -> x() > xPosition && ( INDENT - xStart ) > 0) {
        xStart += OFFSET;
    }
    else if( event -> x() < xPosition && ( width() - xStart - ( sizeCell_ * getWidthField() ) - INDENT) < 0) {
        xStart -= OFFSET;
    }
    if( event -> y() > yPosition && ( INDENT - yStart ) > 0 ) {
        yStart += OFFSET;
    }
    else if ( event -> y() < yPosition && ( height() - yStart - ( sizeCell_ * getHeightField() ) - INDENT ) < 0 ) {
        yStart -= OFFSET;
    }
    xPosition = event -> x();
    yPosition = event -> y();
    update();
}

void RenderArea:: wheelEvent( QWheelEvent * event ) {
    if( event -> delta() > 0 ) {
        sizeCell_ *= 1.0 + ZOOM;
    }
    else{
        if ( sizeCell_ > SIZE_MIN_CELL ) {
            sizeCell_ *= 1.0 - ZOOM;
        }
    }
    update();
}

void RenderArea:: repaint() {
    update();
}

void RenderArea:: startPosition(){
    xStart = 0;
    yStart = 0;
    xPosition = 0;
    yPosition = 0;
}
