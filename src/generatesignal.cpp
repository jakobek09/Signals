#include "generatesignal.h"
#include "ui_generatesignal.h"

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
    ui->customPlot->xAxis->setRange(0,100);
    ui->customPlot->yAxis->setRange(0,100);

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->sig1F->setValidator(new QDoubleValidator());
    ui->sig1A->setValidator(new QDoubleValidator());
    ui->lineEdit_sig2F->setValidator(new QDoubleValidator());
    ui->lineEdit_sig2A->setValidator(new QDoubleValidator());
    ui->lineEdit_sig3F->setValidator(new QDoubleValidator());
    ui->lineEdit_sig3w->setValidator(new QDoubleValidator());
    ui->lineEdit_sig3A->setValidator(new QDoubleValidator());
    ui->lineEdit_sig2w->setValidator(new QDoubleValidator());
    ui->lineEdit_sig1w->setValidator(new QDoubleValidator());
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

    for(int i = 0; i<number;i+=1)
    {
        double y = 0.0;

        y += generate(ui->comboBox->currentIndex(),
                                  i,
                                  ui->lineEdit_sig1w->text().toDouble(),
                                  ui->sig1A->text().toDouble(),
                                  ui->sig1F->text().toDouble(),
                                  number);

        y += generate(ui->comboBox_2->currentIndex(),
                                  i,
                                  ui->lineEdit_sig2w->text().toDouble(),
                                  ui->lineEdit_sig2A->text().toDouble(),
                                  ui->lineEdit_sig2F->text().toDouble(),
                                  number);

        y += generate(ui->comboBox_3->currentIndex(),
                                  i,
                                  ui->lineEdit_sig3w->text().toDouble(),
                                  ui->lineEdit_sig3A->text().toDouble(),
                                  ui->lineEdit_sig3F->text().toDouble(),
                                  number);

        xData.append(i);
        yData.append(y);
    }
    ui->customPlot->graph(0)->setData(xData,yData);
    ui->customPlot->xAxis->setRange(0,100);
    ui->customPlot->yAxis->setRange(-1,1);
    ui->customPlot->replot();
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
    qDebug() << result;
    return result;
}



void generateSignal::setVisiblePhase1()
{
    if(ui->comboBox->currentIndex() == 1 || ui->comboBox->currentIndex() == 0)
    {
        ui->lineEdit_sig1w->setVisible(true);
        ui->label_sig1w->setVisible(true);
    }
    else
    {
        ui->lineEdit_sig1w->setVisible(false);
        ui->label_sig1w->setVisible(false);
    }
}

void generateSignal::setVisiblePhase2()
{
    if(ui->comboBox_2->currentIndex() == 1 || ui->comboBox_2->currentIndex() == 0)
    {
        ui->lineEdit_sig2w->setVisible(true);
        ui->label_sig1w->setVisible(true);
    }
    else
    {
        ui->lineEdit_sig2w->setVisible(false);
        ui->label_sig2w->setVisible(false);
    }
}

void generateSignal::setVisiblePhase3()
{
    if(ui->comboBox_3->currentIndex() == 1 || ui->comboBox_3->currentIndex() == 0)
    {
        ui->lineEdit_sig3w->setVisible(true);
        ui->label_sig3w->setVisible(true);
    }
    else
    {
        ui->lineEdit_sig3w->setVisible(false);
        ui->label_sig3w->setVisible(false);
    }
}

