#ifndef DOTS_H
#define DOTS_H

#include "../plot.h"

class Dots : public Plot
{
public:
    Dots(const QColor color);
    virtual ~Dots();

    void drawElement(QPainter* painter);
};

#endif // DOTS_H
