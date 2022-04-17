#pragma once
#include<QtWidgets>
#include<QPainter>

class DrawFrame : public QWidget
{
protected:
	virtual ~DrawFrame() {};
    //Constants
    const int FIELD_SZ = 402;
    const int HALF_FIELD = FIELD_SZ / 2;
    const int CELL_SZ = FIELD_SZ / 3;
    const int DECREASE = 40;
    const int CELL_COUNT = 3;

    QPoint mClick;
    QPoint cross;
    QSize halfSz;
    struct Field
    {
        QPoint fieldStart;
        QPoint fieldEnd;
    }field;
    QPainter qp;
    //������ ��� �������� �����
    std::array<std::array<int, 3>, 3> fieldArr{ 0 };
    bool gameProgress = false;

    void paintEvent(QPaintEvent* event)override;
    void mousePressEvent(QMouseEvent* pe) override;
    //virtual void Draw() = 0;
    void sizeConversion();
    void initField();
    void moveAI();
    void mouseClick(QMouseEvent* pe);

};