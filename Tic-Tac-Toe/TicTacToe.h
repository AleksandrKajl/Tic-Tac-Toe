#pragma once

#include <QtWidgets>
#include "QPainter"
#include "ui_TicTacToe.h"

class TicTacToe : public QLabel
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

    struct HalfSz
    {
        int widht = 0;
        int height = 0;
    }halfSz;

//Structure discribing the playing field
    struct Field
    {
        struct FieldStart
        {
            int x;
            int y;
        }fieldStart;

        struct FieldEnd
        {
            int x;
            int y;
        }fieldEnd;
    }field;

    std::array<Field, 9> cellArr;


protected:
    void paintEvent(QPaintEvent* event)override;
    void drawField(QPainter* qp);

    void mousePressEvent(QMouseEvent* pe) override;
    void mouseReleaseEvent(QMouseEvent* pe) override;
    void mouseMoveEvent(QMouseEvent* pe) override;

    void mouseClick(QMouseEvent* pe);
};
