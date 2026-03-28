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

    m_timer->start(16);
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
    int hourHandLength = 70;
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
    QPolygonF hourHandShape;
    hourHandShape << QPointF(0, -hourHandLength)    // Вершина (острый кончик)
                  << QPointF(-5, 0)                  // Левый нижний угол
                  << QPointF(0, 10)                  // Низ (в центре, выступает)
                  << QPointF(5, 0);                  // Правый нижний угол

    // 2. Настраиваем цвет и обводку
    painter.setBrush(Qt::red);           // Заполнение красным
    painter.setPen(Qt::black);           // Без обводки (или Qt::black для контура)

    // 3. Рисуем многоугольник
    painter.drawPolygon(hourHandShape);

    painter.restore();  // Восстанавливаем
    //-------------------------------------------------


    // === МИНУТНАЯ СТРЕЛКА ===

    // Получить минуты и секунды
    int second = time.second();

    // Вычислить угол (6° на минуту + 0.1° на секунду)
    double minuteAngle = (minute * 6) + (second * 0.1);

    // Длина стрелки (длиннее часовой)
    int minuteHandLength = 90;

    painter.save();
    painter.translate(centerX, centerY);
    painter.rotate(minuteAngle);

    // Настроить перо (синий, тоньше часовой)
    QPen minutePen(Qt::black, 5);
    minutePen.setCapStyle(Qt::RoundCap);
    painter.setPen(minutePen);

    // Нарисовать линию
    painter.drawLine(0, 0, 0, -minuteHandLength);

    painter.restore();
    //----------------------------------------------


    // === СЕКУНДНАЯ СТРЕЛКА ===

    // Вычислить угол (6° на каждую секунду)
    int ms = time.msec();  // 0-999
    double secondAngle = (second * 6) + (ms * 0.006);

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


    // === ДЕЛЕНИЯ ===

    // === 60 ДЕЛЕНИЙ (каждую минуту) ===
    for (int i = 0; i < 60; i++) {

        painter.save();
        painter.translate(centerX, centerY);
        painter.rotate(i * 6);  // 360° / 60 = 6° на каждое деление

        if (i % 5 == 0) {
            // ЧАСОВОЕ деление (каждые 5 минут)
            QPen hourTickPen(Qt::black, 3);
            painter.setPen(hourTickPen);
            painter.drawLine(0, -125, 0, -110);  // Длинная: 15px
        } else {
            // МИНУТНОЕ деление
            QPen minuteTickPen(Qt::black, 1);
            painter.setPen(minuteTickPen);
            painter.drawLine(0, -125, 0, -120);  // Короткая: 5px
        }

        painter.restore();
    }


    // === Цифры ===

    // Настройки для текста
    painter.setPen(Qt::black);  // Цвет текста
    painter.setFont(QFont("Arial", 12, QFont::Bold));  // Шрифт, размер, жирный

    for (int i = 0; i < 12; i++)
    {
        painter.save();
        painter.translate(centerX, centerY);
        painter.rotate(i * 30);  // ← Тот же угол 30°

        // Какое число рисовать?
        int number = (i == 0) ? 12 : i; // тернарный оператор
        /* int number;
        if (i == 0) {
            number = 12;
        } else {
            number = i;
        } */
        QRectF textRect(-15, -110, 30, 20);  // Прямоугольник для текста
        painter.drawText(textRect, Qt::AlignCenter, QString::number(number));

        painter.restore();
    }

    painter.setBrush(Qt::black);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(QPointF(centerX, centerY), 6, 6);
}
