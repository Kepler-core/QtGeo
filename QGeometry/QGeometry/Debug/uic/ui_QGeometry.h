/********************************************************************************
** Form generated from reading UI file 'QGeometry.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QGEOMETRY_H
#define UI_QGEOMETRY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QGeometryClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QGeometryClass)
    {
        if (QGeometryClass->objectName().isEmpty())
            QGeometryClass->setObjectName(QString::fromUtf8("QGeometryClass"));
        QGeometryClass->resize(600, 400);
        menuBar = new QMenuBar(QGeometryClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QGeometryClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QGeometryClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QGeometryClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QGeometryClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QGeometryClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QGeometryClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QGeometryClass->setStatusBar(statusBar);

        retranslateUi(QGeometryClass);

        QMetaObject::connectSlotsByName(QGeometryClass);
    } // setupUi

    void retranslateUi(QMainWindow *QGeometryClass)
    {
        QGeometryClass->setWindowTitle(QCoreApplication::translate("QGeometryClass", "QGeometry", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QGeometryClass: public Ui_QGeometryClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QGEOMETRY_H
