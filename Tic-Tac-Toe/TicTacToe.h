#pragma once

#include <QtWidgets>
#include "QPainter"
#include "ui_TicTacToe.h"

class TicTacToe : public QWidget
{
    Q_OBJECT

public:
    TicTacToe(QWidget *parent = Q_NULLPTR);

private:
    Ui::TicTacToeClass ui;

    QPainter qp;
 //Constants
    const int FIELD_SZ = 402;
    const int HALF_FIELD = FIELD_SZ / 2;
    const int CELL_SZ = FIELD_SZ / 3;
    const int DECREASE = 40;

    QPoint mClick;
    QSize halfSz;
    QPoint cross;

//Structure discribing the playing field
    struct Field
    {
        QPoint fieldStart;
        QPoint fieldEnd;
    }field;
    

//Metods
    void sizeConversion();

protected:
    void paintEvent(QPaintEvent* event)override;
    void initField(QPainter* qp);

    void mousePressEvent(QMouseEvent* pe) override;
    void mouseReleaseEvent(QMouseEvent* pe) override;
    void mouseMoveEvent(QMouseEvent* pe) override;

    void mouseClick(QMouseEvent* pe);
};
