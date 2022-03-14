#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainWindow.h"

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::mainWindowClass ui;
};
