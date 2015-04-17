#ifndef OL_FLATBUTTON_H
#define OL_FLATBUTTON_H

#include <QPushButton>



class OL_FlatButton : public QPushButton
{
public:
    OL_FlatButton(QIcon &icon, QWidget *parent);
    ~OL_FlatButton();
protected:
    bool event(QEvent *e);
};

#endif // OL_FLATBUTTON_H
