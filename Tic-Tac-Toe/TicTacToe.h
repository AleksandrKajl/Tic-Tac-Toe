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

    QPoint mClick;
    QPoint cross;
    bool gameProgress = false;

//Structure discribing the playing field
    
    //Массив для хронения ходов
    std::array<std::array<int, 3>, 3> fieldArr{0};

//Metods
    void mouseClick(QMouseEvent* pe);
    void initField(QPainter* qp);
    void moveAI();

protected:

    void mousePressEvent(QMouseEvent* pe) override;
    void mouseReleaseEvent(QMouseEvent* pe) override;
    void mouseMoveEvent(QMouseEvent* pe) override;

};
