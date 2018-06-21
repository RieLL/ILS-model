#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPointF>

#include "image/image.h"
#include "plot/plotmanager.h"

#include "data.h"
#include "function/function.h"



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
    Ui::MainWindow* ui;

    Image* krmScheme;
    Image* grmScheme;
    Image* kursMpScheme;

    Function *function;

    qreal f90;
    qreal f150;

    double freqKrm;
    double freqGrm;
    int pitch;
    int bank;

    QVector<PlotManager*> krmScene;
    QVector<PlotManager*> grmScene;
    QVector<PlotManager*> kursMpKrmScene;
    QVector<PlotManager*> kursMpGrmScene;

    QVector<QPointF> f;
    QVector<QString> str;

    QVector<QString> strAxis;
    QVector<qreal> point;

    void init();
    void connectSlots();

    void generateFunction();
    void updateFunction();

    void createScene(QLayout* layout, QVector<PlotManager*>& plotScene,
                   QString dataFile, QWidget *parent = 0);

    void deleteScene(QVector<PlotManager*>& plotScene);
    void updateScene_1(const QVector<PlotManager*>& plotScene);
    void updateScene_2(const QVector<PlotManager*>& plotScene);
};

#endif // MAINWINDOW_H
