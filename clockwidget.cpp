#include "clockwidget.h"

#include <QPainter>

ClockWidget::ClockWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(300, 300);

    // -------- ТАЙМЕР ---------

    m_timer = new QTimer(this);

    connect(m_timer, &QTimer::timeout, this,
            static_cast<void(QWidget::*)()>(&QWidget::update));

    m_timer->start(1000);
}

void ClockWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), Qt::white);

    // ---------КРУГ----------
    int w = width();
    int h = height();

    int size = 250;

    int x = (w - size) / 2;
    int y = (h - size) / 2;

    QRect circleRect(x, y, size, size);

    QPen pen(Qt::black, 3);
    painter.setPen(pen);

    painter.drawEllipse(circleRect);


    // === СТРЕЛКИ ===

    QTime time = QTime::currentTime();
    int hour = time.hour();
    int minute = time.minute();

    double hourAngle = (hour % 12 * 30) + (minute * 0.5);

    int centerX = x + size / 2;
    int centerY = y + size / 2;
    int hourHandLength = 80;
    //-----------------------------------------


    // === ЧАСОВАЯ СТРЕЛКА ===
    painter.save();  // Сохраняем состояние painter

    // Сдвигаем систему координат в центр часов
    painter.translate(centerX, centerY);

    // Поворачиваем на угол
    painter.rotate(hourAngle);

    // Рисуем стрелку (от центра ВВЕРХ, поэтому -length)
    QPen hourPen(Qt::red, 5);
    hourPen.setCapStyle(Qt::RoundCap);
    painter.setPen(hourPen);
    painter.drawLine(0, 0, 0, -hourHandLength);

    painter.restore();  // Восстанавливаем
    //-------------------------------------------------


    // === МИНУТНАЯ СТРЕЛКА ===

    // Получить минуты и секунды
    int second = time.second();

    // Вычислить угол (6° на минуту + 0.1° на секунду)
    double minuteAngle = (minute * 6) + (second * 0.1);

    // Длина стрелки (длиннее часовой)
    int minuteHandLength = 100;  // Например, size/1.5 или 100

    painter.save();
    painter.translate(centerX, centerY);
    painter.rotate(minuteAngle);

    // Настроить перо (синий, тоньше часовой)
    QPen minutePen(Qt::black, 5);  // Цвет, толщина
    minutePen.setCapStyle(Qt::RoundCap);
    painter.setPen(minutePen);

    // Нарисовать линию
    painter.drawLine(0, 0, 0, -minuteHandLength);

    painter.restore();
    //----------------------------------------------


    // === СЕКУНДНАЯ СТРЕЛКА ===

    // Вычислить угол (6° на каждую секунду)
    double secondAngle = second * 6;

    // Длина стрелки
    int secondHandLength = 100;

    painter.save();
    painter.translate(centerX, centerY);
    painter.rotate(secondAngle);

    // Настроить перо (зелёный, очень тонкий)
    QPen secondPen(Qt::blue, 2);
    secondPen.setCapStyle(Qt::RoundCap);
    painter.setPen(secondPen);

    // Нарисовать линию
    painter.drawLine(0, 0, 0, -secondHandLength);

    painter.restore();
}
