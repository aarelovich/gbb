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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GBBMain
{
public:
    QAction *actionRealizar_Backup;
    QAction *actionRestaurar;
    QAction *actionPreferencias;
    QAction *actionAgregar_un_nuevo_producto;
    QAction *actionProductos_por_debajo_del_stock_minimo;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_4;
    QTableWidget *tableWidget;
    QPushButton *pushButton_3;
    QMenuBar *menuBar;
    QMenu *menuHerramientas;
    QMenu *menuBase_de_Datos;
    QMenu *menuConfiguraci_n;

    void setupUi(QMainWindow *GBBMain)
    {
        if (GBBMain->objectName().isEmpty())
            GBBMain->setObjectName(QStringLiteral("GBBMain"));
        GBBMain->resize(1094, 756);
        actionRealizar_Backup = new QAction(GBBMain);
        actionRealizar_Backup->setObjectName(QStringLiteral("actionRealizar_Backup"));
        actionRestaurar = new QAction(GBBMain);
        actionRestaurar->setObjectName(QStringLiteral("actionRestaurar"));
        actionPreferencias = new QAction(GBBMain);
        actionPreferencias->setObjectName(QStringLiteral("actionPreferencias"));
        actionAgregar_un_nuevo_producto = new QAction(GBBMain);
        actionAgregar_un_nuevo_producto->setObjectName(QStringLiteral("actionAgregar_un_nuevo_producto"));
        actionProductos_por_debajo_del_stock_minimo = new QAction(GBBMain);
        actionProductos_por_debajo_del_stock_minimo->setObjectName(QStringLiteral("actionProductos_por_debajo_del_stock_minimo"));
        centralWidget = new QWidget(GBBMain);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addWidget(groupBox);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_2->addWidget(pushButton_4);


        verticalLayout->addLayout(horizontalLayout_2);

        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        GBBMain->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GBBMain);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1094, 21));
        menuHerramientas = new QMenu(menuBar);
        menuHerramientas->setObjectName(QStringLiteral("menuHerramientas"));
        menuBase_de_Datos = new QMenu(menuBar);
        menuBase_de_Datos->setObjectName(QStringLiteral("menuBase_de_Datos"));
        menuConfiguraci_n = new QMenu(menuBar);
        menuConfiguraci_n->setObjectName(QStringLiteral("menuConfiguraci_n"));
        GBBMain->setMenuBar(menuBar);

        menuBar->addAction(menuHerramientas->menuAction());
        menuBar->addAction(menuBase_de_Datos->menuAction());
        menuBar->addAction(menuConfiguraci_n->menuAction());
        menuHerramientas->addAction(actionAgregar_un_nuevo_producto);
        menuHerramientas->addAction(actionProductos_por_debajo_del_stock_minimo);
        menuBase_de_Datos->addAction(actionRealizar_Backup);
        menuBase_de_Datos->addAction(actionRestaurar);
        menuConfiguraci_n->addAction(actionPreferencias);

        retranslateUi(GBBMain);

        QMetaObject::connectSlotsByName(GBBMain);
    } // setupUi

    void retranslateUi(QMainWindow *GBBMain)
    {
        GBBMain->setWindowTitle(QApplication::translate("GBBMain", "GBBMain", nullptr));
        actionRealizar_Backup->setText(QApplication::translate("GBBMain", "Realizar Backup", nullptr));
        actionRestaurar->setText(QApplication::translate("GBBMain", "Restaurar", nullptr));
        actionPreferencias->setText(QApplication::translate("GBBMain", "Preferencias", nullptr));
        actionAgregar_un_nuevo_producto->setText(QApplication::translate("GBBMain", "Agregar un nuevo producto ...", nullptr));
        actionProductos_por_debajo_del_stock_minimo->setText(QApplication::translate("GBBMain", "Productos por debajo del stock minimo ....", nullptr));
        groupBox->setTitle(QApplication::translate("GBBMain", "Busqueda", nullptr));
        pushButton->setText(QApplication::translate("GBBMain", "Filtrar", nullptr));
        label->setText(QApplication::translate("GBBMain", "Resultados de la b\303\272squeda", nullptr));
        pushButton_2->setText(QApplication::translate("GBBMain", "Venta", nullptr));
        pushButton_4->setText(QApplication::translate("GBBMain", "Historial de Ventas", nullptr));
        pushButton_3->setText(QApplication::translate("GBBMain", "Limpiar b\303\272squeda", nullptr));
        menuHerramientas->setTitle(QApplication::translate("GBBMain", "Herramientas", nullptr));
        menuBase_de_Datos->setTitle(QApplication::translate("GBBMain", "Base de Datos", nullptr));
        menuConfiguraci_n->setTitle(QApplication::translate("GBBMain", "Configuraci\303\263n", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GBBMain: public Ui_GBBMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GBBMAIN_H
