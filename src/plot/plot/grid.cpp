#include "grid.h"
#include "variables.h"

Grid::Grid()
    : Window()
    , Scale()
    , Hairstroke()
    , var { new Variables }
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
    painter->drawRect(Window::posX, Window::posY, Window::width, Window::height);

    addHGrid(painter);
    addVGrid(painter);
}

void Grid::addHGrid(QPainter* painter)
{
    qreal x1 = { static_cast<qreal>(Window::posX) };
    qreal x2 = { Window::width + x1 };
    qreal y  = { 0.0 };

    for (int i = 1; i < (Hairstroke::countHLines - 1); ++i)
    {
        y = { i * Scale::scaleY + Window::posY };

        painter->drawLine(QLineF(x1, y, x2, y));
    }
}

void Grid::addVGrid(QPainter* painter)
{
    qreal x  = { 0.0 };
    qreal y1 = { static_cast<qreal>(Window::posY) };
    qreal y2 = { Window::height + y1 };

    for (int i = 1; i < (Hairstroke::countVLines - 1); ++i)
    {
        x = { i * Scale::scaleX + Window::posX };

        painter->drawLine(QLineF(x, y1, x, y2));
    }
}
