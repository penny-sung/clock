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
    void startTimer();   
    void pauseTimer();    
    void stopTimer();     
    void updateDisplay(); 
    void clearLog();

private:
    QTimer *timer;          
    QLabel *timeLabel;     
    QPushButton *pauseBtn;  
    QTime elapsedTime;      
    bool isPaused;         
    QTextEdit *logViewer;   
    QDateTime startTime;    
    QDateTime stopTime;    
    QPushButton *clearLogBtn;

    void addLog(const QString &message); 
};

#endif 
