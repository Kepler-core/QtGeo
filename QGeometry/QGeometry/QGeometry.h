#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QGeometry.h"

class QGeometry : public QMainWindow
{
    Q_OBJECT

public:
    QGeometry(QWidget *parent = nullptr);
    ~QGeometry();

private:
    Ui::QGeometryClass ui;
};
