#include "clockwidget.h"

#include <QPainter>

ClockWidget::ClockWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(300, 300);
}

void ClockWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.fillRect(rect(), Qt::white);
}
