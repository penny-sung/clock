#ifndef ALARMWIDGET_H
#define ALARMWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QTimeEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QJsonArray>
#include <QJsonObject>

class AlarmWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlarmWidget(QWidget *parent = nullptr);
    ~AlarmWidget();

private slots:
    void addAlarm();
    void checkAlarms();
    void selectMusic();
    void deleteAlarm();
    void triggerAlarm(const QJsonObject &alarm);

private:
    void saveAlarms();
    void loadAlarms();
    void updateAlarmList();

    QTimeEdit *timeEdit;
    QCheckBox *repeatCheckbox;
    QPushButton *musicButton;
    QPushButton *addButton;
    QPushButton *deleteButton; 
    QListWidget *alarmList;

    QTimer *timer;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

    QList<QJsonObject> alarms;
    QString selectedMusic;
};

#endif 
