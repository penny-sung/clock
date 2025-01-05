#include <QApplication>
#include <QTabWidget>
#include <QVBoxLayout>
#include "alarmwidget.h"
#include "clocksystem.h"
#include "timerwidget.h"



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget mainWindow;
    mainWindow.setWindowTitle("Multi-Functional Clock");

    QTabWidget *tabWidget = new QTabWidget(&mainWindow);
    clocksystem *clockTab = new clocksystem();
    AlarmWidget *alarmTab = new AlarmWidget();
    TimerWidget *timerTab = new TimerWidget();

    tabWidget->addTab(clockTab, QStringLiteral("Clock"));
    tabWidget->addTab(alarmTab, QStringLiteral("Alarm"));
    tabWidget->addTab(timerTab, QStringLiteral("Timer"));

    QVBoxLayout *mainLayout = new QVBoxLayout(&mainWindow);
    mainLayout->addWidget(tabWidget);

    mainWindow.setLayout(mainLayout);
    mainWindow.resize(500, 400);
    mainWindow.show();

    return app.exec();
}
