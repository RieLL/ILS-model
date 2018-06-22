#include "window.h"

Window::Window()
    : posX   { 0 }
    , posY   { 0 }
    , width  { 0 }
    , height { 0 }
{
    //
}

Window::~Window()
{
    //
}

void Window::setPos(const int x, const int y)
{
    this->posX = { x };
    this->posY = { y };
}

void Window::setPosX(const int x)
{
    this->posX = { x };
}

void Window::setPosY(const int y)
{
    this->posY = { y };
}

void Window::setSize(const int width, const int height)
{
    this->width  = { width };
    this->height = { height };
}

void Window::setWidth(const int width)
{
    this->width = { width };
}

void Window::setHeight(const int height)
{
    this->height = { height };
}

int Window::getPosX() const
{
    return { this->posX };
}

int Window::getPosY() const
{
    return { this->posY };
}

int Window::getWidth() const
{
    return { this->width };
}

int Window::getHeight() const
{
    return { this->height };
}
