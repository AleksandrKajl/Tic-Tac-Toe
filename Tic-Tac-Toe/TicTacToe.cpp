#include "TicTacToe.h"

TicTacToe::TicTacToe(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    this->resize(800, 600);
    QPixmap bknd("Textures/sheet.png");
    QPalette pal;
    pal.setBrush(QPalette::Window, bknd);
    setPalette(pal);
}

void TicTacToe::sizeConversion()
{
    auto sz = this->size();
    halfSz.setWidth(sz.width() / 2);
    halfSz.setHeight(sz.height() / 2);
    field.fieldStart.setX(halfSz.width() - HALF_FIELD);
    field.fieldStart.setY(halfSz.height() - HALF_FIELD);
    field.fieldEnd.setX(halfSz.width() + HALF_FIELD);
    field.fieldEnd.setY(halfSz.height() + HALF_FIELD);
}

void TicTacToe::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    sizeConversion();
    initField(&qp);
    if (!mClick.isNull())
    {
        qp.begin(this);
        QPen pen(Qt::blue, 7, Qt::SolidLine);
        qp.setPen(pen);
//Draw cross
        qp.drawLine(field.fieldStart.x() + cross.x(), field.fieldStart.y() + cross.y(), 
            field.fieldStart.x() + cross.x() + CELL_SZ - DECREASE, field.fieldStart.y() + cross.y() + CELL_SZ - DECREASE);

        qp.drawLine(field.fieldStart.x() + cross.x() + CELL_SZ - DECREASE, field.fieldStart.y() + cross.y(), 
            field.fieldStart.x() + cross.x(), field.fieldStart.y() + cross.y() + CELL_SZ - DECREASE);

        qp.end();
    }
}

// ----------------------------------------------------------------------
void TicTacToe::mousePressEvent(QMouseEvent* pe)
{
    mouseClick(pe);
}

void TicTacToe::initField(QPainter* qp)
{
    //for (auto& cell : cellArr)
    //{
    //    cell = field

    //}

    QPen pen(Qt::red, 3, Qt::SolidLine);
    qp->begin(this);
    qp->setPen(pen);


    //Рисуем поле в высоту
    for (int i = 0, factor = 0; i < 4; i++)
    {
        qp->drawLine(halfSz.width() - HALF_FIELD, halfSz.height() - HALF_FIELD + factor, halfSz.width() + HALF_FIELD, halfSz.height() - HALF_FIELD + factor);
        factor += CELL_SZ;
    }

    //Рисуем поле в ширину
    for (int i = 0, factor = 0; i < 4; i++)
    {
        qp->drawLine(halfSz.width() - HALF_FIELD + factor, halfSz.height() - HALF_FIELD, halfSz.width() - HALF_FIELD + factor, halfSz.height() + HALF_FIELD);
        factor += CELL_SZ;
    }
    qp->end();

}

void TicTacToe::mouseClick(QMouseEvent* pe)
{
    if ((pe->position().x() > field.fieldStart.x() && pe->position().y() > field.fieldStart.y()) &&
        (pe->position().x() < field.fieldEnd.x() && pe->position().y() < field.fieldEnd.y()))
    {
        mClick.setX(pe->position().x());
        mClick.setY(pe->position().y());
        cross.setX((mClick.x() - field.fieldStart.x()) / CELL_SZ);
        cross.setY((mClick.y() - field.fieldStart.y()) / CELL_SZ);
        cross.setX(cross.x() * CELL_SZ + DECREASE / 2);
        cross.setY(cross.y() * CELL_SZ + DECREASE / 2);

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


