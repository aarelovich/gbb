#ifndef DROPABLELINEEDIT_H
#define DROPABLELINEEDIT_H

#include <QLineEdit>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>

class DropableLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    DropableLineEdit(QWidget *parent = 0);

signals:
    void wrongFileType();

protected:
    void dropEvent(QDropEvent *e);
    void dragEnterEvent(QDragEnterEvent *e);
};

#endif // DROPABLELINEEDIT_H
