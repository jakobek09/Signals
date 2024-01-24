#include "generatesignal.h"
#include "ui_generatesignal.h"
#include <fftw3.h>

generateSignal::generateSignal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::generateSignal)
{
    ui->setupUi(this);
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->xAxis->setLabel("X");
    ui->customPlot->yAxis->setLabel("Y");
    ui->customPlot->xAxis->setRange(0,10);
    ui->customPlot->yAxis->setRange(0,10);

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->lineEdit->setValidator(new QIntValidator());

    connect(ui->drawPlotButton, SIGNAL(released()),this,SLOT(drawSignal()));

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),this,SLOT(setVisiblePhase1()));
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(int)),this,SLOT(setVisiblePhase2()));
    connect(ui->comboBox_3, SIGNAL(currentIndexChanged(int)),this,SLOT(setVisiblePhase3()));
}

generateSignal::~generateSignal()
{
    delete ui;
}

void generateSignal::drawSignal()
{
    xData.clear();
    yData.clear();
    int number = ui->lineEdit->text().toInt();

    for(int i = 0; i<=number;i+=1)
    {
        double y = 0.0;

        y += generate(ui->comboBox->currentIndex(),
                                  i,
                                  ui->sig1w->value(),
                                  ui->sig1A->value(),
                                  ui->sig1F->value(),
                                  number);

        y += generate(ui->comboBox_2->currentIndex(),
                                  i,
                                  ui->sig2w->value(),
                                  ui->sig2A->value(),
                                  ui->sig2F->value(),
                                  number);

        y += generate(ui->comboBox_3->currentIndex(),
                                  i,
                                  ui->sig3w->value(),
                                  ui->sig3A->value(),
                                  ui->sig3F->value(),
                                  number);

        int type = ui->comboBox_4->currentIndex();
        if(type != 0)
        {
            switch(type)
            {
            case 1:
                y *= Blackman(i,number);
                break;
            case 2:
                y *= Hanning(i,number);
                break;
            case 3:
                y *= Hamming(i,number);
                break;
            case 4:
                y *= Bartlet(i,number);
                break;
            }
        }
        xData.append(i);
        yData.append(y);
    }

    if(!ui->checkBox_2->isChecked())
    {
        ui->customPlot->graph(0)->setData(xData,yData);
        //ui->customPlot->xAxis->setRange(0,10);
        //ui->customPlot->yAxis->setRange(0,10);
        ui->customPlot->xAxis->setLabel("X");
        ui->customPlot->yAxis->setLabel("Y");
    }
    else
    {
        ui->customPlot->xAxis->setRange(0,100);
        ui->customPlot->yAxis->setRange(0,1);
        QVector<double> spectrum = calculateFFT(yData);

        QVector<double> freqData(number);
        for(int i=0;i<number;i++)
        {
            freqData[i] = i;
        }

        ui->customPlot->graph(0)->setData(freqData, spectrum);

        ui->customPlot->xAxis->setLabel("częstotliwość");
        ui->customPlot->yAxis->setLabel("amplituda");
    }
    ui->customPlot->replot();
}

QVector<double> generateSignal::calculateFFT(const QVector<double> &inputSignal)
{
    int N = inputSignal.size();
    QVector<double> outputSignal(N);

    // Tworzenie planu FFT
    fftw_plan plan = fftw_plan_r2r_1d(N, const_cast<double *>(inputSignal.constData()),
                                      reinterpret_cast<double *>(outputSignal.data()), FFTW_R2HC, FFTW_ESTIMATE);

    // Wykonanie FFT
    fftw_execute(plan);

    // Normalizacja wyniku
    for (double &value : outputSignal)
    {
        value /= N;
    }

    // Przygotowanie widma (moduł wyniku)
    QVector<double> spectrum(N);
    for (int i = 0; i < N; ++i)
    {
        spectrum[i] = std::abs(outputSignal[i]);
    }

    // Zwalnianie zasobów FFTW
    fftw_destroy_plan(plan);

    return spectrum;
}

double generateSignal::generate(int type, int index, double phase, double ampli, double freq, int numOfPoints)
{
    double result = 0.0;
    double t = static_cast<double>(index)/static_cast<double>(numOfPoints-1);
    switch(type)
    {
    case 1:
        result = ampli * qSin((2.0*M_PI*freq*t)+phase);
        break;
    case 2:
        if(qSin(2.0*M_PI*freq*t)==0)
            result = 0;
        else if(qSin(2.0*M_PI*freq*t)>0)
            result = ampli * 1;
        else
            result = ampli * (-1);
        break;
    case 3:
        result = (2 * ampli / M_PI) * atan(tan(M_PI * t / (1/freq)));
        break;

    }
    return result;
}



void generateSignal::setVisiblePhase1()
{
    if(ui->comboBox->currentIndex() == 1 || ui->comboBox->currentIndex() == 0)
    {
        ui->sig1w->setVisible(true);
        ui->label_sig1w->setVisible(true);
    }
    else
    {
        ui->sig1w->setVisible(false);
        ui->label_sig1w->setVisible(false);
    }
}

void generateSignal::setVisiblePhase2()
{
    if(ui->comboBox_2->currentIndex() == 1 || ui->comboBox_2->currentIndex() == 0)
    {
        ui->sig2w->setVisible(true);
        ui->label_sig2w->setVisible(true);
    }
    else
    {
        ui->sig2w->setVisible(false);
        ui->label_sig2w->setVisible(false);
    }
}

void generateSignal::setVisiblePhase3()
{
    if(ui->comboBox_3->currentIndex() == 1 || ui->comboBox_3->currentIndex() == 0)
    {
        ui->sig3w->setVisible(true);
        ui->label_sig3w->setVisible(true);
    }
    else
    {
        ui->sig3w->setVisible(false);
        ui->label_sig3w->setVisible(false);
    }
}

double generateSignal::Bartlet(int n, int N)
{
    return 1 - abs((n - (N - 1) / 2) / ((N - 1) / 2));
}

double generateSignal::Hanning(int n, int N)
{
    return 0.5*(1-cos((2*M_PI*n)/N));
}

double generateSignal::Hamming(int n, int N)
{
    return 0.54 - 0.46 * cos(2 * M_PI * n / N);
}

double generateSignal::Blackman(int n, int N)
{
    return 0.42-0.5*cos(2*M_PI*n/(N-1))-0.08*cos(4*M_PI*n/(N-1));
}
