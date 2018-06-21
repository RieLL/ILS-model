#ifndef SCALE_H
#define SCALE_H

#include <QtGlobal>

class Scale
{
public:
    Scale();
    virtual ~Scale();

    virtual void setScale(const qreal scaleX, const qreal scaleY);
    virtual void setScaleX(const qreal scaleX);
    virtual void setScaleY(const qreal scaleY);

    virtual qreal getScaleX() const;
    virtual qreal getScaleY() const;

protected:
    qreal scaleX;
    qreal scaleY;
};

#endif // SCALE_H
