#include "spectrum.h"

Spectrum::Spectrum(const QColor color)
    : Plot ( color )
{
    //
}

Spectrum::~Spectrum()
{
    //
}

void Spectrum::drawElement(QPainter* painter)
{
    qreal x1 = { 0.0 };
    qreal y1 = { 0.0 };
    qreal y2 = { 0.0 };

    qreal x = { 0.0 };
    qreal y = { 0.0 };
    qreal w = { 0.0 };
    qreal h = { 0.0 };

    qreal sizeX = { 70.0 };
    qreal sizeY = { 24.0 };

    qreal sizeFont = { 11.0 * (width / 500.0) };

    for (int i = { 0 }; i < plotPoints.size(); ++i)
    {
        painter->setPen(QPen(color, 3, Qt::SolidLine));
        painter->setRenderHint(QPainter::Antialiasing, false);

        x1 = { static_cast<qreal>(posX + plotPoints.at(i).x() * scaleX) };
        y1 = { static_cast<qreal>(posY + (countHLines - 1.0 - plotPoints.at(i).y()) * scaleY) };
        y2 = { static_cast<qreal>(posY + height - 2.0) };

        painter->drawLine(x1, y1, x1, y2);

        // Маленькие черточки
        painter->drawLine(x1 - 5.0, y1 - 1.0, x1 + 5.0, y1 - 1.0);

        // Надписи
        x = { x1 - sizeX * 0.5 };
        y = { y1 - sizeY };
        w = { sizeX };
        h = { sizeY };

        QRectF rect(x, y, w, h);

        if (sizeFont < 11.0)
        {
            sizeFont = { 11.0 };
        }

        if (sizeFont > 14.0)
        {
            sizeFont = { 14.0 };
        }

        QFont font("", sizeFont, 1, false);

        painter->setPen(QPen(QColor(0, 0, 0, 255), 1, Qt::SolidLine));
        painter->setFont(font);

        painter->drawText(rect, Qt::AlignCenter, Plot::str.at(i));
    }
}
