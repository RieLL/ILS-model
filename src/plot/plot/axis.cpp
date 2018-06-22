#include "axis.h"
#include <QTextCodec>
#include "variables.h"

Axis::Axis() 
    : Window ()
    , Scale ()
    , Hairstroke ()
    , axis { Off }
    , var  { new Variables }
{
    //
}

Axis::~Axis()
{
    delete var;
}

void Axis::drawElement(QPainter* painter)
{
    painter->setPen(QPen(var->getColorAxis(), 1, Qt::SolidLine));

    if (axis == X)
    {
        this->axisButtom(painter);
        this->drawSignature(painter);

        qreal x1 = { 0.0 };
        qreal y1 = { 0.0 };

        qreal x = { 0.0 };
        qreal y = { 0.0 };
        qreal w = { 0.0 };
        qreal h = { 0.0 };

        qreal sizeX = { 70.0 };
        qreal sizeY = { 24.0 };

        qreal sizeFont = { 11.0 * (width / 500.0) };

        x1 = { width - (sizeX * 0.5) };
        y1 = { posY + height - 1.0 };

        // Надписи
        x = { x1 - (sizeX * 0.5) };
        y = { y1 - sizeY };
        w = { sizeX };
        h = { sizeY };

        QRectF rect(x, y, w, h);

        if (sizeFont < 11)
            sizeFont = { 11 };

        if (sizeFont > 14)
            sizeFont = { 14 };

        QFont font("", sizeFont, 1, false);

        painter->setFont(font);

        painter->drawText(rect, Qt::AlignRight, QString("МГц"));
    }

    if (axis == Y) { axisLeft(painter); }
}

void Axis::setAxis(PlotAxis axis)
{
    this->axis = { axis };
}

void Axis::setSignatureAxis(const QVector<qreal>& point, const QVector<QString>& str)
{
    this->point = { point };
    this->str = { str };
}

void Axis::axisButtom(QPainter* painter)
{
    qreal x1 = { static_cast<qreal>(posX) };
    qreal y1 = { static_cast<qreal>(posY) };
    qreal x2 = { static_cast<qreal>(width) };
    qreal y2 = { y1 };

    painter->drawLine(x1, y1, x2, y2);

    qreal x = { x2 };
    y2 += 5; // SMALL_STRIP_H

    painter->drawLine(x, y1, x, y2);

    for (int i = { 0 }; i < (countVLines - 1); i++)
    {
        x = {  i * scaleX + x1 };
        painter->drawLine(x, y1, x, y2);
    }
}

void Axis::axisLeft(QPainter* painter)
{
    int x1 = { posX + width };
    int y1 = { posY };
    int x2 = { x1 };
    int y2 = { height };

    painter->drawLine(x1, y1, x2, y2);

    int y = { y2 };
    x2 -= 5; // SMALL_STRIP_H

    painter->drawLine(x1, y, x2, y);

    for(int i = { 0 }; i < (countHLines - 1); ++i)
    {
        y = (i * scaleY) + y1;
        painter->drawLine(x1, y, x2, y);
    }
}

void Axis::drawSignature(QPainter* painter)
{
    qreal x1 = { 0.0 };
    qreal y1 = { 0.0 };

    qreal x = { 0.0 };
    qreal y = { 0.0 };
    qreal w = { 0.0 };
    qreal h = { 0.0 };

    qreal sizeX = { 70.0 };
    qreal sizeY = { 24.0 };

    qreal sizeFont = { 11.0 * (width / 500.0) };

    for (int i = { 0 }; i < str.size(); ++i)
    {
        x1 = { point.at(i) * scaleX + 5.0 };
        y1 = { posY + height - 1.0 };

        // Надписи
        x = { x1 - (sizeX * 0.5) };
        y = { y1 - sizeY };
        w = { sizeX };
        h = { sizeY };

        QRectF rect(x, y, w, h);

        if (sizeFont < 11)
            sizeFont = { 11 };

        if (sizeFont > 14)
            sizeFont = { 14 };

        QFont font("", sizeFont, 1, false);

        painter->setFont(font);

        //painter->drawRect(rect);

        painter->drawText(rect, Qt::AlignCenter, str.at(i));
    }
}
