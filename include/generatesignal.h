#ifndef GENERATESIGNAL_H
#define GENERATESIGNAL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class generateSignal;
}
QT_END_NAMESPACE

class generateSignal : public QMainWindow
{
    Q_OBJECT

public:
    generateSignal(QWidget *parent = nullptr);
    ~generateSignal();

private:
    Ui::generateSignal *ui;
    QVector<double> xData, yData;
    double generate(int type, int index, double phase, double ampli, double freq, int numOfPoints);

private slots:
    void drawSignal();
    void setVisiblePhase1();
    void setVisiblePhase2();
    void setVisiblePhase3();
};
#endif // GENERATESIGNAL_H
