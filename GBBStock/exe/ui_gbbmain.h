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
#include <QtWidgets/QFrame>
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
#include <QtWidgets/QTextEdit>
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
    QAction *actionImportar_planilla_CSV;
    QAction *actionAplicar_formulas_a_costos_p_blico_y_mayorista;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLineEdit *leSearch;
    QPushButton *pbSearch;
    QPushButton *pbAdvSearch;
    QHBoxLayout *horizontalLayout_4;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labTitulo;
    QSpacerItem *horizontalSpacer;
    QLabel *labResultados;
    QTableWidget *twSearchResults;
    QFrame *frame;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QPushButton *pbVenta;
    QPushButton *pbHistVentas;
    QPushButton *pbModFormulaCostos;
    QPushButton *pbMassChange;
    QLabel *label_3;
    QTextEdit *pteExtendedInfo;
    QPushButton *pbCleanSearch;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labItems;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QLabel *labCosto;
    QLabel *labCostoPublico;
    QLabel *labCostoMayorista;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *labStockFrente;
    QLabel *labStockDepo;
    QLabel *labStockSuma;
    QMenuBar *menuBar;
    QMenu *menuHerramientas;
    QMenu *menuBase_de_Datos;

    void setupUi(QMainWindow *GBBMain)
    {
        if (GBBMain->objectName().isEmpty())
            GBBMain->setObjectName(QStringLiteral("GBBMain"));
        GBBMain->resize(1123, 868);
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
        actionImportar_planilla_CSV = new QAction(GBBMain);
        actionImportar_planilla_CSV->setObjectName(QStringLiteral("actionImportar_planilla_CSV"));
        actionAplicar_formulas_a_costos_p_blico_y_mayorista = new QAction(GBBMain);
        actionAplicar_formulas_a_costos_p_blico_y_mayorista->setObjectName(QStringLiteral("actionAplicar_formulas_a_costos_p_blico_y_mayorista"));
        centralWidget = new QWidget(GBBMain);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_5 = new QVBoxLayout(centralWidget);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        leSearch = new QLineEdit(groupBox);
        leSearch->setObjectName(QStringLiteral("leSearch"));

        horizontalLayout->addWidget(leSearch);

        pbSearch = new QPushButton(groupBox);
        pbSearch->setObjectName(QStringLiteral("pbSearch"));

        horizontalLayout->addWidget(pbSearch);

        pbAdvSearch = new QPushButton(groupBox);
        pbAdvSearch->setObjectName(QStringLiteral("pbAdvSearch"));

        horizontalLayout->addWidget(pbAdvSearch);


        verticalLayout_5->addWidget(groupBox);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(3);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labTitulo = new QLabel(frame_2);
        labTitulo->setObjectName(QStringLiteral("labTitulo"));
        QFont font;
        font.setPointSize(12);
        labTitulo->setFont(font);

        horizontalLayout_3->addWidget(labTitulo);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        labResultados = new QLabel(frame_2);
        labResultados->setObjectName(QStringLiteral("labResultados"));

        horizontalLayout_3->addWidget(labResultados);


        verticalLayout_2->addLayout(horizontalLayout_3);

        twSearchResults = new QTableWidget(frame_2);
        twSearchResults->setObjectName(QStringLiteral("twSearchResults"));

        verticalLayout_2->addWidget(twSearchResults);


        horizontalLayout_4->addWidget(frame_2);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);

        verticalLayout_4->addWidget(label_2);

        pbVenta = new QPushButton(frame);
        pbVenta->setObjectName(QStringLiteral("pbVenta"));

        verticalLayout_4->addWidget(pbVenta);

        pbHistVentas = new QPushButton(frame);
        pbHistVentas->setObjectName(QStringLiteral("pbHistVentas"));

        verticalLayout_4->addWidget(pbHistVentas);

        pbModFormulaCostos = new QPushButton(frame);
        pbModFormulaCostos->setObjectName(QStringLiteral("pbModFormulaCostos"));

        verticalLayout_4->addWidget(pbModFormulaCostos);

        pbMassChange = new QPushButton(frame);
        pbMassChange->setObjectName(QStringLiteral("pbMassChange"));

        verticalLayout_4->addWidget(pbMassChange);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);

        verticalLayout_4->addWidget(label_3);

        pteExtendedInfo = new QTextEdit(frame);
        pteExtendedInfo->setObjectName(QStringLiteral("pteExtendedInfo"));
        QFont font2;
        font2.setFamily(QStringLiteral("Courier New"));
        pteExtendedInfo->setFont(font2);

        verticalLayout_4->addWidget(pteExtendedInfo);


        horizontalLayout_4->addWidget(frame);


        verticalLayout_5->addLayout(horizontalLayout_4);

        pbCleanSearch = new QPushButton(centralWidget);
        pbCleanSearch->setObjectName(QStringLiteral("pbCleanSearch"));

        verticalLayout_5->addWidget(pbCleanSearch);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labItems = new QLabel(groupBox_2);
        labItems->setObjectName(QStringLiteral("labItems"));
        QFont font3;
        font3.setPointSize(14);
        font3.setBold(true);
        font3.setWeight(75);
        labItems->setFont(font3);

        horizontalLayout_2->addWidget(labItems);

        horizontalSpacer_2 = new QSpacerItem(291, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labCosto = new QLabel(groupBox_2);
        labCosto->setObjectName(QStringLiteral("labCosto"));
        labCosto->setFont(font1);

        verticalLayout->addWidget(labCosto);

        labCostoPublico = new QLabel(groupBox_2);
        labCostoPublico->setObjectName(QStringLiteral("labCostoPublico"));
        labCostoPublico->setFont(font1);

        verticalLayout->addWidget(labCostoPublico);

        labCostoMayorista = new QLabel(groupBox_2);
        labCostoMayorista->setObjectName(QStringLiteral("labCostoMayorista"));
        labCostoMayorista->setFont(font1);

        verticalLayout->addWidget(labCostoMayorista);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(291, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        labStockFrente = new QLabel(groupBox_2);
        labStockFrente->setObjectName(QStringLiteral("labStockFrente"));
        labStockFrente->setFont(font1);

        verticalLayout_3->addWidget(labStockFrente);

        labStockDepo = new QLabel(groupBox_2);
        labStockDepo->setObjectName(QStringLiteral("labStockDepo"));
        labStockDepo->setFont(font1);

        verticalLayout_3->addWidget(labStockDepo);

        labStockSuma = new QLabel(groupBox_2);
        labStockSuma->setObjectName(QStringLiteral("labStockSuma"));
        labStockSuma->setFont(font1);

        verticalLayout_3->addWidget(labStockSuma);


        horizontalLayout_2->addLayout(verticalLayout_3);


        verticalLayout_5->addWidget(groupBox_2);

        GBBMain->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GBBMain);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1123, 21));
        menuHerramientas = new QMenu(menuBar);
        menuHerramientas->setObjectName(QStringLiteral("menuHerramientas"));
        menuBase_de_Datos = new QMenu(menuBar);
        menuBase_de_Datos->setObjectName(QStringLiteral("menuBase_de_Datos"));
        GBBMain->setMenuBar(menuBar);

        menuBar->addAction(menuHerramientas->menuAction());
        menuBar->addAction(menuBase_de_Datos->menuAction());
        menuHerramientas->addAction(actionAgregar_un_nuevo_producto);
        menuHerramientas->addAction(actionProductos_por_debajo_del_stock_minimo);
        menuHerramientas->addAction(actionImportar_planilla_CSV);
        menuBase_de_Datos->addAction(actionRealizar_Backup);

        retranslateUi(GBBMain);

        QMetaObject::connectSlotsByName(GBBMain);
    } // setupUi

    void retranslateUi(QMainWindow *GBBMain)
    {
        GBBMain->setWindowTitle(QApplication::translate("GBBMain", "GBBMain", nullptr));
        actionRealizar_Backup->setText(QApplication::translate("GBBMain", "Manejo de Backups ...", nullptr));
        actionRestaurar->setText(QApplication::translate("GBBMain", "Restaurar ...", nullptr));
        actionPreferencias->setText(QApplication::translate("GBBMain", "Preferencias", nullptr));
        actionAgregar_un_nuevo_producto->setText(QApplication::translate("GBBMain", "Agregar un nuevo producto ...", nullptr));
        actionProductos_por_debajo_del_stock_minimo->setText(QApplication::translate("GBBMain", "Productos por debajo del stock minimo ....", nullptr));
        actionImportar_planilla_CSV->setText(QApplication::translate("GBBMain", "Importar planilla CSV ...", nullptr));
        actionAplicar_formulas_a_costos_p_blico_y_mayorista->setText(QApplication::translate("GBBMain", "Aplicar formulas de costo ...", nullptr));
        groupBox->setTitle(QApplication::translate("GBBMain", "Busqueda", nullptr));
        pbSearch->setText(QApplication::translate("GBBMain", "Buscar", nullptr));
        pbAdvSearch->setText(QApplication::translate("GBBMain", "Avanzado ...", nullptr));
        labTitulo->setText(QApplication::translate("GBBMain", "Resultados de la b\303\272squeda", nullptr));
        labResultados->setText(QString());
        label_2->setText(QApplication::translate("GBBMain", "Operar sobre los resultados", nullptr));
        pbVenta->setText(QApplication::translate("GBBMain", "Venta", nullptr));
        pbHistVentas->setText(QApplication::translate("GBBMain", "Historial de Ventas", nullptr));
        pbModFormulaCostos->setText(QApplication::translate("GBBMain", "Modificacion por f\303\263rmula de costos", nullptr));
        pbMassChange->setText(QApplication::translate("GBBMain", "Cambiar el campo en toda la selecci\303\263n", nullptr));
        label_3->setText(QApplication::translate("GBBMain", "Informaci\303\263n de Producto", nullptr));
        pteExtendedInfo->setHtml(QApplication::translate("GBBMain", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Courier New'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>", nullptr));
        pbCleanSearch->setText(QApplication::translate("GBBMain", "Limpiar b\303\272squeda", nullptr));
        groupBox_2->setTitle(QString());
        labItems->setText(QApplication::translate("GBBMain", "Cantidad de Productos", nullptr));
        labCosto->setText(QApplication::translate("GBBMain", "Costo Total", nullptr));
        labCostoPublico->setText(QApplication::translate("GBBMain", "Costo P\303\272blico", nullptr));
        labCostoMayorista->setText(QApplication::translate("GBBMain", "Costo Mayorista", nullptr));
        labStockFrente->setText(QApplication::translate("GBBMain", "Stock Frente", nullptr));
        labStockDepo->setText(QApplication::translate("GBBMain", "Stock Dep\303\263sito", nullptr));
        labStockSuma->setText(QApplication::translate("GBBMain", "Stock Total", nullptr));
        menuHerramientas->setTitle(QApplication::translate("GBBMain", "Herramientas", nullptr));
        menuBase_de_Datos->setTitle(QApplication::translate("GBBMain", "Base de Datos", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GBBMain: public Ui_GBBMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GBBMAIN_H
