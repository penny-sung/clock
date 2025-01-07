#include "clockwidget.h"
#include <QTimer>
#include <QTime>
#include <QRandomGenerator>
#include <QFontMetrics>

ClockWidget::ClockWidget(QWidget *parent)
    : QWidget(parent), clockStyle(ANALOG_CLOCK) {  // Initialize clockStyle
    setFixedSize(400, 400);

    // update
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&ClockWidget::update));
    timer->start(1000);  // Update every second
}

//clock style
void ClockWidget::setClockStyle(ClockStyle style) {
    clockStyle = style;
    update();
}

void ClockWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    QTime time = QTime::currentTime();

    switch (clockStyle) {
    case ANALOG_CLOCK:
        drawAnalogClock(painter);
        break;
    case DIGITAL_12:
        drawDigitalClock(painter, time.toString("hh:mm:ss AP"));
        drawCpuMemoryUsage(painter);
        break;
    case DIGITAL_24:
        drawDigitalClock(painter, time.toString("HH:mm:ss"));
        drawCpuMemoryUsage(painter);
        break;
    case ANALOG_WITH_DIGITAL:
        drawAnalogClock(painter);
        drawDigitalClock(painter, time.toString("HH:mm:ss"));
        break;
    }
}

void ClockWidget::drawAnalogClock(QPainter &painter) {
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    int radius = qMin(width(), height()) / 2 - 10;

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(QPoint(0, 0), radius, radius);

    QTime time = QTime::currentTime();
    painter.setPen(Qt::black);

    // Hour
    painter.save();
    painter.rotate(30.0 * (time.hour() % 12) + time.minute() / 2.0);
    painter.drawRect(-5, -radius / 3, 10, radius / 3);
    painter.restore();

    // Minute
    painter.save();
    painter.rotate(6.0 * time.minute() + time.second() / 10.0);
    painter.drawRect(-3, -radius / 2, 6, radius / 2);
    painter.restore();

    // Second
    painter.setPen(Qt::red);
    painter.save();
    painter.rotate(6.0 * time.second());
    painter.drawLine(0, 0, 0, -radius + 10);
    painter.restore();
}

void ClockWidget::drawDigitalClock(QPainter &painter, const QString &timeString) {
    painter.setRenderHint(QPainter::TextAntialiasing);
    QFont font("Arial", 24, QFont::Bold);
    painter.setFont(font);
    painter.setPen(Qt::black);

    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(timeString);

    painter.drawText((width() - textWidth) / 2, height() / 2, timeString);
}


void ClockWidget::drawCpuMemoryUsage(QPainter &painter) {
    QString usage = getCpuMemoryUsage();

    QFont font("Arial", 14, QFont::Normal);
    painter.setFont(font);
    painter.setPen(Qt::blue);

    painter.drawText(10, height() - 20, usage);
}

QString ClockWidget::getCpuMemoryUsage() {
    int cpuUsage = QRandomGenerator::global()->bounded(1, 100);
    int memoryUsage = QRandomGenerator::global()->bounded(1, 100);

    return QString("CPU: %1% | Memory: %2%").arg(cpuUsage).arg(memoryUsage);
}
