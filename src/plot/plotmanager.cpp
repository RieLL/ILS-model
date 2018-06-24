#include "plotmanager.h"
#include <QByteArray>
#include <QDebug>

PlotManager::PlotManager(QWidget* parent)
    : QWidget ( parent )
    , countHLines { 0 }
    , countVLines { 0 }

    , idPlot       { 0 }
    , idFreq       { 0 }
    , invelopeFlag { 0 }
    , idAxis       { 0 }

    , marginTop    { 0 }
    , marginButtom { 0 }
    , marginLeft   { 0 }
    , marginRight  { 0 }

    , axisX     { nullptr }
    , axisY     { nullptr }
    , grid      { nullptr }
    , signature { nullptr }

    , colorFunction ( 48, 165, 255, 255)
    , colorInvelope (255, 114, 243, 255)
{
    //
}

PlotManager::~PlotManager()
{
    if (axisX)     { delete axisX; }
    if (axisY)     { delete axisY; }
    if (grid)      { delete grid; }
    if (signature) { delete signature; }

    for(Plot* plot : plots)
    {
        delete plot;
    }

    plots.erase(plots.begin(), plots.end());
}

void PlotManager::setId(int id)
{
    this->idPlot = { id };
}

int PlotManager::getId() const
{
    return { this->idPlot };
}

void PlotManager::setIdFreq(int idFreq)
{
    this->idFreq = { idFreq };
}

int PlotManager::getIdFreq() const
{
    return { this->idFreq };
}

void PlotManager::setInvelopeFlag(int invelopeFlag)
{
    this->invelopeFlag = { invelopeFlag };
}

int PlotManager::getInvelopeFlag() const
{
    return { this->invelopeFlag };
}

void PlotManager::addAxis(Axis::PlotAxis axis)
{
    if (axis == Axis::Off)
    {
        idAxis = { 0 };

        if (axisX) { delete axisX; }
        if (axisY) { delete axisY; }
    }

    if (axis == Axis::X)
    {
        idAxis = { 1 };

        if (!axisX)
        {
            axisX = { new Axis() };
            axisX->setAxis(Axis::X);
        }
    }

    if (axis == Axis::Y)
    {
        idAxis = { 1 };

        if (!axisY)
        {
            axisY = { new Axis() };
            axisY->setAxis(Axis::Y);
        }
   }

    if(axis == Axis::All)
    {
        idAxis = { 1 };

        if (!axisX)
        {
            axisX = { new Axis() };
            axisX->setAxis(Axis::X);
        }

        if (!axisY)
        {
            axisY = { new Axis() };
            axisY->setAxis(Axis::Y);
        }
    }
}

int PlotManager::getIdAxis() const
{
    return { this->idAxis };
}

void PlotManager::setSignatureAxis(const QVector<qreal>& point, const QVector<QString>& str)
{
    if (axisX)
    {
        axisX->setSignatureAxis(point, str);
        repaint();
    }
}

void PlotManager::addGrid(const int countHLine, const int countVLine)
{
    setCountLines(countHLine, countVLine);
    if (!grid)
    {
        grid = { new Grid() };
    }
}

void PlotManager::addSignature(const QString str)
{
    if (!signature)
    {
        signature = { new Signature() };
        signature->setText(str);
    }
    else
    {
        signature->setText(str);
    }
}

void PlotManager::addPlot()
{
    plots.append( new Dots(colorFunction) );
}

void PlotManager::setPlot(const QVector<QPointF>& plotPoints)
{
    plots.at(0)->setPlot(plotPoints);
    repaint();
}

void PlotManager::addInvelope()
{
    plots.append( new Dots(colorInvelope) );
    plots.append( new Dots(colorInvelope) );
}

void PlotManager::setInvelope(const QVector<QPointF>& invelopePoints)
{
    QVector<QPointF> point;

    for(QPointF i : invelopePoints)
    {
        point.append( QPointF(i.x(), i.y() * (-1)) );
    }

    plots.at(1)->setPlot(invelopePoints);
    plots.at(2)->setPlot(point);

    repaint();
}

void PlotManager::addSpectrum()
{
    plots.append( new Spectrum(colorFunction) );
}

void PlotManager::setSpectrum(const QVector<QPointF>& spectrumPoints, const QVector<QString>& str)
{
    plots.at(0)->setPlot(spectrumPoints);
    plots.at(0)->setSignature(str);
    repaint();
}

void PlotManager::setMargin(const int left, const int right, const int top, const int buttom)
{
    this->marginLeft   = { left };
    this->marginRight  = { right };
    this->marginTop    = { top };
    this->marginButtom = { buttom };
    update();
}

void PlotManager::setCountLines(const int countHLines, const int countVLines)
{
    this->countHLines = { countHLines };
    this->countVLines = { countVLines };
}

void PlotManager::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    if (signature) { signature->drawElement(&painter); }
    if (grid)      { grid->drawElement(&painter); }
    if (axisX)     { axisX->drawElement(&painter); }
    if (axisY)     { axisY->drawElement(&painter); }

    for (Plot* i : plots)
    {
        i->drawElement(&painter);
    }

    painter.end();
}

void PlotManager::resizeEvent(QResizeEvent*)
{
    setFixedHeight( 0.5 * (width() - 1) + marginTop + marginButtom );

    consider();
}

void PlotManager::consider()
{
    qreal scaleX = { 0.0 };
    qreal scaleY = { 0.0 };

    int smallAxisSizeX     = { 30 };
    int smallAxisSizeY     = { 5 };
    int smallSignatureSize = { 40 };
    int margin             = { 5 };

    qreal x = { 0 };
    qreal y = { 0 };
    qreal w = { 0 };
    qreal h = { 0 };

    if (!axisX) { smallAxisSizeX = { 0 }; }

    if (!axisY) { smallAxisSizeY = { 0 }; }

    if (signature)
    {
        x = { static_cast<qreal>(smallAxisSizeY + margin + marginLeft) };
        y = { static_cast<qreal>(marginTop + margin) };
        w = { static_cast<qreal>(width() - x - margin - marginRight) };
        h = { static_cast<qreal>(smallSignatureSize) };

        signature->setPos(x, y);
        signature->setSize(w, h);

        smallSignatureSize += y;
    }
    else
    {
        smallSignatureSize = { marginTop };
    }

    // consider scale
    if (width() > 0)
    {
        w ={ static_cast<qreal>(width() - (smallAxisSizeY + margin) - (marginLeft + marginRight)) };

        if (countVLines <= 1)
        {
            countVLines = { 2 };
            scaleX = { w };
        }
        else
        {
            scaleX = { w / (countVLines - 1) };
        }
    }

    if (height() > 0)
    {
        h = height() - (smallSignatureSize + smallAxisSizeX + margin);

        if (countHLines <= 1)
        {
            countHLines = { 2 };
            scaleY = { h };
        }
        else
        {
            scaleY = { h / (countHLines - 1) };
        }
    }

    if (axisX)
    {
        x = { static_cast<qreal>(smallAxisSizeY + margin + marginLeft) };
        y = { static_cast<qreal>(height() - smallAxisSizeX - marginButtom) };
        w = { static_cast<qreal>(width() - margin - marginRight) };
        h = { static_cast<qreal>(smallAxisSizeX) };

        axisX->setCountLines(countHLines, countVLines);
        axisX->setPos(x, y);
        axisX->setSize(w, h);
        axisX->setScale(scaleX, scaleY);
    }

    if (axisY)
    {
        x = { static_cast<qreal>(marginLeft) };
        y = { static_cast<qreal>(smallSignatureSize + margin) };
        w = { static_cast<qreal>(smallAxisSizeY) };
        h = { static_cast<qreal>(height() - smallAxisSizeX - margin - marginButtom) };

        axisY->setCountLines(countHLines, countVLines);
        axisY->setPos(x, y);
        axisY->setSize(w, h);
        axisY->setScaleY(scaleY);
    }

    if (grid)
    {
        x = { static_cast<qreal>(marginLeft + smallAxisSizeY + margin) };
        y = { static_cast<qreal>(smallSignatureSize + margin) };
        w = { static_cast<qreal>(width() - x - margin - marginRight) };
        h = { static_cast<qreal>(height() - y - margin - smallAxisSizeX - marginButtom) };


        grid->setCountLines(countHLines, countVLines);
        grid->setPos(x, y);
        grid->setSize(w, h);
        grid->setScale(scaleX, scaleY);
    }

    for(Plot* plot : plots)
    {
        x = { static_cast<qreal>(grid->getPosX()) };
        y = { static_cast<qreal>(grid->getPosY() + 1) };

        plot->setCountLines(countHLines, countVLines);
        plot->setPos(x, y);
        plot->setSize(grid->getWidth(), grid->getHeight());
        plot->setScale(scaleX, scaleY);
    }

    update();
}
