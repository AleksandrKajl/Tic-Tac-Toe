#include "TicTacToe.h"

TicTacToe::TicTacToe(QWidget *parent)
    : QLabel(parent)
{
    ui.setupUi(this);
    this->resize(800, 600);
    QPixmap bknd("Textures/sheet.png");
    QPalette pal;
    pal.setBrush(QPalette::Window, bknd);
    setPalette(pal);
}

void TicTacToe::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter qp(this);
    field.fieldStart.x = halfSz.widht - HALF_FIELD;
    field.fieldStart.y = halfSz.height - HALF_FIELD;
    field.fieldEnd.x = halfSz.widht + HALF_FIELD;
    field.fieldEnd.y = halfSz.height + HALF_FIELD;
    drawField(&qp);
}

// ----------------------------------------------------------------------
void TicTacToe::mousePressEvent(QMouseEvent* pe)
{
    mouseClick(pe);
}

void TicTacToe::drawField(QPainter* qp)
{
    QPen pen(Qt::red, 3, Qt::SolidLine);
    qp->setPen(pen);
    auto sz = this->size();
    halfSz.widht = sz.width() / 2;
    halfSz.height = sz.height() / 2;

    //Рисуем поле в высоту
    for (int i = 0, factor = 0; i < 4; i++)
    {
        qp->drawLine(halfSz.widht - HALF_FIELD, halfSz.height - HALF_FIELD + factor, halfSz.widht + HALF_FIELD, halfSz.height - HALF_FIELD + factor);
        factor += FIELD_SZ / 3;
    }

    //Рисуем поле в ширину
    for (int i = 0, factor = 0; i < 4; i++)
    {
        qp->drawLine(halfSz.widht - HALF_FIELD + factor, halfSz.height - HALF_FIELD, halfSz.widht - HALF_FIELD + factor, halfSz.height + HALF_FIELD);
        factor += FIELD_SZ / 3;
    }
}

void TicTacToe::mouseClick(QMouseEvent* pe)
{
    int mouseX = pe->position().x();
    int mouseY = pe->position().y();
    if ((mouseX > field.fieldStart.x && mouseY > field.fieldStart.y) &&
        (mouseX < field.fieldEnd.x && mouseY < field.fieldEnd.y))
    {
        

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


