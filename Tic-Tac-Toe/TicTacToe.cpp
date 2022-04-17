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


// ----------------------------------------------------------------------
void TicTacToe::mouseReleaseEvent(QMouseEvent* pe)
{

}
// ----------------------------------------------------------------------
void TicTacToe::mouseMoveEvent(QMouseEvent* pe)
{

}


