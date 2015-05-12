#include "ol_flatbutton.h"

#include <QEvent>
#include <QMessageBox>

int OL_FlatButton::button_number = 0;

OL_FlatButton::OL_FlatButton(QIcon & icon, QWidget *parent) : QPushButton(icon, "", parent)
{
    this->setFlat(true);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setFixedSize(this->height(),this->height());
    button_number += 1;
    QString name;
    name = name.sprintf("%s_%04d", "flatbutton", button_number);
    this->setObjectName(name);
    this->setStyleSheet("#" + name + ":hover { background: #d5e1f2;border: none; }");
}

OL_FlatButton::~OL_FlatButton()
{

}

void OL_FlatButton::addStyleSheet(const QString &s, bool specific)
{
    QString c = this->styleSheet();
    if (specific) {
        c = c.append("\n#" + this->objectName() + s);
    } else {
        c = c.append("\n" + s);
    }
    QMessageBox * msgBox  = new QMessageBox();
    msgBox->setWindowTitle("addStyleSheet");
    msgBox->setText(c);
    msgBox->show();
    //delete msgBox;
    this->setStyleSheet(c);
}

bool OL_FlatButton::event(QEvent *e)
{
    if(e->type() == QEvent::HoverEnter) {
        setFlat(false);
    }

    if(e->type() == QEvent::HoverLeave) {
        setFlat(true);
    }

    return QPushButton::event(e);
}
