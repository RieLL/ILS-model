#ifndef FUNCTION_H
#define FUNCTION_H

#include <QVector>
#include <QPointF>
#include <qmath.h>


class Function
{
public:
    Function(qreal min, qreal step, qreal max);
    ~Function();

    QVector<QPointF> functionCos_1(
            qreal m,
            qreal f,
            qreal biasY = 0.0,
            qreal amplitude = 1.0);

    QVector<QPointF> functionCos_2(
            qreal m90,
            qreal f90,
            qreal m150,
            qreal f150,
            qreal biasY = 0.0,
            qreal amplitude = 1.0);

    QVector<QPointF> functionCos_3(
            qreal m90,
            qreal f90,
            qreal m150,
            qreal f150,
            qreal f,
            qreal amplitude = 1.0);

private:
    qreal min;
    qreal step;
    qreal max;
};

#endif // FUNCTION_H
