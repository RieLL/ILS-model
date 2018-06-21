#include "function.h"



Function::Function(qreal min, qreal step, qreal max)
    : min  (min)
    , step (step)
    , max  (max)
{
    //
}

Function::~Function()
{
    //
}


QVector<QPointF> Function::functionCos_1(
        qreal m,
        qreal f,
        qreal biasY,
        qreal amplitude)
{
    QVector<QPointF> points;
    points.clear();
    qreal y = 0;

    for(qreal x = min; x < max; x += step)
    {
        y = amplitude * (biasY + m * qCos(f * x));

        //y = biasY + m * qCos(f * x);
        //y = biasY +  m90 * qCos(f90 * x) + m150 * qCos(f150 * x);
        //y = qCos(f * x) + (m90 * qCos(f90 * x) + m150 * qCos(f150 * x)) * qCos(f * x);

        points.append(QPointF(x, y));
    }

    return points;
}

QVector<QPointF> Function::functionCos_2(
        qreal m90,
        qreal f90,
        qreal m150,
        qreal f150,
        qreal biasY,
        qreal amplitude)
{
    QVector<QPointF> points;
    points.clear();

    qreal y = 0;

    for(qreal x = min; x < max; x += step)
    {
        y = amplitude * (biasY +  m90 * qCos(f90 * x) + m150 * qCos(f150 * x));
        points.append(QPointF(x, y));
    }

    return points;
}

QVector<QPointF> Function::functionCos_3(
        qreal m90,
        qreal f90,
        qreal m150,
        qreal f150,
        qreal f,
        qreal amplitude)
{
    QVector<QPointF> points;
    points.clear();

    qreal y = 0;

    for(qreal x = min; x < max; x += step)
    {
        y = amplitude * (qCos(f * x) + (m90 * qCos(f90 * x) + m150 * qCos(f150 * x)) * qCos(f * x));
        points.append(QPointF(x, y));
    }

    return points;
}
