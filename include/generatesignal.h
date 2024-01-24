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
    QVector<double> calculateFFT(const QVector<double> &inputSignal);
    double Blackman(int n, int N);
    double Hanning(int n, int N);
    double Hamming(int n, int N);
    double Bartlet(int n, int N);

private slots:
    void drawSignal();
    void setVisiblePhase1();
    void setVisiblePhase2();
    void setVisiblePhase3();
};
#endif // GENERATESIGNAL_H
