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
    const int CELL_COUNT = 3;

    QPoint mClick;
    QSize halfSz;
    QPoint cross;
    bool gameProgress = false;

//Structure discribing the playing field
    struct Field
    {
        QPoint fieldStart;
        QPoint fieldEnd;
    }field;
    
    //Массив для хронения ходов
    std::array<std::array<int, 3>, 3> fieldArr{0};

//Metods
    void sizeConversion();
    void mouseClick(QMouseEvent* pe);
    void initField(QPainter* qp);
    void moveAI();

protected:
    void paintEvent(QPaintEvent* event)override;
    

    void mousePressEvent(QMouseEvent* pe) override;
    void mouseReleaseEvent(QMouseEvent* pe) override;
    void mouseMoveEvent(QMouseEvent* pe) override;

};
