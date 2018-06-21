#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <QByteArray>
#include <QTextCodec>
#include "virtual/window.h"
#include "virtual/mainparameters.h"

class Signature : public Window, public MainParameters
{
public:
    Signature();
    virtual ~Signature();

    void drawElement(QPainter* painter);
    void setText(const QString str);

private:
    QByteArray str;
};

#endif // SIGNATURE_H
