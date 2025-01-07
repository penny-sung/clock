#include "TimerWidget.h"

TimerWidget::TimerWidget(QWidget *parent)
    : QWidget(parent), isPaused(false) {
    // 設置布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    timeLabel = new QLabel("00:00:00.000", this);
    QPushButton *startButton = new QPushButton("Start Timer", this);
    pauseBtn = new QPushButton("Pause Timer", this);
    QPushButton *stopButton = new QPushButton("Stop Timer", this);
    clearLogBtn = new QPushButton("Clear Log", this); // 創建清空日誌按鈕
    logViewer = new QTextEdit(this);

    logViewer->setReadOnly(true); 

    layout->addWidget(timeLabel);
    layout->addWidget(startButton);
    layout->addWidget(pauseBtn);
    layout->addWidget(stopButton);
    layout->addWidget(clearLogBtn); // 添加清空日誌按鈕到布局
    layout->addWidget(logViewer);
    setLayout(layout);

    // 初始化 QTimer
    timer = new QTimer(this);
    timer->setInterval(10); // 每 10 毫秒觸發一次

    // 初始化時間
    elapsedTime = QTime(0, 0);

    // 信號與槽連接
    connect(timer, &QTimer::timeout, this, &TimerWidget::updateDisplay);
    connect(startButton, &QPushButton::clicked, this, &TimerWidget::startTimer);
    connect(pauseBtn, &QPushButton::clicked, this, &TimerWidget::pauseTimer);
    connect(stopButton, &QPushButton::clicked, this, &TimerWidget::stopTimer);
    connect(clearLogBtn, &QPushButton::clicked, this, &TimerWidget::clearLog); // 連接清空日誌按钮
}

void TimerWidget::clearLog() {
    logViewer->clear(); // 清空日誌内容
    addLog("Log cleared at: " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));
}

void TimerWidget::startTimer() {
    if (!isPaused) {
        elapsedTime = QTime(0, 0); // 重置時間
        startTime = QDateTime::currentDateTime();
        addLog("Timer started at: " + startTime.toString("yyyy-MM-dd hh:mm:ss.zzz"));
    }
    timer->start();
    isPaused = false;
}

void TimerWidget::pauseTimer() {
    if (timer->isActive()) {
        timer->stop();
        isPaused = true;
        pauseBtn->setText("Resume Timer");
        addLog("Timer paused at: " + QDateTime::currentDateTime().toString("hh:mm:ss.zzz"));
    } else {
        timer->start();
        isPaused = false;
        pauseBtn->setText("Pause Timer");
        addLog("Timer resumed at: " + QDateTime::currentDateTime().toString("hh:mm:ss.zzz"));
    }
}

void TimerWidget::stopTimer() {
    if (timer->isActive() || isPaused) {
        timer->stop();
        stopTime = QDateTime::currentDateTime();
        addLog("Timer stopped at: " + stopTime.toString("yyyy-MM-dd hh:mm:ss.zzz"));
        addLog("Elapsed time: " + elapsedTime.toString("hh:mm:ss.zzz"));
        isPaused = false;
        pauseBtn->setText("Pause Timer");
    }
}

void TimerWidget::updateDisplay() {
    elapsedTime = elapsedTime.addMSecs(10); // 每次增加 10 毫秒
    timeLabel->setText(elapsedTime.toString("hh:mm:ss.zzz")); // 更新顯示
}

void TimerWidget::addLog(const QString &message) {
    logViewer->append(message);
}
