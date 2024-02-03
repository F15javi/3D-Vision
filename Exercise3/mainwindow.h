//
// (c) Georg Umlauf, 2021
//
#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected slots:
  void updatePointSize(int);

private:
    Ui::MainWindowClass* ui;
};
