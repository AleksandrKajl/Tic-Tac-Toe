#pragma once

#include <QtWidgets>
#include "QPainter"
#include "ui_TicTacToe.h"

enum class Progress
{
    IN_PROGRESS,
    WIN_PLAYER,
    WIN_AI,
    DRAW
};

enum class Cell
{
    EMPTY,
    CROSS,
    ZERO
};

class TicTacToe : public QWidget
{
    Q_OBJECT

public:
    TicTacToe(QWidget *parent = Q_NULLPTR);

private:
    Ui::TicTacToeClass ui;
    //Constants
    const int FIELD_SZ = 402;
    const int HALF_FIELD = FIELD_SZ / 2;
    const int CELL_SZ = FIELD_SZ / 3;
    const int DECREASE = 40;
    const int CELL_COUNT = 3;

    //Массив для хронения ходов
    std::array<std::array<Cell, 3>, 3> fieldArr{ Cell::EMPTY };

    //Variable
    bool gameProgress = false;
    int gameStep = 0;

    QPoint mClick;
    QPoint cross;
    QSize halfSz;
    QPainter qp;
    
    //Structurs
    struct Field
    {
        QPoint fieldStart;
        QPoint fieldEnd;
    }field;
    
   
    //Methods
    void sizeConversion();
    void initField();
    void moveAI();
    void mouseClick(QMouseEvent* pe);
    Cell isWin();

protected:
    //Virtual methods
    void paintEvent(QPaintEvent* event)override;
    void mousePressEvent(QMouseEvent* pe) override;

};
