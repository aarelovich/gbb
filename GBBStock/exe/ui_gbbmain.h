/********************************************************************************
** Form generated from reading UI file 'gbbmain.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GBBMAIN_H
#define UI_GBBMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GBBMain
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GBBMain)
    {
        if (GBBMain->objectName().isEmpty())
            GBBMain->setObjectName(QStringLiteral("GBBMain"));
        GBBMain->resize(400, 300);
        menuBar = new QMenuBar(GBBMain);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        GBBMain->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GBBMain);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GBBMain->addToolBar(mainToolBar);
        centralWidget = new QWidget(GBBMain);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        GBBMain->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GBBMain);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GBBMain->setStatusBar(statusBar);

        retranslateUi(GBBMain);

        QMetaObject::connectSlotsByName(GBBMain);
    } // setupUi

    void retranslateUi(QMainWindow *GBBMain)
    {
        GBBMain->setWindowTitle(QApplication::translate("GBBMain", "GBBMain", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GBBMain: public Ui_GBBMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GBBMAIN_H
