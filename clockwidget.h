#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QString>

// ClockWidget Class Declaration
class ClockWidget : public QWidget {
    Q_OBJECT

public:
    enum ClockStyle { ANALOG_CLOCK, DIGITAL_12, DIGITAL_24, ANALOG_WITH_DIGITAL };

    explicit ClockWidget(QWidget *parent = nullptr);
    void setClockStyle(ClockStyle style);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    ClockStyle clockStyle;  // Declare clockStyle field

    // Helper functions
    void drawAnalogClock(QPainter &painter);
    void drawDigitalClock(QPainter &painter, const QString &timeString);
    void drawCpuMemoryUsage(QPainter &painter);

    QString getCpuMemoryUsage();
};

#endif // CLOCKWIDGET_H
