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

    // 四個按鈕
    QPushButton *button12CPU;
    QPushButton *button24CPU;
    QPushButton *button12Analog;
    QPushButton *buttonAnalogCPU;

    // 標籤用於顯示電子時鐘與CPU記憶體功耗
    QLabel *clockLabel;
    QLabel *cpuLabel;

    // 狀態標誌
    bool showAnalog;
    bool showCPUInfo;
    bool use24HourFormat;

    void displayCPUAndMemoryUsage(); // 模擬 CPU 和記憶體功耗
};

#endif // CLOCKSYSTEM_H
