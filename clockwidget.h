#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTime>

class ClockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClockWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QTimer *m_timer;
};

#endif
