//
// (c) Georg Umlauf, 2021
//
#include "mainwindow.h"

#include <QFileDialog>
#include <QKeyEvent>

#include <iostream>
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
	ui->glwidget->setFocusPolicy(Qt::StrongFocus);
    ui->glwidget->setFocus();

    QObject::connect(ui->pushButton,       &QPushButton ::clicked,      ui->glwidget, &GLWidget  ::openFileDialog);
    QObject::connect(ui->radioButton_1,    &QRadioButton::clicked,      ui->glwidget, &GLWidget  ::radioButtonClicked);
    QObject::connect(ui->radioButton_2,    &QRadioButton::clicked,      ui->glwidget, &GLWidget  ::radioButtonClicked);
    QObject::connect(ui->horizontalSlider, &QSlider     ::valueChanged, this,         &MainWindow::updatePointSize);

    updatePointSize(3);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::updatePointSize(int value)
{
    std::cout << "new pointsize: " << value << std::endl;
    ui->glwidget->setPointSize(value);
}
