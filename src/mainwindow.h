#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "image/image.h"
#include "function/function.h"

#include <QMainWindow>
#include <QVector>
#include <QPointF>
#include <QSharedPointer>

class PlotManager;

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    enum {idKrm = 0, idGrm, idKursMpKrm, idKursMpGrm};

signals:

private slots:
    void setFreqKrm(double freqKrm);
    void setFreqGrm(double freqGrm);
    void setPitch(int pitch);
    void setBank(int bank);

private:
    QSharedPointer<Ui::MainWindow> ui;

    Image krmScheme;
    Image grmScheme;
    Image kursMpScheme;

    Function function;

    qreal f90;
    qreal f150;

    double freqKrm;
    double freqGrm;
    int pitch;
    int bank;

    QVector<QSharedPointer<PlotManager>> krmScene;
    QVector<QSharedPointer<PlotManager>> grmScene;
    QVector<QSharedPointer<PlotManager>> kursMpKrmScene;
    QVector<QSharedPointer<PlotManager>> kursMpGrmScene;

    QVector<QPointF> f;
    QVector<QString> str;

    QVector<QString> strAxis;
    QVector<qreal> point;

    void init();
    void connectSlots();

    void generateFunction();
    void updateFunction();

    void createScene(QLayout* layout,
                     QVector<QSharedPointer<PlotManager>>& plotScene,
                     QString dataFile, QWidget *parent = 0);

    void updateScene_1(const QVector<QSharedPointer<PlotManager>>& plotScene);
    void updateScene_2(const QVector<QSharedPointer<PlotManager>>& plotScene);
};

#endif // MAINWINDOW_H
