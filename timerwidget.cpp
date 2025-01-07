#include "TimerWidget.h"

TimerWidget::TimerWidget(QWidget *parent)
    : QWidget(parent), isPaused(false) {

    QVBoxLayout *layout = new QVBoxLayout(this);
    timeLabel = new QLabel("00:00:00.000", this);
    QPushButton *startButton = new QPushButton("Start Timer", this);
    pauseBtn = new QPushButton("Pause Timer", this);
    QPushButton *stopButton = new QPushButton("Stop Timer", this);
    clearLogBtn = new QPushButton("Clear Log", this); 
    logViewer = new QTextEdit(this);

    logViewer->setReadOnly(true); 

    layout->addWidget(timeLabel);
    layout->addWidget(startButton);
    layout->addWidget(pauseBtn);
    layout->addWidget(stopButton);
    layout->addWidget(clearLogBtn);
    layout->addWidget(logViewer);
    setLayout(layout);


    timer = new QTimer(this);
    timer->setInterval(10); 

    elapsedTime = QTime(0, 0);

    connect(timer, &QTimer::timeout, this, &TimerWidget::updateDisplay);
    connect(startButton, &QPushButton::clicked, this, &TimerWidget::startTimer);
    connect(pauseBtn, &QPushButton::clicked, this, &TimerWidget::pauseTimer);
    connect(stopButton, &QPushButton::clicked, this, &TimerWidget::stopTimer);
    connect(clearLogBtn, &QPushButton::clicked, this, &TimerWidget::clearLog); 
}

void TimerWidget::clearLog() {
    logViewer->clear(); 
    addLog("Log cleared at: " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));
}

void TimerWidget::startTimer() {
    if (!isPaused) {
        elapsedTime = QTime(0, 0);
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
    elapsedTime = elapsedTime.addMSecs(10);
    timeLabel->setText(elapsedTime.toString("hh:mm:ss.zzz")); 
}

void TimerWidget::addLog(const QString &message) {
    logViewer->append(message);
}
