#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <QTextCodec>

#include "../plot.h"

class Spectrum : public Plot
{
public:
    Spectrum(const QColor color);
    virtual ~Spectrum();

    void drawElement(QPainter* painter);
};

#endif // SPECTRUM_H
