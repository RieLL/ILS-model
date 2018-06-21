#include "variables.h"

Variables::Variables() :
    colorGrid(20, 20, 20, 127),
    colorAxis(0, 0, 0, 255),
    colorFunction(48, 165, 255, 255),
    colorInvelope(255, 114, 243, 255)
{
//    const ;
//    const ;
//    const ;
//    const ;
}



QColor Variables::getColorGrid() const
{
    return colorGrid;
}

QColor Variables::getColorAxis() const
{
    return colorAxis;
}

QColor Variables::getColorFunction() const
{
    return colorFunction;
}

QColor Variables::getColorInvelope() const
{
    return colorInvelope;
}
