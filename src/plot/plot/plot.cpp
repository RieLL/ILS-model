#include "plot.h"

Plot::Plot(const QColor color) :
    Window(), Scale(), MainParameters(), Hairstroke(),
    color(color)
{
    //
}

Plot::~Plot()
{
    //
}



void Plot::setPlot(const QVector<QPointF>& plotPoints)
{
    this->plotPoints = plotPoints;
}

void Plot::setSignature(const QVector<QString>& str)
{
    this->str = str;
}
