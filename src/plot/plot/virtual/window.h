#ifndef WINDOW_H
#define WINDOW_H

#include <QPainter>

class Window
{
public:
    Window();
    virtual ~Window();

    virtual void drawElement(QPainter* painter) = 0;

    virtual void setPos(const int x, const int y);
    virtual void setPosX(const int x);
    virtual void setPosY(const int y);
    virtual void setSize(const int width, const int height);
    virtual void setWidth(const int width);
    virtual void setHeight(const int height);

    virtual int  getPosX() const;
    virtual int  getPosY() const;
    virtual int  getWidth() const;
    virtual int  getHeight() const;

protected:
    int posX;
    int posY;
    int width;
    int height;
};

#endif // WINDOW_H
