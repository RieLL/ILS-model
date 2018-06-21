#ifndef VARIABLES_H
#define VARIABLES_H

#include <QColor>

class Variables
{
public:
    Variables();

    QColor getColorGrid() const;
    QColor getColorAxis() const;
    QColor getColorFunction() const;
    QColor getColorInvelope() const;

private:
    QColor colorGrid;
    QColor colorAxis;
    QColor colorFunction;
    QColor colorInvelope;
};

#endif // VARIABLES_H
