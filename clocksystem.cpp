#include "clocksystem.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QTime>
#include <windows.h>
#include <pdh.h>
#include <pdhmsg.h>

clocksystem::clocksystem(QWidget *parent) : QWidget(parent)
{
    setFixedSize(600, 500);


    showAnalog = false;
    showCPUInfo = false;
    use24HourFormat = false;

    //計時器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &clocksystem::updateClock);
    timer->start(1000);

    clockLabel = new QLabel(this);
    clockLabel->setAlignment(Qt::AlignCenter);
    clockLabel->setStyleSheet("font-size: 24px; color: blue;");

    cpuLabel = new QLabel(this);
    cpuLabel->setAlignment(Qt::AlignCenter);
    cpuLabel->setStyleSheet("font-size: 18px; color: green;");

    button12CPU = new QPushButton("電子時鐘12小時 + CPU", this);
    button24CPU = new QPushButton("電子時鐘24小時 + CPU", this);
    button12Analog = new QPushButton("電子時鐘12小時 + 指針時鐘", this);
    buttonAnalogCPU = new QPushButton("時鐘 + CPU", this);

    // 佈局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addWidget(button12CPU);
    buttonLayout->addWidget(button24CPU);
    buttonLayout->addWidget(button12Analog);
    buttonLayout->addWidget(buttonAnalogCPU);

    mainLayout->addWidget(clockLabel);
    mainLayout->addWidget(cpuLabel);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    connect(button12CPU, &QPushButton::clicked, this, &clocksystem::showClock12CPU);
    connect(button24CPU, &QPushButton::clicked, this, &clocksystem::showClock24CPU);
    connect(button12Analog, &QPushButton::clicked, this, &clocksystem::showClock12Analog);
    connect(buttonAnalogCPU, &QPushButton::clicked, this, &clocksystem::showAnalogCPU);
}

void clocksystem::updateClock()
{
    currentTime = QTime::currentTime();
    QString timeText;

    if (use24HourFormat)
        timeText = currentTime.toString("HH:mm:ss");
    else
        timeText = currentTime.toString("hh:mm:ss AP");

    clockLabel->setText(timeText);

    if (showCPUInfo) {
        displayCPUAndMemoryUsage();
        cpuLabel->show();
    } else {
        cpuLabel->clear();
    }

    update();
}

void clocksystem::displayCPUAndMemoryUsage()
{
    static PDH_HQUERY cpuQuery;
    static PDH_HCOUNTER cpuTotal;
    static bool initialized = false;

    if (!initialized) {
        PdhOpenQuery(nullptr, 0, &cpuQuery);
        PdhAddCounter(cpuQuery, TEXT("\\Processor(_Total)\\% Processor Time"), 0, &cpuTotal);
        PdhCollectQueryData(cpuQuery);
        initialized = true;
    }

    PDH_FMT_COUNTERVALUE counterValue;
    PdhCollectQueryData(cpuQuery);
    PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, nullptr, &counterValue);
    double cpuUsage = counterValue.doubleValue;

    // 使用 GlobalMemoryStatusEx 獲取記憶體資訊
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);
    GlobalMemoryStatusEx(&memoryStatus);
    qint64 totalMemory = memoryStatus.ullTotalPhys / (1024 * 1024); // 轉MB
    qint64 usedMemory = (memoryStatus.ullTotalPhys - memoryStatus.ullAvailPhys) / (1024 * 1024); // 轉MB
    cpuLabel->setText(QString("CPU: %1% | Memory: %2/%3 MB").arg(cpuUsage, 0, 'f', 2).arg(usedMemory).arg(totalMemory));

}

void clocksystem::showClock12CPU()
{
    use24HourFormat = false;
    showAnalog = false;
    showCPUInfo = true;
    updateClock();
}

void clocksystem::showClock24CPU()
{
    use24HourFormat = true;
    showAnalog = false;
    showCPUInfo = true;
    updateClock();
}

void clocksystem::showClock12Analog()
{
    use24HourFormat = false;
    showAnalog = true;
    showCPUInfo = false;
    updateClock();
}

void clocksystem::showAnalogCPU()
{
    use24HourFormat = false;
    showAnalog = true;
    showCPUInfo = true;
    updateClock();
}

void clocksystem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // 僅在需要顯示指針時鐘時執行
    if (!showAnalog) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int clockSize = qMin(width(), height()) * 0.5;

    painter.translate(width() / 2, height() / 2);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(-clockSize / 2, -clockSize / 2, clockSize, clockSize);

    QPen pen(Qt::black, 3);
    painter.setPen(pen);

    // 時針
    painter.save();
    painter.rotate(30.0 * (currentTime.hour() % 12) + currentTime.minute() / 2.0);
    painter.drawLine(0, 0, 0, -clockSize / 4);
    painter.restore();

    // 分針
    pen.setWidth(2);
    painter.setPen(pen);
    painter.save();
    painter.rotate(6.0 * currentTime.minute());
    painter.drawLine(0, 0, 0, -clockSize / 3);
    painter.restore();

    // 秒針
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.save();
    painter.rotate(6.0 * currentTime.second());
    painter.drawLine(0, 0, 0, -clockSize / 2.5);
    painter.restore();
}
