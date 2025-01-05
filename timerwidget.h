#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTime>
#include <QDateTime>
#include <QTextEdit>

class TimerWidget : public QWidget {
    Q_OBJECT

public:
    explicit TimerWidget(QWidget *parent = nullptr);

private slots:
    void startTimer();    // 启动或继续定时器
    void pauseTimer();    // 暂停定时器
    void stopTimer();     // 停止定时器
    void updateDisplay(); // 更新时间显示
    void clearLog();

private:
    QTimer *timer;          // 定时器对象
    QLabel *timeLabel;      // 显示时间
    QPushButton *pauseBtn;  // 暂停按钮
    QTime elapsedTime;      // 累计时间
    bool isPaused;          // 暂停状态
    QTextEdit *logViewer;   // 日志显示
    QDateTime startTime;    // 开始时间
    QDateTime stopTime;     // 停止时间
    QPushButton *clearLogBtn;

    void addLog(const QString &message); // 添加日志
};

#endif // TIMERWIDGET_H
