#include "dots.h"

Dots::Dots(const QColor color) :
    Plot(color)
{
    //
}

Dots::~Dots()
{
    //
}



void Dots::drawElement(QPainter* painter)
{
//    QPainterPath path;

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(color, 2, Qt::SolidLine));

//    qreal x1 = posX + plotPoints.at(0).x() * scaleX + 1;
//    qreal y1 = (posY + (height / 2.0)) + plotPoints.at(0).y() * scaleY * 2 + 2;

//    path.moveTo(QPointF(x1, y1));

    qreal x1 = 0.0;
    qreal y1 = 0.0;
    qreal x2 = 0.0;
    qreal y2 = 0.0;


    for(int i = 1; i < plotPoints.size(); ++i)
    {
//        x1 = posX + plotPoints.at(i - 1).x() * scaleX;
//        y1 = (posY + (height / 2.0)) + plotPoints.at(i - 1).y() * scaleY * 2 + 2;
//        x2 = posX + plotPoints.at(i).x() * scaleX;
//        y2 = (posY + (height / 2.0)) + plotPoints.at(i).y() * scaleY * 2 + 2;

        x1 = posX + plotPoints.at(i - 1).x() * scaleX;
        y1 = (posY + (height / 2.0)) + plotPoints.at(i - 1).y() * scaleY * 2 + 2;
        x2 = posX + plotPoints.at(i).x() * scaleX;
        y2 = (posY + (height / 2.0)) + plotPoints.at(i).y() * scaleY * 2 + 2;

        painter->drawLine(x1, y1, x2, y2);

//        path.lineTo(QPointF(x2, y2));

        if (x2 >= width + 5) { break; }
    }

//    painter->drawPath(path);
}
