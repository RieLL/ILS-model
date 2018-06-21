#include "signature.h"

Signature::Signature() : Window(), MainParameters(),
    str("\0")
{
    //
}



Signature::~Signature()
{
    //
}



void Signature::drawElement(QPainter* painter)
{
    painter->setPen(QPen(QColor(0, 0, 0, 255), 1, Qt::SolidLine));

//    painter->drawRect(posX, posY, width, height);

    int sizeFont = 11 * (width / 350);

    if (sizeFont < 11)
        sizeFont = 11;

    if (sizeFont > 16)
        sizeFont = 16;

    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
    QString string = codec->toUnicode(str);

    painter->setFont(QFont("", sizeFont, 1, false));
    painter->drawText(QRectF(posX, posY, width, height), Qt::AlignCenter, string);
}



void Signature::setText(const QString str)
{
    this->str = str.toAscii();
}
