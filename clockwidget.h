#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>

class ClockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClockWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif
