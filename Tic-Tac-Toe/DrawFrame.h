#pragma once
#include<qwidget.h>

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

    QSize halfSz;
    struct Field
    {
        QPoint fieldStart;
        QPoint fieldEnd;
    }field;

    void paintEvent(QPaintEvent* event)override;
    virtual void Draw() = 0;
    void sizeConversion();
    void initField(QPainter* qp);
};