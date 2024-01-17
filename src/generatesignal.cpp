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
}

generateSignal::~generateSignal()
{
    delete ui;
}

void generateSignal::drawSignal()
{
    qDebug("gitara");
}
