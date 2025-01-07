#ifndef CLOCKSYSTEM_H
#define CLOCKSYSTEM_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QPushButton>
#include <QLabel>

class clocksystem : public QWidget
{
    Q_OBJECT
public:
    explicit clocksystem(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void updateClock();
    void showClock12CPU();
    void showClock24CPU();
    void showClock12Analog();
    void showAnalogCPU();

private:
    QTimer *timer;
    QTime currentTime;

    QPushButton *button12CPU;
    QPushButton *button24CPU;
    QPushButton *button12Analog;
    QPushButton *buttonAnalogCPU;

    QLabel *clockLabel;
    QLabel *cpuLabel;

    bool showAnalog;
    bool showCPUInfo;
    bool use24HourFormat;

    void displayCPUAndMemoryUsage(); 
};

#endif // CLOCKSYSTEM_H
