#ifndef VARIABLES_H
#define VARIABLES_H

#include <QColor>

class Variables
{
public:
    Variables();

    QColor& getColorGrid();
    QColor& getColorAxis();
    QColor& getColorFunction();
    QColor& getColorInvelope();

private:
    QColor colorGrid;
    QColor colorAxis;
    QColor colorFunction;
    QColor colorInvelope;
};

#endif // VARIABLES_H
