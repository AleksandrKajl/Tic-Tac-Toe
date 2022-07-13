#include "TicTacToe.h"
#include<QDebug>


TicTacToe::TicTacToe(QWidget *parent)
    : bluePen7(Qt::blue, 7, Qt::SolidLine),
      redPen7(Qt::red, 7, Qt::SolidLine),
      redPen3(Qt::red, 3, Qt::SolidLine),
      QWidget(parent)
{

    ui.setupUi(this);
    this->resize(800, 600);
    //���
    QPixmap bknd(":/resource/sheet.png");
    QPalette pal;
    pal.setBrush(QPalette::Window, bknd);
    setPalette(pal);
}

void TicTacToe::drawText(int textX, int textY, QString str)
{
    qp.setPen(redPen7);
    qp.setFont(QFont("Times", 50, QFont::Normal));
    qp.drawText(textX, textY, str);
}

//����������� ����� ����������� ������
void TicTacToe::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    //�������� ������ � ������� ����
    sizeConversion();
    //������ ���� ��� ����
    initField();

    
    qp.begin(this);
    qp.setPen(bluePen7);

    //���������� ��� ������
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

    if (isWin() == Cell::CROSS)
    {
        gameProgress = false;
        drawText(200, 60, "You Win!");
        qp.setPen(bluePen7);
        gameOver = true;
    }

    //��� ����������
    if (gameProgress)
        moveAI();

    //������ ��� ����������
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

   // win = isWin();
    if (isWin() == Cell::ZERO)
    {
        drawText(200, 60, "AI Win!");
        gameOver = true;
    }

    gameProgress = false;

    qp.end();

}

//��������� �������� ���� � ����������� �� ������� ����
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

//����� ��� ��������� ���� ��� ����
void TicTacToe::initField()
{
    qp.begin(this);
    qp.setPen(redPen3);


    //������ ���� � ������
    for (int i = 0, factor = 0; i < 4; i++)
    {
        qp.drawLine(halfSz.width() - HALF_FIELD, halfSz.height() - HALF_FIELD + factor, halfSz.width() + HALF_FIELD, halfSz.height() - HALF_FIELD + factor);
        factor += CELL_SZ;
    }

    //������ ���� � ������
    for (int i = 0, factor = 0; i < 4; i++)
    {
        qp.drawLine(halfSz.width() - HALF_FIELD + factor, halfSz.height() - HALF_FIELD, halfSz.width() - HALF_FIELD + factor, halfSz.height() + HALF_FIELD);
        factor += CELL_SZ;
    }
    qp.end();
}


//��� AI
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

// ����������� ����� ��������� ������� �� ����
void TicTacToe::mousePressEvent(QMouseEvent* pe)
{
    mouseClick(pe);
}

//��������� ������� ����
void TicTacToe::mouseClick(QMouseEvent* pe)
{
    if (!gameOver)
    {
        //��������� ��� �� ���� � ������� ����
        if ((pe->position().x() > field.fieldStart.x() && pe->position().y() > field.fieldStart.y()) &&
            (pe->position().x() < field.fieldEnd.x() && pe->position().y() < field.fieldEnd.y()))
        {
            mClick.setX(pe->position().x());
            mClick.setY(pe->position().y());
            cross.setX((mClick.x() - field.fieldStart.x()) / CELL_SZ);
            cross.setY((mClick.y() - field.fieldStart.y()) / CELL_SZ);

            if (fieldArr[cross.y()][cross.x()] == Cell::EMPTY)
            {
                fieldArr[cross.y()][cross.x()] = Cell::CROSS;
                gameProgress = true;
            }


            repaint();
        }
    }


}

// �������� ��������
Cell TicTacToe::isWin()
{
    //�������� �������� �� ������� 
    for (int i = 0; i < CELL_COUNT; ++i)
    {
        for (int j = 0, count = 0; j < CELL_COUNT - 1; ++j)
        {
            if (fieldArr[i][j] == fieldArr[i][j + 1] && fieldArr[i][j] != Cell::EMPTY)
                count++;
            //else
            //  break;
            if (count == CELL_COUNT - 1)
            {
                count = 0;
                return fieldArr[i][j];
            }

        }
    }

    //�������� �������� �� �������� 
    for (int i = 0; i < CELL_COUNT; ++i)
    {
        for (int j = 0, count = 0; j < CELL_COUNT - 1; ++j)
        {
            if (fieldArr[j][i] == fieldArr[j + 1][i] && fieldArr[j][i] != Cell::EMPTY)
                count++;
            //else
            //  break;
            if (count == CELL_COUNT - 1)
            {
            
                return fieldArr[j][i];
            }
        }
    }

    //�������� �������� ��������� � ����� ������� �� ������
    for (int i = 0, count = 0; i < CELL_COUNT - 1; ++i)
    {
        if (fieldArr[i][i] == fieldArr[i + 1][i + 1] && fieldArr[i][i] != Cell::EMPTY)
            count++;
        //else
        //  break;
        if (count == CELL_COUNT - 1)
        {
            //count = 0;
            return fieldArr[i][i];
        }
    }

    //�������� �������� ��������� � ������ ������� �� �����
    for (int i = 0, j = CELL_COUNT - 1, count = 0; i < CELL_COUNT - 1; ++i, --j)
    {

        if (fieldArr[i][j] == fieldArr[i + 1][j - 1] && fieldArr[i][j] != Cell::EMPTY)
            count++;
        //else
        //  break;
        if (count == CELL_COUNT - 1)
        {
            //count = 0;
            return fieldArr[i][i];
        }
    }

    return Cell::EMPTY;
}

