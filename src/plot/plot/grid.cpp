#include "grid.h"

Grid::Grid() : Window(), Scale(), Hairstroke(),
    var(new Variables)
{
    //
}

Grid::~Grid()
{
    delete var;
}



void Grid::drawElement(QPainter* painter)
{
    drawGrid(painter);
}



void Grid::drawGrid(QPainter* painter)
{
    painter->setPen(QPen(var->getColorGrid(), 1, Qt::DotLine));
    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->drawRect(posX, posY, width, height);

    addHGrid(painter);
    addVGrid(painter);
}



void Grid::addHGrid(QPainter* painter)
{
    qreal x1 = posX;
    qreal x2 = width + x1;
    qreal y = 0.0;

    for (int i = 1; i < (countHLines - 1); ++i)
    {
        y = (i * scaleY) + posY;

        painter->drawLine(QLineF(x1, y, x2, y));
    }
}

void Grid::addVGrid(QPainter* painter)
{
    qreal x = 0.0;
    qreal y1 = posY;
    qreal y2 = height + y1;

    for (int i = 1; i < (countVLines - 1); ++i)
    {
        x = (i * scaleX) + posX;

        painter->drawLine(QLineF(x, y1, x, y2));
    }
}
