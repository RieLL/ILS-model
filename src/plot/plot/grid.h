#ifndef GRID_H
#define GRID_H

#include "virtual/window.h"
#include "virtual/scale.h"
#include "virtual/hairstroke.h"

#include "variables.h"

class Grid : public Window, public Scale, public Hairstroke
{
public:
    explicit Grid();
    virtual ~Grid();

    void drawElement(QPainter* painter);

    void drawGrid(QPainter* painter);

private:
    Variables* var;

    void addHGrid(QPainter* painter);
    void addVGrid(QPainter* painter);
};

#endif // GRID_H
