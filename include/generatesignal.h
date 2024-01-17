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

private slots:
    void drawSignal();
};
#endif // GENERATESIGNAL_H
