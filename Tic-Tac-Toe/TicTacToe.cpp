#include "TicTacToe.h"

TicTacToe::TicTacToe(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    this->resize(800, 600);
    QPixmap bknd(":/resource/sheet.png");
    QPalette pal;
    pal.setBrush(QPalette::Window, bknd);
    setPalette(pal);
}



void TicTacToe::moveAI()
{
    if (fieldArr[1][1] == 0)
        fieldArr[1][1] = 2;
    else if (fieldArr[0][0] == 0)
        fieldArr[0][0] = 2;
    else if (fieldArr[2][0] == 0)
        fieldArr[2][0] = 2;
    else if (fieldArr[2][2] == 0)
        fieldArr[2][2] = 2;
    else if (fieldArr[0][2] == 0)
        fieldArr[0][2] = 2;
    else
    {
        for (int i = 0; i < CELL_COUNT; ++i)
        {
            for (int j = 0; j < CELL_COUNT; ++j)
            {
                if (fieldArr[i][j] == 0)
                {
                    fieldArr[i][j] = 2;
                    return;
                }
                    
            }
        }
    }
}

// ----------------------------------------------------------------------
void TicTacToe::mousePressEvent(QMouseEvent* pe)
{
    mouseClick(pe);
}

void TicTacToe::mouseClick(QMouseEvent* pe)
{
    //Проверяем был ли клик в игровом поле
    if ((pe->position().x() > field.fieldStart.x() && pe->position().y() > field.fieldStart.y()) &&
        (pe->position().x() < field.fieldEnd.x() && pe->position().y() < field.fieldEnd.y()))
    {
        mClick.setX(pe->position().x());
        mClick.setY(pe->position().y());
        cross.setX((mClick.x() - field.fieldStart.x()) / CELL_SZ);
        cross.setY((mClick.y() - field.fieldStart.y()) / CELL_SZ);
        fieldArr[cross.y()][cross.x()] = 1;
        gameProgress = true;
        repaint();
    }

}

// ----------------------------------------------------------------------
void TicTacToe::mouseReleaseEvent(QMouseEvent* pe)
{

}
// ----------------------------------------------------------------------
void TicTacToe::mouseMoveEvent(QMouseEvent* pe)
{

}


