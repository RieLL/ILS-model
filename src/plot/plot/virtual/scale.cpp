#include "scale.h"

Scale::Scale()
    : scaleX(0)
    , scaleY(0)
{
    //
}

Scale::~Scale()
{
    //
}

void Scale::setScale(const qreal scaleX, const qreal scaleY)
{
    this->scaleX = scaleX;
    this->scaleY = scaleY;
}

void Scale::setScaleX(const qreal scaleX)
{
    this->scaleX = scaleX;
}

void Scale::setScaleY(const qreal scaleY)
{
    this->scaleY = scaleY;
}

qreal Scale::getScaleX() const
{
    return this->scaleX;
}

qreal Scale::getScaleY() const
{
    return this->scaleY;
}
