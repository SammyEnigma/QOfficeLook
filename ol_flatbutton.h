#ifndef OL_FLATBUTTON_H
#define OL_FLATBUTTON_H

#include <QPushButton>



class OL_FlatButton : public QPushButton
{
private:
    static int button_number;
public:
    void addStyleSheet(const QString & s, bool specific = true);
public:
    OL_FlatButton(QIcon &icon, QWidget *parent);
    ~OL_FlatButton();
protected:
    bool event(QEvent *e);
};

#endif // OL_FLATBUTTON_H
