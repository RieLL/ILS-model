#include "signature.h"

Signature::Signature()
    : Window ()
    , MainParameters ()
    , str {}
{
    //
}

Signature::~Signature()
{
    //
}

void Signature::drawElement(QPainter* painter)
{
    painter->setPen( QPen(QColor(0, 0, 0, 255), 1, Qt::SolidLine) );

    int sizeFont = 11 * (width / 350);

    if (sizeFont < 11)
        sizeFont = { 11 };

    if (sizeFont > 16)
        sizeFont = { 16 };

    painter->setFont(QFont("", sizeFont, 1, false));
    painter->drawText(QRectF(posX, posY, width, height), Qt::AlignCenter, str);
}

void Signature::setText(const QString& str)
{
    this->str = { str };
}
