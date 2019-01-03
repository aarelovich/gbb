#ifndef GBBMAIN_H
#define GBBMAIN_H

#include <QMainWindow>

namespace Ui {
class GBBMain;
}

class GBBMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit GBBMain(QWidget *parent = 0);
    ~GBBMain();

private:
    Ui::GBBMain *ui;
};

#endif // GBBMAIN_H
