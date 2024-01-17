#include "generatesignal.h"
#include "ui_generatesignal.h"

generateSignal::generateSignal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::generateSignal)
{
    ui->setupUi(this);
}

generateSignal::~generateSignal()
{
    delete ui;
}
