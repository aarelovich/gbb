#include "dropablelineedit.h"

DropableLineEdit::DropableLineEdit(QWidget *parent): QLineEdit(parent)
{
    this->setAcceptDrops(true);
    this->setReadOnly(true);
}

void DropableLineEdit::dragEnterEvent(QDragEnterEvent *e){
    e->acceptProposedAction();
}

void DropableLineEdit::dropEvent(QDropEvent *e){
    QString filename = e->mimeData()->text().remove("file:///");

    // Making sure it is a PDF;
    if (!filename.endsWith(".pdf")){
        emit(wrongFileType());
        this->setText("");
    }
    else this->setText(filename);
}
