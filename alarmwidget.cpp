#include "alarmwidget.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QListWidget>
#include <QTimeEdit>
#include <QJsonDocument>
#include <QFile>
#include <QTime>

AlarmWidget::AlarmWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("鬧鐘");
    resize(400, 300);

    // 初始化 UI
    QVBoxLayout *layout = new QVBoxLayout(this);

    timeEdit = new QTimeEdit(this);
    timeEdit->setDisplayFormat("HH:mm");
    layout->addWidget(new QLabel("選擇時間:"));
    layout->addWidget(timeEdit);

    repeatCheckbox = new QCheckBox("每日重複", this);
    layout->addWidget(repeatCheckbox);

    musicButton = new QPushButton("選擇音樂", this);
    connect(musicButton, &QPushButton::clicked, this, &AlarmWidget::selectMusic);
    layout->addWidget(musicButton);

    addButton = new QPushButton("新增鬧鐘", this);
    connect(addButton, &QPushButton::clicked, this, &AlarmWidget::addAlarm);
    layout->addWidget(addButton);

    deleteButton = new QPushButton("刪除選定鬧鐘", this); // 新增刪除按鈕
    connect(deleteButton, &QPushButton::clicked, this, &AlarmWidget::deleteAlarm);
    layout->addWidget(deleteButton);

    alarmList = new QListWidget(this);
    alarmList->setContextMenuPolicy(Qt::CustomContextMenu); // 設定右鍵菜單
    layout->addWidget(alarmList);

    // 初始化鬧鐘和定時器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &AlarmWidget::checkAlarms);
    timer->start(1000); // 每秒檢查一次

    // 初始化播放器和音頻輸出
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);

    // 加載本地儲存的鬧鐘
    loadAlarms();
}

AlarmWidget::~AlarmWidget() = default;

void AlarmWidget::addAlarm()
{
    QTime alarmTime = timeEdit->time();
    bool repeat = repeatCheckbox->isChecked();

    if (selectedMusic.isEmpty()) {
        QMessageBox::warning(this, "警告", "請選擇音樂！");
        return;
    }

    QJsonObject alarm;
    alarm["time"] = alarmTime.toString("HH:mm");
    alarm["repeat"] = repeat;
    alarm["music"] = selectedMusic;

    alarms.append(alarm);
    saveAlarms();
    updateAlarmList();
}

void AlarmWidget::checkAlarms()
{
    QString currentTime = QTime::currentTime().toString("HH:mm");
    QList<QJsonObject> alarmsToRemove;

    for (const QJsonObject &alarm : alarms) {
        if (alarm["time"].toString() == currentTime) {
            triggerAlarm(alarm);
            if (alarm.contains("snoozed")) {
                alarmsToRemove.append(alarm); // 將臨時鬧鐘標記為過期
            }
        }
    }

    // 移除所有過期的臨時鬧鐘
    for (const QJsonObject &alarm : alarmsToRemove) {
        alarms.removeOne(alarm);
    }
}

void AlarmWidget::triggerAlarm(const QJsonObject &alarm)
{
    player->setSource(QUrl::fromLocalFile(alarm["music"].toString())); // 設置音樂來源
    player->play(); // 開始播放音樂

    QMessageBox msg(this);
    msg.setWindowTitle("鬧鐘");
    msg.setText("時間到了！");
    QPushButton *snoozeButton = msg.addButton("延後10分鐘", QMessageBox::RejectRole);
    QPushButton *confirmButton = msg.addButton("確定", QMessageBox::AcceptRole);
    msg.exec();

    if (msg.clickedButton() == snoozeButton) {
        player->stop(); // 停止播放音樂
        QTime snoozeTime = QTime::currentTime().addSecs(10 * 60); // 計算延後的時間

        QJsonObject snoozeAlarm = alarm; // 從現有鬧鐘複製屬性
        snoozeAlarm["time"] = snoozeTime.toString("HH:mm"); // 更新時間
        snoozeAlarm["snoozed"] = true; // 標記為臨時鬧鐘

        alarms.append(snoozeAlarm); // 新增延後的鬧鐘
    }

    if (msg.clickedButton() == confirmButton) {
        player->stop(); // 停止播放音樂
    }

    if (!alarm["repeat"].toBool() && !alarm.contains("snoozed")) {
        alarms.removeOne(alarm); // 刪除非重複鬧鐘
    }
    saveAlarms();
    updateAlarmList();
}

void AlarmWidget::selectMusic()
{
    QString filePath = QFileDialog::getOpenFileName(this, "選擇音樂", "", "音樂檔案 (*.mp3 *.wav)");
    if (!filePath.isEmpty()) {
        selectedMusic = filePath;
    }
}

void AlarmWidget::deleteAlarm()
{
    QListWidgetItem *currentItem = alarmList->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "警告", "請選擇一個鬧鐘進行刪除！");
        return;
    }

    // 獲取選定的鬧鐘索引並刪除
    int row = alarmList->row(currentItem);
    alarmList->takeItem(row);
    alarms.removeAt(row);
    saveAlarms();
}

void AlarmWidget::saveAlarms()
{
    QJsonArray alarmArray;
    for (const QJsonObject &alarm : alarms) {
        if (!alarm.contains("snoozed")) { // 不保存臨時鬧鐘
            alarmArray.append(alarm);
        }
    }

    QFile file("alarms.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(alarmArray).toJson());
    }
}

void AlarmWidget::loadAlarms()
{
    QFile file("alarms.json");
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        for (const QJsonValue &value : doc.array()) {
            alarms.append(value.toObject());
        }
        updateAlarmList();
    }
}

void AlarmWidget::updateAlarmList()
{
    alarmList->clear();
    for (const QJsonObject &alarm : alarms) {
        QString repeat = alarm["repeat"].toBool() ? " (每日)" : "";
        QString label = alarm["time"].toString() + repeat + " - " + alarm["music"].toString();

        QListWidgetItem *item = new QListWidgetItem(label, alarmList);
        if (alarm.contains("snoozed") && alarm["snoozed"].toBool()) {
            item->setForeground(Qt::gray); // 臨時鬧鐘顯示為灰色
        }
        alarmList->addItem(item);
    }
}
