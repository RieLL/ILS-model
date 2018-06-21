#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>
#include <QPainter>
#include <QPalette>
#include <QPointF>
#include <QMouseEvent>

class Image : public QWidget
{

public:
    Image(QString image, QWidget *parent = 0, int readFlag = 0);
    virtual ~Image();
    void lineConsider(int bank, int pitch);

private:
    const QImage img;
    QImage copyImg;
    QPointF oldPos;
    int x;
    int y;
    int readFlag;
    QLine bankLine;
    QLine pitchLine;

    void consider();

    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // IMAGE_H
