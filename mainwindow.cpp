#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "clockwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ClockWidget *clock = new ClockWidget(this);

    setCentralWidget(clock);
    setWindowTitle("Часы");
}

MainWindow::~MainWindow()
{
    delete ui;
}
