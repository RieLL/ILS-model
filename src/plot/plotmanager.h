#ifndef PLOTMANAGER_H
#define PLOTMANAGER_H

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QColor>

#include "plot/axis.h"
#include "plot/grid.h"
#include "plot/signature.h"

#include "plot/plot.h"
#include "plot/plotTypes/dots.h"
#include "plot/plotTypes/spectrum.h"



class PlotManager : public QWidget
{
    Q_OBJECT

public:
    PlotManager(QWidget* parent = 0);
    virtual ~PlotManager();

    void setId(const int id);
    int  getId() const;
    void setIdFreq(const int idFreq);
    int  getIdFreq() const;
    void setInvelopeFlag(const int invelopeFlag);
    int  getInvelopeFlag() const;

    void addAxis(const Axis::PlotAxis axis);
    int  getIdAxis() const;
    void setSignatureAxis(const QVector<qreal>& point, const QVector<QString>& str);
    void addGrid(const int countHLine, const int countVLine);
    void addSignature(const QString str);
    void addPlot();
    void setPlot(const QVector<QPointF>& plotPoints);
    void addInvelope();
    void setInvelope(const QVector<QPointF>& invelopePoints);
    void addSpectrum();
    void setSpectrum(const QVector<QPointF>& spectrumPoints, const QVector<QString>& str);

    void setMargin(const int left, const int right, const int top, const int buttom);
    void setCountLines(const int countHLine, const int countVLine);

//public slots:
//    void setFreqKrm(double freqKrm);
//    void setFreqGrm(double freqGrm);
//    void setPitch(int pitch);
//    void setBank(int bank);

protected:
    virtual void paintEvent(QPaintEvent*);
    virtual void resizeEvent(QResizeEvent* event);

private:
    int countHLines;
    int countVLines;

    int idPlot;
    int idFreq;
    int invelopeFlag;
    int idAxis;

    int marginTop;
    int marginButtom;
    int marginLeft;
    int marginRight;

    Axis* axisX;
    Axis* axisY;
    Grid* grid;
    Signature* signature;

    QColor colorFunction;
    QColor colorInvelope;

    QVector<Plot*> plots;

    void consider();
};

#endif // PLOTMANAGER_H
