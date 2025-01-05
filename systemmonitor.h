#ifndef SYSTEMMONITOR_H
#define SYSTEMMONITOR_H

#include <QWidget>
#include <QTimer>

class SystemMonitor : public QWidget {
    Q_OBJECT

public:
    explicit SystemMonitor(QWidget *parent = nullptr);

private:
    QTimer *updateTimer;
    void updateStatus();
};

#endif // SYSTEMMONITOR_H
