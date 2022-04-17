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

//Structure discribing the playing field

//Metods

protected:
    void mouseReleaseEvent(QMouseEvent* pe) override;
    void mouseMoveEvent(QMouseEvent* pe) override;

};
