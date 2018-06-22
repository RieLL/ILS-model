#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent),
    ui(new Ui::MainWindow),

    krmScheme(new Image(":/res/KRM.png", parent)),
    grmScheme(new Image(":/res/GRM.png", parent)),
    kursMpScheme(new Image(":/res/Kurs-MP.png", parent, 1)),

    function(new Function(0, 0.01, 9)),

    f90(4.8),
    f150(8.0),

    freqKrm(108.0),
    freqGrm(328.0),
    pitch(0),
    bank(0)
{
    ui->setupUi(this);

    str.append("f�-150");
    str.append("f�-90");
    str.append("f�");
    str.append("f�+90");
    str.append("f�+150");

    init();
    connectSlots();

    ui->krm_scheme->addWidget(krmScheme);
    ui->grm_scheme->addWidget(grmScheme);
    ui->kursMp_scheme->addWidget(kursMpScheme);

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
    delete ui;
    delete krmScheme;
    delete grmScheme;
    delete kursMpScheme;
    delete function;

    deleteScene(krmScene);
    deleteScene(grmScene);
    deleteScene(kursMpKrmScene);
    deleteScene(kursMpGrmScene);
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

void MainWindow::createScene(QLayout* layout, QVector<PlotManager*>& plotScene,
                             QString dataFile, QWidget* parent)
{
    Data data(dataFile);

    int idPlot   = 0;
    int idFreq   = 0;
    int cLineH   = 0;
    int cLineV   = 0;
    int invelope = 0;
    int idAxis   = 0;
    QString namePlot = "\0";

    for (int i = 0; i < data.line(); ++i)
    {
        idPlot   = data.readData(i, 0).toInt();   // ID �������
        idFreq   = data.readData(i, 1).toInt();   // ID ������� (��� ��� ���)
        cLineH   = data.readData(i, 2).toInt();   // ���������� ����� �� �����������
        cLineV   = data.readData(i, 3).toInt();   // ���������� ����� �� ���������
        invelope = data.readData(i, 4).toInt();   // �������� ���������
        idAxis   = data.readData(i, 5).toInt();   // �������� ���
        namePlot = data.readData(i, 6); // ��� �������

        plotScene.append(new PlotManager(parent));

        plotScene.last()->setId(idPlot);
        plotScene.last()->setIdFreq(idFreq);

        plotScene.last()->addGrid(cLineH, cLineV);
        plotScene.last()->addSignature(namePlot);

        if ((idPlot == 8) || (idPlot == 12))
        {
            plotScene.last()->addSpectrum();
        }
        else
        {
            plotScene.last()->addPlot();
        }

        plotScene.last()->addAxis((Axis::PlotAxis)idAxis);

        if (i > 0)
        {
            plotScene.last()->setMargin(0, 0, 40, 0);
        }

        if(invelope == 1)
        {
            plotScene.last()->addInvelope();
            plotScene.last()->setInvelopeFlag(1);
        }

        layout->addWidget(plotScene.last());
    }
}

void MainWindow::updateScene_1(const QVector<PlotManager*>& plotScene)
{
    qreal f1 = (10 * freqKrm) - 1065.0;
    qreal f2 = (10 * freqGrm) - 3260.0;

    int id = 0;
    int invelopeFlag = 0;

    for (PlotManager* pm : plotScene)
    {
        id = pm->getId();
        invelopeFlag = pm->getInvelopeFlag();

        // IdFreq == 1
        if (pm->getIdFreq() == 1)
        {
            if (id == 1) // ������ �� ������ ���
            {
                f = function->functionCos_1(1, f1);
                pm->setPlot(f);
            }

            if (id == 3) // ������ ����������������� �������� "90 ��"
            {
                f = function->functionCos_3(0.2, f90, 0.0, 0.0, f1);
                pm->setPlot(f);

                if (invelopeFlag == 1)
                {
                    f = function->functionCos_1(0.2, f90, 1);
                    pm->setInvelope(f);
                }
            }

            if (id == 5) // ������ ����������������� �������� "150 ��"
            {
                f = function->functionCos_3(0.0, 0.0, 0.2, f150, f1);
                pm->setPlot(f);

                if (invelopeFlag == 1)
                {
                    f = function->functionCos_1(0.2, f150, 1);
                    pm->setInvelope(f);
                }
            }

            if (id == 6) // �������������� ������
            {
                f = function->functionCos_3(0.2, f90, 0.2, f150, f1);
                pm->setPlot(f);

                if (invelopeFlag == 1)
                {
                    f = function->functionCos_2(0.2, f90, 0.2, f150, 1);
                    pm->setInvelope(f);
                }
            }

            if (id == 8)
            {
                if (pm->getIdAxis() == 1)
                {
                    strAxis.clear();
                    point.clear();

                    strAxis.append(QString::number(freqKrm, 'f', 2));
                    point.append(5);

                    pm->setSignatureAxis(point, strAxis);
                }
            }
        }

        // IdFreq == 2
        if (pm->getIdFreq() == 2)
        {
            if (id == 1) // ������ �� ������ ���
            {
                f = function->functionCos_1(1, f2);
                pm->setPlot(f);
            }

            if (id == 3) // ������ ����������������� �������� "90 ��"
            {
                f = function->functionCos_3(0.2, f90, 0.0, 0.0, f2);
                pm->setPlot(f);

                if (invelopeFlag == 1)
                {
                    f = function->functionCos_1(0.2, f90, 1);
                    pm->setInvelope(f);
                }
            }

            if (id == 5) // ������ ����������������� �������� "150 ��"
            {
                f = function->functionCos_3(0.0, 0.0, 0.2, f150, f2);
                pm->setPlot(f);

                if (invelopeFlag == 1)
                {
                    f = function->functionCos_1(0.2, f150, 1);
                    pm->setInvelope(f);
                }
            }

            if (id == 6) // �������������� ������
            {
                f = function->functionCos_3(0.2, f90, 0.2, f150, f2);
                pm->setPlot(f);

                if (invelopeFlag == 1)
                {
                    f = function->functionCos_2(0.2, f90, 0.2, f150, 1);
                    pm->setInvelope(f);
                }
            }

            if (id == 8)
            {
                if (pm->getIdAxis() > 0)
                {
                    strAxis.clear();
                    point.clear();

                    strAxis.append(QString::number(freqGrm, 'f', 2));
                    strAxis.append("���");
                    point.append(5);
                    point.append(11);

                    pm->setSignatureAxis(point, strAxis);
                }
            }
        }

        if (id == 2) // ������������ ��������� "90 ��"
        {
            f = function->functionCos_1(1, f90);
            pm->setPlot(f);
        }

        if (id == 4) // ������������ ��������� "150 ��"
        {
            f = function->functionCos_1(1, f150);
            pm->setPlot(f);
        }

        if (id == 8)
        {
            f.clear();
            f.append(QPointF(1, 3));
            f.append(QPointF(3, 3));
            f.append(QPointF(5, 6));
            f.append(QPointF(7, 3));
            f.append(QPointF(9, 3));

            pm->setSpectrum(f, str);
        }
    }
}

void MainWindow::updateScene_2(const QVector<PlotManager*>& plotScene)
{
    qreal f1 = (10.0 * freqKrm) - 1065.0;
    qreal f2 = (10.0 * freqGrm) - 3260.0;

    qreal k_bank  = (bank / 15.0) * 0.2;
    qreal k_pitch = (pitch / 8.0) * 0.2;

    int id = 0;
    int invelopeFlag = 0;

    kursMpScheme->lineConsider(bank, pitch);

    for (PlotManager* pm : plotScene)
    {        
        id = pm->getId();
        invelopeFlag = pm->getInvelopeFlag();

        if (pm->getIdFreq() == 1)
        {
            if (id == 7) // ������ �� ����� ������� ��������� ILS
            {
                f = function->functionCos_3(0.2 - k_bank, f90, 0.2 + k_bank, f150, f1);
                pm->setPlot(f);

                if (invelopeFlag == 1)
                {
                    f = function->functionCos_2(0.2 - k_bank, f90, 0.2 + k_bank, f150, 1);
                    pm->setInvelope(f);
                }
            }

            if (id == 9) // ������ �� ������ ������������ ���������
            {
                f = function->functionCos_2(0.2 - k_bank, f90, 0.2 + k_bank, f150, 0, 2.5);
                pm->setPlot(f);
            }

            if (id == 10) // ��������� �� ������ ������� "90 ��"
            {
                f = function->functionCos_1(0.2 - k_bank, f90, 0, 2.5);
                pm->setPlot(f);
            }

            if (id == 11) // ��������� �� ������ ������� "150 ��"
            {
                f = function->functionCos_1(0.2 + k_bank, f150, 0, 2.5);
                pm->setPlot(f);
            }

            if (id == 12) // ������ ������������ �������
            {
                qreal k     = (bank / 15.0) * 2;
                qreal h_90  = 3 - k;
                qreal h_150 = 3 + k;

                f.clear();
                f.append(QPointF(1, h_150));
                f.append(QPointF(3, h_90));
                f.append(QPointF(5, 6));
                f.append(QPointF(7, h_90));
                f.append(QPointF(9, h_150));

                pm->setSpectrum(f, str);

                if (pm->getIdAxis() > 0)
                {
                    strAxis.clear();
                    point.clear();

                    strAxis.append(QString::number(freqKrm, 'f', 2));
                    point.append(5);

                    strAxis.append("���");
                    point.append(11);

                    pm->setSignatureAxis(point, strAxis);
                }
            }
        }

        if (pm->getIdFreq() == 2)
        {
            if (id == 7) // ������ �� ����� ������� ��������� ILS
            {
                f = function->functionCos_3(0.2 + k_pitch, f90, 0.2 - k_pitch, f150, f2);
                pm->setPlot(f);

                if (invelopeFlag == 1)
                {
                    f = function->functionCos_2(0.2 + k_pitch, f90, 0.2 - k_pitch, f150, 1);
                    pm->setInvelope(f);
                }
            }

            if (id == 9) // ������ �� ������ ������������ ���������
            {
                f = function->functionCos_2(0.2 + k_pitch, f90, 0.2 - k_pitch, f150, 0, 2.5);
                pm->setPlot(f);
            }

            if (id == 10) // ��������� �� ������ ������� "90 ��"
            {
                f = function->functionCos_1(0.2 + k_pitch, f90, 0, 2.5);
                pm->setPlot(f);
            }

            if (id == 11) // ��������� �� ������ ������� "150 ��"
            {
                f = function->functionCos_1(0.2 - k_pitch, f150, 0, 2.5);
                pm->setPlot(f);
            }

            if (id == 12) // ������ ������������ �������
            {
                qreal k     = (pitch / 8.0) * 2;
                qreal h_90  = 3 + k;
                qreal h_150 = 3 - k;

                f.clear();
                f.append(QPointF(1, h_150));
                f.append(QPointF(3, h_90));
                f.append(QPointF(5, 6));
                f.append(QPointF(7, h_90));
                f.append(QPointF(9, h_150));

                pm->setSpectrum(f, str);

                if (pm->getIdAxis() > 0)
                {
                    strAxis.clear();
                    point.clear();

                    strAxis.append(QString::number(freqGrm, 'f', 2));
                    point.append(5);

                    strAxis.append("���");
                    point.append(11);

                    pm->setSignatureAxis(point, strAxis);
                }
            }
        }
    }
}

void MainWindow::deleteScene(QVector<PlotManager*>& plotScene)
{
    for (PlotManager* pm : plotScene)
    {
        delete pm;
    }

    plotScene.erase(plotScene.begin(), plotScene.end());
}

// public slots
void MainWindow::setFreqKrm(double freqKrm)
{
    this->freqKrm = freqKrm;
    updateScene_1(krmScene);
    updateScene_2(kursMpKrmScene);
}

void MainWindow::setFreqGrm(double freqGrm)
{
    this->freqGrm = freqGrm;
    updateScene_1(grmScene);
    updateScene_2(kursMpGrmScene);
}

void MainWindow::setPitch(int pitch)
{
    this->pitch = pitch;
    updateScene_2(kursMpGrmScene);
}

void MainWindow::setBank(int bank)
{
    this->bank = bank;
    updateScene_2(kursMpKrmScene);
}
// end public slots
