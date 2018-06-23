#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "plot/plotmanager.h"
#include "data.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui { new Ui::MainWindow }

    , krmScheme    (":/res/KRM.png", parent)
    , grmScheme    (":/res/GRM.png", parent)
    , kursMpScheme (":/res/Kurs-MP.png", parent, 1)

    , function (0, 0.01, 9)

    , f90  { 4.8 }
    , f150 { 8.0 }

    , freqKrm { 108.0 }
    , freqGrm { 328.0 }
    , pitch   { 0 }
    , bank    { 0 }
{
    ui->setupUi(this);

    str.append("fн-150");
    str.append("fн-90");
    str.append("fн");
    str.append("fн+90");
    str.append("fн+150");

    init();
    connectSlots();

    ui->krm_scheme->addWidget(&krmScheme);
    ui->grm_scheme->addWidget(&grmScheme);
    ui->kursMp_scheme->addWidget(&kursMpScheme);

    createScene(ui->krm_scene,       krmScene,       ":/res/krm.dat",       parent);
    createScene(ui->grm_scene,       grmScene,       ":/res/grm.dat",       parent);
    createScene(ui->kursMpKrm_scene, kursMpKrmScene, ":/res/kursMpKrm.dat", parent);
    createScene(ui->kursMpGrm_scene, kursMpGrmScene, ":/res/kursMpGrm.dat", parent);

    updateScene_1(krmScene);
    updateScene_1(grmScene);
    updateScene_2(kursMpKrmScene);
    updateScene_2(kursMpGrmScene);
}

MainWindow::~MainWindow()
{
    //
}

void MainWindow::init()
{
    ui->bankLabel->setNum(0);
    ui->pitchLabel->setNum(0);

    ui->scrollArea->setBackgroundRole(QPalette::Base);
    ui->scrollArea_2->setBackgroundRole(QPalette::Base);
    ui->scrollArea_3->setBackgroundRole(QPalette::Base);
    ui->scrollArea_4->setBackgroundRole(QPalette::Base);
}

void MainWindow::connectSlots()
{
    connect(ui->bankSlider, SIGNAL(valueChanged(int)), ui->bankLabel, SLOT(setNum(int)));
    connect(ui->pitchSlider, SIGNAL(valueChanged(int)), ui->pitchLabel, SLOT(setNum(int)));

    connect(ui->bankSlider, SIGNAL(valueChanged(int)), this, SLOT(setBank(int)));
    connect(ui->pitchSlider, SIGNAL(valueChanged(int)), this, SLOT(setPitch(int)));
    connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setFreqKrm(double)));
    connect(ui->doubleSpinBox_2, SIGNAL(valueChanged(double)), this, SLOT(setFreqGrm(double)));
}

void MainWindow::createScene(QLayout* layout,
                             QVector<QSharedPointer<PlotManager>>& plotScene,
                             QString dataFile, QWidget* parent)
{
    Data data(dataFile);

    for (int32_t i = { 0 }; i < data.getData()->length(); i++)
    {
        uint32_t idPlot   = { data.getData()->value(i).idPlot };   // ID графика
        uint32_t idFreq   = { data.getData()->value(i).idFreq };   // ID частоты (КРМ или ГРМ)
        uint32_t cLineH   = { data.getData()->value(i).cLineH };   // Количество линий по горизонтали
        uint32_t cLineV   = { data.getData()->value(i).cLineV };   // Количество линий по вертикали
        uint32_t invelope = { data.getData()->value(i).invelope }; // Добавить огибающую
        uint32_t idAxis   = { data.getData()->value(i).idAxis };   // Добавить ось
        QString namePlot  = { data.getData()->value(i).namePlot }; // Имя графика

        plotScene.append( QSharedPointer<PlotManager>( new PlotManager(parent) ) );

        plotScene.last()->setId(idPlot);
        plotScene.last()->setIdFreq(idFreq);

        plotScene.last()->addGrid(cLineH, cLineV);
        plotScene.last()->addSignature(namePlot);

        if (idPlot == 8 || idPlot == 12)
        {
            plotScene.last()->addSpectrum();
        }
        else
        {
            plotScene.last()->addPlot();
        }

        plotScene.last()->addAxis(static_cast<Axis::PlotAxis>(idAxis));

        if (i > 0)
        {
            plotScene.last()->setMargin(0, 0, 40, 0);
        }

        if (invelope == 1)
        {
            plotScene.last()->addInvelope();
            plotScene.last()->setInvelopeFlag(1);
        }

        layout->addWidget(plotScene.last().get());
    }
}

void MainWindow::updateScene_1(const QVector<QSharedPointer<PlotManager>>& plotScene)
{
    qreal f1 = { 10 * freqKrm - 1065.0 };
    qreal f2 = { 10 * freqGrm - 3260.0 };

    int id = { 0 };
    int invelopeFlag = { 0 };

    for (int i = 0; i < plotScene.length(); i++)
    {
        id = { plotScene.at(i)->getId() };
        invelopeFlag = { plotScene.at(i)->getInvelopeFlag() };

        // IdFreq == 1
        if (plotScene.at(i)->getIdFreq() == 1)
        {
            if (id == 1) // Сигнал на выходе ГВЧ
            {
                f = { function.functionCos_1(1, f1) };
                plotScene.at(i)->setPlot(f);
            }

            if (id == 3) // Сигнал промодулированный частотой "90 Гц"
            {
                f = { function.functionCos_3(0.2, f90, 0.0, 0.0, f1) };
                plotScene.at(i)->setPlot(f);

                if (invelopeFlag == 1)
                {
                    f = { function.functionCos_1(0.2, f90, 1) };
                    plotScene.at(i)->setInvelope(f);
                }
            }

            if (id == 5) // Сигнал промодулированный частотой "150 Гц"
            {
                f = { function.functionCos_3(0.0, 0.0, 0.2, f150, f1) };
                plotScene.at(i)->setPlot(f);

                if (invelopeFlag == 1)
                {
                    f = { function.functionCos_1(0.2, f150, 1) };
                    plotScene.at(i)->setInvelope(f);
                }
            }

            if (id == 6) // Сформированный сигнал
            {
                f = { function.functionCos_3(0.2, f90, 0.2, f150, f1) };
                plotScene.at(i)->setPlot(f);

                if (invelopeFlag == 1)
                {
                    f = { function.functionCos_2(0.2, f90, 0.2, f150, 1) };
                    plotScene.at(i)->setInvelope(f);
                }
            }

            if (id == 8)
            {
                if (plotScene.at(i)->getIdAxis() == 1)
                {
                    strAxis.clear();
                    point.clear();

                    strAxis.append(QString::number(freqKrm, 'f', 2));
                    point.append(5);

                    plotScene.at(i)->setSignatureAxis(point, strAxis);
                }
            }
        }

        // IdFreq == 2
        if (plotScene.at(i)->getIdFreq() == 2)
        {
            if (id == 1) // Сигнал на выходе ГВЧ
            {
                f = { function.functionCos_1(1, f2) };
                plotScene.at(i)->setPlot(f);
            }

            if (id == 3) // Сигнал промодулированный частотой "90 Гц"
            {
                f = { function.functionCos_3(0.2, f90, 0.0, 0.0, f2) };
                plotScene.at(i)->setPlot(f);

                if (invelopeFlag == 1)
                {
                    f = { function.functionCos_1(0.2, f90, 1) };
                    plotScene.at(i)->setInvelope(f);
                }
            }

            if (id == 5) // Сигнал промодулированный частотой "150 Гц"
            {
                f = { function.functionCos_3(0.0, 0.0, 0.2, f150, f2) };
                plotScene.at(i)->setPlot(f);

                if (invelopeFlag == 1)
                {
                    f = { function.functionCos_1(0.2, f150, 1) };
                    plotScene.at(i)->setInvelope(f);
                }
            }

            if (id == 6) // Сформированный сигнал
            {
                f = { function.functionCos_3(0.2, f90, 0.2, f150, f2) };
                plotScene.at(i)->setPlot(f);

                if (invelopeFlag == 1)
                {
                    f = { function.functionCos_2(0.2, f90, 0.2, f150, 1) };
                    plotScene.at(i)->setInvelope(f);
                }
            }

            if (id == 8)
            {
                if (plotScene.at(i)->getIdAxis() > 0)
                {
                    strAxis.clear();
                    point.clear();

                    strAxis.append(QString::number(freqGrm, 'f', 2));
                    strAxis.append("МГц");
                    point.append(5);
                    point.append(11);

                    plotScene.at(i)->setSignatureAxis(point, strAxis);
                }
            }
        }

        if (id == 2) // Модулирующее колебание "90 Гц"
        {
            f = { function.functionCos_1(1, f90) };
            plotScene.at(i)->setPlot(f);
        }

        if (id == 4) // Модулирующее колебание "150 Гц"
        {
            f = { function.functionCos_1(1, f150) };
            plotScene.at(i)->setPlot(f);
        }

        if (id == 8)
        {
            f.clear();
            f.append(QPointF(1, 3));
            f.append(QPointF(3, 3));
            f.append(QPointF(5, 6));
            f.append(QPointF(7, 3));
            f.append(QPointF(9, 3));

            plotScene.at(i)->setSpectrum(f, str);
        }
    }
}

void MainWindow::updateScene_2(const QVector<QSharedPointer<PlotManager>>& plotScene)
{
    qreal f1 = { 10.0 * freqKrm - 1065.0 };
    qreal f2 = { 10.0 * freqGrm - 3260.0 };

    qreal k_bank  = { (bank / 15.0) * 0.2 };
    qreal k_pitch = { (pitch / 8.0) * 0.2 };

    int id = { 0 };
    int invelopeFlag = { 0 };

    kursMpScheme.drawCrossHair(bank, pitch);

    for (int i = {0}; i < plotScene.length(); i++)
    {
        id = { plotScene.at(i)->getId() };
        invelopeFlag = { plotScene.at(i)->getInvelopeFlag() };

        if (plotScene.at(i)->getIdFreq() == 1)
        {
            if (id == 7) // Сигнал на входе антенны приемника ILS
            {
                f = { function.functionCos_3(0.2 - k_bank, f90, 0.2 + k_bank, f150, f1) };
                plotScene.at(i)->setPlot(f);

                if (invelopeFlag == 1)
                {
                    f = { function.functionCos_2(0.2 - k_bank, f90, 0.2 + k_bank, f150, 1) };
                    plotScene.at(i)->setInvelope(f);
                }
            }

            if (id == 9) // Сигнал на выходе амплитудного детектора
            {
                f = { function.functionCos_2(0.2 - k_bank, f90, 0.2 + k_bank, f150, 0, 2.5) };
                plotScene.at(i)->setPlot(f);
            }

            if (id == 10) // Колебание на выходе фильтра "90 Гц"
            {
                f = { function.functionCos_1(0.2 - k_bank, f90, 0, 2.5) };
                plotScene.at(i)->setPlot(f);
            }

            if (id == 11) // Колебание на выходе фильтра "150 Гц"
            {
                f = { function.functionCos_1(0.2 + k_bank, f150, 0, 2.5) };
                plotScene.at(i)->setPlot(f);
            }

            if (id == 12) // Спектр принимаемого сигнала
            {
                qreal k     = { (bank / 15.0) * 2.0 };
                qreal h_90  = { 3.0 - k };
                qreal h_150 = { 3.0 + k };

                f.clear();
                f.append(QPointF(1, h_150));
                f.append(QPointF(3, h_90));
                f.append(QPointF(5, 6));
                f.append(QPointF(7, h_90));
                f.append(QPointF(9, h_150));

                plotScene.at(i)->setSpectrum(f, str);

                if (plotScene.at(i)->getIdAxis() > 0)
                {
                    strAxis.clear();
                    point.clear();

                    strAxis.append(QString::number(freqKrm, 'f', 2));
                    point.append(5);

                    strAxis.append("МГц");
                    point.append(11);

                    plotScene.at(i)->setSignatureAxis(point, strAxis);
                }
            }
        }

        if (plotScene.at(i)->getIdFreq() == 2)
        {
            if (id == 7) // Сигнал на входе антенны приемника ILS
            {
                f = { function.functionCos_3(0.2 + k_pitch, f90, 0.2 - k_pitch, f150, f2) };
                plotScene.at(i)->setPlot(f);

                if (invelopeFlag == 1)
                {
                    f = { function.functionCos_2(0.2 + k_pitch, f90, 0.2 - k_pitch, f150, 1) };
                    plotScene.at(i)->setInvelope(f);
                }
            }

            if (id == 9) // Сигнал на выходе амплитудного детектора
            {
                f = { function.functionCos_2(0.2 + k_pitch, f90, 0.2 - k_pitch, f150, 0, 2.5) };
                plotScene.at(i)->setPlot(f);
            }

            if (id == 10) // Колебание на выходе фильтра "90 Гц"
            {
                f = { function.functionCos_1(0.2 + k_pitch, f90, 0, 2.5) };
                plotScene.at(i)->setPlot(f);
            }

            if (id == 11) // Колебание на выходе фильтра "150 Гц"
            {
                f = { function.functionCos_1(0.2 - k_pitch, f150, 0, 2.5) };
                plotScene.at(i)->setPlot(f);
            }

            if (id == 12) // Спектр принимаемого сигнала
            {
                qreal k     = { (pitch / 8.0) * 2.0 };
                qreal h_90  = { 3.0 + k };
                qreal h_150 = { 3.0 - k };

                f.clear();
                f.append(QPointF(1, h_150));
                f.append(QPointF(3, h_90));
                f.append(QPointF(5, 6));
                f.append(QPointF(7, h_90));
                f.append(QPointF(9, h_150));

                plotScene.at(i)->setSpectrum(f, str);

                if (plotScene.at(i)->getIdAxis() > 0)
                {
                    strAxis.clear();
                    point.clear();

                    strAxis.append(QString::number(freqGrm, 'f', 2));
                    point.append(5);

                    strAxis.append("МГц");
                    point.append(11);

                    plotScene.at(i)->setSignatureAxis(point, strAxis);
                }
            }
        }
    }
}

// public slots
void MainWindow::setFreqKrm(double freqKrm)
{
    this->freqKrm = { freqKrm };
    updateScene_1(krmScene);
    updateScene_2(kursMpKrmScene);
}

void MainWindow::setFreqGrm(double freqGrm)
{
    this->freqGrm = { freqGrm };
    updateScene_1(grmScene);
    updateScene_2(kursMpGrmScene);
}

void MainWindow::setPitch(int pitch)
{
    this->pitch = { pitch };
    updateScene_2(kursMpGrmScene);
}

void MainWindow::setBank(int bank)
{
    this->bank = { bank };
    updateScene_2(kursMpKrmScene);
}
// end public slots
