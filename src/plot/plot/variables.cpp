#include "variables.h"

Variables::Variables()
    : colorGrid     ( 20,  20,  20, 127)
    , colorAxis     (  0,   0,   0, 255)
    , colorFunction ( 48, 165, 255, 255)
    , colorInvelope (255, 114, 243, 255)
{
    //
}

QColor& Variables::getColorGrid()
{
    return { colorGrid };
}

QColor& Variables::getColorAxis()
{
    return { colorAxis };
}

QColor& Variables::getColorFunction()
{
    return { colorFunction };
}

QColor& Variables::getColorInvelope()
{
    return { colorInvelope };
}
