#ifndef PLOT_H
#define PLOT_H

#include "virtual/window.h"
#include "virtual/scale.h"
#include "virtual/mainparameters.h"
#include "virtual/hairstroke.h"

#include <QVector>
#include <QPointF>
#include <QColor>

#include "../../function/function.h"

class Plot : public Window, public Scale, public MainParameters, public Hairstroke
{
public:
    explicit Plot(const QColor color);
    virtual ~Plot();

    void setPlot(const QVector<QPointF>& plotPoints);
    void setSignature(const QVector<QString>& str);

protected:
    QVector<QPointF> plotPoints;
    QVector<QString> str;
    QColor color;
};

#endif // PLOT_H
