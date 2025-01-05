#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H

#include <QLCDNumber>
#include <QTimer>

// DigitalClock 類別繼承自 QLCDNumber
class DigitalClock : public QLCDNumber {
    Q_OBJECT

public:
    explicit DigitalClock(QWidget *parent = nullptr);

private slots:
    void showTime(); // 用於更新時間
};

#endif // DIGITALCLOCK_H
