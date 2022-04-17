#include"DrawFrame.h"

void DrawFrame::sizeConversion()
{
    auto sz = this->size();
    halfSz.setWidth(sz.width() / 2);
    halfSz.setHeight(sz.height() / 2);
    field.fieldStart.setX(halfSz.width() - HALF_FIELD);
    field.fieldStart.setY(halfSz.height() - HALF_FIELD);
    field.fieldEnd.setX(halfSz.width() + HALF_FIELD);
    field.fieldEnd.setY(halfSz.height() + HALF_FIELD);
}

void DrawFrame::initField(QPainter* qp)
{
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

void DrawFrame::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    //Получаем данные о размере окна
    sizeConversion();
    //Рисуем поле для игры
    initField(&qp);

    //Проверяем есть ли координаты для рисования хода
    qp.begin(this);
    QPen pen(Qt::blue, 7, Qt::SolidLine);
    qp.setPen(pen);

    //Нарисовать ход игрока
    for (int i = 0; i < CELL_COUNT; ++i)
    {
        for (int j = 0; j < CELL_COUNT; ++j)
        {
            if (fieldArr[i][j] == 1)
            {
                int x = j * CELL_SZ + DECREASE / 2;
                int y = i * CELL_SZ + DECREASE / 2;
                qp.drawLine(field.fieldStart.x() + x, field.fieldStart.y() + y,
                    field.fieldStart.x() + x + CELL_SZ - DECREASE, field.fieldStart.y() + y + CELL_SZ - DECREASE);

                qp.drawLine(field.fieldStart.x() + x + CELL_SZ - DECREASE, field.fieldStart.y() + y,
                    field.fieldStart.x() + x, field.fieldStart.y() + y + CELL_SZ - DECREASE);
            }
        }
    }

    //Ход компьютера
    if (gameProgress)
        moveAI();

    gameProgress = false;

    //Рисуем ход компьютера
    for (int i = 0; i < CELL_COUNT; ++i)
    {
        for (int j = 0; j < CELL_COUNT; ++j)
        {
            if (fieldArr[i][j] == 2)
            {
                int x = j * CELL_SZ + DECREASE / 2;
                int y = i * CELL_SZ + DECREASE / 2;
                qp.drawEllipse(field.fieldStart.x() + x, field.fieldStart.y() + y, 100, 100);
            }
        }
    }

    qp.end();

}