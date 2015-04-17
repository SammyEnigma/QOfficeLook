#include "ol_flatbutton.h"

#include <QEvent>

OL_FlatButton::OL_FlatButton(QIcon & icon, QWidget *parent) : QPushButton(icon, "", parent)
{
    this->setFlat(true);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setFixedSize(this->height(),this->height());
}

OL_FlatButton::~OL_FlatButton()
{

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
