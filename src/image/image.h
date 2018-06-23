#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>
#include <QPalette>
#include <QPointF>
#include <QMouseEvent>

class Image : public QWidget
{

public:
    explicit Image(QString pathToImage, QWidget *parent = 0, int readFlag = 0);
    virtual ~Image();
    void drawCrossHair(int bank, int pitch);

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

    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
};

#endif // IMAGE_H
