#include "systemmonitor.h"
#include <QProcess>

SystemMonitor::SystemMonitor(QWidget *parent) : QWidget(parent) {
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &SystemMonitor::updateStatus);
    updateTimer->start(1000); // 每秒更新系統狀態
}

void SystemMonitor::updateStatus() {
    QProcess process;
    process.start("date");
    process.waitForFinished();
}
