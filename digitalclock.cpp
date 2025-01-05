#include "digitalclock.h"
#include <QTime>
#include <QString>

// DigitalClock 構造函數
DigitalClock::DigitalClock(QWidget *parent)
    : QLCDNumber(parent) {
    // 設定 LCD 樣式為 Filled
    setSegmentStyle(Filled);

    // 初始化定時器
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
    timer->start(1000); // 每秒觸發

    // 顯示當前時間
    showTime();

    // 設置窗口標題與大小
    setWindowTitle(tr("Digital Clock"));
    resize(150, 60);
}

// 顯示時間的槽函數
void DigitalClock::showTime() {
    // 獲取當前時間並格式化為 HH:mm:ss
    QString timeString = QTime::currentTime().toString("HH:mm:ss");
    display(timeString); // 更新 LCD 顯示
}
