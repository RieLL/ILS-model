#ifndef AXIS_H
#define AXIS_H

#include <QVector>
#include <QPointF>
#include <QString>

#include "virtual/window.h"
#include "virtual/scale.h"
#include "virtual/hairstroke.h"

#include "variables.h"

class Axis : public Window, public Scale, public Hairstroke
{
public:
    typedef enum {Off, X, Y, All} PlotAxis;

    explicit Axis();
    virtual ~Axis();

    virtual void drawElement(QPainter* painter);

    void setAxis(PlotAxis axis);
    void setSignatureAxis(const QVector<qreal>& point, const QVector<QString>& str);

private:
    PlotAxis axis;
    Variables* var;
    QVector<qreal> point;
    QVector<QString> str;

    void axisButtom(QPainter* painter);
    void axisLeft(QPainter* painter);
    void drawSignature(QPainter* painter);
};

#endif // AXIS_H
