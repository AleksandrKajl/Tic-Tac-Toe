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

void TicTacToe::initField()
{
    QPen pen(Qt::red, 3, Qt::SolidLine);
    qp.begin(this);
    qp.setPen(pen);


    //Рисуем поле в высоту
    for (int i = 0, factor = 0; i < 4; i++)
    {
        qp.drawLine(halfSz.width() - HALF_FIELD, halfSz.height() - HALF_FIELD + factor, halfSz.width() + HALF_FIELD, halfSz.height() - HALF_FIELD + factor);
        factor += CELL_SZ;
    }

    //Рисуем поле в ширину
    for (int i = 0, factor = 0; i < 4; i++)
    {
        qp.drawLine(halfSz.width() - HALF_FIELD + factor, halfSz.height() - HALF_FIELD, halfSz.width() - HALF_FIELD + factor, halfSz.height() + HALF_FIELD);
        factor += CELL_SZ;
    }
    qp.end();
}

void TicTacToe::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    //Получаем данные о размере окна
    sizeConversion();
    //Рисуем поле для игры
    initField();

    //Проверяем есть ли координаты для рисования хода
    qp.begin(this);
    QPen pen(Qt::blue, 7, Qt::SolidLine);
    qp.setPen(pen);

    auto win = isWin();
    if (win == Cell::CROSS)
    {

    }

    //Нарисовать ход игрока
    for (int i = 0; i < CELL_COUNT; ++i)
    {
        for (int j = 0; j < CELL_COUNT; ++j)
        {
            if (fieldArr[i][j] == Cell::CROSS)
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
            if (fieldArr[i][j] == Cell::ZERO)
            {
                int x = j * CELL_SZ + DECREASE / 2;
                int y = i * CELL_SZ + DECREASE / 2;
                qp.drawEllipse(field.fieldStart.x() + x, field.fieldStart.y() + y, 100, 100);
            }
        }
    }

    qp.end();

}

void TicTacToe::moveAI()
{
    if (fieldArr[1][1] == Cell::EMPTY)
        fieldArr[1][1] = Cell::ZERO;
    else if (fieldArr[0][0] == Cell::EMPTY)
        fieldArr[0][0] = Cell::ZERO;
    else if (fieldArr[2][0] == Cell::EMPTY)
        fieldArr[2][0] = Cell::ZERO;
    else if (fieldArr[2][2] == Cell::EMPTY)
        fieldArr[2][2] = Cell::ZERO;
    else if (fieldArr[0][2] == Cell::EMPTY)
        fieldArr[0][2] = Cell::ZERO;
    else
    {
        for (int i = 0; i < CELL_COUNT; ++i)
        {
            for (int j = 0; j < CELL_COUNT; ++j)
            {
                if (fieldArr[i][j] == Cell::EMPTY)
                {
                    fieldArr[i][j] = Cell::ZERO;
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
        fieldArr[cross.y()][cross.x()] = Cell::CROSS;
        gameProgress = true;
        repaint();
    }

}

Cell TicTacToe::isWin()
{
    //Проверка выигрыша по строкам 
    for (int i = 0; i < CELL_COUNT - 1; ++i)
    {
        for (int j = 0, count = 0; j < CELL_COUNT - 1; ++j)
        {
            if (fieldArr[i][j] == fieldArr[i][j + 1] && fieldArr[i][j] != Cell::EMPTY)
                count++;
            if (count == CELL_COUNT - 1)
                return fieldArr[i][j];

        }
    }

    //Проверка выигрыша по столбцам 
    for (int i = 0, count = 0; i < CELL_COUNT - 1; ++i)
    {
        for (int j = 0; j < CELL_COUNT - 1; ++j)
        {
            if (fieldArr[j][i] == fieldArr[j + 1][i] && fieldArr[j][i] != Cell::EMPTY)
                count++;
            if (count == CELL_COUNT - 1)
                return fieldArr[j][i];
        }
    }

    //Проверка выигрыша наискосок с левой стороны на правую
    for (int i = 0, count = 0; i < CELL_COUNT - 1; ++i)
    {

        if (fieldArr[i][i] == fieldArr[i + 1][i + 1] && fieldArr[i][i] != Cell::EMPTY)
            count++;
        if (count == CELL_COUNT - 1)
            return fieldArr[i][i];
    }

    //Проверка выигрыша наискосок с правой стороны на левую
    for (int i = CELL_COUNT - 1, count = 0; i > 0; --i)
    {

        if (fieldArr[i][i] == fieldArr[i - 1][i - 1] && fieldArr[i][i] != Cell::EMPTY)
            count++;
        if (count == CELL_COUNT - 1)
            return fieldArr[i][i];
    }

    return Cell::EMPTY;
}



